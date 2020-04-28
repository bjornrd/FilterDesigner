#ifndef FILTERDESIGNERMAIN_H
#define FILTERDESIGNERMAIN_H

#include <QMainWindow>
#include <QDockWidget>
#include <QString>

#include "filteranalyzer.h"
#include "filterdesigner.h"
#include "filtertab.h"

/*  PRIMARY TO-DO LIST
 *
 * TODO: List filter types
 * TODO: List filter design methods (equiripple, windowed, least-squared...)
 * TODO: Create window design class [hamming, hann, kaizers, bartlett]
 * TODO: Biquad filter banks, for IIR filter implementation
 *
 *
 *
 *
 *
 *
 *
 */

QT_BEGIN_NAMESPACE
namespace Ui { class FilterDesignerMain; }
QT_END_NAMESPACE


class FilterDesignerMain : public QMainWindow
{
    Q_OBJECT

public:
    FilterDesignerMain(QWidget *parent = nullptr);
    ~FilterDesignerMain();

private slots:
    void on_actionNew_Filter_triggered();
    void on_main_TabWidget_tabCloseRequested(int index);
    void on_main_TabWidget_tabBarDoubleClicked(int index);
    void on_actionExit_triggered();
    void on_newFilter_pushButton_clicked();

    private:
    void setDarkUI();
    void setTabbarStyleSheet();
    void mainAppSetup();

private:
    Ui::FilterDesignerMain *ui;
};
#endif // FILTERDESIGNERMAIN_H
