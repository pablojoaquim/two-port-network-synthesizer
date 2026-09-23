#ifndef RATIONAL_FUNCTION_HPP
#define RATIONAL_FUNCTION_HPP

#include "polynomial.hpp"

class RationalFunction
{
public:
    RationalFunction(const Polynomial &numerator,
                     const Polynomial &denominator);

    const Polynomial &numerator() const;
    const Polynomial &denominator() const;

    void replace(const Polynomial &numerator, const Polynomial &denominator);

private:
    Polynomial numerator_;
    Polynomial denominator_;
};

#endif
