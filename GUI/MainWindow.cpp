#include "MainWindow.h"
#include "Preprocessing/ImageConverter.h"

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

    grid->addWidget(btnOpenImage, 0, 0);
    grid->addWidget(lblImageFilePath, 0, 1, 1, 4);
    grid->addWidget(new QLabel("Preview:"), 1, 0);
    grid->addWidget(imageView, 2, 0, 1, 5, Qt::AlignLeft);

    grid->addWidget(btnQueryDB, 3, 0, 1, 1);
    grid->addWidget(new QLabel("Tolerance (in %)"), 3, 1);
    grid->addWidget(spbTolerance, 3, 2);
    grid->addWidget(new QLabel("Result:"), 4, 0);
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
        QString desc = "Length  " + QString::number(hashcode.count())
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
    vector<ImageInfo> result = db->query(mp, tolerance);

    for (auto info : result) {
        QString filepath = QString::fromStdString(info.filepath);

        int wrong_bits = 0;
        for ( int i=0; i < BLOCK_CNT; i++ ) {
            wrong_bits += hashcode[i] ^ info.hashcode[i]; // xor the bits in the bitsring
        }

        string desc = "Distance  " +  QString::number(wrong_bits).toStdString()
                + "\nBitstring   " + info.hashcode.to_string()
                + "\nFilepath    " + info.filepath;

        resultView->addImage(QImage(filepath), QString::fromStdString(desc));
    }
}
