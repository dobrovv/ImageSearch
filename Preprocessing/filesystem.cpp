#include "FileSystem.h"

namespace FileSystem {

    // Returns file paths present in a directory
    vector<string> getDirectoryFiles(const string & dirpath) {
        vector<string> result;

        QDir dir(QString::fromStdString(dirpath));
        dir.setFilter(QDir::Files | QDir::NoSymLinks);

        for (QString filename : dir.entryList() ) {
            filename = dir.absoluteFilePath(filename);
            //filename = dir.relativeFilePath(filename);
            result.push_back(filename.toStdString());
        }

        return result;
    }
}
