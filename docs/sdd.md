# Software Design Document

## 1. Purpose

Define the minimal design for a command-line tool that interactively synthesizes an LTI two-port network from a rational function.

## 2. Scope

The system accepts numerator and denominator polynomial coefficients, analyzes the resulting rational function, and performs successive total removals until no poles remain or the user enters `q`.

The system displays each synthesis step and the resulting circuit in the terminal using ASCII diagrams. The final output includes the synthesized circuit, component values, and removal sequence accumulated during the session.

## 3. Requirements

### Functional Requirements

The system shall:

1. Accept numerator and denominator coefficient vectors as command-line arguments.
2. Interpret coefficients in descending powers of `s`.
3. Represent the input as a rational function:

   $$
   H(s) = \frac{N(s)}{D(s)}
   $$

4. Reject missing, malformed, incompatible, or non-finite command-line arguments by displaying an error message and terminating before synthesis begins.
5. Display the current rational function and synthesis state.
6. Determine and display available total-removal options.
7. Accept the user's removal selection or `q` to finish interactively.
8. Validate a total removal by ensuring that the remaining network has no pole at the frequency of that removal.
9. Use the Foster method to determine the removed component's type and value.
10. Update the rational function and synthesis state after a removal.
11. Display each synthesis step as terminal text and ASCII graphics.
12. Stop when no poles remain or when the user enters `q`.
13. Display the accumulated removal sequence, component values, and circuit representation when the process ends.

### Non-Functional Requirements

- The application shall run in a terminal.
- The implementation shall use C.
- The C standard library should be used whenever possible.
- External dependencies shall be minimal or absent.
- Floating-point values shall be used for polynomial and component calculations.
- Two decimal places are sufficient for calculated and displayed values.
- The design should allow additional synthesis methods and network representations in the future.

## 4. Architecture

The application is organized as a small pipeline coordinated by an interactive synthesis controller:

1. Parse command-line arguments into polynomial coefficient vectors.
2. Build the initial rational-function model.
3. Analyze the current state and determine removal options.
4. Present the state and options to the user.
5. Apply the selected removal using Foster-based component extraction.
6. Record the result and render the updated state.
7. Repeat until the completion criteria are met.

## 5. Components

### Command-Line Input

Parses the numerator and denominator vectors supplied to the application.

### Polynomial and Rational-Function Model

Stores floating-point polynomial coefficients and the current numerator and denominator. Provides the polynomial operations needed to update the rational function.

### Synthesis Analysis

Identifies available poles and total-removal options. Determines whether a selected removal is valid and uses the Foster method to obtain the component type and value.

### Synthesis State

Stores the current rational function, selected removals, extracted components, and current circuit representation.

### Synthesis Controller

Coordinates the interactive loop, user selections, state updates, and completion checks.

### Terminal Renderer

Displays rational functions, synthesis states, available choices, intermediate steps, component values, and final ASCII circuit diagrams.

## 6. Interfaces

### Command-Line Interface

The application is invoked as:

```text
application [numerator coefficients][denominator coefficients]
```

Example:

```text
application [1,1,2][2,1,3]
```

The first vector is the numerator and the second vector is the denominator. Coefficients are ordered from highest to lowest power of `s`.

### Interactive Interface

At each synthesis step, the application displays the available removal options and accepts the user's selection. The user may enter `q` to finish interactively.

### Internal Interfaces

- The rational-function model provides the current polynomials to synthesis analysis.
- Synthesis analysis returns available removal options and the component type and value for a valid removal.
- The controller applies a selected removal and updates the synthesis state.
- The renderer receives state data and produces terminal output.

## 7. Data Flow

```text
Command-line arguments
	-> polynomial vectors
	-> rational-function model
	-> synthesis analysis
	-> removal options and current state
	-> user selection
	-> Foster component extraction
	-> updated rational function and synthesis state
	-> terminal rendering
```

The analysis-render-selection-update sequence repeats until no poles remain or the user enters `q`.

## 8. Constraints

- The input consists of numerator and denominator coefficient vectors.
- Coefficients are specified in descending powers of `s`.
- Calculations use floating-point values with two decimal places sufficient for precision and display.
- Coefficients must be finite floating-point values. `NaN`, positive infinity, and negative infinity are invalid input.
- A valid total removal leaves no pole in the remaining network at the removal frequency.
- Component type and value are obtained using the Foster method.
- The application is terminal-based and uses ASCII diagrams.
- The implementation targets C and a WSL environment.
- The implementation should avoid unnecessary external dependencies.

## 9. Technology Decisions

- Use C as the implementation language.
- Prefer the C standard library for parsing, numerical handling, interaction, and output.
- Use command-line arguments for the two input coefficient vectors.
- Use terminal text and ASCII diagrams for visualization.

## 10. Testing Strategy

Testing shall cover the defined mathematical and workflow behavior, including:

- Parsing the two coefficient-vector arguments.
- Polynomial and rational-function operations.
- Detection of available poles and valid total removals.
- Foster component type and value extraction.
- State updates after a removal.
- Termination when no poles remain.
- Termination when the user enters `q`.
- Rendering of intermediate and final synthesis information.

The exact test framework and build commands remain unspecified.

## 11. Definition of Done

The initial implementation is complete when it can:

- Accept the documented command-line input format.
- Represent the input rational function using floating-point coefficients.
- Run the interactive total-removal workflow.
- Identify valid removals according to the no-remaining-pole condition.
- Obtain component types and values using the Foster method.
- Stop when no poles remain or when `q` is entered.
- Display the removal sequence, component values, and ASCII circuit representation.
- Build and run in the intended C and WSL environment.

## 12. Risks

- Floating-point calculations may affect pole detection and component values.
- The supported magnitude range for finite coefficients has not been defined.
- The exact circuit and ASCII representations may evolve as synthesis capabilities are implemented.
- The mathematical details required for all synthesis cases may require refinement during implementation.

## 13. Open Decisions

- Supported magnitude range for finite coefficients.
- Exact rules for invalid interactive selections.
- Exact Foster decomposition procedures for all supported network cases.
- Exact component and network topology notation in intermediate and final ASCII diagrams.
- Whether an early `q` result is labeled as partial synthesis or complete output.
- Exact build commands and test framework.