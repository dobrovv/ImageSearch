#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include "Typedefs.h"

#include <QDir>

namespace FileSystem {

    // Returns file paths present in a directory
    vector<string> getDirectoryFiles(const string & dirpath);
}

#endif // FILESYSTEM_H
