#include "ImageView.h"
#include <QVBoxLayout>
#include <QHBoxLayout>

ImageView::ImageView(QImage image, QString desc, bool descInLine, QWidget *parent)
    : QWidget(parent)
{
    lblImg = new QLabel();
    lblDesc = new QLabel(desc);
    lblImg->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    lblDesc->setAlignment(Qt::AlignTop);

    QBoxLayout * hBox;

    if (!descInLine)
        hBox = new QVBoxLayout();
    else
        hBox = new QHBoxLayout();

    hBox->addWidget(lblImg);
    hBox->addWidget(lblDesc, Qt::AlignTop);
    hBox->setSpacing(5);

    setImage(image, desc);

    setLayout(hBox);
}

void ImageView::setImage(QImage image, QString desc)
{
    if (!image.isNull()) {
        image = image.scaled(200, 200, Qt::KeepAspectRatio);
        lblImg->setPixmap(QPixmap::fromImage(image));
    }
    lblDesc->setText(desc);
}


ImageGridView::ImageGridView(QWidget *parent)
    : QWidget(parent)
{
    imgCount = 0;
    grid = new QGridLayout;
    setLayout(grid);
}

void ImageGridView::addImage(QImage image, QString desc)
{
    int x = imgCount % 2;
    int y = imgCount / 2;
    imgCount += 1;
    ImageView * imgView = new ImageView(image, desc);
    grid->addWidget(imgView, y, x);
}

void ImageGridView::clearImages()
{
    qDeleteAll(children());
    grid = new QGridLayout;
    setLayout(grid);
    imgCount = 0;
}

ImageScrollView::ImageScrollView(QWidget *parent)
    : QScrollArea(parent)
{
    grid = new ImageGridView(this);
    setWidget(grid);
    setWidgetResizable(true);
}

void ImageScrollView::addImage(QImage image, QString desc)
{
    grid->addImage(image, desc);
}

void ImageScrollView::clearImages()
{
    grid->clearImages();
}
