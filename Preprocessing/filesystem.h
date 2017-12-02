#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <QDir>
#include <vector>
#include <string>

using std::string;
using std::vector;

namespace FileSystem {

    // Returns file paths present in a directory
    vector<string> getDirectoryFiles(const string & dirpath);
}

#endif // FILESYSTEM_H
