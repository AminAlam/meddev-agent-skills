---
skill_id: CONN-USB
version: 1.0.0
last_updated: 2026-01-04
applies_to: [Class A, Class B, Class C]
jurisdiction: [Global]
prerequisites: [FW-EMBEDDED-C, REG-ISO14971]
---

# USB for Medical Devices

## Purpose
Implement safe USB device connectivity: class selection, enumeration handling, data validation, electrical and safety considerations.

## When to Apply
- Adding/updating USB device functions (CDC, HID, MSC, custom).
- Handling PHI or control over USB.
- Managing firmware update or diagnostics via USB.

## Requirements (testable)
1. Class Selection: Choose appropriate USB class; avoid custom class unless justified; document host driver expectations. Rationale: interoperability and supportability.
2. Enumeration Robustness: Validate descriptors; handle stalls/timeouts; retry with limits; no busy loops in ISR context. Rationale: robustness.
3. Data Validation: Validate lengths, types, and ranges on endpoint data; avoid trusting host input. Rationale: prevent overflow/unsafe commands.
4. Control vs Data Separation: Separate control endpoints from bulk data; ensure control writes are authenticated if they affect safety/config. Rationale: safety and security.
5. Power & Electrical: Respect VBUS detection; do not source power when not allowed; handle suspend/resume correctly. Rationale: electrical safety.
6. Firmware Update over USB: Require signed packages; verify before apply; atomic update/rollback. Rationale: integrity.
7. PHI Protection: Encrypt PHI over USB (application layer) if data stored/transported; do not rely solely on physical link. Rationale: confidentiality.

## Recommended Practices
- Rate-limit control requests; track malformed request counts and detach on abuse.
- Use composite devices only when necessary; document interface mapping.
- Provide deterministic error codes for host logs.
- If using MSC for logs, ensure logs are sanitized of PHI or encrypted.

## Patterns
Control request validation:
```c
// REQ-USB-CTL-01; TEST-USB-04
int handle_ctrl_req(const usb_ctrl_req_t *r) {
    if (r->wLength > MAX_CTRL_LEN) return STALL;
    if (!is_supported_req(r->bRequest)) return STALL;
    return dispatch_req(r);
}
```

Firmware update guard:
```c
// REQ-USB-OTA-02; TEST-USB-07
int handle_fw_update(const uint8_t *buf, size_t len) {
    if (!verify_signature(buf, len)) return -1;
    return apply_update_atomically(buf, len);
}
```

VBUS handling:
```c
// REQ-USB-PWR-03; TEST-USB-09
void usb_vbus_changed(bool present) {
    if (present) enable_pullups();
    else disable_pullups();
}
```

## Anti-Patterns (risks)
- Blindly trusting host control requests -> risk: arbitrary config change, memory issues.
- Unsigned firmware updates over USB -> risk: malware injection.
- Ignoring VBUS -> risk: back-powering host or undefined behavior.
- Using custom class without driver plan -> risk: poor interoperability.

## Verification Checklist
- [ ] USB class choice justified; drivers documented.
- [ ] Enumeration and control handling validated with bounds and timeouts.
- [ ] Endpoint data validated; control vs data separated; auth for safety/config controls.
- [ ] VBUS/suspend/resume handled; power rules respected.
- [ ] USB firmware update path uses signature verification and atomic apply/rollback.
- [ ] PHI over USB encrypted at application layer if applicable.
- [ ] Abuse/malformed request handling and rate limits in place.

## Traceability
- Use `REQ-USB-###` and `TEST-USB-###`; link firmware update controls to security skill.

## References
- USB 2.0/3.x specs; class specs (CDC, HID, MSC, DFU).
- FDA cybersecurity guidance for update integrity (informative).

## Changelog
- 1.0.0 (2026-01-04): Initial USB skill with class selection, validation, and secure update guidance.

## Audit History
- **2026-01-04**: Audit performed. Verified:
  - USB 2.0/3.x spec references accurate
  - USB class specs (CDC, HID, MSC, DFU) correctly mentioned
  - VBUS and power handling patterns technically sound
