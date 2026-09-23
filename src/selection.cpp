#include "selection.hpp"

#include <cctype>
#include <limits>
#include <sstream>
#include <string>

namespace
{
bool parseIndex(const std::string &value, std::size_t &index)
{
    std::istringstream stream(value);
    stream >> index;
    return !stream.fail() && stream.eof();
}
}

SelectionResult handleSelection(
    std::istream &input,
    std::ostream &output,
    const std::vector<RemovalOption> &options,
    SynthesisState &state)
{
    std::string line;
    while (std::getline(input, line))
    {
        if (line == "q")
        {
            state.markPartial();
            return {SelectionStatus::Quit, 0U};
        }

        std::size_t selectedIndex = 0U;
        bool valid = parseIndex(line, selectedIndex);
        if (valid)
        {
            for (const RemovalOption &option : options)
            {
                if (option.index == selectedIndex)
                {
                    return {SelectionStatus::Selected, selectedIndex};
                }
            }
        }

        output << "Invalid selection. Try again: ";
    }

    state.markPartial();
    return {SelectionStatus::Quit, 0U};
}