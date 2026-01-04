---
skill_id: REG-IEC62443
version: 1.0.0
last_updated: 2026-01-04
applies_to: [Class A, Class B, Class C]
jurisdiction: [Global]
prerequisites: [REG-ISO14971]
---

# IEC 62443 for Networked Medical Devices

## Purpose
Apply IEC 62443 concepts (secure development lifecycle, component requirements, security levels) to networked medical devices, ensuring threat-aware design, implementation, and verification of cybersecurity controls.

## When to Apply
- Networked or interoperable medical devices (wired/wireless).
- Adding or modifying network services, remote access, OTA updates.
- Introducing third-party network stacks or protocol libraries (SOUP).
- Security level (SL) determination or reassessment.

## Requirements (testable)
1. Security Level Targeting: Define security level (SL 1–4) for relevant zones/conduits; justify based on threat model and environment. Rationale: scope controls.
2. Threat Modeling: Perform and maintain threat models (STRIDE or similar) for networked components; map threats to controls. Rationale: risk-driven controls.
3. Secure SDLC Activities: Include security requirements, code review, SAST/DAST, dependency scanning, and security testing per IEC 62443-4-1 practices. Rationale: lifecycle assurance.
4. Component Requirements: Implement applicable technical requirements from IEC 62443-4-2 (e.g., authentication, encryption, integrity, audit, resource control) per SL. Rationale: consistent control set.
5. Identity & Access Control: Enforce role-based access and mutual authentication for remote interfaces; avoid shared credentials. Rationale: restrict access.
6. Secure Communication: Use authenticated, encrypted channels (e.g., TLS 1.3, DTLS) for data in transit; protect keys. Rationale: confidentiality/integrity.
7. Patch & Vulnerability Management: Maintain a process to receive, assess, and patch vulnerabilities; time-bound remediation targets. Rationale: reduce exposure.
8. Logging & Audit: Implement integrity-protected audit logs for security-relevant events; ensure time synchronization. Rationale: forensics and monitoring.
9. Resource & DoS Protections: Input validation, rate limiting, and watchdogs for networked services; validate message sizes and timeouts. Rationale: robustness.
10. Secure Boot & Updates Linkage: Verify firmware/software integrity and signatures; enforce rollback protection; align with secure-boot/OTA skills. Rationale: chain of trust.

## Recommended Practices
- Partition network services into lower-privilege processes; use MPU/MMU separation where available.
- Minimize open ports/services; default-deny firewall rules on device.
- Enforce least-privilege for service accounts and IPC permissions.
- Maintain SBOM with CVE monitoring; include network stack components.
- Include fuzzing for protocol parsers aligned to SL targets.

## Patterns
Mutual TLS for device-to-server:
```c
// REQ-62443-AC-01, RISK-CTRL-NTW-03, SL2
tls_session_t *connect_secure(const char *host) {
    tls_session_t *s = tls_new();
    tls_set_ca(s, ca_cert);          // verify server
    tls_set_client_cert(s, dev_cert, dev_key); // verify device
    tls_set_min_version(s, TLS1_3);
    tls_enable_ocsp(s, true);
    if (tls_connect(s, host, 443) != 0) {
        audit_log("EV-CONN-FAIL", host); // TEST-SEC-12
        return NULL;
    }
    return s;
}
```

Rate limiting / input validation:
```c
// REQ-62443-RES-02: prevent oversized messages; RISK-CTRL-NTW-07
int handle_msg(const uint8_t *buf, size_t len) {
    if (len > MAX_MSG) {
        audit_log("EV-DROP-LEN", NULL);
        return -1;
    }
    return parse_and_dispatch(buf, len);
}
```

Security logging (tamper-evident hash chaining):
```c
// LOG-01: hash-chained audit log; TEST-LOG-03 verifies chain
typedef struct { uint8_t hash[32]; audit_event_t ev; } audit_entry_t;
```

## Anti-Patterns (risks)
- Open debug ports/services in production firmware -> risk: unauthorized access (SL violation).
- Plaintext management interfaces -> risk: credential theft, tampering.
- Shared/default credentials -> risk: mass compromise.
- No vulnerability handling SLA -> risk: prolonged exposure.
- Unbounded message parsing -> risk: DoS or buffer overflow.

## Verification Checklist
- [ ] Security level(s) defined and justified for zones/conduits.
- [ ] Threat model current; controls mapped to threats.
- [ ] Secure SDLC activities executed (SAST/DAST/depscan/review) with evidence.
- [ ] Authentication/authorization enforced for remote interfaces; no shared creds.
- [ ] Communications encrypted/authenticated; key management documented.
- [ ] Patch/vulnerability process defined; recent CVE scan results reviewed.
- [ ] Audit logging implemented with integrity protection; time sync verified.
- [ ] Resource protections (limits, timeouts, validation) implemented and tested.
- [ ] Secure boot/update integrity enforced; rollback protection present.
- [ ] Services/ports inventory reviewed; unnecessary ones removed/disabled.

## Traceability
- Link threat model items (TH-###) to controls (`RISK-CTRL-NTW-###`) and tests (`TEST-SEC-###`).
- SBOM entries linked to network-facing components; track CVEs to remediation tickets.
- Keep security level rationale with architecture views for zones/conduits.

## References
- IEC 62443-4-1 (secure product development lifecycle).
- IEC 62443-4-2 (technical security requirements for components).
- FDA Cybersecurity Premarket Guidance (aligns with SDLC, SBOM, patching).
- NIST SP 800-53/82 (supporting control references; informative).

## Changelog
- 1.0.0 (2026-01-04): Initial skill covering SL targeting, secure SDLC, component controls, logging, and DoS protections.

## Audit History
- **2026-01-04**: Regulatory audit performed. Verified:
  - IEC 62443-4-1 (secure product development lifecycle) correctly referenced
  - IEC 62443-4-2 (technical security requirements for components) correctly referenced
  - Security Level (SL 1-4) concepts accurately described
  - STRIDE threat modeling methodology correctly attributed
  - NIST references (SP 800-53/82) appropriately marked as informative
