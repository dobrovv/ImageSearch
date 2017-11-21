#include "ImageConverter.h"

QImage toQImage(const MonoPixmap &mp) {
    return QImage( mp.data_ptr(), mp.w(), mp.h(), QImage::Format_Grayscale8);
}

QImage toQImage(std::string filepath) {
    return QImage(QString::fromStdString(filepath));
}

MonoPixmap toMonoPixmap(const QImage &qimg, UInt width, UInt height) {

    if ( qimg.isNull() )
        return MonoPixmap(0,0);

    QImage qtmp = qimg.convertToFormat(QImage::Format_Grayscale8);
    qtmp = qtmp.scaled(width, height, Qt::IgnoreAspectRatio, Qt::FastTransformation);

    return MonoPixmap(width, height, qtmp.bits());
}

MonoPixmap toMonoPixmap(std::string filepath, UInt width, UInt height) {
    QImage qimg = toQImage(filepath);
    return toMonoPixmap(qimg, width, height);
}
