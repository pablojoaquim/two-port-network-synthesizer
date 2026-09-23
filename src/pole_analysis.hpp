#ifndef POLE_ANALYSIS_HPP
#define POLE_ANALYSIS_HPP

#include <complex>
#include <cstddef>
#include <vector>

#include "rational_function.hpp"

struct RemovalOption
{
    std::size_t index;
    std::complex<double> pole;
    std::size_t multiplicity;
};

std::vector<RemovalOption> identifyRemovalOptions(
    const RationalFunction &rationalFunction);

#endif
