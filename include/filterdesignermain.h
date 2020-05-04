#ifndef FILTERDESIGNERMAIN_H
#define FILTERDESIGNERMAIN_H

#include <QMainWindow>
#include <QDockWidget>
#include <QString>
#include <QPropertyAnimation>
#include <QGraphicsEffect>
#include <QKeyEvent>

#include <QDebug>

#include "filteranalyzer.h"
#include "filterdesigner.h"
#include "filtertab.h"
#include "appsettings.h"

/*  PRIMARY TO-DO LIST
 *
 * % App Stuff
 * TODO: AutoSave (?)
 * TODO: Save Filter / Window
 * TODO: Load Filter / Window
 *
 * % Actual Filter Stuff
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

protected:
    bool eventFilter(QObject *watched, QEvent *event);
    void closeEvent(QCloseEvent* event);

private slots:
    void on_actionNew_Filter_triggered();
    void on_main_TabWidget_tabCloseRequested(int index);
    void on_main_TabWidget_tabBarDoubleClicked(int index);
    void on_actionExit_triggered();
    void on_newFilter_pushButton_clicked();
    void on_actionSettings_triggered();


    void on_actionAbout_triggered();

private:
    void writeSettings();
    void readSettings();
    void applySettings();

    void setDarkUI();
    void setTabbarStyleSheet();
    void setOtherStyleSheet();
    void mainAppSetup();

    void showAppSettings();
    void hideAppSettings();

private:
    Ui::FilterDesignerMain *ui;
    AppSettings* _appSettings;
};
#endif // FILTERDESIGNERMAIN_H
