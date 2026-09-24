#include "ascii_circuit.hpp"

#include <iomanip>
#include <sstream>

std::string buildAsciiCircuit(const std::vector<SynthesisStep> &steps)
{
    std::ostringstream output;
    output << "IN o";
    std::size_t rcIndex = 1U;
    std::size_t rlIndex = 1U;
    std::size_t lcIndex = 1U;
    std::size_t resistorIndex = 1U;
    std::size_t capacitorIndex = 1U;
    std::size_t inductorIndex = 1U;
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
        else if (step.component.type == FosterComponentType::ParallelRL)
        {
            output << "RL" << rlIndex++ << ": R="
                   << step.component.resistance << " ohm, L="
                   << step.component.inductance << " H";
        }
        else if (step.component.type == FosterComponentType::ParallelLC)
        {
            output << "LC" << lcIndex++ << ": L="
                   << step.component.inductance << " H, C="
                   << step.component.capacitance << " F";
        }
        else if (step.component.type == FosterComponentType::SeriesResistor)
        {
            output << "R" << resistorIndex++ << ": R="
                   << step.component.resistance << " ohm";
        }
        else if (step.component.type == FosterComponentType::SeriesCapacitor)
        {
            output << "C" << capacitorIndex++ << ": C="
                   << step.component.capacitance << " F";
        }
        else
        {
            output << "L" << inductorIndex++ << ": L="
                   << step.component.inductance << " H";
        }
        output << " ]";
    }
    output << "---o OUT";
    return output.str();
}