#include "ascii_circuit.hpp"

#include <iomanip>
#include <sstream>

std::string buildAsciiCircuit(const std::vector<SynthesisStep> &steps)
{
    std::ostringstream output;
    output << "IN o";
    std::size_t rcIndex = 1U;
    std::size_t lcIndex = 1U;
    for (const SynthesisStep &step : steps)
    {
        output << "---[ ";
        output << std::fixed << std::setprecision(2);
        if (step.component.type == FosterComponentType::ParallelRC)
        {
            output << "RC" << rcIndex++ << ": R="
                   << step.component.resistance << " ohm, C="
                   << step.component.capacitance << " F";
        }
        else
        {
            output << "LC" << lcIndex++ << ": L="
                   << step.component.inductance << " H, C="
                   << step.component.capacitance << " F";
        }
        output << " ]";
    }
    output << "---o OUT";
    return output.str();
}