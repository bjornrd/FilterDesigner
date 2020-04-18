#include "filterdesignermain.h"

#include <QApplication>
#include <QtTest/QtTest>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FilterDesignerMain w;
    w.show();
    return a.exec();
}
