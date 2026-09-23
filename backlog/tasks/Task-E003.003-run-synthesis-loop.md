# Task E003.003 — Run the Synthesis Loop

## Objective
Coordinate analysis, selection, removal, state update, and completion.

## Context
The synthesis process repeats until no poles remain, `q` is entered, or no valid Foster decomposition is available.

## Requirements

- Display the current state and options at each step.
- Apply a selected valid removal and update synthesis state.
- Stop for no remaining poles, `q`, or unavailable Foster decomposition.

## Design References

- README.md: Synthesis Process
- docs/sdd.md: Sections 2, 4, and 7

## Acceptance Criteria

- [x] A valid removal advances the workflow to the next state.
- [x] No remaining poles ends the workflow.
- [x] `q` ends the workflow as partial synthesis.
- [x] An unavailable Foster decomposition ends the workflow with a report.

## Tests

Test each completion path and a multi-step removal sequence.

## Definition of Done

The synthesis controller and focused workflow tests are implemented and pass.

## Dependencies

- Task E002.003
- Task E003.001
- Task E003.002
