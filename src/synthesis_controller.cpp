#include "synthesis_controller.hpp"

#include <cmath>
#include <complex>
#include <vector>

#include "foster.hpp"
#include "ascii_circuit.hpp"
#include "selection.hpp"
#include "synthesis_renderer.hpp"

namespace
{
std::vector<double> subtract(const std::vector<double> &first,
                             const std::vector<double> &second)
{
    const std::size_t size = std::max(first.size(), second.size());
    std::vector<double> result(size, 0.0);
    const std::size_t firstOffset = size - first.size();
    const std::size_t secondOffset = size - second.size();
    for (std::size_t index = 0U; index < first.size(); ++index)
    {
        result[firstOffset + index] += first[index];
    }
    for (std::size_t index = 0U; index < second.size(); ++index)
    {
        result[secondOffset + index] -= second[index];
    }
    while (result.size() > 1U && std::abs(result.front()) <= 1.0e-10)
    {
        result.erase(result.begin());
    }
    return result;
}

std::vector<double> multiply(const std::vector<double> &first,
                             const std::vector<double> &second)
{
    std::vector<double> result(first.size() + second.size() - 1U, 0.0);
    for (std::size_t firstIndex = 0U; firstIndex < first.size(); ++firstIndex)
    {
        for (std::size_t secondIndex = 0U;
             secondIndex < second.size(); ++secondIndex)
        {
            result[firstIndex + secondIndex] +=
                first[firstIndex] * second[secondIndex];
        }
    }
    return result;
}

std::vector<double> divideByFactor(const std::vector<double> &polynomial,
                                   const std::vector<double> &factor)
{
    std::vector<double> work = polynomial;
    std::vector<double> quotient(polynomial.size() - factor.size() + 1U,
                                 0.0);
    for (std::size_t index = 0U;
         index + factor.size() <= work.size(); ++index)
    {
        const double scale = work[index] / factor.front();
        quotient[index] = scale;
        for (std::size_t factorIndex = 0U; factorIndex < factor.size();
             ++factorIndex)
        {
            work[index + factorIndex] -= scale * factor[factorIndex];
        }
    }
    while (quotient.size() > 1U && std::abs(quotient.front()) <= 1.0e-10)
    {
        quotient.erase(quotient.begin());
    }
    return quotient;
}

RationalFunction removeComponent(const RationalFunction &rationalFunction,
                                 const RemovalOption &option,
                                 const FosterComponent &component)
{
    std::vector<double> factor;
    std::vector<double> termNumerator;
    if (component.type == FosterComponentType::ParallelRC)
    {
        const double a = -option.pole.real();
        factor = {1.0, a};
        termNumerator = {1.0 / component.capacitance};
    }
    else
    {
        const double omega = std::abs(option.pole.imag());
        factor = {1.0, 0.0, omega * omega};
        termNumerator = {1.0 / component.capacitance, 0.0};
    }

    const std::vector<double> numerator = rationalFunction.numerator().coefficients();
    const std::vector<double> denominator = rationalFunction.denominator().coefficients();
    const std::vector<double> unreducedNumerator = subtract(
        multiply(numerator, factor), multiply(termNumerator, denominator));
    const std::vector<double> updatedNumerator =
        divideByFactor(unreducedNumerator, factor);
    const std::vector<double> reducedDenominator =
        divideByFactor(denominator, factor);
    return RationalFunction(Polynomial(updatedNumerator),
                            Polynomial(reducedDenominator));
}

}

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

        const RationalFunction updated = removeComponent(
            state.currentRationalFunction(), option, component);
        std::vector<SynthesisStep> updatedSteps = state.steps();
        updatedSteps.push_back({option, component});
        state.recordRemoval(option, component, updated,
                            buildAsciiCircuit(updatedSteps));
        output << "Circuit:\n" << state.circuitRepresentation() << "\n";
        output << "Removal applied.\n";
    }
}