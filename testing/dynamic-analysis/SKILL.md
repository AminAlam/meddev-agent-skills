---
skill_id: TEST-DAST
version: 1.0.0
last_updated: 2026-01-04
applies_to: [Class A, Class B, Class C]
jurisdiction: [Global]
prerequisites: [FW-EMBEDDED-C, FW-RTOS-PATTERNS]
---

# Dynamic Analysis

## Purpose
Detect runtime defects (memory, concurrency, timing, performance, power) via dynamic tools and instrumentation in medical device software.

## When to Apply
- New features touching memory/concurrency/timing.
- Pre-release test campaigns; after major refactors.

## Requirements (testable)
1. Memory Checks: Run dynamic memory error detection (ASan/Valgrind-like on host or target tools) for host-testable code. Rationale: catch leaks/overflows/use-after-free.
2. Concurrency: Use thread/lock analysis where available; instrument for deadlock/livelock detection. Rationale: concurrency safety.
3. Timing/Performance: Measure critical path timing against requirements; detect overruns; log and assert as needed. Rationale: safety timing.
4. Power Profiling: For battery devices, measure power in representative scenarios; verify within budget. Rationale: safety/availability.
5. Logging/Instrumentation: Enable sufficient logging counters/metrics for runtime checks; avoid excessive overhead in production builds. Rationale: observability.

## Recommended Practices
- Use hardware tracing/profiling (ETM/ITM) where available.
- Run sanitizers in CI for host portions; use target sanitizers for embedded if supported.
- Automate performance/timing tests in integration rigs.

## Patterns
Timing assertion:
```c
// REQ-DAST-TIME-01; TEST-DAST-04
uint32_t t0 = timer_now_us();
run_control_loop();
assert(timer_now_us() - t0 < 5000); // 5 ms
```

Memory diagnostics hook:
```c
// REQ-DAST-MEM-02; TEST-DAST-06
void *my_malloc(size_t sz) {
    void *p = malloc(sz);
    log_alloc(p, sz);
    return p;
}
```

## Anti-Patterns (risks)
- Skipping runtime checks because “unit tests pass” -> risk: missed concurrency/timing bugs.
- Disabling logs/metrics with no alternate observability -> risk: opaque failures.
- Ignoring power profiling -> risk: brownouts or spec violations.

## Verification Checklist
- [ ] Memory dynamic checks run for host-testable code; issues triaged.
- [ ] Concurrency/lock checks applied where available; deadlock tests run.
- [ ] Timing of critical paths measured vs requirements; overruns handled.
- [ ] Power measured against budget for key scenarios.
- [ ] Instrumentation/logging available for runtime diagnostics; overhead acceptable.

## Traceability
- `REQ-DAST-###` to `TEST-DAST-###`; timing/power results stored with test artifacts.

## References
- Tool-specific guides (ASan/TSan/Valgrind); MCU vendor tracing docs.
- IEC 62304 timing considerations; ISO 14971 for risk-based focus.

## Changelog
- 1.0.0 (2026-01-04): Initial dynamic analysis skill with memory, concurrency, timing, and power focus.

## Audit History
- **2026-01-04**: Audit performed. Verified:
  - ASan/TSan/Valgrind tool references are accurate
  - Timing assertion patterns are technically sound
  - Memory diagnostics patterns are appropriate
