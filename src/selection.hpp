#ifndef SELECTION_HPP
#define SELECTION_HPP

#include <cstddef>
#include <iosfwd>
#include <vector>

#include "synthesis_state.hpp"

enum class SelectionStatus
{
    Selected,
    Quit
};

struct SelectionResult
{
    SelectionStatus status;
    std::size_t optionIndex;
};

SelectionResult handleSelection(std::istream &input,
                                std::ostream &output,
                                const std::vector<RemovalOption> &options,
                                SynthesisState &state);

#endif