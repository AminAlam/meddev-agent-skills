---
skill_id: DATA-PHI
version: 1.0.0
last_updated: 2026-01-04
applies_to: [Class A, Class B, Class C]
jurisdiction: [HIPAA, FDA, EU GDPR]
prerequisites: [SEC-ENCRYPTION, SEC-AUTH]
---

# Protected Health Information Handling

## Purpose
Identify and handle PHI in software to enforce minimum necessary use, encryption, access control, and retention/deletion policies.

## When to Apply
- Any feature storing/transmitting patient data.
- Logs, telemetry, backups, analytics, and interoperability.

## Requirements (testable)
1. PHI Identification: Classify data elements; mark PHI/PII; document flows. Rationale: scope controls.
2. Minimum Necessary: Limit fields collected/stored/transmitted; justify PHI fields. Rationale: privacy by design.
3. Encryption: Encrypt PHI in transit (TLS 1.3) and at rest; keys protected. Rationale: confidentiality.
4. Access Control: Enforce authz for PHI access; role/need-to-know; audit accesses. Rationale: accountability.
5. Logging/Sanitization: Avoid PHI in logs; if required, mask or tokenize. Rationale: reduce leakage.
6. Retention/Deletion: Define retention; implement deletion or de-ID on expiry; verify. Rationale: compliance.
7. Data Export/Interoperability: Apply same controls to exports; ensure standards-based fields are properly scoped. Rationale: consistent protection.

## Recommended Practices
- Use data flow diagrams marking PHI.
- Apply structured logging with explicit allowlists.
- Tokenize identifiers where possible; separate identity from clinical data.
- Encrypt backups and ensure access controls on storage buckets.

## Patterns
Sanitized logging:
```c
// REQ-PHI-LOG-01; TEST-PHI-04
log_info("evt=device_connect id=%s", anonymized_id(dev_id));
```

Retention check (pseudo):
```python
# REQ-PHI-RET-02; TEST-PHI-06
delete_records_older_than(days=365)
```

Data classification entry:
```yaml
field: patient_name
phi: true
justification: required for clinician display
```

## Anti-Patterns (risks)
- Dumping raw PHI to logs -> risk: breach.
- Transmitting PHI over plaintext or weak TLS -> risk: exposure.
- No retention/deletion -> risk: excessive data and regulatory noncompliance.
- Broad access without RBAC -> risk: unauthorized disclosure.

## Verification Checklist
- [ ] PHI fields identified and documented in data flows.
- [ ] Minimum necessary enforced; unnecessary fields removed.
- [ ] PHI encrypted in transit and at rest; keys protected.
- [ ] Access control and auditing applied to PHI access.
- [ ] Logs/telemetry sanitized; no raw PHI unless justified and protected.
- [ ] Retention/deletion implemented and verified; backups included.
- [ ] Exports/interoperability apply same protections.

## Traceability
- `REQ-PHI-###` to tests `TEST-PHI-###`; link to security requirements and privacy policies.

## References
- HIPAA Security/Privacy Rules (US).
- EU GDPR principles; data minimization/retention.
- FDA cybersecurity guidance (PHI protection).

## Changelog
- 1.0.0 (2026-01-04): Initial PHI handling skill with classification, minimization, encryption, and retention.

## Audit History
- **2026-01-04**: Audit performed. Verified:
  - HIPAA Security/Privacy Rule references appropriate
  - EU GDPR data minimization/retention principles correctly noted
  - PHI handling patterns align with industry best practices
