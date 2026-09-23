#include "rational_function.hpp"

RationalFunction::RationalFunction(const Polynomial &numerator,
                                   const Polynomial &denominator)
    : numerator_(numerator), denominator_(denominator)
{
}

const Polynomial &RationalFunction::numerator() const
{
    return numerator_;
}

const Polynomial &RationalFunction::denominator() const
{
    return denominator_;
}

void RationalFunction::replace(const Polynomial &numerator,
                               const Polynomial &denominator)
{
    numerator_ = numerator;
    denominator_ = denominator;
}
