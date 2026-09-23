#ifndef SYNTHESIS_RENDERER_HPP
#define SYNTHESIS_RENDERER_HPP

#include <iosfwd>
#include <vector>

#include "synthesis_state.hpp"

void renderSynthesisInformation(std::ostream &output,
                                const SynthesisState &state,
                                const std::vector<RemovalOption> &options);

#endif