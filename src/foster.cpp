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

double residualSeriesResistance(const RationalFunction &rationalFunction)
{
    const std::vector<double> &numerator =
        rationalFunction.numerator().coefficients();
    const std::vector<double> &denominator =
        rationalFunction.denominator().coefficients();
    double resistance = numerator.front() / denominator.front();
    const std::vector<RemovalOption> poles =
        identifyDenominatorPoles(rationalFunction);
    for (const RemovalOption &pole : poles)
    {
        if (pole.multiplicity != 1U ||
            std::abs(pole.pole.imag()) > kAxisTolerance ||
            pole.pole.real() >= -kAxisTolerance)
        {
            continue;
        }
        const std::complex<double> residue =
            evaluate(rationalFunction.numerator(), pole.pole) /
            derivativeAt(rationalFunction.denominator(), pole.pole);
        if (residue.real() < 0.0 && std::abs(residue.imag()) <= kAxisTolerance)
        {
            resistance -= -residue.real() / -pole.pole.real();
        }
    }
    return resistance;
}
}

bool extractFosterComponent(const RationalFunction &rationalFunction,
                            const RemovalOption &option,
                            FosterComponent &component)
{
    const std::vector<double> &numerator =
        rationalFunction.numerator().coefficients();
    const std::vector<double> &denominator =
        rationalFunction.denominator().coefficients();
    if (option.location == RemovalLocation::Infinity)
    {
        if (numerator.size() != denominator.size() + 1U)
        {
            return false;
        }
        const double inductance = numerator.front() / denominator.front();
        if (!finitePositive(inductance))
        {
            return false;
        }
        component = {FosterComponentType::SeriesInductor, 0.0, 0.0,
                     inductance};
        return true;
    }
    if (option.location == RemovalLocation::Constant)
    {
        if (numerator.size() != denominator.size())
        {
            return false;
        }
        const double resistance = residualSeriesResistance(rationalFunction);
        if (!std::isfinite(resistance) || resistance < 0.0)
        {
            return false;
        }
        component = {FosterComponentType::SeriesResistor, resistance,
                     0.0, 0.0};
        return true;
    }

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
        if (std::abs(residue.imag()) > kAxisTolerance)
        {
            return false;
        }
        if (std::abs(a) <= kAxisTolerance)
        {
            const double capacitance = 1.0 / residue.real();
            if (!finitePositive(capacitance))
            {
                return false;
            }
            component = {FosterComponentType::SeriesCapacitor, 0.0,
                         capacitance, 0.0};
            return true;
        }
        if (!finitePositive(a))
        {
            return false;
        }
        if (residue.real() > 0.0)
        {
            const double capacitance = 1.0 / residue.real();
            const double resistance = residue.real() / a;
            if (!finitePositive(capacitance) || !finitePositive(resistance))
            {
                return false;
            }
            component = {FosterComponentType::ParallelRC, resistance,
                         capacitance, 0.0};
            return true;
        }

        const double resistance = -residue.real() / a;
        const double inductance = resistance / a;
        if (!finitePositive(resistance) || !finitePositive(inductance))
        {
            return false;
        }
        component = {FosterComponentType::ParallelRL, resistance, 0.0,
                     inductance};
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