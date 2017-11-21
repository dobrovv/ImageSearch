#include "ImageDB.h"
#include <algorithm>    // std::sort
#include <vector>       // std::vector

ImageDB::ImageDB()
{

}

Hashcode ImageDB::hash(const MonoPixmap & img)
{
    UInt block_width = img.w()  / sqrt(BLOCK_CNT);
    UInt block_height = img.h() / sqrt(BLOCK_CNT);

    vector<double> block_mean_values;
    block_mean_values.reserve(BLOCK_CNT);

    for ( UInt y = 0; y < img.h(); y += block_height ) {
        for ( UInt x = 0; x < img.w(); x += block_width ) {
            double block_mean = getBlockMeanPixel(img, x, y, block_width, block_height);
            block_mean_values.push_back(block_mean);
        }
    }

    Hashcode hashcode;
    auto tmp = block_mean_values;
    std::sort(tmp.begin(), tmp.end());
    UInt blocks_median = tmp[ (tmp.size()/2) ];

    for ( UInt i = 0; i < block_mean_values.size(); i++ )
        hashcode[i] = block_mean_values[i] < blocks_median ? 0 : 1;

    return hashcode;
}

double ImageDB::getBlockMeanPixel(const MonoPixmap &img, UInt x_start, UInt y_start, UInt block_width, UInt block_height)
{
    UInt sum = 0;
    UInt x_end = x_start + block_width;
    UInt y_end = y_start + block_height;

    for (UInt y = y_start; y < y_end; y++ )
        for ( UInt x = x_start; x < x_end; x++ )
            sum += img.pixel(x,y);

    return (1.0 * sum) / (block_width * block_height);
}
