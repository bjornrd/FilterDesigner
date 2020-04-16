#ifndef FILTERANALYZER_H
#define FILTERANALYZER_H

#include <QWidget>
#include <QtCharts>
#include <QChart>
#include <QLineSeries>

#include "sigproc.h"

namespace Ui {
class FilterAnalyzer;
}

class FilterAnalyzer : public QWidget
{
    Q_OBJECT

public:
    explicit FilterAnalyzer(QWidget *parent = nullptr);
    ~FilterAnalyzer();


public slots:
    void updateCoefficients(sigproc::CArray coefNum = {}, sigproc::CArray coefDen = {});

private slots:
    void on_coef_pushButton_clicked();
    void on_mag_pushButton_clicked();

    void on_phase_pushButton_clicked();

private:
    void setStyleSheets();

private:
    Ui::FilterAnalyzer *ui;

    sigproc::CArray _filterCoefNum;
    sigproc::CArray _filterCoefDen;

    QLineSeries*  _filterCoef;
    QChart*       _filterCoefChart;

    QLineSeries*  _freqMagVals;
    QChart*       _freqMagChart;

    QLineSeries*  _freqPhaseVals;
    QChart*       _freqPhaseChart;

    void setUpCharts();
};

#endif // FILTERANALYZER_H
