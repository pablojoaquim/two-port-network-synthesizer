# Task E003.002 — Handle Interactive Selections

## Objective
Process a user's removal selection or early termination request.

## Context
The user selects an available removal at each step or enters `q` to finish interactively.

## Requirements

- Accept a valid available removal selection.
- Display an error and reprompt for an invalid selection without changing state.
- Accept `q` and mark the result as partial synthesis.

## Design References

- README.md: Synthesis Process
- docs/sdd.md: Sections 3 and 6

## Acceptance Criteria

- [x] A valid selection is returned to the controller.
- [x] An invalid selection causes a reprompt and preserves state.
- [x] `q` ends interaction and marks partial synthesis.

## Tests

Test valid selection, invalid selection, repeated prompting, and `q` input.

## Definition of Done

Interactive selection handling and focused tests are implemented and pass.

## Dependencies

- Task E002.001
- Task E003.001
