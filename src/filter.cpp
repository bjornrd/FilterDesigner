#include "filter.h"

Filter::Filter()
{

}

Filter::~Filter()
{

}

sigproc::CArray Filter::coefficients() const
{
    return _coefficients;
}

void Filter::setCoefficients(sigproc::CArray coefficients)
{
    _coefficients = coefficients;
    _length = _coefficients.size();
}

unsigned int Filter::length() const
{
    return _length;
}
