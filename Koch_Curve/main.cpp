#include "koch_curve.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Koch_Curve w;
    w.show();
    return a.exec();
}
