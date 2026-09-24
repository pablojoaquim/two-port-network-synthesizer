#include "realizability.hpp"

#include <algorithm>
#include <cmath>
#include <complex>
#include <vector>

#include <contrib/Eigen/Polynomials>

#include "pole_analysis.hpp"

namespace
{
constexpr double kTolerance = 1.0e-8;

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
    std::complex<double> result(0.0, 0.0);
    const std::size_t degree = coefficients.size() - 1U;
    for (std::size_t index = 0U; index < degree; ++index)
    {
        result = result * value +
                 static_cast<double>(degree - index) * coefficients[index];
    }
    return result;
}

std::vector<double> ascending(const Polynomial &polynomial)
{
    std::vector<double> result = polynomial.coefficients();
    while (result.size() > 1U && std::abs(result.front()) <= kTolerance)
    {
        result.erase(result.begin());
    }
    std::reverse(result.begin(), result.end());
    return result;
}

std::vector<double> realPartNumerator(const RationalFunction &function)
{
    const std::vector<double> numerator = ascending(function.numerator());
    const std::vector<double> denominator = ascending(function.denominator());
    std::vector<double> result(
        (numerator.size() + denominator.size()) / 2U, 0.0);
    const std::complex<double> imaginaryUnit(0.0, 1.0);
    for (std::size_t first = 0U; first < numerator.size(); ++first)
    {
        for (std::size_t second = 0U; second < denominator.size(); ++second)
        {
            const std::size_t power = first + second;
            if (power % 2U != 0U)
            {
                continue;
            }
            const std::complex<double> factor =
                std::pow(imaginaryUnit, static_cast<int>(first)) *
                std::pow(-imaginaryUnit, static_cast<int>(second));
            result[power / 2U] +=
                numerator[first] * denominator[second] * factor.real();
        }
    }
    while (result.size() > 1U && std::abs(result.back()) <= kTolerance)
    {
        result.pop_back();
    }
    return result;
}

double evaluateAscending(const std::vector<double> &coefficients, double value)
{
    double result = 0.0;
    for (auto coefficient = coefficients.rbegin();
         coefficient != coefficients.rend(); ++coefficient)
    {
        result = result * value + *coefficient;
    }
    return result;
}

bool isNonNegativeForNonNegativeArguments(
    const std::vector<double> &coefficients)
{
    bool allZero = true;
    for (const double coefficient : coefficients)
    {
        allZero = allZero && std::abs(coefficient) <= kTolerance;
    }
    if (allZero)
    {
        return true;
    }
    if (coefficients.size() == 1U)
    {
        return coefficients[0] >= -kTolerance;
    }

    Eigen::VectorXd polynomial(static_cast<Eigen::Index>(coefficients.size()));
    for (Eigen::Index index = 0; index < polynomial.size(); ++index)
    {
        polynomial[index] = coefficients[static_cast<std::size_t>(index)];
    }
    const Eigen::PolynomialSolver<double, Eigen::Dynamic> solver(polynomial);
    std::vector<double> boundaries = {0.0};
    for (Eigen::Index index = 0; index < solver.roots().size(); ++index)
    {
        const std::complex<double> root = solver.roots()[index];
        if (std::abs(root.imag()) <= kTolerance && root.real() > kTolerance)
        {
            boundaries.push_back(root.real());
        }
    }
    std::sort(boundaries.begin(), boundaries.end());

    for (std::size_t index = 0U; index < boundaries.size(); ++index)
    {
        const double sample = index + 1U < boundaries.size()
                                  ? (boundaries[index] + boundaries[index + 1U]) / 2.0
                                  : boundaries[index] +
                                        std::max(1.0, boundaries[index]);
        if (evaluateAscending(coefficients, sample) < -kTolerance)
        {
            return false;
        }
    }
    return evaluateAscending(coefficients, 0.0) >= -kTolerance;
}
}

bool validateFosterRealizability(const RationalFunction &rationalFunction,
                                 std::string &errorMessage)
{
    errorMessage.clear();
    const std::vector<RemovalOption> poles =
        identifyDenominatorPoles(rationalFunction);
    for (const RemovalOption &pole : poles)
    {
        if (pole.multiplicity != 1U)
        {
            errorMessage = "Foster synthesis requires simple poles";
            return false;
        }
        if (pole.pole.real() > kTolerance)
        {
            errorMessage = "right-half-plane poles are not realizable";
            return false;
        }
        if (std::abs(pole.pole.real()) > kTolerance &&
            std::abs(pole.pole.imag()) > kTolerance)
        {
            errorMessage = "off-axis complex poles are unsupported";
            return false;
        }

        const std::complex<double> derivative =
            derivativeAt(rationalFunction.denominator(), pole.pole);
        const std::complex<double> residue =
            evaluate(rationalFunction.numerator(), pole.pole) / derivative;
        if (!std::isfinite(residue.real()) || !std::isfinite(residue.imag()) ||
            std::abs(residue) <= kTolerance)
        {
            errorMessage = "denominator pole has no removable Foster residue";
            return false;
        }
        if (std::abs(pole.pole.real()) <= kTolerance &&
            (std::abs(residue.imag()) > kTolerance ||
             residue.real() <= kTolerance))
        {
            errorMessage = "imaginary-axis poles require positive real residues";
            return false;
        }
    }

    if (!isNonNegativeForNonNegativeArguments(
            realPartNumerator(rationalFunction)))
    {
        errorMessage = "impedance is not positive real";
        return false;
    }
    return true;
}