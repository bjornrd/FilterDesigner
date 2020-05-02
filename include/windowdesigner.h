/****************************************************************************
 * Bjørn Rudi Dahl
 *
 * Written by: bjornrd
 * 20/04/2020
 * bjorn.rudi.dahl@outlook.com
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
        const static inline std::string Rectangular = "Rectangular";
        const static inline std::string Hamming     = "Hamming";
        const static inline std::string Hann        = "Hann";
        const static inline std::string Kaiser      = "Kaiser";
        const static inline std::string Blackman    = "Blackman";

        const static inline std::vector<std::string> Types{WindowTypesLiteral::Rectangular,
                                                           WindowTypesLiteral::Hamming,
                                                           WindowTypesLiteral::Hann,
                                                           WindowTypesLiteral::Kaiser,
                                                           WindowTypesLiteral::Blackman};

    private:
        WindowTypesLiteral(){} // Disallow creating an instance of this object
};

class WindowDesigner
{
    public:
        static std::vector<double> designWindow(WindowType type, uint windowLength);

        static std::vector<double> windowCoefficients();

        static double kaizerAlpha();
        static void setKaizerAlpha(double kaizerAlpha);

    private:
        WindowDesigner() {}

        static void designRectWindow(      uint windowLength               );
        static void designHammingWindow(   uint windowLength               );
        static void designHannWindow(      uint windowLength               );
        static void designKaiserWindow(    uint windowLength, double alpha );
        static void designBlackmanWindow(  uint windowLength               );

        static double bessel(double x, uint windowLength);
        static double factorial(double n);

    private:
        static inline std::vector<double> _windowCoefficients;
        static inline double _kaizerAlpha = 0.5;

};

#endif // WINDOWFIR_H
