#ifndef POLE_ANALYSIS_HPP
#define POLE_ANALYSIS_HPP

#include <complex>
#include <cstddef>
#include <vector>

#include "rational_function.hpp"

enum class RemovalLocation
{
    FinitePole,
    Infinity,
    Constant
};

struct RemovalOption
{
    std::size_t index;
    std::complex<double> pole;
    std::size_t multiplicity;
    std::vector<std::complex<double>> poleGroup;
    RemovalLocation location = RemovalLocation::FinitePole;
};

std::vector<RemovalOption> identifyRemovalOptions(
    const RationalFunction &rationalFunction);
std::vector<RemovalOption> identifyDenominatorPoles(
    const RationalFunction &rationalFunction);

#endif
