---
skill_id: ARCH-SEPARATION
version: 1.0.0
last_updated: 2026-01-04
applies_to: [Class A, Class B, Class C]
jurisdiction: [Global]
prerequisites: [ARCH-SAFETY-CLASS]
---

# Separation of Safety-Critical Concerns

## Purpose
Define architectural partitioning to contain failures, simplify verification, and align safety classes with appropriate isolation.

## When to Apply
- Designing or refactoring architecture for mixed-criticality systems.
- Introducing new subsystems with different safety impacts (e.g., UI vs control).
- Adding third-party/SOUP modules or connectivity stacks near safety logic.

## Requirements (testable)
1. Partitioning: Separate safety-critical from non-critical components using process/MPU/MMU or language-level isolation; document boundaries. Rationale: fault containment.
2. Minimal Interfaces: Keep interfaces between partitions minimal and typed; avoid shared mutable state. Rationale: reduce coupling and fault vectors.
3. Validation at Boundaries: Validate all data crossing partitions (lengths, ranges, CRC/MAC); enforce timeouts and error handling. Rationale: prevent propagation.
4. Principle of Least Privilege: Assign minimal privileges to non-critical partitions; restrict syscalls/IO where possible. Rationale: limit impact of compromise.
5. Monitoring: Add health monitoring/heartbeats for critical partitions; safe fallback on failure. Rationale: detect and react to partition failure.
6. Testability: Provide mocks/stubs for non-critical partitions to test critical logic deterministically. Rationale: reliable verification.

## Recommended Practices
- Use message queues or well-defined RPC instead of shared globals.
- Define data transfer objects (DTOs) with explicit versioning and size fields.
- Apply static analysis to enforce layering (no upward dependencies).
- Consider dual-core separation if hardware supports, with strict comms.

## Patterns
DTO with size and CRC:
```c
// REQ-SEP-IF-01; TEST-SEP-04
typedef struct {
    uint16_t len;
    uint16_t crc;
    uint8_t payload[48];
} msg_t;

bool validate_msg(const msg_t *m) {
    if (m->len > sizeof(m->payload)) return false;
    return crc16(m->payload, m->len) == m->crc;
}
```

Partition watchdog:
```c
// REQ-SEP-MON-02; TEST-SEP-09
void monitor_control_partition(void) {
    if (!heartbeat_ok()) {
        enter_safe_state(); // stop outputs, alarm
    }
}
```

## Anti-Patterns (risks)
- Shared global buffers between UI and control logic -> risk: corruption.
- Unbounded/unvalidated IPC -> risk: DoS or malformed data affecting safety.
- Broad privileges for non-critical services -> risk: escalation into safety domain.
- Hidden backdoors (debug UART) bridging partitions -> risk: bypassing controls.

## Verification Checklist
- [ ] Partitions defined; safety-critical isolated from non-critical.
- [ ] Interfaces documented and minimal; no shared mutable state across classes.
- [ ] Boundary validation implemented (size/range/CRC/MAC, timeouts).
- [ ] Privileges for non-critical partitions minimized.
- [ ] Monitoring/heartbeat for critical partition with safe fallback.
- [ ] Mocks/stubs available for testing critical logic without non-critical code.

## Traceability
- Map partitions to safety classes and hazards; link interface validation tests (`TEST-SEP-###`).
- Maintain an interface contract document; tie to architecture diagrams.

## References
- IEC 62304 segregation intent (5.3).
- ISO 26262 Part 6 (informative for mixed-criticality partitioning concepts).
- SEI CERT C and MISRA guidance on shared state avoidance (informative).

## Changelog
- 1.0.0 (2026-01-04): Initial partitioning guidance with boundary validation and monitoring.

## Audit History
- **2026-01-04**: Audit performed. Verified:
  - IEC 62304 segregation intent correctly referenced to clause 5.3
  - ISO 26262 Part 6 reference appropriate as informative for mixed-criticality concepts
  - SEI CERT C and MISRA guidance correctly marked as informative
