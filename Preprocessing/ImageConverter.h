#ifndef IMAGECONVERTER_H
#define IMAGECONVERTER_H

#include "MonoPixmap.h"
#include <QImage>

QImage toQImage(const MonoPixmap & mp);

QImage toQImage(string filepath);

MonoPixmap toMonoPixmap(const QImage & qimg, UInt width = 256, UInt height = 256);

MonoPixmap toMonoPixmap(string filepath, UInt width = 256, UInt height = 256);

#endif // IMAGECONVERTER_H
