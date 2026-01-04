---
skill_id: FW-RTOS-PATTERNS
version: 1.0.0
last_updated: 2026-01-04
applies_to: [Class A, Class B, Class C]
jurisdiction: [Global]
prerequisites: [FW-EMBEDDED-C, ARCH-SAFETY-CLASS]
---

# RTOS Patterns for Medical Devices

## Purpose
Provide safe RTOS usage patterns: task design, priorities, IPC, deadlines, priority inversion avoidance, and timing analysis for medical devices.

## When to Apply
- RTOS-based firmware for safety-related functions.
- Designing task sets, IPC, or timing-sensitive features.

## Requirements (testable)
1. Task Design: Each task has a defined purpose, period/deadline, and priority justified by safety impact. Rationale: predictability.
2. Priority Assignment: Higher priority for safety-critical/timing-critical tasks; avoid priority inversion; document scheme. Rationale: timely execution.
3. IPC Discipline: Use bounded queues; validate message sizes; avoid blocking indefinitely; check return codes. Rationale: robustness.
4. Synchronization: Use mutexes with priority inheritance/ceiling; avoid holding locks in high-priority tasks; no blocking in ISRs. Rationale: avoid inversion/deadlocks.
5. Deadline Handling: Monitor execution times; detect overruns; degrade or go safe on sustained misses. Rationale: meeting safety timing.
6. Stack Sizing: Size stacks with margin based on analysis/measurement; enable stack overflow detection where available. Rationale: prevent corruption.
7. Timing Analysis: Perform schedulability or worst-case response analysis for critical tasks; revisit on changes. Rationale: timing assurance.

## Recommended Practices
- Use deferred interrupt handling (ISR signals a task).
- Keep IPC schemas versioned; include length and CRC.
- Avoid dynamic memory for queues in safety paths; statically allocate.
- Instrument runtime (e.g., trace hooks) to measure execution and latency.

## Patterns
Deferred ISR work:
```c
// REQ-RTOS-ISR-01; TEST-RTOS-03
static SemaphoreHandle_t data_sem;
void UART_IRQHandler(void) {
    BaseType_t hpw = pdFALSE;
    clear_irq();
    xSemaphoreGiveFromISR(data_sem, &hpw);
    portYIELD_FROM_ISR(hpw);
}
```

Bounded queue send with timeout:
```c
// REQ-RTOS-IPC-02; TEST-RTOS-05
bool send_cmd(cmd_t *cmd) {
    return xQueueSend(cmd_queue, cmd, pdMS_TO_TICKS(10)) == pdPASS;
}
```

Deadline monitor:
```c
// REQ-RTOS-TIME-04; TEST-RTOS-09
void vTaskControl(void *arg) {
    for (;;) {
        TickType_t start = xTaskGetTickCount();
        run_control_loop();
        if (xTaskGetTickCount() - start > pdMS_TO_TICKS(5)) {
            log_overrun();
            enter_safe_state();
        }
        vTaskDelayUntil(&start, pdMS_TO_TICKS(10));
    }
}
```

## Anti-Patterns (risks)
- Same priority for critical and non-critical tasks -> risk: starvation or jitter.
- Blocking calls without timeout in control tasks -> risk: deadlock/hang.
- ISRs doing heavy work or taking mutexes -> risk: latency, inversion.
- Unbounded queues or unchecked send/recv -> risk: overflow, data loss.
- Ignoring stack usage -> risk: silent corruption.

## Verification Checklist
- [ ] Task priorities/periods documented and justified; critical tasks highest feasible.
- [ ] IPC uses bounded queues; timeouts set; return codes checked.
- [ ] Mutexes with PI/ceiling; no blocking in ISRs; lock durations minimized.
- [ ] Deadline/overrun monitoring implemented for critical tasks.
- [ ] Stack sizes analyzed/measured; overflow detection enabled.
- [ ] Timing/schedulability reviewed after changes to tasks or priorities.

## Traceability
- Map `REQ-RTOS-###` to tasks and tests (`TEST-RTOS-###`); record timing evidence.

## References
- FreeRTOS, Zephyr, ThreadX safety notes (vendor safety manuals if available).
- IEC 62304 timing and segregation considerations.
- ISO 14971 risk basis for timing failures.

## Changelog
- 1.0.0 (2026-01-04): Initial RTOS patterns with priority, IPC, deadline, and stack guidance.

## Audit History
- **2026-01-04**: Audit performed. Verified:
  - FreeRTOS API examples are accurate (xSemaphoreGiveFromISR, portYIELD_FROM_ISR, xQueueSend, etc.)
  - Priority inversion concepts correctly explained
  - Deadline monitoring patterns technically sound
