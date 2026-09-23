#include "pole_analysis.hpp"

#include <algorithm>
#include <cmath>
#include <complex>
#include <cstddef>
#include <vector>

#include <contrib/Eigen/Polynomials>

namespace
{
constexpr double kResidualTolerance = 1.0e-10;
constexpr double kRepeatedRootTolerance = 1.0e-8;

std::vector<double> ascendingCoefficients(const Polynomial &polynomial)
{
    std::vector<double> coefficients = polynomial.coefficients();
    while (!coefficients.empty() && coefficients.front() == 0.0)
    {
        coefficients.erase(coefficients.begin());
    }
    std::reverse(coefficients.begin(), coefficients.end());
    return coefficients;
}

double polynomialMagnitude(const std::vector<double> &coefficients,
                           const std::complex<double> &value)
{
    double magnitude = 0.0;
    double valuePower = 1.0;
    for (const double coefficient : coefficients)
    {
        magnitude += std::abs(coefficient) * valuePower;
        valuePower *= std::abs(value);
    }
    return magnitude;
}

std::complex<double> evaluatePolynomial(
    const std::vector<double> &coefficients,
    const std::complex<double> &value)
{
    std::complex<double> result(0.0, 0.0);
    for (auto coefficient = coefficients.rbegin();
         coefficient != coefficients.rend(); ++coefficient)
    {
        result = result * value + *coefficient;
    }
    return result;
}

bool isRoot(const std::vector<double> &coefficients,
            const std::complex<double> &value)
{
    const double scale = polynomialMagnitude(coefficients, value);
    return std::abs(evaluatePolynomial(coefficients, value)) <=
           kResidualTolerance * scale;
}

bool comesBefore(const std::complex<double> &first,
                 const std::complex<double> &second)
{
    if (first.real() != second.real())
    {
        return first.real() < second.real();
    }
    return first.imag() < second.imag();
}

bool belongsToGroup(const std::complex<double> &value,
                    const std::complex<double> &representative)
{
    const double scale = std::max(
        1.0, std::max(std::abs(value), std::abs(representative)));
    return std::abs(value - representative) <=
           kRepeatedRootTolerance * scale;
}
}

std::vector<RemovalOption> identifyRemovalOptions(
    const RationalFunction &rationalFunction)
{
    const std::vector<double> coefficients =
        ascendingCoefficients(rationalFunction.denominator());
    if (coefficients.size() <= 1U)
    {
        return std::vector<RemovalOption>();
    }

    Eigen::VectorXd polynomial(static_cast<Eigen::Index>(coefficients.size()));
    for (Eigen::Index index = 0; index < polynomial.size(); ++index)
    {
        polynomial[index] = coefficients[static_cast<std::size_t>(index)];
    }

    const Eigen::PolynomialSolver<double, Eigen::Dynamic> solver(polynomial);
    std::vector<std::complex<double>> roots;
    roots.reserve(static_cast<std::size_t>(solver.roots().size()));
    for (Eigen::Index index = 0; index < solver.roots().size(); ++index)
    {
        const std::complex<double> root = solver.roots()[index];
        if (isRoot(coefficients, root))
        {
            roots.push_back(root);
        }
    }
    std::sort(roots.begin(), roots.end(), comesBefore);

    std::vector<RemovalOption> options;
    for (const std::complex<double> &root : roots)
    {
        bool added = false;
        for (RemovalOption &option : options)
        {
            if (belongsToGroup(root, option.pole))
            {
                ++option.multiplicity;
                added = true;
                break;
            }
        }
        if (!added)
        {
            options.push_back(
                {options.size(), root, 1U});
        }
    }

    return options;
}
