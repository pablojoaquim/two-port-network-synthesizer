#include "synthesis_renderer.hpp"

#include <cmath>
#include <iomanip>
#include <ostream>

namespace
{
void renderPolynomial(std::ostream &output, const Polynomial &polynomial)
{
    const std::vector<double> &coefficients = polynomial.coefficients();
    for (std::size_t index = 0U; index < coefficients.size(); ++index)
    {
        if (index != 0U)
        {
            output << (coefficients[index] < 0.0 ? " - " : " + ");
        }
        else if (coefficients[index] < 0.0)
        {
            output << '-';
        }

        output << std::fixed << std::setprecision(2)
               << std::abs(coefficients[index]);
        const std::size_t power = coefficients.size() - index - 1U;
        if (power > 0U)
        {
            output << "s";
            if (power > 1U)
            {
                output << "^" << power;
            }
        }
    }
}

void renderComponent(std::ostream &output, const FosterComponent &component)
{
    if (component.type == FosterComponentType::ParallelRC)
    {
        output << "parallel RC (R=" << std::fixed << std::setprecision(2)
               << component.resistance << " ohm, C=" << component.capacitance
               << " F)";
    }
    else
    {
        output << "parallel LC (L=" << std::fixed << std::setprecision(2)
               << component.inductance << " H, C=" << component.capacitance
               << " F)";
    }
}
}

void renderSynthesisInformation(std::ostream &output,
                                const SynthesisState &state,
                                const std::vector<RemovalOption> &options)
{
    const RationalFunction &rationalFunction =
        state.currentRationalFunction();
    output << "Current impedance: ";
    renderPolynomial(output, rationalFunction.numerator());
    output << " / ";
    renderPolynomial(output, rationalFunction.denominator());
    output << "\n";

    output << "Available removals:\n";
    for (const RemovalOption &option : options)
    {
        output << option.index << ": " << std::fixed << std::setprecision(2)
               << option.pole.real();
        if (std::abs(option.pole.imag()) > 1.0e-8)
        {
            output << (option.pole.imag() >= 0.0 ? " + j" : " - j")
                   << std::abs(option.pole.imag());
        }
        output << " (multiplicity " << option.multiplicity << ")\n";
    }

    output << "Removal sequence:\n";
    if (state.steps().empty())
    {
        output << "none\n";
    }
    for (std::size_t index = 0U; index < state.steps().size(); ++index)
    {
        const SynthesisStep &step = state.steps()[index];
        output << index << ": pole " << std::fixed << std::setprecision(2)
               << step.removal.pole.real();
        if (std::abs(step.removal.pole.imag()) > 1.0e-8)
        {
            output << (step.removal.pole.imag() >= 0.0 ? " + j" : " - j")
                   << std::abs(step.removal.pole.imag());
        }
        output << ", ";
        renderComponent(output, step.component);
        output << "\n";
    }
}