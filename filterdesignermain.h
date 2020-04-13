#ifndef FILTERDESIGNERMAIN_H
#define FILTERDESIGNERMAIN_H

#include <QMainWindow>

#include "filterdesigner.h"

QT_BEGIN_NAMESPACE
namespace Ui { class FilterDesignerMain; }
QT_END_NAMESPACE

class FilterDesignerMain : public QMainWindow
{
    Q_OBJECT

public:
    FilterDesignerMain(QWidget *parent = nullptr);
    ~FilterDesignerMain();

private:
    Ui::FilterDesignerMain *ui;
    void mainAppSetup();

    FilterDesigner* _filterDesigner;
    void setUpTools();
};
#endif // FILTERDESIGNERMAIN_H
