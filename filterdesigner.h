#ifndef FILTERDESIGNER_H
#define FILTERDESIGNER_H

#include <QWidget>
#include <QChartView>

#include <QtCharts>
#include <QChart>
#include <QLineSeries>

#include "sigproc.h"

namespace Ui {
class FilterDesigner;
}

class FilterDesigner : public QWidget
{
    Q_OBJECT

public:
    explicit FilterDesigner(QWidget *parent = nullptr);
    ~FilterDesigner();

private slots:
    void on_coef_pushButton_clicked();

    void on_mag_pushButton_clicked();

private:
    Ui::FilterDesigner *ui;

    sigproc::CArray _filterCoefNum;
    sigproc::CArray _filterCoefDen;

    QLineSeries*  _filterCoef;
    QChart*       _filterCoefChart;
    QChartView*   _filterCoefChartView;

    QLineSeries*  _freqMagVals;
    QLineSeries*  _freqPhaseVals;
    QChart*       _freqAnalysisChart;
    QChartView*   _freqAnalysisChartView;

};

#endif // FILTERDESIGNER_H
