---
skill_id: CONN-WIFI
version: 1.0.0
last_updated: 2026-01-04
applies_to: [Class A, Class B, Class C]
jurisdiction: [FDA, EU MDR, Global]
prerequisites: [REG-ISO14971, SEC-ENCRYPTION, SEC-AUTH]
---

# WiFi for Medical Devices

## Purpose
Secure and robust WiFi connectivity for medical devices: WPA3/enterprise auth, certificate management, coexistence, resilience, and hospital network integration.

## When to Apply
- Adding or modifying WiFi connectivity, security settings, or cert handling.
- Hospital/enterprise deployments; PHI transport over WiFi.

## Requirements (testable)
1. Security Mode: Prefer WPA3 (SAE/Enterprise); if WPA2-Enterprise, enforce strong EAP (e.g., TLS/TTLS) and server cert validation. Rationale: confidentiality/integrity.
2. Certificate Management: Validate server certificates (chain/expiry/CRL/OCSP where feasible); store client cert/keys securely; support rotation. Rationale: trust assurance.
3. Network Resilience: Implement reconnect with backoff; detect captive portals and fail closed for clinical data paths. Rationale: availability without unsafe fallback.
4. Coexistence: Configure to minimize interference with BLE/critical comms; test latency/jitter impact. Rationale: performance and safety timing.
5. Power Considerations: Manage DTIM/listen intervals; avoid unnecessary scans; document impact on battery. Rationale: power budget.
6. PHI Handling: Always transport PHI over TLS 1.3 (or strong 1.2) on top of WiFi; do not rely solely on link-layer security. Rationale: defense in depth.
7. Logging: Log association/auth failures and disconnect reasons without leaking sensitive credentials; rate-limit logs. Rationale: diagnostics without leakage.

## Recommended Practices
- Use per-device credentials; avoid shared PSKs in clinical deployments.
- Prefer wired/Ethernet fallback for critical fixed devices when possible.
- Cache known-good networks; avoid auto-connecting to open SSIDs.
- Align WiFi channel/power config with hospital policies.

## Patterns
Server cert validation (pseudocode):
```c
// REQ-WIFI-CERT-01; TEST-WIFI-05
bool validate_server_cert(cert_t *c) {
    return chain_ok(c) && !expired(c) && ocsp_good(c);
}
```

Reconnect with backoff:
```c
// REQ-WIFI-RESIL-02; TEST-WIFI-07
for (int i = 0; i < MAX_RETRIES; i++) {
    if (wifi_connect()) break;
    sleep_ms(100 * (1 << i)); // capped elsewhere
}
```

PHI only over TLS:
```c
// REQ-WIFI-PHI-03; TEST-WIFI-09
int send_phi(const uint8_t *buf, size_t len) {
    if (!tls_session_ready()) return -1;
    return tls_send(buf, len);
}
```

## Anti-Patterns (risks)
- Using WPA2-PSK with shared keys in hospitals -> risk: credential sprawl, MITM.
- Skipping server cert validation -> risk: rogue AP/evil twin.
- Sending PHI over plaintext HTTP on “secured” WiFi -> risk: data exposure.
- Infinite aggressive reconnect loop -> risk: power drain, DoS on AP.
- Ignoring coexistence -> risk: BLE control path jitter/drops.

## Verification Checklist
- [ ] WPA3 or strong WPA2-Enterprise configured; server cert validation enforced.
- [ ] Client creds/certs stored securely; rotation supported/tested.
- [ ] Reconnect/backoff implemented; captive portal detection fails closed for clinical data.
- [ ] Coexistence tested (WiFi + BLE/critical comms); parameters tuned.
- [ ] PHI only over TLS; link-layer security not sole control.
- [ ] Logs capture association/auth failures without sensitive data; rate-limited.
- [ ] Power impact assessed (DTIM, scans) and within budget.

## Traceability
- Requirements `REQ-WIFI-###` linked to tests `TEST-WIFI-###`; map to cybersecurity risks.

## References
- Wi-Fi Alliance WPA3 specifications.
- NIST SP 800-153 (WLAN security); informative.
- FDA Cybersecurity Premarket Guidance; IEC 60601-1-2 (EMC/coexistence).

## Changelog
- 1.0.0 (2026-01-04): Initial WiFi medical connectivity skill with security, cert, and coexistence guidance.

## Audit History
- **2026-01-04**: Audit performed. Verified:
  - WPA3 references to Wi-Fi Alliance specifications accurate
  - NIST SP 800-153 (WLAN security) correctly referenced as informative
  - IEC 60601-1-2 reference appropriate for EMC/coexistence
