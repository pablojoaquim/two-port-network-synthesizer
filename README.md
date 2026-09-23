# Two-Port Network Synthesizer

A command-line tool for the step-by-step synthesis of linear time-invariant (LTI) two-port networks.

The system takes an LTI network impedance as a rational function and interactively performs a sequence of total removals until the final circuit is obtained.

The synthesis process is presented graphically in the terminal using ASCII diagrams.

## Objective

The main objective of this project is to provide an interactive tool for studying and performing the synthesis of two-port networks.

Given a rational transfer function:

$$
H(s) = \frac{N(s)}{D(s)}
$$

the tool analyzes the system and guides the user through the synthesis process by applying successive total removals.

At each step, the user can inspect the current synthesis state and select which component or pole should be removed.

The process continues until the complete circuit has been synthesized.

## Input

The system is defined by two vectors of polynomial coefficients:

* Numerator coefficients
* Denominator coefficients

Coefficients are provided in descending powers of `s`.

For example:

```text
N(s) = 2s + 4

numerator   = [2, 4]

D(s) = s² + 3s + 2

denominator = [1, 3, 2]
```

The resulting transfer function is:

```text
        2s + 4
H(s) = ---------
        s² + 3s + 2
```

## Synthesis Process

The synthesis is performed through successive total removals.

At each stage, the tool:

1. Displays the current rational function.
2. Displays the current synthesis state.
3. Displays the available removal options.
4. Asks the user which component or pole should be removed.
5. Performs the selected removal.
6. Updates the rational function.
7. Displays the resulting synthesis step graphically.
8. Continues until the network is completely synthesized.

The rational function always represents impedance. A total removal at a selected
frequency is valid only when the remaining impedance has no pole at that
frequency. Foster extraction supports real negative poles and conjugate pole
pairs on the $j\omega$ axis. For a real pole $p=-a$ with residue $K$, the
Foster term is $K/(s+a)$ and represents a parallel RC branch:

$$
C = \frac{1}{K}, \qquad R = \frac{K}{a}
$$

For a conjugate pair at $\pm j\omega_0$, the Foster term is
$K s/(s^2+\omega_0^2)$ and represents a parallel LC branch:

$$
C = \frac{1}{K}, \qquad L = \frac{K}{\omega_0^2}
$$

Only decompositions with finite positive component values are available for
removal.

The user therefore controls the synthesis path interactively.

The process is intended to make every intermediate step visible rather than treating synthesis as a black-box operation.

## Terminal Visualization

The application runs entirely in the terminal.

No graphical user interface is required.

The synthesis is represented using ASCII diagrams.

Example:

```text
        R1
  +----/\/\/\----+
  |              |
--+              +--
  |              |
  +------ C1 ----+
```

The canonical circuit representation uses `IN` and `OUT` terminals, series-ordered
Foster branches, deterministic branch labels, and `GND` where a grounded
representation is needed. Parallel RC and LC branches are displayed as:

```text
IN o---[ RC1: R=10.00 ohm, C=0.10 F ]---o OUT
IN o---[ LC1: L=1.00 H, C=1.00 F ]---o OUT
```

Multiple branches use the same notation in synthesis order:

```text
IN o---[ RC1: R=10.00 ohm, C=0.10 F ]---[ LC1: L=1.00 H, C=1.00 F ]---o OUT
```

Intermediate and final diagrams use this same notation. Component values are
displayed to two decimal places.

The final circuit will also be displayed as an ASCII circuit in the terminal.

## Final Output

When the synthesis process is complete, the application provides:

* The complete synthesized circuit.
* The sequence of removals performed.
* The component values obtained during synthesis.
* An ASCII representation of the final circuit.

Example:

```text
SYNTHESIS COMPLETE

Circuit:

          R1
IN o---/\/\/\---+---o OUT
                |
               C1
                |
               GND

Components:

R1 = 10.0 Ω
C1 = 100.0 µF
```

## Technology

The software is developed in **C**.

The implementation should use the C standard library whenever possible, with minimal or no dependency on external libraries.

The project is intended to run in a **WSL (Windows Subsystem for Linux)** environment.

## Project Goals

The initial implementation focuses on:

* LTI systems represented as rational polynomials.
* Polynomial manipulation.
* Analysis required for total removals.
* Interactive synthesis.
* Step-by-step synthesis visualization.
* ASCII circuit representation.
* Final circuit generation.
* Reproducible command-line execution.

The architecture should allow additional synthesis methods and network representations to be incorporated in the future.

## Building

Build and run the application from WSL:

```bash
cd /mnt/c/jpablo/00_Projects/cyborg-training/two-port-network-synthesizer
make all
printf '0\n0\n' | ./build/main '[2,3]' '[1,3,2]'
```

The input represents the impedance

$$
Z(s) = \frac{2s+3}{s^2+3s+2}
$$

The two `0` lines select the available removals in sequence. The session
prints the current impedance and available options, displays each removal and
its circuit, and ends with `SYNTHESIS COMPLETE`. To stop interactively instead,
replace the input with `printf 'q\n'`; the result is labeled `PARTIAL SYNTHESIS`.

## Development Methodology

The project is developed following the **Software Design Document (SDD)** methodology.

The `SDD.md` document defines the software requirements, design decisions, open points, and development guidance used to implement the project.

The README describes **what the project is and how it is used**.

The SDD describes **what the software must do and how it should be developed**.

## Project Status

Early development.

The initial version focuses on establishing the mathematical model, synthesis process, interactive workflow, and terminal representation.
