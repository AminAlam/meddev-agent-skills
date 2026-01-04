---
skill_id: ARCH-FAULT-TOL
version: 1.0.0
last_updated: 2026-01-04
applies_to: [Class A, Class B, Class C]
jurisdiction: [Global]
prerequisites: [ARCH-SAFETY-CLASS]
---

# Fault Tolerance Design

## Purpose
Provide patterns for detecting, containing, and recovering from faults in medical device software, scaled to safety class.

## When to Apply
- Safety-critical control loops, sensing/actuation, communication paths.
- Watchdogs, redundancy, health monitoring, self-test.
- Power, memory, and comms error handling.

## Requirements (testable)
1. Fault Detection: Implement monitoring for critical resources (tasks, sensors, comms) with thresholds and alarms. Rationale: early detection.
2. Graceful Degradation: Define degraded modes or safe state when partial functionality fails. Rationale: bounded failure.
3. Redundancy Strategy: For Class C functions, consider redundancy (sensing, computation, or communication) with voter/consistency checks. Rationale: resilience.
4. Watchdog Use: Configure hardware/software watchdogs with bounded servicing windows; service only after critical checks pass. Rationale: recover from hangs.
5. Self-Test/BIST: Run self-tests at startup and periodically for critical components; handle failures deterministically. Rationale: latent fault detection.
6. Error Propagation Control: Sanitize/contain errors at boundaries; avoid cascading faults. Rationale: containment.
7. Logging & Alarms: Log and, where required, annunciate safety-relevant faults; ensure tamper-evident logs for post-incident analysis. Rationale: traceability.

## Recommended Practices
- Use majority voting or reasonableness checks instead of blind trust in single sensors.
- Employ brownout/power-fail detection to enter safe state gracefully.
- For RTOS, assign dedicated safety monitor task with higher priority than non-critical tasks.
- Debounce fault signals to reduce false positives but cap with timeouts.

## Patterns
Watchdog servicing with checks:
```c
// REQ-FT-WD-01; TEST-FT-03
void service_watchdog(void) {
    if (critical_tasks_healthy() && comms_alive()) {
        wdt_kick();
    } else {
        // Do not kick; let watchdog reset into safe boot
    }
}
```

Sensor plausibility check:
```c
// REQ-FT-SNS-02; TEST-FT-07
bool validate_pressure(float p_kpa) {
    return (p_kpa >= 0.0f && p_kpa <= 300.0f);
}
```

Redundant reading vote:
```c
// REQ-FT-RED-01; TEST-FT-10
float fused_temp(float a, float b) {
    if (fabsf(a - b) > 2.0f) {
        alarm_sensor_disagree();
        enter_safe_state();
    }
    return (a + b) * 0.5f;
}
```

## Anti-Patterns (risks)
- Servicing watchdog unconditionally in main loop -> risk: hides deadlocks.
- Single-point sensors without plausibility checks -> risk: unsafe outputs.
- Logging faults without annunciation where required -> risk: latent hazards.
- No degraded mode or safe fallback -> risk: uncontrolled failure behavior.

## Verification Checklist
- [ ] Fault monitors implemented for critical resources with thresholds/timeouts.
- [ ] Watchdog configuration reviewed; serviced only after health checks.
- [ ] Degraded modes or safe state defined and reachable on fault.
- [ ] Redundancy/plausibility checks implemented for critical sensors/paths.
- [ ] Self-tests executed at startup/periodically; failures handled deterministically.
- [ ] Errors contained at boundaries; no unchecked propagation.
- [ ] Faults logged and annunciated as applicable; integrity of logs maintained.

## Traceability
- Link `REQ-FT-###` to hazards and controls; map to tests (`TEST-FT-###`).
- Store watchdog and fault monitor configuration with release artifacts.

## References
- IEC 62304 design/implementation expectations (fault control).
- ISO 14971 for risk-driven fault handling.
- IEC 60601-1 (power/brownout considerations; informative).

## Changelog
- 1.0.0 (2026-01-04): Initial fault tolerance patterns with watchdog, redundancy, and safe fallback guidance.

## Audit History
- **2026-01-04**: Audit performed. Verified:
  - Fault tolerance patterns technically accurate
  - IEC 60601-1 reference appropriate as informative for power/brownout considerations
  - Watchdog and redundancy patterns follow industry best practices
