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
    Byte *  data;

public:
    MonoPixmap(UInt width = 256, UInt height = 256, Byte * data = nullptr)
        :width(width), height(height), data(data)
    {  std::cout << "Create" << &data << std::flush;}

    MonoPixmap(const MonoPixmap &other) { std::cout << "Copy Ctor" << std::flush;}
/*
    MonoPixmap(MonoPixmap && other) {
        this->width = other.width;
        this->height = other.height;
        this->data = other.data;

        other.width = other.height = 0;
        other.data = nullptr;

        std::cout << "Move" << std::flush;

    }*/

    ~MonoPixmap() {
        delete[] data;
    }

    inline UInt h() const { return height; }
    inline UInt w() const { return width; }
    //inline const Byte *data_ptr() const { return data; }

    void setPixel(UInt x, UInt y, UInt pixval) {
        data[x+y*width] = pixval;
    }

    inline uint8_t pixel(UInt x, UInt y) const {
        return data[x+y*width];
    }

    /// Returns a new MonoPixmap containing a subregion of image's pixels
    /// No boundary checks
    MonoPixmap region (UInt x, UInt y, UInt rwidth, UInt rheight) {
        Byte * rdata = new Byte[rwidth*rheight];


        for ( UInt row = 0; row < rheight; row++ )
            // copy a row of the source image clipped to [x ... rwidth]
            memcpy(&rdata[row*rwidth], &data[x+(y+row)*width], rwidth);

        return MonoPixmap(rwidth, rheight, rdata);
    }

    string toString() const {
        string str;
        for ( UInt y = 0; y < height; y++ ) {
            str += '[';
            for ( UInt x = 0; x < width; x++ ) {
                str += std::to_string(pixel(x,y));
                str += (x+1 == width ? "]" : ", ");
            }
            str += "\n";
        }
        return str;
    }
};

#endif // MONOPIXMAP_H
