#include "MonoPixmap.h"
#include "Preprocessing/ImageConverter.h"

#include <QtGui>
#include <QtWidgets>
#include <QLabel>

using namespace std;

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QLabel lbl;
    QImage img = toQImage("images/architecture_2.jpg");
    MonoPixmap mp = toMonoPixmap(img);
    img = toQImage(mp);
    lbl.setPixmap(QPixmap::fromImage(img));
    lbl.show();

    return app.exec();
}
