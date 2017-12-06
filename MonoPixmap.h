// Class to store image's pixel data after preprocessin

#ifndef MONOPIXMAP_H
#define MONOPIXMAP_H

#include "Typedefs.h"

class MonoPixmap
{
    UInt width;
    UInt height;
    Byte * data;

public:
    MonoPixmap(UInt width = 256, UInt height = 256, Byte * data = nullptr);

    MonoPixmap(const MonoPixmap & other);
    MonoPixmap(MonoPixmap && other);
    MonoPixmap & operator = (const MonoPixmap &);
    MonoPixmap & operator = ( MonoPixmap &&);

    ~MonoPixmap();

    inline UInt h() const { return height; }
    inline UInt w() const { return width; }

    inline Byte pixel(UInt x, UInt y) const { return data[x+y*width]; }
    inline void setPixel(UInt x, UInt y, UInt pixval) { data[x+y*width] = pixval; }
    inline const Byte * data_ptr() const { return data; }

    // Returns a new MonoPixmap containing a subregion of image's pixels
    // No boundary checks
    MonoPixmap region (UInt x, UInt y, UInt rwidth, UInt rheight);

    string toString() const;
};

#endif // MONOPIXMAP_H
