#include "ImageView.h"
#include <QVBoxLayout>

ImageView::ImageView(QImage image = QImage(), QString desc = "", QWidget *parent)
    : QWidget(parent)
{
    lblImg = new QLabel();
    lblDesc = new QLabel(desc);
    lblImg->setAlignment(Qt.AlignLeft | Qt.AlignTop);
    lblDesc->setAlignment(Qt.AlignTop);

    auto hBox = QVBoxLayout();
    hBox.addWidget(lblImg);
    hBox.addWidget(lblDesc);

    setImage(image, desc);

    setLayout(hBox);
}

void ImageView::setImage(QImage image, QString desc)
{
    image = image.scaled(200, 200, Qt.KeepAspectRatio);
    lblImg.setPixmap(QPixmap.fromImage(image));
    lblDesc.setText(desc);
}

