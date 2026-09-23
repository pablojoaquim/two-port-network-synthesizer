# Task E001.001 — Parse Command-Line Coefficient Vectors

## Objective
Parse the numerator and denominator coefficient vectors supplied on the command line.

## Context
The application is invoked as `application [numerator coefficients][denominator coefficients]`. Coefficients are ordered from highest to lowest power of `s`.

## Requirements

- Accept one numerator vector and one denominator vector.
- Parse numeric values as floating-point coefficients.
- Reject missing, malformed, incompatible, or non-finite arguments with an error message before synthesis begins.

## Design References

- README.md: Input
- docs/sdd.md: Sections 3 and 6

## Acceptance Criteria

- [ ] A valid example such as `[1,1,2][2,1,3]` is parsed into two coefficient vectors.
- [ ] Missing or malformed vectors are rejected without starting synthesis.
- [ ] Non-finite coefficient values are rejected.

## Tests

Test valid input, missing arguments, malformed syntax, incompatible vectors, and non-finite values.

## Definition of Done

Parsing behavior and focused tests are implemented and pass.

## Dependencies

None.
