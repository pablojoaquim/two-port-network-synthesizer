# Epic E007 — Correct Network Synthesis Model

## Objective

Replace the current prototype removal behavior with a mathematically defined, realizable network-synthesis workflow based on the reference synthesis methods.

## Scope

Resolve the supported network scope, validate positive-real and pole/zero conditions, represent removal candidates correctly, extract Foster components using the selected immittance form, and verify that each removal produces a valid remaining network.

The current application models one rational impedance. True terminated two-port synthesis requires additional source/load and two-port data; that scope must be explicitly decided before implementation expands beyond one-port synthesis.

## Tasks

- Task E007.001 — Define supported synthesis scope and Foster conventions
- Task E007.002 — Validate realizability and positive-real input conditions
- Task E007.003 — Represent valid removal candidates and conjugate pole groups
- Task E007.004 — Implement mathematically correct Foster removal extraction
- Task E007.005 — Validate removal updates and endpoint poles
- Task E007.006 — Add reference-based synthesis verification coverage

## Completion Criteria

The supported synthesis scope is documented, invalid or unsupported functions are rejected before synthesis, removal candidates correspond to valid Foster terms, conjugate poles are handled as one component, removal updates preserve the rational function identity, and reference-based tests verify the complete supported workflow.