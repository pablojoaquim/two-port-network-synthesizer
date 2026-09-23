# Task E004.001 — Render Synthesis Information

## Objective
Render the current rational function, synthesis state, available options, and recorded component data.

## Context
Each step must remain visible rather than treating synthesis as a black box.

## Requirements

- Render the current rational function.
- Render the current synthesis state and available removal options.
- Render the removal sequence and component values.
- Display numerical values to two decimal places.

## Design References

- README.md: Synthesis Process and Final Output
- docs/sdd.md: Sections 3 and 5

## Acceptance Criteria

- [x] Current rational function and options are displayed before selection.
- [x] Each completed removal and component value is displayed.
- [x] Values use two decimal places.

## Tests

Test rendering for an initial state, an intermediate state, and an accumulated result.

## Definition of Done

Text rendering and focused output tests are implemented and pass.

## Dependencies

- Task E003.001
