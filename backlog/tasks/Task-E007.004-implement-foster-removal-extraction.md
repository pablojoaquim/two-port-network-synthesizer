# Task E007.004 — Implement Mathematically Correct Foster Removal Extraction

## Objective

Extract component data and the removed Foster term using the conventions defined by E007.001.

## Requirements

- Compute residues or endpoint coefficients according to the selected Foster form.
- Return the correct component type and value for each supported pole group.
- Support the documented real-pole and $j\omega$-pair cases.
- Handle poles at zero and infinity when included by the scope decision.
- Return an unavailable-decomposition result without mutating synthesis state when extraction fails.

## Acceptance Criteria

- [x] Reference Foster examples produce the expected component values.
- [x] Real-pole extraction matches the documented RC/RL convention.
- [x] Conjugate-pair extraction produces one LC component.
- [x] Unsupported or invalid residues produce no component data.

## Tests

Add formula-level tests using independently calculated Foster expansions and component values.

## Definition of Done

Foster extraction is mathematically consistent with the documented synthesis scope.

## Dependencies

- Task E007.001
- Task E007.003