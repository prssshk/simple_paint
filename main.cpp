#include "paint.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Paint w;
    w.resize(1280,720);
    w.show();
    return a.exec();
}
