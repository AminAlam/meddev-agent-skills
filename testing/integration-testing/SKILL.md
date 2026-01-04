---
skill_id: TEST-INTEGRATION
version: 1.0.0
last_updated: 2026-01-04
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
1. Interface Coverage: Test all public interfaces and IPC paths, including error paths. Rationale: verify contracts.
2. Environment Representativeness: Use representative hardware or high-fidelity simulators; include timing where safety-relevant. Rationale: realism.
3. Data Validation: Validate size/range/CRC across interfaces; inject malformed data to confirm rejection. Rationale: robustness.
4. Determinism: Control nondeterminism (clocks, randomness, network) for repeatability where possible. Rationale: reproducibility.
5. Traceability: Link tests to interface requirements and risks. Rationale: compliance and impact analysis.
6. Automation: Run in CI (or nightly if hardware-limited); capture logs/artifacts. Rationale: continuous assurance.

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
- IEC 62304 integration testing (5.6).
- ISO 14971 for risk-based test scope.

## Changelog
- 1.0.0 (2026-01-04): Initial integration testing skill with interface coverage and robustness focus.

## Audit History
- **2026-01-04**: Audit performed. Verified:
  - IEC 62304 section 5.6 reference for integration testing is accurate
  - Interface validation patterns are technically sound
