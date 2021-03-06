#include "filteranalyzer.h"
#include "ui_filteranalyzer.h"

#include <QStyle>

#include <qdebug.h>

FilterAnalyzer::FilterAnalyzer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FilterAnalyzer)
{
    ui->setupUi(this);

    setStyleSheets();
    setUpCharts();

    _filterCoefNum = sigproc::CArray {{ 1.0 , 2.0}, 1.0, 1.0, 1.0, 0.0, 0.0, 0.0, 0.0 };

    ui->analysis_chartView->setChart(_filterCoefChart);

}

FilterAnalyzer::~FilterAnalyzer()
{
    delete ui;
}

void FilterAnalyzer::updateCoefficients(sigproc::CArray coefNum, sigproc::CArray coefDen)
{
    _filterCoefNum = coefNum;
    _filterCoefDen = coefDen;
}

void FilterAnalyzer::setStyleSheets()
{
    QString pushButtonStyleSheet = "QPushButton{"
                                            "border: 0px;"
                                            "border-radius: 0px;"
                                            "min-width: 80px;"
                                            "min-height: 40px;"
                                    "}"

                                    "QPushButton:hover {background: #5E5F60;}";


    ui->coef_pushButton ->setStyleSheet(pushButtonStyleSheet);
    ui->mag_pushButton  ->setStyleSheet(pushButtonStyleSheet);
    ui->phase_pushButton->setStyleSheet(pushButtonStyleSheet);
}

void FilterAnalyzer::setUpCharts()
{
    _filterCoef     = new QLineSeries();
    _filterCoefChart= new QChart();
    _filterCoefChart->setTheme(QChart::ChartThemeDark);

    _freqMagVals    = new QLineSeries();
    _freqMagChart   = new QChart();
    _freqMagChart->setTheme(QChart::ChartThemeDark);

    _freqPhaseVals  = new QLineSeries();
    _freqPhaseChart = new QChart();
    _freqPhaseChart->setTheme(QChart::ChartThemeDark);


    _filterCoefChart->legend()->hide();
    _freqMagChart   ->legend()->hide();
    _freqPhaseChart ->legend()->hide();
}

void FilterAnalyzer::on_coef_pushButton_clicked()
{
    ui->analysis_chartView->setChart(_filterCoefChart);
    ui->currentPane_label->setText("[" + ui->coef_pushButton->text() + "]");

    //----------------------
    // For experimental purposes
    _filterCoef->clear();

    int i=0;
    for(auto elem:_filterCoefNum)
    {
        _filterCoef->append(i, elem.real());
        i++;
    }

    //----------------------


    if(_filterCoefChart->series().size() == 0)
        _filterCoefChart->addSeries(_filterCoef);

    _filterCoefChart->createDefaultAxes();
}

void FilterAnalyzer::on_mag_pushButton_clicked()
{
    ui->analysis_chartView->setChart(_freqMagChart);
    ui->currentPane_label->setText("[" + ui->mag_pushButton->text() + "]");

    //----------------------
    // Add the values we want to the series
    // Just for testing purposes

    sigproc::CArray fftData = _filterCoefNum;
    sigproc::fft(fftData);

    _freqMagVals->clear();

    int f=0;
    for(auto elem:fftData)
    {
        _freqMagVals->append(f, std::sqrt(elem.real()*elem.real() + elem.imag()*elem.imag()));
        f++;
    }


    //----------------------


    if(_freqMagChart->series().size() == 0)
        _freqMagChart->addSeries(_freqMagVals);


    _freqMagChart->createDefaultAxes();

}



void FilterAnalyzer::on_phase_pushButton_clicked()
{
    ui->analysis_chartView->setChart(_freqPhaseChart);
    ui->currentPane_label->setText("[" + ui->phase_pushButton->text() + "]");

    //----------------------
    // Add the values we want to the series
    // Just for testing purposes

    sigproc::CArray fftData = _filterCoefNum;
    sigproc::fft(fftData);

    _freqPhaseVals->clear();

    int f=0;
    for(auto elem:fftData)
    {
        _freqPhaseVals->append(f, std::atan2(elem.imag(), elem.real()));
        f++;
    }


    //----------------------


    if(_freqPhaseChart->series().size() == 0)
        _freqPhaseChart->addSeries(_freqPhaseVals);


    _freqPhaseChart->createDefaultAxes();
}
