#include "filterdesignermain.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    a.setApplicationName("FilterDesigner");
    FilterDesignerMain w;
    w.show();
    return a.exec();
}
