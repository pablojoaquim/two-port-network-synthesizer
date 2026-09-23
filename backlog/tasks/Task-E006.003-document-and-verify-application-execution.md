# Task E006.003 — Document and Verify Interactive Application Execution

## Objective

Provide a reproducible documented example for running the integrated application.

## Context

The current README describes the synthesis workflow, but the built executable currently produces no synthesis output because the entry point is not connected.

## Requirements

- Document the build command required before running the application.
- Document a valid impedance example with representative interactive input.
- Document the expected complete or partial synthesis output markers.
- Verify the documented command in the intended WSL environment.

## Design References

- README.md: Input, Synthesis Process, Terminal Visualization, and Final Output
- docs/sdd.md: Sections 6, 9, and 11
- Task E006.002

## Acceptance Criteria

- [ ] A user can follow the documented commands to start the application.
- [ ] The example demonstrates an actual interactive synthesis session.
- [ ] The documented output matches the executable behavior.
- [ ] WSL build and execution are verified.

## Tests

Run the documented build and example commands under WSL and record the result.

## Definition of Done

The application has a reproducible, verified command-line execution example.

## Dependencies

- Task E006.002