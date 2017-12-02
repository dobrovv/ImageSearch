#include "ImageDB.h"

#include "Preprocessing/ImageConverter.h"
#include "Preprocessing/FileSystem.h"

#include <algorithm>    // std::sort
#include <vector>       // std::vector

ImageDB::ImageDB() {}

void ImageDB::loadImagesFromDir(const std::string &dirpath)
{
    vector<string> files = FileSystem::getDirectoryFiles(dirpath);

    for (string & file : files) {
        MonoPixmap mp = ImgConv::toMonoPixmap(file, IMG_WIDTH, IMG_HEIGHT);
        Hashcode hashcode = hash(mp);

        cout << "Filepath:\n\t" << file << "\n\tHashcode: " << hashcode.count() << " " << hashcode.to_string() << endl;

        ImageInfo imginf;
        imginf.filepath = file;
        imginf.hashcode = hashcode;

        tree.insert(hashcode.count(), imginf);
    }

    cout << "BPlusTree: " << tree.toString() << endl;
}

vector<ImageInfo> ImageDB::query(const MonoPixmap &image, double tolerance)
{
    Hashcode hashcode = hash(image);

    vector<ImageInfo> result;

    int key = hashcode.count(); // number of ones in the hashcode

    double radius = 1.0 * BLOCK_CNT* tolerance / 2;

    int min_key = floor(1.0 * key - radius); // smallest key satisfing the tolerance
    int max_key = ceil(1.0 * key + radius); // largest key satisfing the tolerance

    cout << "Searching for images with hashcode in range (" << min_key << ", " << max_key << ")" << endl;

    // Find the leaf node in the tree containing the min_key
    BPlusNode * node = tree.search(min_key);

    // Iterate over the leaf nodes while their keys <= max_key
    while( node && node->keys.at(0) <= max_key ) {

        for (int i = 0; i < node->keys.size(); i++) {

            // Get the image info from the tree
            ImageInfo imgInfo = node->vals.at(i);
            cout << imgInfo.filepath << endl;

            // Apply the filter
            bool passed = filter(hashcode, imgInfo.hashcode, tolerance);

            if ( passed )
                result.push_back(imgInfo);
        }
        node = node->next;
    }

    return result;
}

bool ImageDB::filter(Hashcode hashcode, Hashcode trgt, double tolerance)
{
    // Number of bits in the bitstring that can be unequal
    int max_wrong_bits = 1.0 * BLOCK_CNT * tolerance;

    int wrong_bits = 0;
    for ( int i=0; i < BLOCK_CNT; i++ ) {
        wrong_bits += hashcode[i] ^ trgt[i]; // xor the bits in the bitsring
    }

    cout << hashcode.to_string() << endl;
    cout << trgt.to_string() << endl;
    cout << "Wrong " << wrong_bits << " Max: " << max_wrong_bits << endl;

    if ( wrong_bits > max_wrong_bits )
        return false;

    return true;
}

Hashcode ImageDB::hash(const MonoPixmap & img)
{
    Hashcode hashcode; // resulting bitstring

    UInt block_width = img.w()  / sqrt(BLOCK_CNT);
    UInt block_height = img.h() / sqrt(BLOCK_CNT);

    vector<double> block_mean_values;
    block_mean_values.reserve(BLOCK_CNT);

    // Go over each block of the image and find the mean pixel
    for ( UInt y = 0; y < img.h(); y += block_height ) {
        for ( UInt x = 0; x < img.w(); x += block_width ) {
            double block_mean = getBlockMeanPixel(img, x, y, block_width, block_height);
            block_mean_values.push_back(block_mean);
        }
    }

    vector<double> tmp = block_mean_values;

    // sort the mean values
    std::sort(tmp.begin(), tmp.end());

    //get the median
    double blocks_median = 1.0 * (tmp[ (tmp.size()/2) ] + tmp[ (tmp.size()/2 -1) ]) / 2;

    // create the hashcode bitstring
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
