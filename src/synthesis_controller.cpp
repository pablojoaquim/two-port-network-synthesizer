#include "synthesis_controller.hpp"

#include <vector>

#include "foster.hpp"
#include "ascii_circuit.hpp"
#include "selection.hpp"
#include "synthesis_renderer.hpp"
#include "total_removal.hpp"

SynthesisResult runSynthesis(std::istream &input,
                             std::ostream &output,
                             SynthesisState &state)
{
    while (true)
    {
        const std::vector<RemovalOption> options =
            identifyRemovalOptions(state.currentRationalFunction());
        if (options.empty())
        {
            output << "Circuit:\n" << state.circuitRepresentation() << "\n";
            output << "SYNTHESIS COMPLETE\n";
            return SynthesisResult::Complete;
        }

        renderSynthesisInformation(output, state, options);
        output << "Select a removal or q: ";
        const SelectionResult selection =
            handleSelection(input, output, options, state);
        if (selection.status == SelectionStatus::Quit)
        {
            output << "PARTIAL SYNTHESIS\n";
            return SynthesisResult::Partial;
        }

        const RemovalOption &option = options[selection.optionIndex];
        FosterComponent component;
        if (!extractFosterComponent(state.currentRationalFunction(), option,
                                    component))
        {
            output << "No valid Foster decomposition is available.\n";
            return SynthesisResult::NoDecomposition;
        }

        RationalFunction updated = state.currentRationalFunction();
        if (!applyTotalRemoval(state.currentRationalFunction(), option,
                               component, updated))
        {
            output << "Removal validation failed.\n";
            return SynthesisResult::NoDecomposition;
        }
        std::vector<SynthesisStep> updatedSteps = state.steps();
        updatedSteps.push_back({option, component});
        state.recordRemoval(option, component, updated,
                            buildAsciiCircuit(updatedSteps));
        output << "Circuit:\n" << state.circuitRepresentation() << "\n";
        output << "Removal applied.\n";
    }
}