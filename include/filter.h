#ifndef FILTER_H
#define FILTER_H

/*
 * TODO: Define base filter properties
 *
 *
 */

#include "sigproc.h"

class Filter
{
public:
    Filter();
    virtual ~Filter();

    sigproc::CArray coefficients() const;
    void setCoefficients(sigproc::CArray coefficients);

    unsigned int length() const;

protected:
    sigproc::CArray _coefficients;
    unsigned int    _length;


};

#endif // FILTER_H
