# Task E002.003 — Extract Foster Component Data

## Objective
Use the Foster method to obtain the component type and value for a valid removal.

## Context
The synthesis process records the component values produced by each total removal.

## Requirements

- Apply the Foster method to a valid removal.
- Return the removed component type and value.
- Report that no removal can be performed when no valid Foster decomposition is available.

## Design References

- README.md: Project Goals and Final Output
- docs/sdd.md: Sections 3, 5, and 8

## Acceptance Criteria

- [ ] A valid removal returns a component type.
- [ ] A valid removal returns a component value.
- [ ] An unavailable decomposition is reported without producing component data.

## Tests

Test Foster extraction for supported valid removals and the unavailable-decomposition case.

## Definition of Done

Foster extraction and focused tests are implemented and pass.

## Dependencies

- Task E002.002
