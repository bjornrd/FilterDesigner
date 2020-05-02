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

    _filterCoefNum = sigproc::CArray {1.0, 1.0, 1.0, 1.0, -1.0, -1.0, -1.0, -1.0};

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
                                            "border-top: 4px;"
                                            "min-width: 6em;"
                                            "min-height: 2em;"
                                    "}"

                                    "QPushButton:hover {background: #484852;}"
                                    "QPushButton:focus {background: #2A2A32;"
                                    "                   border-top: 3px solid #7A7A84; "
                                    "                   border-radius: 0px;};";


    ui->coef_pushButton ->setStyleSheet(pushButtonStyleSheet);
    ui->mag_pushButton  ->setStyleSheet(pushButtonStyleSheet);
    ui->phase_pushButton->setStyleSheet(pushButtonStyleSheet);
}

void FilterAnalyzer::setUpCharts()
{

    // Coefficients
    // -----------------------------------------
    _filterCoef     = new QLineSeries();
    _filterCoefChart= new QChart();
    _filterCoefChart->setTheme(QChart::ChartThemeDark);

    _coefXAxis = new QValueAxis();
    _coefYAxis = new QValueAxis();

    _filterCoefChart->addAxis(_coefXAxis, Qt::AlignBottom);
    _filterCoefChart->addAxis(_coefYAxis, Qt::AlignLeft);


    // Magnitude
    // -----------------------------------------
    _freqMagVals    = new QLineSeries();
    _freqMagChart   = new QChart();
    _freqMagChart->setTheme(QChart::ChartThemeDark);

    // Phase
    // -----------------------------------------
    _freqPhaseVals  = new QLineSeries();
    _freqPhaseChart = new QChart();
    _freqPhaseChart->setTheme(QChart::ChartThemeDark);



    // Misc.
    // -----------------------------------------
    _filterCoefChart->legend()->hide();
    _freqMagChart   ->legend()->hide();
    _freqPhaseChart ->legend()->hide();


}

void FilterAnalyzer::on_coef_pushButton_clicked()
{
    ui->analysis_chartView->setChart(_filterCoefChart);


    //----------------------
    // For experimental purposes
    _filterCoef->clear();


    int i=0;

    double ymin = 0, ymax = 0;
    for(const auto& elem:_filterCoefNum)
    {
        auto er = elem.real();
        _filterCoef->append(i, er);
        i++;

        ymax = er > ymax ? er : ymax;
        ymin = er < ymin ? er : ymin;
    }

    _coefXAxis->setRange(1, _filterCoef->count());
    _coefXAxis ->setTickCount(_filterCoef->count());
    _coefXAxis->setLabelFormat("%i");

    _coefYAxis->setRange(ymin, ymax);


    //----------------------


    if(_filterCoefChart->series().size() == 0)
        _filterCoefChart->addSeries(_filterCoef);

}

void FilterAnalyzer::on_mag_pushButton_clicked()
{
    ui->analysis_chartView->setChart(_freqMagChart);

    //----------------------
    // Add the values we want to the series
    // Just for testing purposes

    sigproc::CArray fftData = _filterCoefNum;
    auto ffted = sigproc::fft(fftData, 1024);

    _freqMagVals->clear();

    int f=0;
    for(auto elem:ffted)
    {
        _freqMagVals->append(f, 20.0*std::log10(std::sqrt(elem.real()*elem.real() + elem.imag()*elem.imag())) );
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
