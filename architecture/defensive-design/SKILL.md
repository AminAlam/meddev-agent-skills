---
skill_id: ARCH-DEFENSIVE
version: 1.0.0
last_updated: 2026-01-04
applies_to: [Class A, Class B, Class C]
jurisdiction: [Global]
prerequisites: [ARCH-SAFETY-CLASS]
---

# Defensive Programming for Medical Devices

## Purpose
Apply defensive coding techniques to prevent, detect, and safely handle abnormal conditions in safety-relevant software.

## When to Apply
- All safety-related modules; heightened rigor for Class B/C items.
- Input/output handling, hardware interactions, IPC, and configuration parsing.

## Requirements (testable)
1. Input Validation: Validate range, length, format of all external inputs; reject or sanitize invalid data. Rationale: prevent hazardous behavior and memory faults.
2. Output Bounds Checking: Enforce limits on actuators/outputs; clamp with alarms when exceeded. Rationale: prevent unsafe outputs.
3. Assertions and Guards: Use assertions for invariants in non-production or guarded builds; runtime checks for production where safety impact exists. Rationale: detect defects early.
4. Error Propagation: Return explicit error codes; avoid silent failures; ensure callers handle errors. Rationale: predictable handling.
5. Timeouts: Apply timeouts to blocking waits (I/O, IPC); on timeout, transition to safe/error handling. Rationale: avoid hangs.
6. Defensive Defaults: Fail closed/safe on config or sensor anomalies; prefer explicit initialization for all fields. Rationale: safe startup and operation.

## Recommended Practices
- Prefer explicit enums over magic numbers; exhaustive switch with default-safe handling.
- Zero-initialize structs; validate configuration at startup with a single validation function.
- Log abnormal conditions with context but avoid leaking sensitive data.
- Use compile-time checks (`static_assert`) for structure sizes, array lengths.

## Patterns
Input validation:
```c
// REQ-DEF-INPUT-01; TEST-DEF-03
bool validate_flow(float ml_hr) {
    return ml_hr >= 0.0f && ml_hr <= MAX_FLOW;
}
```

Output clamping with alarm:
```c
// REQ-DEF-OUT-02; TEST-DEF-05
float clamp_output(float cmd) {
    if (cmd > MAX_OUTPUT) {
        alarm_over_output();
        return MAX_OUTPUT;
    }
    if (cmd < MIN_OUTPUT) return MIN_OUTPUT;
    return cmd;
}
```

Timeout wrapper:
```c
// REQ-DEF-TIMEOUT-04; TEST-DEF-07
int read_with_timeout(int fd, uint8_t *buf, size_t len, uint32_t ms) {
    if (!poll_ready(fd, ms)) return -ETIMEDOUT;
    return read(fd, buf, len);
}
```

## Anti-Patterns (risks)
- Trusting external input without bounds checking -> risk: overflow, unsafe commands.
- Silent error swallowing (`return;` with no log/propagation) -> risk: hidden failure.
- Infinite waits with no timeout -> risk: deadlock/hang in critical path.
- Using uninitialized data -> risk: nondeterministic behavior.

## Verification Checklist
- [ ] Inputs validated (range/length/format) at boundaries.
- [ ] Outputs clamped with alarms for out-of-range commands.
- [ ] Assertions/guards present for invariants; runtime checks on safety paths.
- [ ] Errors propagated and handled; no silent failure paths.
- [ ] Blocking operations have timeouts; safe fallback on timeout.
- [ ] Defensive defaults applied; structures initialized explicitly.

## Traceability
- Tag defensive checks with requirement IDs (`REQ-DEF-###`) and link to tests.
- Keep logs of validation failures tied to fault handling requirements where applicable.

## References
- MISRA C/C++ defensive guidelines.
- IEC 62304 implementation discipline expectations.
- SEI CERT C secure coding (informative).

## Changelog
- 1.0.0 (2026-01-04): Initial defensive design guidance with validation, clamping, and timeout patterns.

## Audit History
- **2026-01-04**: Audit performed. Verified:
  - MISRA C/C++ defensive guideline references accurate
  - SEI CERT C reference appropriate as informative
  - Code examples follow stated defensive patterns correctly
