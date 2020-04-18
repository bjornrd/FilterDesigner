#include "test_fft.h"

#include <iostream>

using namespace sigproc;

void TestFFT::testFFT()
{
    const Complex test[] = { 1.0, 1.0, 1.0, 1.0, 0.0, 0.0, 0.0, 0.0 };
    CArray data(test, 8);

    // forward fft
    fft(data);

    const CArray expected( {Complex(4.0, 0.0), Complex(1.0, -2.41421356237), Complex(0.0, 0.0),   Complex(1.0, -0.414213562373),
                            Complex(0.0, 0.0), Complex(1.0, 0.414213562373), Complex(0.0, 0.0),   Complex(1.0, 2.41421356237)} );

    CArray comp = data - expected;

    bool areTheSame = true;
    double threshold =1.0/1000.0;
    for(const auto& c:comp)
    {
        areTheSame = c.real() < threshold ? true : false;
        areTheSame = c.imag() < threshold ? true : false;
    }

    QVERIFY(areTheSame);

}

void TestFFT::testIFFT()
{
    CArray data ({Complex(4.0, 0.0), Complex(1.0, -2.41421356237), Complex(0.0, 0.0),   Complex(1.0, -0.414213562373),
                  Complex(0.0, 0.0), Complex(1.0, 0.414213562373), Complex(0.0, 0.0),   Complex(1.0, 2.41421356237)});

    const CArray expected( {Complex(1.0, 0.0), Complex(1.0, 0.0), Complex(1.0, 0.0),   Complex(1.0, 0.0),
                            Complex(0.0, 0.0), Complex(0.0, 0.0), Complex(0.0, 0.0),   Complex(0.0, 0.0)} );

    ifft(data);

    CArray comp = data - expected;

    bool areTheSame = true;
    double threshold =1.0/1000.0;
    for(const auto& c:comp)
    {
        areTheSame = c.real() < threshold ? true : false;
        areTheSame = c.imag() < threshold ? true : false;
    }

    QVERIFY(areTheSame);
}


QTEST_MAIN(TestFFT)
