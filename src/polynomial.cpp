#include "polynomial.hpp"

#include <cstddef>

Polynomial::Polynomial(const std::vector<double> &coefficients)
    : coefficients_(coefficients)
{
}

const std::vector<double> &Polynomial::coefficients() const
{
    return coefficients_;
}

Polynomial Polynomial::operator+(const Polynomial &other) const
{
    const std::size_t resultSize = coefficients_.size() > other.coefficients_.size()
                                       ? coefficients_.size()
                                       : other.coefficients_.size();
    std::vector<double> result(resultSize, 0.0);
    const std::size_t firstOffset = resultSize - coefficients_.size();
    const std::size_t secondOffset = resultSize - other.coefficients_.size();

    for (std::size_t index = 0U; index < coefficients_.size(); ++index)
    {
        result[firstOffset + index] += coefficients_[index];
    }
    for (std::size_t index = 0U; index < other.coefficients_.size(); ++index)
    {
        result[secondOffset + index] += other.coefficients_[index];
    }

    return Polynomial(result);
}

Polynomial Polynomial::operator*(const Polynomial &other) const
{
    if (coefficients_.empty() || other.coefficients_.empty())
    {
        return Polynomial(std::vector<double>());
    }

    std::vector<double> result(coefficients_.size() + other.coefficients_.size() - 1U,
                               0.0);
    for (std::size_t firstIndex = 0U; firstIndex < coefficients_.size();
         ++firstIndex)
    {
        for (std::size_t secondIndex = 0U;
             secondIndex < other.coefficients_.size(); ++secondIndex)
        {
            result[firstIndex + secondIndex] +=
                coefficients_[firstIndex] * other.coefficients_[secondIndex];
        }
    }

    return Polynomial(result);
}
