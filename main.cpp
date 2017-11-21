#include "ImageDB.h"
#include "Preprocessing/ImageConverter.h"

#include <QtGui>
#include <QtWidgets>
#include <QLabel>

using namespace std;

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QLabel lbl;
    MonoPixmap mp = toMonoPixmap("images/architecture_2.jpg");

    Hashcode h = ImageDB::hash(mp);
    std::cout << h.count() << " " << h << std::endl;

    lbl.setPixmap(QPixmap::fromImage(toQImage(mp)));
    lbl.show();

    return app.exec();
}
