# Foster-I One-Port Impedance Synthesizer

Product documentation for users and developers.

## 1. Product Overview

The application is a command-line study tool for interactive Foster-I synthesis
of a realizable one-port impedance. It accepts numerator and denominator
coefficient vectors for

$$
Z(s)=\frac{N(s)}{D(s)}
$$

and guides the user through successive component removals. Each step displays
the current impedance, available removals, accumulated components, and an ASCII
circuit.

Despite the repository's historical name, terminated two-port synthesis is not
implemented. The supported immittance is impedance only.

## 2. Supported Synthesis

The implemented method is Foster-I impedance synthesis. The resulting circuit
is a series connection of supported Foster terms:

- A positive-residue real pole $K/(s+a)$ becomes a parallel RC branch with
  $C=1/K$ and $R=K/a$.
- A negative-residue real pole represented as $Ks/(s+a)$ becomes a parallel RL
  branch with $R=K$ and $L=K/a$.
- A conjugate pole pair at $\pm j\omega_0$ represented as
  $Ks/(s^2+\omega_0^2)$ becomes a parallel LC branch with
  $C=1/K$ and $L=K/\omega_0^2$.
- $K_0/s$ becomes a series capacitor with $C=1/K_0$.
- $K_\infty s$ becomes a series inductor with $L=K_\infty$.
- A non-negative constant term becomes a series resistor.

Reactive component values must be finite and positive. Resistance values must
be finite and non-negative.

## 3. Input and Realizability

Coefficients are finite floating-point values in descending powers of `s`.
The application requires exactly two bracketed command-line vectors:

```text
./build/main '[numerator coefficients]' '[denominator coefficients]'
```

Before interaction, the application validates the supported Foster-I
realizability conditions. It rejects right-half-plane poles, unsupported
off-axis complex poles, repeated poles where simple poles are required,
invalid imaginary-axis residues, zero-residue denominator poles, and
impedances that fail the implemented positive-real test.

Common numerator and denominator factors are not canceled. Every denominator
root remains a pole; a zero-residue pole is therefore rejected as unsupported.

## 4. Interactive Workflow

For valid input, the application:

1. Displays the current impedance and accumulated state.
2. Displays indexed physical removal candidates.
3. Accepts an option index or `q`.
4. Extracts the Foster component.
5. Subtracts the term and verifies the rational identity.
6. Verifies that the selected pole group is absent and the remainder is realizable.
7. Records and renders the updated circuit.
8. Repeats until no terms remain.

Invalid selections produce an error and reprompt without changing state. Input
`q` ends the session with `PARTIAL SYNTHESIS`. A completed realization ends
with `SYNTHESIS COMPLETE`.

## 5. Circuit Notation

Intermediate and final diagrams use `IN` and `OUT` terminals and join Foster
components in series with `---`. Labels are deterministic:

- `RC1`, `RL1`, `LC1` for parallel branches.
- `R1`, `C1`, `L1` for series endpoint components.

Examples:

```text
IN o---[ RC1: R=10.00 ohm, C=0.10 F ]---o OUT
IN o---[ RL1: R=1.00 ohm, L=1.00 H ]---o OUT
IN o---[ LC1: L=1.00 H, C=1.00 F ]---o OUT
IN o---[ L1: L=3.00 H ]---[ R1: R=2.00 ohm ]---o OUT
```

Displayed numerical values use two decimal places.

## 6. Architecture

The C++17 implementation consists of command-line parsing, an application
runner, polynomial and rational-function models, pole discovery, physical
candidate grouping, realizability validation, Foster extraction, validated
removal updates, synthesis state, an interactive controller, and renderers.

Eigen provides polynomial root solving. Acutest provides the test framework.

## 7. Build and Run

From WSL:

```bash
cd /mnt/c/jpablo/00_Projects/cyborg-training/two-port-network-synthesizer
make clean
make all
make run-tests
```

Representative examples:

```bash
printf '0\n0\n' | ./build/main '[2,3]' '[1,3,2]'
printf '0\n' | ./build/main '[1,0]' '[1,0,1]'
printf '0\n0\n' | ./build/main '[3,2]' '[1]'
```

## 8. Current Limitations

- One-port impedance and Foster-I synthesis only.
- No Foster-II admittance synthesis.
- No Cauer ladder synthesis.
- No terminated two-port or transfer-function synthesis.
- No automatic common-factor cancellation.
- Numerical behavior is limited by floating-point root and residue tolerances.

## 9. Verification

The automated suite covers parsing, mathematical models, pole analysis,
realizability, candidate grouping, component formulas, validated updates,
complete and partial workflows, rendering, and executable integration. The WSL
Makefile build and test path is the supported verification route.
