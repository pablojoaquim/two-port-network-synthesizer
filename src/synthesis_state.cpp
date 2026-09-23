#include "synthesis_state.hpp"

SynthesisState::SynthesisState(const RationalFunction &rationalFunction)
    : rationalFunction_(rationalFunction), partial_(false)
{
}

const RationalFunction &SynthesisState::currentRationalFunction() const
{
    return rationalFunction_;
}

const std::vector<SynthesisStep> &SynthesisState::steps() const
{
    return steps_;
}

const std::string &SynthesisState::circuitRepresentation() const
{
    return circuitRepresentation_;
}

bool SynthesisState::isPartial() const
{
    return partial_;
}

void SynthesisState::recordRemoval(
    const RemovalOption &removal,
    const FosterComponent &component,
    const RationalFunction &updatedRationalFunction,
    const std::string &circuitRepresentation)
{
    steps_.push_back({removal, component});
    rationalFunction_ = updatedRationalFunction;
    circuitRepresentation_ = circuitRepresentation;
}

void SynthesisState::markPartial()
{
    partial_ = true;
}