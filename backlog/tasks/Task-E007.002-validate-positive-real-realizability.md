# Task E007.002 — Validate Positive-Real Realizability

## Objective

Reject rational functions that cannot be synthesized by the documented passive network method.

## Context

The current pole analysis exposes arbitrary roots, including right-half-plane and non-axis complex poles, without checking positive-real conditions or the required pole/zero structure.

## Requirements

- Validate the selected input scope from E007.001.
- Reject unsupported right-half-plane poles.
- Validate simple-pole and residue conditions for poles on the $j\omega$ axis.
- Validate the real-axis pole and zero conditions required by the selected RL/RC or Foster method.
- Report a clear reason when the input is not realizable by the supported method.

## Acceptance Criteria

- [x] Realizable reference functions are accepted.
- [x] Non-realizable pole locations are rejected before synthesis.
- [x] Invalid repeated or non-positive-residue cases are rejected where required.
- [x] Validation failures do not start the interactive workflow.

## Tests

Add positive-real, right-half-plane, repeated-pole, non-axis-complex, and invalid-residue cases.

## Definition of Done

The application does not present unsupported poles as available synthesis removals.

## Dependencies

- Task E007.001