#ifndef REALIZABILITY_HPP
#define REALIZABILITY_HPP

#include <string>

#include "rational_function.hpp"

bool validateFosterRealizability(const RationalFunction &rationalFunction,
                                 std::string &errorMessage);

#endif