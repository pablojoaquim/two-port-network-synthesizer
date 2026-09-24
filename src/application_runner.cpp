#include "application_runner.hpp"

#include <string>

#include "cli_parser.hpp"
#include "polynomial.hpp"
#include "realizability.hpp"
#include "rational_function.hpp"
#include "synthesis_controller.hpp"
#include "synthesis_state.hpp"

int runApplication(int argc, char *argv[], std::istream &input,
                   std::ostream &output, std::ostream &errors)
{
    ParsedInput parsedInput;
    std::string errorMessage;
    if (!parseCommandLine(argc, argv, parsedInput, errorMessage))
    {
        errors << "Error: " << errorMessage << '\n';
        return 1;
    }

    const RationalFunction rationalFunction(
        Polynomial(parsedInput.numerator),
        Polynomial(parsedInput.denominator));
    if (!validateFosterRealizability(rationalFunction, errorMessage))
    {
        errors << "Error: " << errorMessage << '\n';
        return 1;
    }
    SynthesisState state(rationalFunction);
    runSynthesis(input, output, state);
    return 0;
}