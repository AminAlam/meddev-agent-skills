---
skill_id: TEST-INTEGRATION
version: 1.1.0
last_updated: 2026-05-21
applies_to: [Class A, Class B, Class C]
jurisdiction: [Global]
prerequisites: [FW-HAL, ARCH-SEPARATION]
---

# Integration Testing

## Purpose
Validate interactions between software components and hardware interfaces, ensuring interfaces, protocols, and data flows behave correctly in realistic configurations.

## When to Apply
- New or changed interfaces between modules, tasks, or hardware drivers.
- After refactors affecting boundaries or IPC.

## Requirements (testable)
1. Integrate per Plan [Class B, C]: Integrate software units per integration plan. Rationale: 5.6.1.
2. Integration Verification [Class B, C]: Verify integration matches plan; retain evidence (often inspection). Rationale: 5.6.2.
3. Integration Testing [Class B, C]: Test integrated items for intended behaviour—functionality, risk controls, timing, interfaces, abnormal/misuse cases. Rationale: 5.6.3–5.6.4.
4. Procedure Adequacy [Class B, C]: Evaluate integration test procedures for adequacy. Rationale: 5.6.5.
5. Regression [Class B, C]: After integrating items, run regression tests on previously integrated software. Rationale: 5.6.6.
6. Test Records [Class B, C]: Record pass/fail, anomalies, data to repeat test, and tester identity. Rationale: 5.6.7.
7. Problem Process [Class B, C]: Enter integration anomalies into `DOC-PROBLEM-RES`. Rationale: 5.6.8.
8. Interface Coverage: Test all public interfaces and IPC paths, including error paths. Rationale: verify contracts.
9. Traceability: Link tests to interface requirements and risks. Rationale: compliance.
10. Automation: Run in CI or scheduled hardware runs; capture logs/artifacts. Rationale: continuous assurance.

## Recommended Practices
- Use contract tests between components; mock only external dependencies, not the components under test.
- Include timing assertions where relevant (e.g., max latency).
- For hardware-involved tests, gate by availability and provide skip markers; still exercise simulators in CI.

## Patterns
CRC rejection test:
```c
// TEST-INT-205 covers REQ-SEP-IF-01
TEST(Interface, RejectsBadCrc) {
    msg_t m = {.len = 4, .crc = 0xFFFF};
    CHECK_FALSE(validate_msg(&m));
}
```

IPC timing:
```c
// TEST-INT-210 covers REQ-RTOS-IPC-02
CHECK_TRUE(send_cmd(&cmd));
// assert queue receive within 10ms
```

## Anti-Patterns (risks)
- Relying solely on unit tests for interface logic -> risk: gaps in real interaction.
- No malformed/negative tests -> risk: acceptance of bad data.
- Tests only on ideal timing -> risk: missed race/timing issues.

## Verification Checklist
- [ ] All interfaces/IPC paths tested (happy + error).
- [ ] Representative environment used (HW or high-fidelity sim); timing considered.
- [ ] Size/range/CRC validations tested including malformed inputs.
- [ ] Nondeterminism controlled or bounded; tests repeatable.
- [ ] Requirements/risk IDs linked; artifacts/logs captured.
- [ ] Automated execution in CI/nightly; failures block or trigger triage.

## Traceability
- `TEST-INT-###` mapped to interface requirements; timing evidence stored with results.

## References
- IEC 62304:2006+A1:2015, 5.6 (integration and integration testing).
- `DOC-PROBLEM-RES`, `DOC-TEST-DOCS`.
- ISO 14971:2019 for risk-based test scope.

## Changelog
- 1.1.0 (2026-05-21): Aligned with 5.6.1–5.6.8 including regression and problem process.
- 1.0.0 (2026-01-04): Initial integration testing skill with interface coverage and robustness focus.

## Audit History
- **2026-01-04**: Audit performed. Verified:
  - IEC 62304 section 5.6 reference for integration testing is accurate
  - Interface validation patterns are technically sound
