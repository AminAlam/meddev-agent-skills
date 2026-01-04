---
skill_id: CONN-BLE
version: 1.0.0
last_updated: 2026-01-04
applies_to: [Class A, Class B, Class C]
jurisdiction: [FDA, EU MDR, Global]
prerequisites: [REG-ISO14971, FW-EMBEDDED-C, SEC-ENCRYPTION, SEC-AUTH]
---

# Bluetooth Low Energy for Medical Devices

## Purpose
Guide secure, reliable BLE implementation for medical devices handling PHI/therapy control: services, pairing/bonding, LE Secure Connections, privacy, and performance.

## When to Apply
- Adding/updating BLE services, characteristics, pairing flows, or security settings.
- Handling PHI or control commands over BLE.
- Coexistence with WiFi or other radios.

## Requirements (testable)
1. Security Mode: Use LE Secure Connections, authenticated pairing, and encryption for PHI/control; disallow Just Works for PHI/control paths. Rationale: confidentiality/integrity.
2. Bonding & Keys: Store bonds securely; support key rotation/invalidation; handle lost/changed keys gracefully. Rationale: access control.
3. GATT Design: Define characteristics with explicit permissions; validate lengths/ranges; separate PHI from non-PHI where possible. Rationale: least privilege and data protection.
4. Privacy: Enable address privacy (RPA) and limit advertising data to non-sensitive info. Rationale: reduce tracking and PHI leakage.
5. Connection Parameters: Set parameters to balance latency/power while meeting safety timing; document rationale. Rationale: performance vs responsiveness.
6. Error Handling: Fail closed on malformed requests; rate-limit; disconnect on repeated failures. Rationale: robustness against abuse.
7. Regulatory: Document wireless coexistence and risk controls; align with FDA cybersecurity and MDR expectations for wireless (interference, security). Rationale: compliance.

## Recommended Practices
- Use whitelisting/peripheral-side filters for allowed peers where applicable.
- Keep OTA/service control on authenticated+encrypted links only.
- Log pairing/auth failures (without sensitive data); expose metrics.
- Test RF coexistence (BLE + WiFi) for timing-sensitive functions.

## Patterns
Secure pairing requirement (pseudocode):
```c
// REQ-BLE-SEC-01; TEST-BLE-05
void ble_on_pair_request(bool mitm, bool lesc) {
    if (!mitm || !lesc) {
        reject_pair();
    } else {
        accept_pair();
    }
}
```

GATT characteristic with permissions:
```c
// REQ-BLE-GATT-02; TEST-BLE-07
const gatt_char_t glucose_meas = {
    .uuid = GLUCOSE_MEAS_UUID,
    .props = READ | NOTIFY,
    .perm = AUTHENTICATED | ENCRYPTED,
    .max_len = sizeof(glucose_meas_t),
};
```

Length validation on write:
```c
// REQ-BLE-VALID-03; TEST-BLE-09
int on_cmd_write(const uint8_t *data, uint16_t len) {
    if (len != sizeof(cmd_t)) return ERR_LEN;
    if (!crc_ok(data, len)) return ERR_CRC;
    return handle_cmd((const cmd_t *)data);
}
```

## Anti-Patterns (risks)
- Using Just Works for PHI/control -> risk: MITM, data exposure.
- Plaintext characteristics with PHI -> risk: confidentiality breach.
- Accepting variable-length writes without validation -> risk: overflow/DoS.
- Advertising PHI/device identifiers -> risk: privacy violation.
- No handling for bond loss/rotation -> risk: denial of service or unintended access.

## Verification Checklist
- [ ] LE Secure Connections + authenticated pairing enforced; Just Works disabled for PHI/control.
- [ ] Bond storage secure; rotation/invalidation supported; loss handled.
- [ ] GATT perms set; lengths/ranges validated; PHI separated/minimized.
- [ ] Privacy features (RPA) enabled; advertising data non-sensitive.
- [ ] Connection params justified for safety timing and power.
- [ ] Malformed/abuse handling present (rate-limit, disconnect).
- [ ] Coexistence and regulatory wireless security risks addressed in risk file.

## Traceability
- Tag requirements `REQ-BLE-###` to tests `TEST-BLE-###`; link to cybersecurity risk controls.

## References
- Bluetooth Core Spec v5.x (LE Secure Connections, GAP security modes).
- Bluetooth SIG Medical profiles (GLP, HTP) for interoperability.
- FDA Cybersecurity Premarket Guidance (wireless).
- IEC 60601-1-2 (EMC considerations; informative).

## Changelog
- 1.0.0 (2026-01-04): Initial BLE medical connectivity skill with security, privacy, and validation patterns.

## Audit History
- **2026-01-04**: Audit performed. Verified:
  - Bluetooth Core Spec v5.x LE Secure Connections references accurate
  - GLP/HTP profile references for medical profiles correct
  - IEC 60601-1-2 reference appropriate for EMC considerations
