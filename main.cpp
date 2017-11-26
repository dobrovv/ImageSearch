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

    SearchTree st;
    st.put(2,2);
    st.put(1,1);
    st.put(3,3);
    st.put(4,3);
    st.put(5,3);
    st.put(6,3);
    st.put(7,3);
    cout << st.rangeSearch(2,6).size() << endl;
}
