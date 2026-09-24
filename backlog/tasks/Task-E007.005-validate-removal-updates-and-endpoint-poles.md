# Task E007.005 — Validate Removal Updates and Endpoint Poles

## Objective

Ensure each selected Foster removal produces a valid remaining rational function.

## Requirements

- Apply the extracted Foster term to the current immittance.
- Verify that the selected pole group is fully removed from the remaining function.
- Reject an update that leaves a pole at the selected frequency.
- Preserve state when validation or update fails.
- Implement the documented zero and infinity removal behavior when in scope.

## Acceptance Criteria

- [x] Valid removal updates preserve the rational-function identity.
- [x] The selected pole or pole group is absent from the remaining function.
- [x] Invalid updates are rejected without state mutation.
- [x] Endpoint removal behavior matches the documented convention.

## Tests

Test polynomial identity before and after removal, residual pole detection, failed updates, and endpoint cases.

## Definition of Done

The controller cannot advance with a mathematically invalid remaining network.

## Dependencies

- Task E007.002
- Task E007.004