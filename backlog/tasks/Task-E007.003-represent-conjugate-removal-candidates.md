# Task E007.003 — Represent Valid Removal Candidates and Conjugate Pole Groups

## Objective

Expose removal options that correspond to physical Foster terms rather than individual denominator roots.

## Context

An LC Foster term at $\pm j\omega$ is associated with a conjugate pole pair and one component. The current implementation exposes the two roots as separate removal choices.

## Requirements

- Group conjugate $j\omega$ poles into one removal candidate.
- Preserve real-pole candidates as single-pole candidates where supported.
- Include the complete pole-group data needed for residue and component extraction.
- Keep selection indices stable and unique for the current state.
- Exclude candidates rejected by realizability validation.

## Acceptance Criteria

- [ ] A conjugate pole pair produces one removal option.
- [ ] A real simple pole produces one removal option.
- [ ] Group multiplicity and frequency data are preserved.
- [ ] Unsupported roots are not selectable.

## Tests

Test real poles, conjugate pairs, repeated poles, ordering, and mixed candidate sets.

## Definition of Done

Removal options represent complete physical Foster terms.

## Dependencies

- Task E007.001
- Task E007.002