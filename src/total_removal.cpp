#include "total_removal.hpp"

#include <cmath>
#include <complex>

namespace
{
constexpr double kFrequencyTolerance = 1.0e-8;

bool sameFrequency(const std::complex<double> &first,
                   const std::complex<double> &second)
{
    const double scale = std::max(1.0, std::max(std::abs(first), std::abs(second)));
    return std::abs(first - second) <= kFrequencyTolerance * scale;
}
}

bool validateTotalRemoval(const RationalFunction &rationalFunction,
                          const RemovalOption &candidate)
{
    const std::vector<RemovalOption> options =
        identifyRemovalOptions(rationalFunction);
    for (const RemovalOption &option : options)
    {
        if (sameFrequency(option.pole, candidate.pole) &&
            option.poleGroup.size() == candidate.poleGroup.size())
        {
            return option.multiplicity == 1U;
        }
    }
    return false;
}