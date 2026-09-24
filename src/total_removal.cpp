#include "total_removal.hpp"

#include <cmath>
#include <complex>
#include <vector>

namespace
{
constexpr double kFrequencyTolerance = 1.0e-8;

bool sameFrequency(const std::complex<double> &first,
                   const std::complex<double> &second)
{
    const double scale = std::max(1.0, std::max(std::abs(first), std::abs(second)));
    return std::abs(first - second) <= kFrequencyTolerance * scale;
}

std::vector<double> subtract(const std::vector<double> &first,
                             const std::vector<double> &second)
{
    const std::size_t size = std::max(first.size(), second.size());
    std::vector<double> result(size, 0.0);
    const std::size_t firstOffset = size - first.size();
    const std::size_t secondOffset = size - second.size();
    for (std::size_t index = 0U; index < first.size(); ++index)
    {
        result[firstOffset + index] += first[index];
    }
    for (std::size_t index = 0U; index < second.size(); ++index)
    {
        result[secondOffset + index] -= second[index];
    }
    while (result.size() > 1U && std::abs(result.front()) <= 1.0e-10)
    {
        result.erase(result.begin());
    }
    return result;
}

std::vector<double> multiply(const std::vector<double> &first,
                             const std::vector<double> &second)
{
    std::vector<double> result(first.size() + second.size() - 1U, 0.0);
    for (std::size_t firstIndex = 0U; firstIndex < first.size(); ++firstIndex)
    {
        for (std::size_t secondIndex = 0U;
             secondIndex < second.size(); ++secondIndex)
        {
            result[firstIndex + secondIndex] +=
                first[firstIndex] * second[secondIndex];
        }
    }
    return result;
}

bool divideExactly(const std::vector<double> &polynomial,
                   const std::vector<double> &factor,
                   std::vector<double> &quotient)
{
    if (polynomial.size() < factor.size())
    {
        return false;
    }
    std::vector<double> work = polynomial;
    quotient.assign(polynomial.size() - factor.size() + 1U, 0.0);
    for (std::size_t index = 0U; index < quotient.size(); ++index)
    {
        const double scale = work[index] / factor.front();
        quotient[index] = scale;
        for (std::size_t factorIndex = 0U; factorIndex < factor.size();
             ++factorIndex)
        {
            work[index + factorIndex] -= scale * factor[factorIndex];
        }
    }
    for (std::size_t index = quotient.size(); index < work.size(); ++index)
    {
        if (std::abs(work[index]) > 1.0e-8)
        {
            return false;
        }
    }
    while (quotient.size() > 1U && std::abs(quotient.front()) <= 1.0e-10)
    {
        quotient.erase(quotient.begin());
    }
    return true;
}

bool isZeroPolynomial(const std::vector<double> &polynomial)
{
    for (const double coefficient : polynomial)
    {
        if (std::abs(coefficient) > 1.0e-10)
        {
            return false;
        }
    }
    return true;
}

bool samePolynomial(const std::vector<double> &first,
                    const std::vector<double> &second)
{
    const std::size_t size = std::max(first.size(), second.size());
    const std::size_t firstOffset = size - first.size();
    const std::size_t secondOffset = size - second.size();
    for (std::size_t index = 0U; index < size; ++index)
    {
        const double firstValue = index < firstOffset ? 0.0 : first[index - firstOffset];
        const double secondValue = index < secondOffset ? 0.0 : second[index - secondOffset];
        if (std::abs(firstValue - secondValue) >
            1.0e-8 * std::max(1.0, std::max(std::abs(firstValue),
                                            std::abs(secondValue))))
        {
            return false;
        }
    }
    return true;
}

void fosterTerm(const RemovalOption &candidate,
                const FosterComponent &component,
                std::vector<double> &numerator,
                std::vector<double> &denominator)
{
    denominator = {1.0};
    if (component.type == FosterComponentType::ParallelRC)
    {
        numerator = {1.0 / component.capacitance};
        denominator = {1.0, -candidate.pole.real()};
    }
    else if (component.type == FosterComponentType::ParallelRL)
    {
        numerator = {component.resistance, 0.0};
        denominator = {1.0, -candidate.pole.real()};
    }
    else if (component.type == FosterComponentType::ParallelLC)
    {
        const double omega = std::abs(candidate.pole.imag());
        numerator = {1.0 / component.capacitance, 0.0};
        denominator = {1.0, 0.0, omega * omega};
    }
    else if (component.type == FosterComponentType::SeriesCapacitor)
    {
        numerator = {1.0 / component.capacitance};
        denominator = {1.0, 0.0};
    }
    else if (component.type == FosterComponentType::SeriesInductor)
    {
        numerator = {component.inductance, 0.0};
    }
    else
    {
        numerator = {component.resistance};
    }
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

bool applyTotalRemoval(const RationalFunction &rationalFunction,
                       const RemovalOption &candidate,
                       const FosterComponent &component,
                       RationalFunction &remainingFunction)
{
    std::vector<double> termNumerator;
    std::vector<double> termDenominator;
    fosterTerm(candidate, component, termNumerator, termDenominator);

    const std::vector<double> originalNumerator =
        rationalFunction.numerator().coefficients();
    const std::vector<double> originalDenominator =
        rationalFunction.denominator().coefficients();
    std::vector<double> remainingDenominator;
    if (termDenominator.size() > 1U &&
        !divideExactly(originalDenominator, termDenominator,
                       remainingDenominator))
    {
        return false;
    }
    if (termDenominator.size() == 1U)
    {
        remainingDenominator = originalDenominator;
    }

    const std::vector<double> uncancelledNumerator = subtract(
        originalNumerator,
        multiply(termNumerator, remainingDenominator));
    std::vector<double> remainingNumerator;
    if (isZeroPolynomial(uncancelledNumerator))
    {
        remainingNumerator = {0.0};
        remainingDenominator = {1.0};
    }
    else if (termDenominator.size() > 1U)
    {
        if (!divideExactly(uncancelledNumerator, termDenominator,
                           remainingNumerator))
        {
            return false;
        }
    }
    else
    {
        remainingNumerator = uncancelledNumerator;
    }

    std::vector<double> reconstructed = multiply(
        termNumerator, remainingDenominator);
    const std::vector<double> remainingContribution = multiply(
        remainingNumerator, termDenominator);
    const std::size_t size = std::max(reconstructed.size(),
                                      remainingContribution.size());
    std::vector<double> sum(size, 0.0);
    const std::size_t termOffset = size - reconstructed.size();
    const std::size_t remainingOffset = size - remainingContribution.size();
    for (std::size_t index = 0U; index < reconstructed.size(); ++index)
        sum[termOffset + index] += reconstructed[index];
    for (std::size_t index = 0U; index < remainingContribution.size(); ++index)
        sum[remainingOffset + index] += remainingContribution[index];
    if (!samePolynomial(originalNumerator, sum))
    {
        return false;
    }

    const RationalFunction candidateRemaining{
        Polynomial(remainingNumerator), Polynomial(remainingDenominator)};
    if (candidate.location == RemovalLocation::FinitePole)
    {
        const std::vector<RemovalOption> remainingPoles =
            identifyDenominatorPoles(candidateRemaining);
        for (const RemovalOption &pole : remainingPoles)
        {
            for (const std::complex<double> &removedPole : candidate.poleGroup)
            {
                if (sameFrequency(pole.pole, removedPole))
                {
                    return false;
                }
            }
        }
    }
    remainingFunction.replace(candidateRemaining.numerator(),
                              candidateRemaining.denominator());
    return true;
}