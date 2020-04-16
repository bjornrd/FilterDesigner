#ifndef FILTERDESIGNERMAIN_H
#define FILTERDESIGNERMAIN_H

#include <QMainWindow>
#include <QDockWidget>

#include "filteranalyzer.h"
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
    void setDarkUI();
    void setTabbarStyleSheet();
    void setUpTools();
    void mainAppSetup();

private:
    Ui::FilterDesignerMain *ui;

    FilterDesigner* _filterDesigner;
    FilterAnalyzer* _filterAnalyzer;

};
#endif // FILTERDESIGNERMAIN_H
