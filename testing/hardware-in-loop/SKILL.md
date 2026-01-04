---
skill_id: TEST-HIL
version: 1.0.0
last_updated: 2026-01-04
applies_to: [Class A, Class B, Class C]
jurisdiction: [Global]
prerequisites: [TEST-INTEGRATION, FW-HAL, ARCH-SAFETY-CLASS]
---

# Hardware-in-the-Loop (HIL) Testing

## Purpose
Validate software with real or representative hardware, sensors, actuators, and timing, to uncover integration and safety issues not visible in simulation.

## When to Apply
- Before release for safety-relevant features.
- After hardware/driver changes or timing-sensitive refactors.

## Requirements (testable)
1. Fixture Design: Use representative hardware fixtures with controllable stimuli and measurements; include fault injection paths. Rationale: realism and safety coverage.
2. Automation: Automate HIL sequences; script stimuli and assertions; capture logs/measurements. Rationale: repeatability and evidence.
3. Safety Monitoring: Monitor outputs for safety limits; include E-stops; ensure safe state on test failure. Rationale: operator/device safety.
4. Timing: Measure latencies and deadlines under realistic load; verify against requirements. Rationale: timing assurance.
5. Parallelization: Where possible, run tests in parallel fixtures; manage resource contention safely. Rationale: efficiency.
6. Traceability: Link HIL tests to requirements/risks and record configurations (HW rev, firmware rev, calibration). Rationale: reproducibility.

## Recommended Practices
- Use DAQ/logging for analog signals; timestamp with synchronized clocks.
- Combine HIL with fault injection (disconnects, noise, power dips).
- Keep fixtures version-controlled (BOM, wiring, firmware).
- Provide dry-run/simulation mode for CI when hardware not available.

## Patterns
HIL test record (YAML):
```yaml
# REQ-HIL-REC-01
test_id: TEST-HIL-102
reqs: [REQ-62304-102, REQ-FT-WD-01]
hw_rev: "board v2.1"
fw_rev: "1.3.0"
stimuli:
  - type: digital
    signal: door_open
    at_ms: 0
measures:
  - signal: motor_pwm
    expect: 0 within 50ms
result: pass
```

Fault injection step:
```text
// REQ-HIL-FAULT-02; TEST-HIL-120
At t=500 ms, drop comms line; expect safe state within 200 ms.
```

## Anti-Patterns (risks)
- Ad-hoc manual HIL with no logs -> risk: non-reproducible results.
- No safety limits/E-stop during tests -> risk: injury/device damage.
- Ignoring hardware configuration tracking -> risk: unrepeatable tests.
- Only ideal conditions tested -> risk: missed real-world faults.

## Verification Checklist
- [ ] Fixture representative; stimuli/measurements controlled; fault injection available.
- [ ] Automated scripts/sequences with logged results and timestamps.
- [ ] Safety monitoring and E-stop implemented; safe state on failure.
- [ ] Timing under load measured and within requirements.
- [ ] Parallel execution handled safely; resource conflicts managed.
- [ ] Hardware/firmware/config recorded; tests linked to requirements/risks.

## Traceability
- Map `TEST-HIL-###` to requirements and hazards; store fixture/config data with results.

## References
- IEC 62304 integration/system testing context.
- ISO 14971 risk-based verification.

## Changelog
- 1.0.0 (2026-01-04): Initial HIL testing skill with fixture, automation, and safety/timing focus.

## Audit History
- **2026-01-04**: Audit performed. Verified:
  - HIL fixture patterns follow industry best practices
  - Safety monitoring and E-stop requirements accurately described
  - Fault injection concepts are appropriate for medical device testing
