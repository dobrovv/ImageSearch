#include "ImageDB.h"
#include "Preprocessing/ImageConverter.h"
#include "Preprocessing/FileSystem.h"


#include <QtGui>
#include <QtWidgets>
#include <QLabel>

#include <BPlusTree.h>
#include <iostream>

using namespace std;

int main(int argc, char *argv[]) {
//    QApplication app(argc, argv);

//    QLabel lbl;
//    MonoPixmap mp = toMonoPixmap("images/architecture_2.jpg");

//    Hashcode h = ImageDB::hash(mp);
//    std::cout << h.count() << " " << h << std::endl;

//    lbl.setPixmap(QPixmap::fromImage(toQImage(mp)));
//    lbl.show();

//    return app.exec();

    ImageDB db;
    vector<ImageInfo> result;
    db.loadImagesFromDir("images");
    MonoPixmap mp = ImgConv::toMonoPixmap("C:/Dev/Projects/Qt/ImageSearchReleaseBuild/images/architecture1.jpg");
    cout << "Query Hashcode" << ImageDB::hash(mp) << endl;
    result = db.query(mp, 0.4);

    for (auto t : result) {
        cout << t.filepath << endl;
    }


    BPlusTree t;

//    t.insert(1, 101);
//    t.insert(4, 101);
//    t.insert(16, 116);
//    t.insert(25, 125);
//    t.insert(9, 109);
//    t.insert(20, 109);
//    t.insert(13, 109);
//    t.insert(15, 109);
//    t.insert(10, 109);
//    t.insert(11, 109);
//    t.insert(12, 109);
//    t.insert(5, 109);
//    t.insert(6, 109);
//    t.insert(7, 109);
//    t.insert(8, 109);
    for (int i = 0; i < 3; i++){
//        t.insert(1,i);
//        t.insert(101,i);
//        t.insert(100,i);
//        t.insert(100,i);
//        t.insert(100,i);
//        t.insert(100,i);
//        t.insert(100,i);
//        t.insert(100,i);
//        t.insert(100,i);
//        t.insert(100,i);
//        t.insert(100,i);
//        t.insert(100,i);
//        t.insert(100,i);
//        t.insert(100,i);
//        t.insert(1,i);
//        t.insert(101,i);
    }

    cout << "Test " << (true^false);

    cout << endl << t.root->toString() << endl;
    cout << t.search(3)->toString();
}
