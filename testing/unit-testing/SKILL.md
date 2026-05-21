---
skill_id: TEST-UNIT
version: 1.1.0
last_updated: 2026-05-21
applies_to: [Class A, Class B, Class C]
jurisdiction: [Global]
prerequisites: [FW-EMBEDDED-C, FW-HAL, ARCH-SAFETY-CLASS]
---

# Unit Testing for Medical Device Software

## Purpose
Establish patterns for unit tests that verify software units against requirements with safety-class-appropriate rigor.

## When to Apply
- New or changed functions/modules, especially safety-related.
- Bug fixes to prevent regression.

## Requirements (testable)
1. Implement Units [Class A, B, C]: Implement each software unit per design. Rationale: 5.5.1.
2. Verification Process [Class B, C]: Define strategies, methods, and procedures for unit verification; evaluate test procedure adequacy. Rationale: 5.5.2.
3. Acceptance Criteria [Class B, C]: Define acceptance criteria before integration; confirm units meet criteria (requirements, interface consistency, coding standards). Rationale: 5.5.3.
4. Class C Criteria [Class C]: Where design requires, add criteria for event sequencing, data/control flow, resource use, fault handling, initialization, diagnostics, memory behaviour, and boundary conditions. Rationale: 5.5.4 (engineering checklist).
5. Execute and Record [Class B, C]: Perform unit verification and document results. Rationale: 5.5.5.
6. Structure: Use Arrange-Act-Assert; deterministic tests with clear preconditions. Rationale: reliable evidence.
7. Isolation: Mock hardware/HAL; no real hardware in unit tests. Rationale: determinism.
8. Traceability: Each test links to requirement and risk control IDs. Rationale: compliance.
9. CI Integration: Run in CI; archive results. Rationale: continuous assurance.

## Recommended Practices
- Keep tests fast (<1s each) to encourage frequent runs.
- Use table-driven tests for combinations; parametrize to reduce duplication.
- Enforce `-Wall -Wextra -Werror` in test builds.
- Add sanitizers (ASan/UBSan) on host where possible for non-embedded logic.

## Patterns
C unit test with Unity (example):
```c
// TEST-UNIT-105 covers REQ-C-TYPE-01
TEST(SumSamples, AccumulatesAll) {
    uint16_t s[] = {1, 2, 3};
    CHECK_EQUAL(6, sum_samples(s, 3));
}
```

Boundary test:
```c
// TEST-UNIT-110 covers REQ-DEF-INPUT-01
TEST(ValidateFlow, RejectsNegative) {
    CHECK_FALSE(validate_flow(-1.0f));
}
```

Mock HAL:
```c
// TEST-UNIT-120 covers REQ-HAL-IF-01
MOCK_FUNCTION_WITH_RETURN(hal_status_t, hal_uart_write, const uint8_t*, size_t, size_t*);
```

## Anti-Patterns (risks)
- Tests that depend on real timing or hardware -> risk: flakiness.
- No negative/boundary tests -> risk: missed edge defects.
- Untagged tests with requirements -> risk: broken traceability.
- Ignoring test failures in CI -> risk: regressions ship.

## Verification Checklist
- [ ] Tests follow AAA and are deterministic.
- [ ] Coverage meets class targets (branch/MC-DC for critical logic).
- [ ] Hardware/HAL calls mocked; no real hardware dependencies.
- [ ] Requirements/risk IDs referenced in tests.
- [ ] Negative/boundary cases included.
- [ ] Tests run in CI with warnings-as-errors; failures block merges.

## Traceability
- Map `TEST-UNIT-###` to `REQ-###`; store coverage reports per release.

## References
- IEC 62304:2006+A1:2015, 5.5 (software unit implementation and verification).
- `TEST-COVERAGE` (informative MC/DC depth by class).
- ISO 14971:2019 for risk-based test depth.

## Changelog
- 1.1.0 (2026-05-21): Aligned with 5.5.2–5.5.5 and Class C acceptance topics.
- 1.0.0 (2026-01-04): Initial unit testing skill with coverage targets and traceability.

## Audit History
- **2026-01-04**: Audit performed. Verified:
  - IEC 62304 section 5.5 reference for unit implementation/verification is accurate
  - MC/DC requirement for Class B/C control logic aligns with industry practice
  - Unity test framework examples are syntactically correct
