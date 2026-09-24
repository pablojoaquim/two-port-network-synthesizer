#ifndef FOSTER_HPP
#define FOSTER_HPP

#include "pole_analysis.hpp"

enum class FosterComponentType
{
    ParallelRC,
    ParallelRL,
    ParallelLC,
    SeriesResistor,
    SeriesCapacitor,
    SeriesInductor
};

struct FosterComponent
{
    FosterComponentType type;
    double resistance;
    double capacitance;
    double inductance;
};

bool extractFosterComponent(const RationalFunction &rationalFunction,
                            const RemovalOption &option,
                            FosterComponent &component);

#endif