#include "MonoPixmap.h"

MonoPixmap::MonoPixmap(UInt width, UInt height, Byte *rdata)
    : width(width), height(height)
{
    this->data = new Byte[width*height];

    if ( rdata != nullptr )
        memcpy(data, rdata, width*height);
}

MonoPixmap::MonoPixmap(const MonoPixmap & other) {

    this->data = new Byte[width*height];
    this->width = other.width;
    this->height = other.height;
    memcpy(this->data, other.data, width*height);

}


MonoPixmap::MonoPixmap(MonoPixmap && other) {

    this->width = other.width;
    this->height = other.height;
    this->data = other.data;

    other.width = other.height = 0;
    other.data = nullptr;

}

MonoPixmap &MonoPixmap::operator =(const MonoPixmap & other)
{
    if ( data )
        delete[] data;

    data = new Byte [other.width * other.height];
    width = other.width;
    height = other.height;
    memcpy(data, other.data, width*height);

    return *this;
}

MonoPixmap & MonoPixmap::operator = (MonoPixmap && other)
{
    if ( data )
        delete[] data;

    data = other.data;
    width = other.width;
    height = other.height;

    other.data = nullptr;

    //std::cout << "Moved" << std::flush;
    return *this;
}


MonoPixmap::~MonoPixmap() {
    delete[] data;
}

MonoPixmap MonoPixmap::region(UInt x, UInt y, UInt rwidth, UInt rheight) {

    MonoPixmap tmp(rwidth, rheight);
    Byte * rdata = tmp.data;

    for ( UInt row = 0; row < rheight; row++ )
        // copy a row of the source image pixels clipped to [x ... x+rwidth)
        memcpy(&rdata[row*rwidth], &data[x+(y+row)*width], rwidth);

    return tmp;
}

string MonoPixmap::toString() const {
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
