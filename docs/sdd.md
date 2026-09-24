# Software Design Document

## 1. Purpose

Define the minimal design for a command-line tool that interactively synthesizes a one-port LTI impedance from a rational function using Foster-I synthesis.

## 2. Scope

The system accepts numerator and denominator polynomial coefficients, analyzes the resulting one-port impedance, and performs successive Foster-I total removals until no terms remain or the user enters `q`. Admittance and terminated two-port synthesis are outside the current scope.

The system displays each synthesis step and the resulting circuit in the terminal using ASCII diagrams. The final output includes the synthesized circuit, component values, and removal sequence accumulated during the session.

## 3. Requirements

### Functional Requirements

The system shall:

1. Accept numerator and denominator coefficient vectors as command-line arguments.
2. Interpret coefficients in descending powers of `s`.
3. Represent the input impedance as a rational function:

   $$
	Z(s) = \frac{N(s)}{D(s)}
   $$

4. Reject missing, malformed, incompatible, or non-finite command-line arguments by displaying an error message and terminating before synthesis begins.
5. Display the current rational function and synthesis state.
6. Determine and display available total-removal options.
7. Accept the user's removal selection or `q` to finish interactively.
8. Validate a total removal by ensuring that the remaining network has no pole at the frequency of that removal.
9. Use the Foster method for impedance to determine the removed component's type and value.
10. If no valid Foster decomposition is available for the current state, report that no removal can be performed and stop synthesis.
11. Update the rational function and synthesis state after a removal.
12. Display each synthesis step as terminal text and ASCII graphics.
13. Stop when no poles remain or when the user enters `q`.
14. Label output produced after `q` as partial synthesis.
15. Display the accumulated removal sequence, component values, and circuit representation when the process ends.

### Non-Functional Requirements

- The application shall run in a terminal.
- The implementation shall use C++17.
- The C++ standard library should be used whenever possible.
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

Entering `q` intentionally terminates the session. The application displays the accumulated result and labels it as partial synthesis.

### Internal Interfaces

- The rational-function model provides the current polynomials to synthesis analysis.
- Synthesis analysis returns available removal options. Each option contains an internal selection index and the associated pole value.
- Pole values are represented as complex floating-point values; a real pole has zero imaginary part.
- Repeated poles are represented with multiplicity information.
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
- The rational function always represents impedance.
- The supported realization is Foster-I one-port impedance synthesis. Foster-II
	admittance and terminated two-port synthesis are unsupported.
- Coefficients are specified in descending powers of `s`.
- Calculations use floating-point values with two decimal places sufficient for precision and display.
- Coefficients must be finite floating-point values. `NaN`, positive infinity, and negative infinity are invalid input.
- Finite coefficients may use any value representable by the implementation's floating-point type.
- A valid total removal leaves no pole in the remaining network at the removal frequency.
- A total removal is valid only when the remaining impedance has no pole at the
	selected frequency; the selected pole must therefore be fully removed.
- A denominator root is treated as a pole unless cancellation behavior is explicitly defined.
- Common numerator and denominator factors are not canceled. A denominator root
	with zero residue is therefore unsupported rather than silently removed.
- Foster impedance extraction supports real negative poles and conjugate pole
	pairs on the $j\omega$ axis. A real pole $p=-a$ with residue $K$ contributes
	$K/(s+a)$ and is represented by a parallel RC branch with
	$C=1/K$ and $R=K/a$. A conjugate pair at $\pm j\omega_0$ contributes
	$Ks/(s^2+\omega_0^2)$ and is represented by a parallel LC branch with
	$C=1/K$ and $L=K/\omega_0^2$.
- Component values must be finite and positive; unsupported pole locations or
	non-positive residues have no valid Foster decomposition.
- A finite real pole $p=-a$ with positive residue $K$ is a parallel RC term
	$K/(s+a)$ with $C=1/K$ and $R=K/a$. A negative residue $-Ka$ is a parallel
	RL term $Ks/(s+a)$ with $R=K$ and $L=K/a$.
- A pole at zero contributes a series capacitor term $K_0/s$ with $C=1/K_0$.
	A pole at infinity contributes a series inductor term $K_\infty s$ with
	$L=K_\infty$. A non-negative constant polynomial term is a series resistor.
- The Foster-I impedance is the series sum of endpoint terms, finite parallel
	RC/RL branches, and finite parallel LC branches. Reactive values must be
	finite and positive; resistance values must be finite and non-negative.
- Invalid interactive selections produce an error message and reprompt without changing the synthesis state.
- The application is terminal-based and uses ASCII diagrams.
- Intermediate and final circuit diagrams use consistent ASCII labels for components, terminals, connections, and ground.
- Circuit diagrams use `IN` and `OUT` terminals, series-ordered Foster branches,
	deterministic `RC1`, `RL1`, `LC1`, `R1`, `C1`, `L1`, and subsequent labels, and `GND` when a
	grounded representation is needed. A branch is rendered as
	`[ RC1: R=10.00 ohm, C=0.10 F ]`,
	`[ RL1: R=1.00 ohm, L=1.00 H ]`, or
	`[ LC1: L=1.00 H, C=1.00 F ]`; endpoint components use `R`, `C`, or `L`
	labels and multiple components are joined with `---`.
- Intermediate and final diagrams use the same notation and display component
	values to two decimal places.
- The implementation targets C and a WSL environment.
- External dependencies should remain minimal; Eigen is required for polynomial root solving.

## 9. Technology Decisions

- Use C++17 as the implementation language.
- Prefer the C++ standard library for parsing, numerical handling, interaction, and output.
- Use command-line arguments for the two input coefficient vectors.
- Use terminal text and ASCII diagrams for visualization.
- Use the repository Makefile as the build entry point.
- Use the Acutest-based test suite through the Makefile test targets.
- Represent poles as complex floating-point values and expose removal options through an internal selection index and pole value.
- Use Eigen's `PolynomialSolver` for denominator roots through a companion-matrix eigenvalue calculation.
- Use a scale-aware pole residual tolerance of `1e-10`.
- Group repeated roots when their distance is at most `1e-8 * max(1, |p_i|, |p_j|)`.

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
- Build with `make` or `make all` and execute tests with `make run-tests`.

The test framework is Acutest. The repository build commands are `make all`
and `make run-tests` in WSL.

## 11. Definition of Done

The initial implementation is complete when it can:

- Accept the documented command-line input format.
- Represent the input rational function using floating-point coefficients.
- Run the interactive total-removal workflow.
- Identify valid removals according to the no-remaining-pole condition.
- Obtain component types and values using the Foster method.
- Stop when no poles remain or when `q` is entered.
- Label a result terminated by `q` as partial synthesis.
- Display the removal sequence, component values, and ASCII circuit representation.
- Build with the repository Makefile and run the Acutest suite with `make run-tests`.

## 12. Risks

- Floating-point calculations may affect pole detection and component values.
- The supported magnitude range for finite coefficients has not been defined.
- Unsupported synthesis families require separate design work before implementation.
- The supported finite coefficient range is limited by the implementation's floating-point type.

## 13. Unsupported Scope

- Foster-II admittance synthesis.
- Cauer continued-fraction ladder synthesis.
- Terminated two-port synthesis and transfer-function realization.
- Automatic cancellation of common numerator and denominator factors.