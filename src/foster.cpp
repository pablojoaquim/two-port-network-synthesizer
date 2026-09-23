#include "foster.hpp"

#include <cmath>
#include <complex>
#include <limits>
#include <vector>

namespace
{
constexpr double kAxisTolerance = 1.0e-8;

std::complex<double> evaluate(const Polynomial &polynomial,
                              const std::complex<double> &value)
{
    std::complex<double> result(0.0, 0.0);
    for (const double coefficient : polynomial.coefficients())
    {
        result = result * value + coefficient;
    }
    return result;
}

std::complex<double> derivativeAt(const Polynomial &polynomial,
                                  const std::complex<double> &value)
{
    const std::vector<double> &coefficients = polynomial.coefficients();
    if (coefficients.size() <= 1U)
    {
        return std::complex<double>(0.0, 0.0);
    }

    std::complex<double> result(0.0, 0.0);
    const std::size_t degree = coefficients.size() - 1U;
    for (std::size_t index = 0U; index < degree; ++index)
    {
        result = result * value +
                 static_cast<double>(degree - index) * coefficients[index];
    }
    return result;
}

bool finitePositive(double value)
{
    return std::isfinite(value) && value > 0.0;
}
}

bool extractFosterComponent(const RationalFunction &rationalFunction,
                            const RemovalOption &option,
                            FosterComponent &component)
{
    const std::complex<double> denominatorDerivative = derivativeAt(
        rationalFunction.denominator(), option.pole);
    if (std::abs(denominatorDerivative) <= std::numeric_limits<double>::epsilon())
    {
        return false;
    }

    const std::complex<double> residue =
        evaluate(rationalFunction.numerator(), option.pole) /
        denominatorDerivative;
    if (!std::isfinite(residue.real()) || !std::isfinite(residue.imag()))
    {
        return false;
    }

    if (std::abs(option.pole.imag()) <= kAxisTolerance)
    {
        const double a = -option.pole.real();
        const double conductanceResidue = residue.real();
        const double capacitance = 1.0 / conductanceResidue;
        const double resistance = conductanceResidue / a;
        if (!finitePositive(a) || !finitePositive(capacitance) ||
            !finitePositive(resistance) || std::abs(residue.imag()) > kAxisTolerance)
        {
            return false;
        }
        component = {FosterComponentType::ParallelRC, resistance,
                     capacitance, 0.0};
        return true;
    }

    if (std::abs(option.pole.real()) > kAxisTolerance)
    {
        return false;
    }

    const double omega = std::abs(option.pole.imag());
    const double coefficient = 2.0 * residue.real();
    const double capacitance = 1.0 / coefficient;
    const double inductance = coefficient / (omega * omega);
    if (!finitePositive(omega) || !finitePositive(capacitance) ||
        !finitePositive(inductance) || std::abs(residue.imag()) > kAxisTolerance)
    {
        return false;
    }
    component = {FosterComponentType::ParallelLC, 0.0, capacitance,
                 inductance};
    return true;
}