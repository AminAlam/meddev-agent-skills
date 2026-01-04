---
skill_id: FW-MEMORY
version: 1.0.0
last_updated: 2026-01-04
applies_to: [Class A, Class B, Class C]
jurisdiction: [Global]
prerequisites: [FW-EMBEDDED-C]
---

# Memory Management for Safety-Critical Systems

## Purpose
Ensure deterministic and safe memory usage: static allocation, pools, stack sizing, MPU usage, and corruption detection for medical device firmware.

## When to Apply
- Any code handling buffers, dynamic data, ISR/RTOS stacks.
- Introducing third-party libs with allocations; configuring MPU/MMU.

## Requirements (testable)
1. Static Allocation Preference: Use static or stack allocation for safety-critical paths; avoid heap unless bounded and justified. Rationale: determinism.
2. Memory Pools: If dynamic behavior needed, use fixed-size pools with bounded allocation time and failure handling. Rationale: predictability.
3. Stack Analysis: Analyze stack usage per task/ISR with margin; enable overflow detection/guards. Rationale: prevent corruption.
4. MPU/MMU Protections: Configure MPU/MMU to protect code, read-only data, and segregate critical data regions; no-exec where possible. Rationale: containment.
5. Bounds Checking: Enforce bounds on all buffer operations; avoid unsafe functions; use length-checked variants. Rationale: prevent overflows.
6. Initialization: Zero-init all memory before use; avoid reading uninitialized data. Rationale: determinism and safety.
7. Corruption Detection: Use canaries/guards for critical buffers; CRC on critical stored data. Rationale: detect latent faults.

## Recommended Practices
- Centralize alloc/free wrappers; forbid raw malloc/free in safety modules.
- Use linker scripts to place critical data separately and guard with MPU.
- Periodically scrub/clear sensitive data (keys, credentials) per security needs.
- Add lightweight heap diagnostics if heap is permitted outside safety path.

## Patterns
Fixed pool allocator:
```c
// REQ-MEM-POOL-01; TEST-MEM-03
typedef struct { bool used; uint8_t buf[64]; } blk_t;
static blk_t pool[8];

void *pool_alloc(void) {
    for (size_t i = 0; i < 8; i++) {
        if (!pool[i].used) { pool[i].used = true; return pool[i].buf; }
    }
    return NULL; // handle failure
}
```

Bounds-checked copy:
```c
// REQ-MEM-BOUND-02; TEST-MEM-05
bool copy_payload(uint8_t *dst, size_t dst_len, const uint8_t *src, size_t src_len) {
    if (src_len > dst_len) return false;
    memcpy(dst, src, src_len);
    return true;
}
```

Stack guard (RTOS example):
```c
// REQ-MEM-STACK-04; TEST-MEM-07
configCHECK_FOR_STACK_OVERFLOW == 2
```

## Anti-Patterns (risks)
- Unbounded malloc/free in control loop -> risk: fragmentation, failure.
- Ignoring stack sizing -> risk: silent stack overflow corrupting state.
- Shared buffers without length checks -> risk: overflow and data corruption.
- Disabling MPU or running everything RWX -> risk: corruption/execution of data.

## Verification Checklist
- [ ] Safety paths use static or pooled allocation; no raw heap in safety code.
- [ ] Pools bounded; allocation failure handled deterministically.
- [ ] Stack sizes analyzed/measured; overflow detection enabled.
- [ ] MPU/MMU protections configured; code RO, data segregated, NX where available.
- [ ] All buffer ops bounds-checked; unsafe libc calls avoided.
- [ ] Memory zero-initialized; no uninitialized reads.
- [ ] Corruption detection (canaries/CRC) in place for critical data/buffers.

## Traceability
- Use `REQ-MEM-###`; link to tests and to MPU/linker configuration artifacts.

## References
- MISRA C/C++ rules on dynamic memory.
- IEC 62304 implementation discipline for Class B/C determinism.
- CWE-119/120/787 (informative) for buffer overflows.

## Changelog
- 1.0.0 (2026-01-04): Initial memory management skill with pools, MPU, and bounds checking.

## Audit History
- **2026-01-04**: Audit performed. Verified:
  - MISRA C/C++ dynamic memory rules correctly referenced
  - CWE references (CWE-119/120/787) accurate for buffer overflow classifications
  - Memory pool patterns technically sound
