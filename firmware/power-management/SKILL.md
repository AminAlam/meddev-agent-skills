---
skill_id: FW-POWER
version: 1.0.0
last_updated: 2026-01-04
applies_to: [Class A, Class B, Class C]
jurisdiction: [Global]
prerequisites: [FW-EMBEDDED-C]
---

# Power Management for Battery-Operated Medical Devices

## Purpose
Define safe power management patterns: sleep modes, wake sources, power budget, battery monitoring, graceful shutdown, and data preservation.

## When to Apply
- Battery-operated or portable devices; low-power modes; brownout handling.
- Adding/adjusting sleep policies or power domains.

## Requirements (testable)
1. Sleep/Wake Policy: Define allowed sleep states and wake sources; ensure critical monitoring preserved. Rationale: avoid missing safety events.
2. Power Budget: Establish budget per mode; verify high-load features fit within limits. Rationale: battery life and thermal safety.
3. Battery Monitoring: Monitor voltage/SOC with thresholds; annunciate low/critical; throttle or safe shutdown when critical. Rationale: prevent unsafe operation on low power.
4. Brownout Handling: Detect brownout; enter safe state and preserve critical data; avoid unstable operation. Rationale: prevent corruption/unsafe outputs.
5. Persistent Data Integrity: Use CRC/ECC and atomic writes for retained data; verify on startup. Rationale: data reliability.
6. Wake Handling: Validate wake source; debounce to avoid rapid cycles; reinitialize peripherals safely. Rationale: stable resume.

## Recommended Practices
- Isolate safety monitoring from aggressive sleep (keep minimal always-on domain).
- Stagger high-current events; avoid simultaneous radio + motor where possible.
- Log power events and thresholds crossed for diagnostics.
- Test across temperature/voltage corners.

## Patterns
Low battery handling:
```c
// REQ-PWR-BATT-01; TEST-PWR-04
void handle_battery(float vbat) {
    if (vbat < VBAT_CRIT) {
        annunciate_low_batt();
        save_state_crc();
        enter_safe_shutdown();
    } else if (vbat < VBAT_WARN) {
        annunciate_low_batt();
    }
}
```

Brownout interrupt:
```c
// REQ-PWR-BROWN-02; TEST-PWR-06
void BOD_IRQHandler(void) {
    clear_bod_irq();
    save_state_crc();
    enter_safe_shutdown();
}
```

Atomic retained write:
```c
// REQ-PWR-DATA-03; TEST-PWR-08
bool save_state_crc(void) {
    state_t s = collect_state();
    s.crc = crc32(&s, sizeof(s) - sizeof(s.crc));
    return write_retained_atomic(&s, sizeof(s));
}
```

## Anti-Patterns (risks)
- Deep sleep disabling critical monitoring/alarms -> risk: missed safety events.
- No brownout handling -> risk: corrupted state, unsafe outputs during voltage sag.
- Writing retained data without integrity checks -> risk: silent corruption.
- Aggressive radio/motor use without budget -> risk: brownout or thermal issues.

## Verification Checklist
- [ ] Sleep/wake policy defined; critical monitoring maintained.
- [ ] Power budget documented; high-load features assessed.
- [ ] Battery monitoring thresholds set; warnings/critical handling implemented.
- [ ] Brownout detection and safe shutdown implemented/tested.
- [ ] Persistent data uses CRC/ECC and atomic writes; verified on startup.
- [ ] Wake source validation and peripheral reinit implemented.
- [ ] Power event logging and corner testing performed.

## Traceability
- Use `REQ-PWR-###` and `TEST-PWR-###`; link to risk controls for power loss hazards.

## References
- IEC 60601-1 (power safety considerations; informative).
- IEC 62304 for safe state handling.

## Changelog
- 1.0.0 (2026-01-04): Initial power management guidance with brownout, battery, and data integrity patterns.

## Audit History
- **2026-01-04**: Audit performed. Verified:
  - IEC 60601-1 reference appropriate as informative for power safety
  - Brownout and battery monitoring patterns technically accurate
  - Atomic write patterns for data integrity are sound
