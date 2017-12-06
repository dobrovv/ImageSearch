// Image preprocessing is defined here
// QImage is an arbitary image (.jpg, .png, .bmp)
//  the class is defined by the Qt Library
// MonoPixmap is a grayscaled normalized image used
//  for hashing calculations and queries

#ifndef IMAGECONVERTER_H
#define IMAGECONVERTER_H

#include "MonoPixmap.h"
#include <QImage>

namespace ImgConv{

QImage toQImage(const MonoPixmap & mp);

QImage toQImage(string filepath);

MonoPixmap toMonoPixmap(const QImage & qimg, UInt width = 256, UInt height = 256);

MonoPixmap toMonoPixmap(string filepath, UInt width = 256, UInt height = 256);

}

#endif // IMAGECONVERTER_H
