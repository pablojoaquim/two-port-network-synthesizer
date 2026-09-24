#ifndef TOTAL_REMOVAL_HPP
#define TOTAL_REMOVAL_HPP

#include "pole_analysis.hpp"
#include "foster.hpp"

bool validateTotalRemoval(const RationalFunction &rationalFunction,
                          const RemovalOption &candidate);
bool applyTotalRemoval(const RationalFunction &rationalFunction,
                       const RemovalOption &candidate,
                       const FosterComponent &component,
                       RationalFunction &remainingFunction);

#endif