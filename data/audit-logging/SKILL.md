---
skill_id: DATA-AUDIT
version: 1.0.0
last_updated: 2026-01-04
applies_to: [Class A, Class B, Class C]
jurisdiction: [FDA, 21 CFR Part 11, HIPAA, EU MDR]
prerequisites: [REG-21CFR11, SEC-THREAT-MODELING]
---

# Audit Logging

## Purpose
Define what and how to log for medical devices: security/safety events, integrity, protection, and retention of logs for compliance and forensics.

## When to Apply
- Security-relevant actions, configuration changes, access to PHI, safety events.
- System/device state changes, updates, connectivity, and error conditions.

## Requirements (testable)
1. Scope: Log authentication events, config changes, safety actions, updates, anomalies, and PHI access (without logging PHI content). Rationale: accountability.
2. Integrity: Protect logs against tampering (hash chain/MAC, restricted access); no user-level editing. Rationale: trustworthiness.
3. Time Sync: Ensure timestamps are reliable (NTP/PTP or hardware RTC); detect drift. Rationale: ordering and forensics.
4. Minimal PHI: Do not store PHI unless necessary; if stored, encrypt and minimize. Rationale: privacy.
5. Retention: Define retention and secure storage/backup; support export for investigations. Rationale: compliance and availability.
6. Performance: Logging must not jeopardize safety/timing; use buffering with backpressure limits. Rationale: safety.

## Recommended Practices
- Use structured logs (key=value/JSON) with event IDs.
- Separate audit log from operational logs; stricter controls on audit.
- Rate-limit repetitive events to avoid flooding; but ensure critical events always logged.
- Include device ID, software version, and correlation IDs.

## Patterns
Hash-chained log entry:
```c
// REQ-AUD-INT-01; TEST-AUD-04
typedef struct {
    uint8_t prev_hash[32];
    audit_event_t ev;
    uint8_t hash[32];
} audit_record_t;
```

Structured log example:
```text
evt=auth_fail user=clinician1 code=LOCKOUT ts=2026-01-04T12:00:00Z
```

## Anti-Patterns (risks)
- Logging PHI verbatim -> risk: privacy breach.
- Editable or deletable logs -> risk: tampering and noncompliance.
- Unsynchronized clocks -> risk: unusable forensic timeline.
- Logging so much that timing is affected -> risk: safety impact.

## Verification Checklist
- [ ] Audit events defined and implemented (auth, config, safety, update, PHI access).
- [ ] Log integrity protection implemented; access restricted.
- [ ] Timestamps reliable; drift detection in place.
- [ ] PHI minimized/omitted; if present, encrypted and justified.
- [ ] Retention/backup defined; export supported securely.
- [ ] Logging performance impact assessed; backpressure/limits applied.

## Traceability
- `REQ-AUD-###` to `TEST-AUD-###`; logs tied to device ID/version; align with Part 11/ISO 14971 controls.

## References
- 21 CFR Part 11 (audit trail), HIPAA Security Rule.
- FDA cybersecurity guidance (logging/monitoring).
- IEC 62443 logging recommendations (informative).

## Changelog
- 1.0.0 (2026-01-04): Initial audit logging skill with scope, integrity, and retention guidance.

## Audit History
- **2026-01-04**: Audit performed. Verified:
  - 21 CFR Part 11 audit trail requirements correctly referenced
  - HIPAA Security Rule reference appropriate
  - IEC 62443 logging recommendations correctly marked as informative
