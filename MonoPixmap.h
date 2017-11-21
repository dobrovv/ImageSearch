#ifndef MONOPIXMAP_H
#define MONOPIXMAP_H

#include <cstdint>
#include <string>
#include <vector>

#include <iostream>


using Byte = std::uint8_t;
using UInt = std::uint32_t;

using std::string;
using std::vector;

class MonoPixmap
{
    UInt width;
    UInt height;
    Byte * data;

public:
    MonoPixmap(UInt width = 256, UInt height = 256, Byte * data = nullptr);

    MonoPixmap(MonoPixmap && other);
    MonoPixmap(const MonoPixmap & other);
    MonoPixmap & operator = (const MonoPixmap &);
    ~MonoPixmap();

    inline UInt h() const { return height; }
    inline UInt w() const { return width; }
    inline const Byte * data_ptr() const { return data; }

    inline void setPixel(UInt x, UInt y, UInt pixval) {
        data[x+y*width] = pixval;
    }

    inline uint8_t pixel(UInt x, UInt y) const {
        return data[x+y*width];
    }

    /// Returns a new MonoPixmap containing a subregion of image's pixels
    /// No boundary checks
    MonoPixmap region (UInt x, UInt y, UInt rwidth, UInt rheight);

    string toString() const;
};

#endif // MONOPIXMAP_H
