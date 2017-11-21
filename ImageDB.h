#ifndef IMAGEDB_H
#define IMAGEDB_H

#include <MonoPixmap.h>
#include <Preprocessing/ImageConverter.h>

#include <bitset>

constexpr int BLOCK_CNT = 64; // must be a perfect square

using Hashcode = std::bitset<BLOCK_CNT>;

class ImageDB
{ 

public:
    ImageDB();

    static Hashcode hash(const MonoPixmap & image);

private:
    static double getBlockMeanPixel(const MonoPixmap & image, UInt x, UInt y, UInt block_width, UInt block_height);
};

#endif // IMAGEDB_H
