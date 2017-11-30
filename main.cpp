#include "ImageDB.h"
#include "Preprocessing/ImageConverter.h"

#include <QtGui>
#include <QtWidgets>
#include <QLabel>

#include <SearchTree.h>
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

    BPTree t;
    t.insert(1, 101);
    t.insert(4, 101);
    t.insert(16, 116);
    t.insert(25, 125);
    t.insert(9, 109);
    t.insert(20, 109);
    t.insert(13, 109);
    t.insert(15, 109);
    t.insert(10, 109);
    t.insert(11, 109);
    t.insert(12, 109);
    //t.insert(12, 109);


    cout << t.root->toString() << endl;
}
