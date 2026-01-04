---
skill_id: FW-INTERRUPTS
version: 1.0.0
last_updated: 2026-01-04
applies_to: [Class A, Class B, Class C]
jurisdiction: [Global]
prerequisites: [FW-EMBEDDED-C]
---

# Interrupt Handling in Medical Devices

## Purpose
Define safe interrupt design: short ISRs, deferred work, priority assignment, critical section management, and testing strategies.

## When to Apply
- Any ISR or interrupt-driven feature; safety-relevant timing/response paths.

## Requirements (testable)
1. ISR Minimalism: ISRs do minimal, non-blocking work; defer processing to tasks; no dynamic allocation. Rationale: predictability and latency.
2. Priority Scheme: Assign priorities to meet safety/timing; avoid unintentional preemption of critical tasks; document scheme. Rationale: correct responsiveness.
3. Shared Data Protection: Use atomic ops or proper locks (or disable interrupts briefly) for shared data; `volatile` for flags shared with ISRs. Rationale: data consistency.
4. Critical Sections: Keep interrupt masking short and bounded; no masking around unbounded loops. Rationale: latency control.
5. Reentrancy: ISR-invoked functions must be reentrant or protected; no non-reentrant libc calls in ISRs. Rationale: avoid corruption.
6. Testing: Provide ISR unit/integration tests where feasible; measure latency and service time; fault injection for missed/rapid interrupts. Rationale: verification.

## Recommended Practices
- Use double-buffering for ISR-produced data.
- Keep ISR code in fast memory if available; minimize branching.
- Provide statistics (count, overrun) for diagnostics.
- Avoid long chains of interrupt enabling/disabling; prefer fine-grained critical sections.

## Patterns
Deferred work:
```c
// REQ-INT-ISR-01; TEST-INT-03
volatile bool g_rx_ready = false;
void UART_IRQHandler(void) {
    clear_uart_irq();
    g_rx_ready = true; // defer to task
}
```

Atomic flag update:
```c
// REQ-INT-SHARED-02; TEST-INT-05
void set_flag_from_isr(void) {
    atomic_store_explicit(&g_flag, 1, memory_order_release);
}
```

Bounded critical section:
```c
// REQ-INT-CRIT-03; TEST-INT-07
uint32_t read_counter_atomic(void) {
    uint32_t primask = disable_irq();
    uint32_t v = g_counter;
    restore_irq(primask);
    return v;
}
```

## Anti-Patterns (risks)
- Heavy processing or blocking in ISR -> risk: latency, missed deadlines.
- Calling non-reentrant functions (e.g., printf) from ISR -> risk: corruption.
- Long interrupt masking -> risk: jitter and missed time-critical events.
- Shared data without synchronization -> risk: race conditions.

## Verification Checklist
- [ ] ISRs minimal, non-blocking, no heap; defer work to tasks.
- [ ] Interrupt priorities assigned/documented; critical ISRs prioritized appropriately.
- [ ] Shared data protected; volatile flags/atomics used; no data races.
- [ ] Critical sections short and bounded; masking limited.
- [ ] ISR-invoked functions reentrant or protected.
- [ ] Latency/service time measured; tests/fault injection performed.

## Traceability
- Use `REQ-INT-###`; link to tests `TEST-INT-###`; keep timing measurements with artifacts.

## References
- MCU vendor interrupt guidance; CMSIS recommendations.
- IEC 62304 timing and design expectations.

## Changelog
- 1.0.0 (2026-01-04): Initial interrupt handling skill with ISR minimalism, priority, and testing guidance.

## Audit History
- **2026-01-04**: Audit performed. Verified:
  - CMSIS recommendations accurately represented
  - ISR patterns follow embedded best practices
  - Atomic operations correctly used in examples
