---
skill_id: FW-EMBEDDED-C
version: 1.0.0
last_updated: 2026-01-04
applies_to: [Class A, Class B, Class C]
jurisdiction: [Global]
prerequisites: [ARCH-DEFENSIVE, ARCH-SAFETY-CLASS]
---

# Embedded C Coding Standards for Medical Devices

## Purpose
Define C coding practices aligned with MISRA C and medical device safety needs: type safety, control flow, memory management, interrupts, and static analysis.

## When to Apply
- All C firmware code for safety-related device functions.
- New modules, refactors, or code reviews affecting safety classes.

## Requirements (testable)
1. Types: Use fixed-width integers (`uint32_t`, etc.); avoid implicit type promotions; enable warnings-as-errors (`-Wall -Wextra -Werror`). Rationale: predictability.
2. Const Correctness: Mark read-only data/parameters `const`; avoid casting away const. Rationale: prevent unintended mutation.
3. Control Flow: No recursion; bounded loops; single exit per function preferred unless clarity dictates otherwise. Rationale: analyzability.
4. Memory: Avoid dynamic allocation in safety-critical paths; prefer static or pooled allocation; no unchecked `malloc`. Rationale: determinism.
5. Pointer Safety: No pointer arithmetic on unrelated objects; check for null before deref; avoid double-free; restrict casts. Rationale: memory safety.
6. Interrupt Safety: ISRs minimal, no blocking, defer work to threads; protect shared data with proper primitives; volatile on shared flags. Rationale: correctness under concurrency.
7. Complexity: Maintain function size and cyclomatic complexity within agreed limits; refactor large functions. Rationale: testability and reviewability.
8. Includes & Headers: Use include guards; separate interface in headers; no hidden macros; document ownership of globals. Rationale: clarity and hygiene.
9. Static Analysis: Run MISRA checks and SAST; address findings or document justified deviations. Rationale: defect prevention.

## Recommended Practices
- Use `static inline` for simple accessors; minimize macros.
- Prefer enums over macros for states/constants; ensure exhaustive switch.
- Keep module-level ownership clear; avoid global mutable state.
- Use `static_assert` for sizes and assumptions where compiler supports.
- Document timing constraints near code (e.g., ISR max latency).

## Patterns
Fixed-width types and const:
```c
// REQ-C-TYPE-01; TEST-C-01
static uint32_t sum_samples(const uint16_t *samples, size_t n) {
    uint32_t acc = 0U;
    for (size_t i = 0; i < n; i++) {
        acc += samples[i];
    }
    return acc;
}
```

Static buffer, no malloc:
```c
// REQ-C-MEM-02; TEST-C-05
static uint8_t rx_buf[128];
size_t uart_read_safe(uint8_t *out, size_t max_len) {
    size_t n = uart_read(rx_buf, sizeof(rx_buf));
    if (n > max_len) n = max_len;
    memcpy(out, rx_buf, n);
    return n;
}
```

ISR defers work:
```c
// REQ-C-ISR-03; TEST-C-10
volatile bool g_data_ready = false;
void UART_IRQHandler(void) {
    clear_irq();
    g_data_ready = true; // minimal work
}
```

## Anti-Patterns (risks)
- Heap allocation in control loops -> risk: fragmentation, failure to allocate.
- Recursion or unbounded loops -> risk: stack overflow, non-termination.
- Large ISRs doing I/O or blocking -> risk: missed deadlines, priority inversion.
- Implicit int/enum conversions without checks -> risk: overflow/undefined behavior.
- Ignoring MISRA/SAST findings -> risk: latent defects.

## Verification Checklist
- [ ] Fixed-width types used; warnings as errors enabled.
- [ ] Const correctness applied; no casts removing const without justification.
- [ ] No recursion; loops bounded; complexity within limits.
- [ ] No dynamic allocation in safety paths; pools/static used; no unchecked malloc.
- [ ] Pointer use validated; null checks present; casts justified.
- [ ] ISRs minimal; shared data protected; volatile flags used where appropriate.
- [ ] Headers guarded; interfaces clean; globals ownership documented.
- [ ] MISRA/static analysis run; deviations documented; findings resolved.

## Traceability
- Tag requirements as `REQ-C-###`; link to unit tests `TEST-C-###` and MISRA deviation records.
- Store tool reports with build artifacts for the release.

## References
- MISRA C:2012 with Amendment 1 (2016), Amendment 2 (2020), and Amendment 3 (2024) guidelines.
- MISRA C:2023 (Third Edition) - consider for new projects.
- IEC 62304 implementation discipline expectations.
- SEI CERT C (informative).

## Changelog
- 1.0.1 (2026-01-04): Audit correction - updated MISRA C references to include all amendments and MISRA C:2023.
- 1.0.0 (2026-01-04): Initial embedded C skill with MISRA-aligned rules, ISR handling, and static analysis.

## Audit History
- **2026-01-04**: Audit performed. Corrections:
  - MISRA C:2012 Amendment 2 reference expanded to include all amendments (1, 2, 3)
  - Added reference to MISRA C:2023 (Third Edition)
  - Code examples verified for C11 compliance and MISRA alignment
