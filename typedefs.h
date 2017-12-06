// All user types and constants used in the program are defined here.

#ifndef TYPEDEFS_H
#define TYPEDEFS_H

#include <cstdint>
#include <string>
#include <vector>
#include <bitset>
#include <iostream>

using std::cout;
using std::endl;

constexpr int IMG_WIDTH  = 256; // Normalized width
constexpr int IMG_HEIGHT = 256; // Normalized height

// Number of blocks / size of the bitstring
constexpr int BLOCK_CNT = 64; // must be a perfect square

using Byte = std::uint8_t;
using UInt = std::uint32_t;

using std::string;
using std::vector;

using Hashcode = std::bitset<BLOCK_CNT>;

// A class storing information about the image
// It is the type stored in the leafs of BPlusTree
struct ImageInfo {
    Hashcode hashcode;
    string filepath;
};

#endif // TYPEDEFS_H
