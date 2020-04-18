#ifndef TEST_FFT_H
#define TEST_FFT_H

#include <QtTest/QtTest>

#include "sigproc.h"

class TestFFT : public QObject
{
    Q_OBJECT

private slots:
    void testFFT();
    void testIFFT();

};

#endif // TEST_FFT_H
