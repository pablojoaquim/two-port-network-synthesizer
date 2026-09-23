# Task E002.001 — Identify Poles and Removal Options

## Objective
Identify the poles of the current rational function and expose the available removal options.

## Context
Each synthesis step displays the available component or pole removal choices.

## Requirements

- Analyze the current denominator for poles.
- Represent each available removal option for the interactive workflow.
- Report when no poles remain.

## Design References

- README.md: Synthesis Process
- docs/sdd.md: Sections 3, 5, and 7

## Acceptance Criteria

- [x] Poles can be identified from the current rational function.
- [x] Available removal options are returned in a form usable by the controller.
- [x] An empty pole set is reported as the completion condition.

## Tests

Test pole detection and option generation for rational functions with zero, single, and multiple poles.

## Definition of Done

Done. Pole analysis and focused tests are implemented and pass.

## Dependencies

- Task E001.003
