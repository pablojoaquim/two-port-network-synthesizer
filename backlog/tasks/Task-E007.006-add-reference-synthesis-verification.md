# Task E007.006 — Add Reference-Based Synthesis Verification Coverage

## Objective

Verify the corrected synthesis workflow against representative reference cases.

## Requirements

- Cover accepted and rejected realizability cases.
- Cover real-pole Foster synthesis.
- Cover conjugate-pair LC synthesis.
- Cover complete and partial interactive workflows.
- Verify rendered component values and circuit structure.
- Verify the documented one-port or two-port scope boundary.

## Acceptance Criteria

- [x] Reference-based mathematical cases pass with expected values.
- [x] Invalid cases stop before interactive selection.
- [x] Complete and `q` partial workflows remain distinguishable.
- [x] Rendered output reflects the physical component groups.
- [x] The full WSL Makefile build and test path passes.

## Tests

Add focused unit, workflow, and executable-path tests required by the preceding tasks.

## Definition of Done

The supported synthesis method is verified end to end and its limitations are explicit.

## Dependencies

- Task E007.002
- Task E007.003
- Task E007.004
- Task E007.005