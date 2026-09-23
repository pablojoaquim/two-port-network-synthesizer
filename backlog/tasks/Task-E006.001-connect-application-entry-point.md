# Task E006.001 — Connect the Application Entry Point to Synthesis

## Objective

Connect command-line parsing to the existing rational-function model and synthesis controller.

## Context

`main.cpp` currently validates the command-line vectors and exits without constructing a `RationalFunction`, creating a `SynthesisState`, or invoking `runSynthesis`.

## Requirements

- Preserve the existing command-line validation and error reporting.
- Construct the initial `Polynomial` objects and `RationalFunction` from parsed coefficients.
- Create the initial `SynthesisState` and invoke the existing synthesis controller using standard input and output.
- Preserve the existing behavior for invalid command-line input.

## Design References

- README.md: Input and Synthesis Process
- docs/sdd.md: Sections 3, 4, 5, and 7
- src/main.cpp
- src/synthesis_controller.hpp

## Acceptance Criteria

- [ ] Valid command-line input starts the synthesis workflow.
- [ ] The initial impedance and available removal options are displayed by the executable.
- [ ] Interactive input reaches the synthesis controller.
- [ ] Invalid command-line input terminates before synthesis begins.

## Tests

Add focused entry-point or application-runner tests for valid input, `q`, and invalid input.

## Definition of Done

The executable is connected to the implemented synthesis workflow and focused tests pass.

## Dependencies

- Task E003.003
- Task E004.001
- Task E004.002