#ifndef ASCII_CIRCUIT_HPP
#define ASCII_CIRCUIT_HPP

#include <string>
#include <vector>

#include "synthesis_state.hpp"

std::string buildAsciiCircuit(const std::vector<SynthesisStep> &steps);

#endif