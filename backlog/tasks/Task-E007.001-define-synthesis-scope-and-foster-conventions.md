# Task E007.001 — Define Supported Synthesis Scope and Foster Conventions

## Objective

Resolve the mathematical and product scope required for a correct synthesis implementation.

## Context

The reference distinguishes one-port impedance/admittance Foster synthesis from resistively terminated two-port synthesis. It also defines Foster I and Foster II forms, LC/RL/RC cases, and endpoint poles. The current application accepts only one rational impedance and has no source, load, or two-port parameter model.

## Requirements

- Decide whether the current product supports one-port impedance synthesis only or also terminated two-port synthesis.
- Define whether the supported immittance is impedance only, admittance as well, or both.
- Define the supported Foster forms and component families.
- Resolve the RC residue-to-component formula and document the chosen circuit convention.
- Define handling for poles at zero and infinity.
- Define cancellation policy for common numerator and denominator factors.

## Acceptance Criteria

- [x] The supported network scope is explicitly documented.
- [x] Foster form, immittance, component, and endpoint conventions are documented.
- [x] RC residue formulas are internally consistent with the selected circuit topology.
- [x] Cancellation and unsupported-input behavior are explicitly defined.

## Tests

Review the documented decisions against the reference synthesis formulas before implementation tasks begin.

## Definition of Done

No implementation task depends on an unresolved synthesis convention.

## Dependencies

- None