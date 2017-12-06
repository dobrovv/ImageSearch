#include "MainWindow.h"
#include "Preprocessing/ImageConverter.h"

#include <ctime> // for timing

#include <QGridLayout>
#include <QPushButton>
#include <QFileDialog>

MainWindow::MainWindow( ImageDB* db, QWidget *parent)
    : QWidget(parent)
{

    this->db = db;
    queryImg = QImage();

    QGridLayout * grid = new QGridLayout();
    imageView = new ImageView(QImage(), "", true);
    lblImageFilePath = new QLabel("Filepath: ");
    resultView = new ImageScrollView();

    btnOpenImage = new QPushButton("Open Image");
    btnQueryDB   = new QPushButton("Find");
    spbTolerance = new QSpinBox();
    spbTolerance->setRange(0,100);
    spbTolerance->setValue(25);

    lblResultTxt = new QLabel("Result:");

    grid->addWidget(btnOpenImage, 0, 0);
    grid->addWidget(lblImageFilePath, 0, 1, 1, 4);
    grid->addWidget(new QLabel("Preview:"), 1, 0);
    grid->addWidget(imageView, 2, 0, 1, 5, Qt::AlignLeft);

    grid->addWidget(btnQueryDB, 3, 0, 1, 1);
    grid->addWidget(new QLabel("Tolerance (in %)"), 3, 1);
    grid->addWidget(spbTolerance, 3, 2);
    grid->addWidget(lblResultTxt, 4, 0);
    grid->addWidget(resultView, 5, 0, 3, 5);

    grid->setSpacing(5);
    grid->setColumnStretch(4, 100);
    grid->setRowStretch(5, 100);
    setLayout(grid);


    connect(btnOpenImage, SIGNAL(clicked(bool)), SLOT(btnOpenImageClicked()));
    connect(btnQueryDB, SIGNAL(clicked(bool)), SLOT(btnQueryDBClicked()));
}

void MainWindow::btnOpenImageClicked()
{
    QString filePath = QFileDialog::getOpenFileName(this, "Open Image", "images", "Image Files (*.png *.jpg *.bmp)");
    QImage img(filePath);
    if (!img.isNull()) {
        queryImg = img;
        MonoPixmap mp = ImgConv::toMonoPixmap(queryImg);
        Hashcode hashcode = ImageDB::hash(mp);
        QString desc = "Norm   " + QString::number(ImageDB::length(hashcode))
            + "\nBitstring   " + QString::fromStdString(hashcode.to_string());
            + "\nFilepath   " + filePath;

        imageView->setImage(img, desc);
        lblImageFilePath->setText("Filepath: " + filePath);
    } else {
        queryImg = QImage();
        lblImageFilePath->setText("Filepath: ");
    }
}

void MainWindow::btnQueryDBClicked()
{
    resultView->clearImages();

    if (queryImg.isNull())
        return;

    MonoPixmap mp = ImgConv::toMonoPixmap(queryImg);
    Hashcode hashcode = ImageDB::hash(mp);

    double tolerance = 1.0 * spbTolerance->value() / 100.0;

    std::clock_t c_start = std::clock();

    vector<ImageInfo> result = db->query(mp, tolerance);

    std::clock_t c_end = std::clock();

    double elapsedTimeMs = 1000.0 * (c_end-c_start) / CLOCKS_PER_SEC;

    QString resultTxt("Result: ");
    resultTxt += "( in " + QString::number(elapsedTimeMs, 'g') + " ms )";
    lblResultTxt->setText(resultTxt);

    for (auto info : result) {
        QString filepath = QString::fromStdString(info.filepath);
        int distance = ImageDB::hamming_distance(hashcode, info.hashcode);
        double difference = 1.0 * distance / BLOCK_CNT * 100;
        string desc = + "Norm   " + QString::number(ImageDB::length(info.hashcode)).toStdString()
                + "\t\tDistance  " +  QString::number(difference).toStdString() + "%"
                + "\nBitstring   " + info.hashcode.to_string()
                + "\nFilepath    " + info.filepath;

        resultView->addImage(QImage(filepath), QString::fromStdString(desc));
    }
}
