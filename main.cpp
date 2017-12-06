#include "BPlusTree.h"
#include "ImageDB.h"
#include "Preprocessing/ImageConverter.h"
#include "Preprocessing/FileSystem.h"
#include "GUI/MainWindow.h"

#include <QtWidgets/QApplication>

using namespace std;

int main(int argc, char *argv[]) {

    ImageDB db;

    // load images
    db.loadImagesFromDir("images");

    // Display the gui
    QApplication app(argc, argv);
    MainWindow * mw = new MainWindow(&db);
    mw->show();

    return app.exec();
}


//    vector<ImageInfo> result;
//    db.loadImagesFromDir("images");
//    MonoPixmap mp = ImgConv::toMonoPixmap("C:/Dev/Projects/Qt/ImageSearchReleaseBuild/images/architecture1.jpg");
//    cout << "Query Hashcode " << ImageDB::hash(mp) << endl;
//    result = db.query(mp, 1);

//    for (auto t : result) {
//        cout << t.filepath << endl;
//    }

//    ImageScrollView * v = new ImageScrollView();
//    for (auto t : result) {
//        QString filepath = QString::fromStdString(t.filepath);
//        v->addImage(QImage(filepath), filepath);
//    }

//    BPlusTree t;
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
//    cout << endl << t.root->toString() << endl;
//    cout << t.search(3)->toString();
