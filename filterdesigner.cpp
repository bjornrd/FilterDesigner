#include "filterdesigner.h"
#include "ui_filterdesigner.h"

//#include <QPalette>

#include <qdebug.h>

FilterDesigner::FilterDesigner(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FilterDesigner)
{
    ui->setupUi(this);

//    ui->coef_pushButton->setStyleSheet("QPushButton#coef_pushButton {border-width: 0px;}"
//                                       "QPushButton#coef_pushButton:hover {background-color: #ffffff;}"
//                                       );

    _filterCoefNum = sigproc::CArray { 1.0, 1.0, 1.0, 1.0, 0.0, 0.0, 0.0, 0.0 };


    _filterCoef         = new QLineSeries();
    _filterCoefChart    = new QChart();
    _filterCoefChartView= new QChartView(_filterCoefChart);

    _freqMagVals            = new QLineSeries();
    _freqPhaseVals          = new QLineSeries();
    _freqAnalysisChart      = new QChart();
    _freqAnalysisChartView  = new QChartView(_freqAnalysisChart);

    _freqAnalysisChart->legend()->hide();

    ui->analysis_groupBox->layout()->addWidget(_filterCoefChartView);
    ui->analysis_groupBox->layout()->addWidget(_freqAnalysisChartView);

    _filterCoefChartView->hide();
    _freqAnalysisChartView->hide();

}

FilterDesigner::~FilterDesigner()
{
    delete ui;
}

void FilterDesigner::on_coef_pushButton_clicked()
{
    _freqAnalysisChartView->hide();
}

void FilterDesigner::on_mag_pushButton_clicked()
{
    _filterCoefChartView->hide();
    _freqAnalysisChartView->show();


    // Add the values we want to the series
    // Just for testing purposes

    sigproc::CArray fftData = _filterCoefNum;
    sigproc::fft(fftData);

    _freqMagVals->clear();

    int f=0;
    for(auto elem:fftData)
    {
        _freqMagVals->append(f, std::sqrt(elem.real()*elem.real() + elem.imag()*elem.imag()));
//        _freqPhaseVals.append(f, std::atan2(elem.imag(), elem.real()));
        f++;
    }



    if(_freqAnalysisChart->series().size() == 0)
        _freqAnalysisChart->addSeries(_freqMagVals);


    _freqAnalysisChart->createDefaultAxes();


}
