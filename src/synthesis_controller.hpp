#ifndef SYNTHESIS_CONTROLLER_HPP
#define SYNTHESIS_CONTROLLER_HPP

#include <iosfwd>

#include "synthesis_state.hpp"

enum class SynthesisResult
{
    Complete,
    Partial,
    NoDecomposition
};

SynthesisResult runSynthesis(std::istream &input,
                             std::ostream &output,
                             SynthesisState &state);

#endif