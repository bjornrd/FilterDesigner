/****************************************************************************
 * Copyright (C) 2020 Bjørn Rudi Dahl
 *
 * Written by: bjornrd
 * 20/04/2020/4/2020
 * me_brd@hotmail.com
 ****************************************************************************/
#ifndef WINDOWFIR_H
#define WINDOWFIR_H

#include <vector>

#include "sigproc.h"

enum class WindowType
{
    Rect = 0,
    Hamming,
    Hann,
    Kaiser,
    Blackman
};

class WindowTypesLiteral
{
    public:
        const static std::string Rectangular;
        const static std::string Hamming;
        const static std::string Hann;
        const static std::string Kaiser;
        const static std::string Blackman;

        const static std::vector<std::string> Types;

    private:
        WindowTypesLiteral(){} // Disallow creating an instance of this object
};

const std::string WindowTypesLiteral::Rectangular  = "Rectangular";
const std::string WindowTypesLiteral::Hamming      = "Hamming";
const std::string WindowTypesLiteral::Hann         = "Hann";
const std::string WindowTypesLiteral::Kaiser       = "Kaiser";
const std::string WindowTypesLiteral::Blackman     = "Blackman";

const std::vector<std::string>  WindowTypesLiteral::Types{WindowTypesLiteral::Rectangular,
                                                          WindowTypesLiteral::Hamming,
                                                          WindowTypesLiteral::Hann,
                                                          WindowTypesLiteral::Kaiser,
                                                          WindowTypesLiteral::Blackman};



class WindowFIR
{
    public:
        WindowFIR();
        ~WindowFIR();

        void designWindow(WindowType type, uint windowLength);

        std::vector<double> filterCoefficients() const;
        std::vector<double> windowCoefficients() const;

        double kaizerAlpha() const;
        void setKaizerAlpha(double kaizerAlpha);

    private:
        void designRectWindow(      uint windowLength               );
        void designHammingWindow(   uint windowLength               );
        void designHannWindow(      uint windowLength               );
        void designKaiserWindow(    uint windowLength, double alpha );
        void designBlackmanWindow(  uint windowLength               );

        double bessel(double x, uint windowLength);
        double factorial(double n);

    private:
        std::vector<double> _filterCoefficients;
        std::vector<double> _windowCoefficients;

        double _kaizerAlpha;

};

#endif // WINDOWFIR_H
