# Task E002.002 — Validate Total Removals

## Objective
Validate a candidate total removal against the remaining network.

## Context
A total removal is valid when the remaining network has no pole at the frequency of the removal.

## Requirements

- Evaluate a candidate removal at its associated frequency.
- Accept the removal only when the remaining network has no pole at that frequency.
- Leave the rational-function state unchanged when validation fails.

## Design References

- docs/sdd.md: Sections 3, 5, and 8

## Acceptance Criteria

- [x] A candidate satisfying the no-remaining-pole condition is accepted.
- [x] A candidate that leaves a pole at the removal frequency is rejected.
- [x] Rejected validation does not modify the synthesis state.

## Tests

Test valid and invalid candidate removals, including floating-point values displayed to two decimals.

## Definition of Done

Removal validation and focused tests are implemented and pass.

## Dependencies

- Task E002.001
