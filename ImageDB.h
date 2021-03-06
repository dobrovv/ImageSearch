// Implementation of image database
// uses B+ Tree to store image's information
// all function related to image hashing and retrieval are here.

#ifndef IMAGEDB_H
#define IMAGEDB_H

#include "Typedefs.h"
#include "MonoPixmap.h"
#include "BPlusTree.h"


class ImageDB
{ 
    BPlusTree tree;

public:
    ImageDB();

    inline BPlusTree * getTree() {return &tree;}

    // Loads each image from a directory using Preprocessing/FileSystem.h
    // Normalizes and grayscales the image using Preprocessing/ImageConverter.h
    // Calculates the image hashcode
    // Inserts the hashcode into the tree
    void loadImagesFromDir(const string  & dirpath);

    // Finds similar images according to specified tolerance
    // tollerance should be in range [0.0, 1.0]
    vector<ImageInfo> query(const MonoPixmap & image, double tolerance = 0.05);

    // Compares two bitstrings according to a given tolerance
    // using the hamming distance
    // returns true if trgt doesn't exceed the tolerance
    bool filter(Hashcode hashcode, Hashcode trgt, double tolerance);

    // Calculates the hash bitstring of a normalized and grayscaled image
    static Hashcode hash(const MonoPixmap & image);

    //Calculates the hamming distance between two hashcodes
    static int hamming_distance(Hashcode hashcode, Hashcode trgt);

    // Calculates the length of hashcode's bitstring
    static int length(Hashcode hashcode);

private:
    // A utility function
    // Finds the mean pixel of a given block
    static double getBlockMeanPixel(const MonoPixmap & image, UInt x, UInt y, UInt block_width, UInt block_height);

};

#endif // IMAGEDB_H
