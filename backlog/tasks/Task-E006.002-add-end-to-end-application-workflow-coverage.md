# Task E006.002 — Add End-to-End Application Workflow Coverage

## Objective

Verify the connected executable through complete and partial command-line workflows.

## Context

The current tests exercise `runSynthesis` directly, but do not prove that the built application connects parsing, model construction, interaction, state updates, and rendering.

## Requirements

- Exercise a valid executable invocation with interactive input.
- Cover complete synthesis through the executable.
- Cover `q` and partial synthesis through the executable.
- Cover malformed command-line input through the executable.
- Verify the resulting terminal output and exit behavior defined by the application entry point.

## Design References

- README.md: Synthesis Process and Final Output
- docs/sdd.md: Sections 3, 6, 7, and 10
- Task E006.001

## Acceptance Criteria

- [ ] A complete executable workflow is automated.
- [ ] A partial `q` executable workflow is automated.
- [ ] Invalid input is verified not to enter synthesis.
- [ ] Tests distinguish executable behavior from direct controller tests.

## Tests

Add process-level or application-runner coverage using the repository's supported test tooling.

## Definition of Done

The executable workflow is covered for complete, partial, and invalid-input paths.

## Dependencies

- Task E006.001