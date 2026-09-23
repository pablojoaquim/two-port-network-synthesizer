# Task E001.002 — Polynomial Representation and Operations

## Objective
Provide the polynomial representation and operations required by the rational-function model.

## Context
Polynomial coefficients use floating-point values and are stored in descending powers of `s`.

## Requirements

- Represent a polynomial as a coefficient vector.
- Preserve descending-power ordering.
- Provide the polynomial operations required to update the synthesis rational function.

## Design References

- README.md: Input and Project Goals
- docs/sdd.md: Sections 3, 5, and 8

## Acceptance Criteria

- [ ] Polynomials can be created from parsed coefficient vectors.
- [ ] Required polynomial operations produce correctly ordered coefficient vectors.
- [ ] Calculations use floating-point values and display precision can be limited to two decimals.

## Tests

Test polynomial creation and each implemented operation with representative coefficient vectors.

## Definition of Done

The polynomial model and focused tests are implemented and pass.

## Dependencies

- Task E001.001
