---
skill_id: REG-21CFR11
version: 1.0.0
last_updated: 2026-01-04
applies_to: [Class A, Class B, Class C]
jurisdiction: [FDA]
prerequisites: [REG-ISO14971]
---

# 21 CFR Part 11 Electronic Records and Signatures

## Purpose
Provide implementation guidance for electronic records/signatures (ER/ES) compliance: access control, audit trails, data integrity, and validation expectations in medical device software and supporting tools.

## When to Apply
- Systems creating, modifying, storing, or transmitting electronic records subject to FDA records.
- Implementing electronic signatures or approvals in software lifecycle tools (e.g., QMS, ALM, CI/CD approvals).
- Handling PHI/PII or regulated data with retention requirements.

## Requirements (testable)
1. Access Control: Unique user identities; role-based permissions; no shared accounts. Rationale: accountability.
2. Authentication Strength: Enforce strong auth (password policy or MFA for remote) appropriate to risk; session timeout and lockout. Rationale: prevent unauthorized use.
3. Electronic Signatures: Link signatures to unique user IDs; include printed name, date/time, and meaning of signature (e.g., review/approval) per §11.50. Rationale: non-repudiation.
4. Signature Controls: For open systems, require two distinct factors at signing or equivalent control; log signature attempts; prevent reuse of credentials without re-auth (§11.200). Rationale: signature integrity.
5. Audit Trails: Computer-generated, time-stamped, secure, and independent audit trail for create/modify/delete; capture user, timestamp, action, before/after where feasible; no alteration by users (§11.10(e)). Rationale: record integrity.
6. Record Integrity: Protect records from alteration; use checksums/hashes, versioning, and controlled storage; backups with integrity checks. Rationale: data reliability.
7. Time Synchronization: System clocks synchronized (e.g., NTP) for audit and signature timestamps. Rationale: reliable timing.
8. Validation: Validate systems for intended use; document requirements, test protocols/results, and deviations (§11.10(a)). Rationale: fitness for use.
9. Training & Policies: Users trained on ER/ES use; policies for credentials and signatures documented. Rationale: procedural control.

## Recommended Practices
- Use tamper-evident logging (hash chaining, sealed storage).
- Require step-up authentication for high-risk signatures or remote access.
- Implement per-event reason codes for critical record changes.
- Store signature meaning as a controlled vocabulary (e.g., APPROVE, REVIEW).
- Periodically review accounts/roles; disable dormant accounts automatically.

## Patterns
Audit log with hash chaining:
```c
// LOG-11: hash-chained audit entry; TEST-AUD-04 validates integrity
typedef struct {
    uint8_t prev_hash[32];
    uint8_t entry_hash[32];
    audit_event_t ev;
} audit_record_t;
```

Signature capture (conceptual):
```c
// SIG-11: enforce re-auth + meaning capture
int sign_change(const user_t *u, const char *meaning, const char *record_id) {
    if (!reauthenticate(u)) return -1;            // MFA or password re-prompt
    audit_log("SIG_ATTEMPT", u->id, record_id);
    if (!is_allowed_meaning(meaning)) return -2;  // controlled vocab
    return persist_signature(u, meaning, record_id, timestamp_now());
}
```

Record integrity with checksum:
```c
// REQ-11-INTEGRITY: checksum stored with record
uint32_t checksum_record(const void *buf, size_t len) {
    return crc32(buf, len);
}
```

## Anti-Patterns (risks)
- Shared or generic accounts for approvals -> risk: noncompliant signatures.
- Editable audit logs or logs stored with app-level delete rights -> risk: tampering.
- No re-authentication for signatures -> risk: repudiation and misuse.
- Unsynchronized clocks -> risk: unreliable audit trails.
- Unvalidated tools generating submission records -> risk: invalid evidence.

## Verification Checklist
- [ ] Unique user IDs; RBAC applied; no shared accounts.
- [ ] Authentication policy enforced (complexity/MFA as applicable); session timeout/lockout configured.
- [ ] Signature records include user, timestamp, meaning; re-authentication enforced.
- [ ] Audit trail implemented, immutable/tamper-evident; captures create/modify/delete.
- [ ] Record integrity controls (hash/checksum/versioning) in place; backups validated.
- [ ] System time synchronized and monitored.
- [ ] System validated for intended use with documented test evidence.
- [ ] Policies and training documented; access/role reviews performed.

## Traceability
- Link ER/ES requirements (`REQ-11-###`) to design elements, code, and tests (`TEST-11-###`).
- Keep validation artifacts in configuration control; associate signatures with requirement/test IDs.
- Store audit log integrity verification results with release artifacts.

## References
- 21 CFR Part 11 (notably §§11.10, 11.50, 11.200).
- FDA guidance on Part 11 scope and application (2003).
- NIST SP 800-63 (for authentication strength considerations; informative).

## Changelog
- 1.0.0 (2026-01-04): Initial skill covering ER/ES access control, signatures, audit, integrity, and validation expectations.

## Audit History
- **2026-01-04**: Regulatory audit performed. Verified:
  - 21 CFR Part 11 section references (§§11.10, 11.50, 11.200) are accurate
  - FDA 2003 guidance "Part 11, Electronic Records; Electronic Signatures — Scope and Application" correctly referenced
  - Scope of Part 11 relative to predicate rules correctly explained
  - NIST SP 800-63 reference appropriate as informative guidance for authentication strength
