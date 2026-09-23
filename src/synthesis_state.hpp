#ifndef SYNTHESIS_STATE_HPP
#define SYNTHESIS_STATE_HPP

#include <string>
#include <vector>

#include "foster.hpp"

struct SynthesisStep
{
    RemovalOption removal;
    FosterComponent component;
};

class SynthesisState
{
public:
    explicit SynthesisState(const RationalFunction &rationalFunction);

    const RationalFunction &currentRationalFunction() const;
    const std::vector<SynthesisStep> &steps() const;
    const std::string &circuitRepresentation() const;
    bool isPartial() const;

    void recordRemoval(const RemovalOption &removal,
                       const FosterComponent &component,
                       const RationalFunction &updatedRationalFunction,
                       const std::string &circuitRepresentation);
    void markPartial();

private:
    RationalFunction rationalFunction_;
    std::vector<SynthesisStep> steps_;
    std::string circuitRepresentation_;
    bool partial_;
};

#endif