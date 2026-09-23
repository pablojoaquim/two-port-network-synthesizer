# Task E001.003 — Rational-Function Representation

## Objective
Represent the current rational function and support updates to its numerator and denominator.

## Context
The system models $H(s) = N(s) / D(s)$ and updates it after each total removal.

## Requirements

- Store numerator and denominator polynomials.
- Preserve the current rational-function state.
- Expose the state to synthesis analysis and terminal rendering.

## Design References

- README.md: Objective and Synthesis Process
- docs/sdd.md: Sections 2, 4, and 5

## Acceptance Criteria

- [ ] A rational function can be constructed from two polynomials.
- [ ] Numerator and denominator can be read by dependent components.
- [ ] The rational function can be replaced with an updated state after a removal.

## Tests

Test construction, access, and replacement of rational-function state.

## Definition of Done

The rational-function model and focused tests are implemented and pass.

## Dependencies

- Task E001.002
