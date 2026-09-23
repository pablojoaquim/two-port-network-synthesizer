#ifndef POLYNOMIAL_HPP
#define POLYNOMIAL_HPP

#include <vector>

class Polynomial
{
public:
    explicit Polynomial(const std::vector<double> &coefficients);

    const std::vector<double> &coefficients() const;

    Polynomial operator+(const Polynomial &other) const;
    Polynomial operator*(const Polynomial &other) const;

private:
    std::vector<double> coefficients_;
};

#endif
