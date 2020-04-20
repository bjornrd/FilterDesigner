/****************************************************************************
 * Copyright (C) 2020 Bjørn Rudi Dahl
 *
 * Written by: bjornrd
 * 20/04/2020/4/2020
 * me_brd@hotmail.com
 ****************************************************************************/
#include "windowdesigner.h"

WindowDesigner::WindowDesigner() :
    _kaizerAlpha(0.5)
{

}

WindowDesigner::~WindowDesigner()
{

}

void WindowDesigner::designWindow(WindowType type, uint windowLength)
{
    switch (type) {
        case WindowType::Rect:
            designRectWindow(windowLength);
        break;

        case WindowType::Hamming:
            designHammingWindow(windowLength);
        break;

        case WindowType::Hann:
            designHannWindow(windowLength);
        break;

        case WindowType::Kaiser:
            designKaiserWindow(windowLength, _kaizerAlpha);
        break;

        case WindowType::Blackman:
            designBlackmanWindow(windowLength);
        break;
    }

}

void WindowDesigner::designRectWindow(uint windowLength)
{
    _windowCoefficients.clear();
    _windowCoefficients.reserve(windowLength);

    for(uint i=0; i<windowLength; i++)
        _windowCoefficients.push_back(1);

}

void WindowDesigner::designHammingWindow(uint windowLength)
{
    _windowCoefficients.clear();
    _windowCoefficients.reserve(windowLength);

    double alpha = 0.53836;
    double beta =  0.46164;

    for(uint i=0; i<windowLength; i++)
        _windowCoefficients.push_back( 1.0*(alpha - beta*cos(2*sigproc::PI*i/(windowLength-1))) );
}

void WindowDesigner::designHannWindow(uint windowLength)
{
    _windowCoefficients.clear();
    _windowCoefficients.reserve(windowLength);

    for(uint i=0; i<windowLength; i++)
            _windowCoefficients.push_back( 0.5 - 0.5*cos(2*sigproc::PI*i/(windowLength-1)) );
}

void WindowDesigner::designKaiserWindow(uint windowLength, double alpha)
{
    _windowCoefficients.clear();
    _windowCoefficients.reserve(windowLength);

    double besselNom, besselDenom, p = 0.0;

    for(uint i=0; i<windowLength; i++) {
        p = (2.0*i/(windowLength-1)-1)*(2.0*i/(windowLength-1)-1);

        besselNom   = bessel(sigproc::PI*alpha*sqrt(1-p), windowLength);
        besselDenom = bessel(sigproc::PI*alpha, windowLength);

        _windowCoefficients.push_back(besselNom/besselDenom);
    }

    std::string a = WindowTypesLiteral::Types[static_cast<int>(WindowType::Hann)];
}

void WindowDesigner::designBlackmanWindow(uint windowLength)
{
    _windowCoefficients.clear();
    _windowCoefficients.reserve(windowLength);

    double alpha, a0, a1, a2;
    alpha = 0.16;
    a0 = (1-alpha)/2.0;
    a1 = 0.5;
    a2 = alpha/2.0;

    for(uint i=0; i<windowLength; i++) {
        _windowCoefficients.push_back( a0-a1*cos(2*sigproc::PI*i/(windowLength-1))+a2*cos(4*sigproc::PI*i/(windowLength-1)) );
    }
}

double WindowDesigner::bessel(double x, uint windowLength)
{
    double fact1        = 0;
    double besselOutput = 0;

    for(uint i=0; i<windowLength; i++) {
        fact1 = factorial(i);
        besselOutput += 1/(fact1*fact1)*std::pow(x/2, 2*i);
    }

    return besselOutput;
}

double WindowDesigner::factorial(double n)
{
    double factorialOutput=1;
    for(int i=1; i<n+1; i++)
        factorialOutput *= i;

    return factorialOutput;
}

double WindowDesigner::kaizerAlpha() const
{
    return _kaizerAlpha;
}

void WindowDesigner::setKaizerAlpha(double kaizerAlpha)
{
    _kaizerAlpha = kaizerAlpha;
}

std::vector<double> WindowDesigner::windowCoefficients() const
{
    return _windowCoefficients;
}

