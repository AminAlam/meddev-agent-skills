---
skill_id: CONN-INTEROP
version: 1.0.0
last_updated: 2026-01-04
applies_to: [Class A, Class B, Class C]
jurisdiction: [FDA, EU MDR, Global]
prerequisites: [REG-ISO14971, REG-FDA-PREMARKET]
---

# Medical Device Interoperability

## Purpose
Enable safe and standards-aligned interoperability: HL7 FHIR/IHE profiles, data formats, terminology mapping, and API design for medical data exchange.

## When to Apply
- Designing or updating device APIs, data exchange, or integrations with HIS/EMR/cloud.
- Handling PHI or clinical decisions based on exchanged data.

## Requirements (testable)
1. Standards Use: Prefer established standards (HL7 FHIR, HL7 v2 where applicable, IHE profiles) for relevant data flows; document conformance. Rationale: interoperability and clarity.
2. Terminology: Use standard vocabularies (SNOMED CT, LOINC) for clinical concepts; map device codes to standard codes. Rationale: semantic consistency.
3. Data Integrity: Validate messages (schema/length/range); apply checksums/hashes over payloads where appropriate; reject/flag invalid data. Rationale: correctness.
4. Security & Privacy: Protect PHI with TLS 1.3+; enforce authz (scopes/roles); log access; minimize data shared. Rationale: confidentiality/integrity.
5. Error Handling: Provide clear, standard error responses; fail safe; no silent truncation. Rationale: predictable integration.
6. Traceability: Log message IDs, timestamps, and correlation IDs; link to requirements/tests; keep audit for safety-relevant exchanges. Rationale: accountability.
7. Interop Risks: Document interop-related hazards (misinterpretation, time sync, version mismatch) and mitigations. Rationale: safety.

## Recommended Practices
- Provide versioned APIs and explicit capability statements (e.g., FHIR CapabilityStatement).
- Time-sync devices (NTP/PTP) to avoid timestamp drift in clinical workflows.
- Use contract tests against partner systems; include negative cases.
- Avoid custom extensions unless necessary; document them clearly.

## Patterns
FHIR-like JSON validation (pseudo):
```python
# REQ-INTOP-VALID-01; TEST-INTOP-04
def validate_observation(obs: dict) -> bool:
    required = ["resourceType", "status", "code", "subject", "effectiveDateTime"]
    if obs.get("resourceType") != "Observation":
        return False
    return all(k in obs for k in required)
```

Terminology mapping table (YAML):
```yaml
# REQ-INTOP-TERM-02
device_code: FLOW_RATE
loinc: 8310-5
display: Infusion flow rate
```

Error response:
```json
// REQ-INTOP-ERR-03; TEST-INTOP-07
{ "error": "invalid-parameter", "detail": "missing code" }
```

## Anti-Patterns (risks)
- Custom proprietary formats without mapping -> risk: misinterpretation by HIS/EMR.
- Sending PHI over plaintext or weak TLS -> risk: data breach.
- Silent acceptance of invalid messages -> risk: wrong clinical decisions.
- No time sync -> risk: misleading timestamps in therapy/diagnostics.

## Verification Checklist
- [ ] Standards selected and documented; conformance statements present.
- [ ] Terminology mapped to SNOMED/LOINC (or applicable); mappings versioned.
- [ ] Message validation implemented; invalid data rejected/logged.
- [ ] TLS 1.3+ and authz enforced; PHI minimized; access logged.
- [ ] Error responses clear and standard; no silent truncation.
- [ ] Interop hazards documented with mitigations/tests.
- [ ] Time synchronization implemented and monitored.

## Traceability
- Requirements `REQ-INTOP-###` linked to contract/interop tests `TEST-INTOP-###`; logs maintain correlation IDs for message tracing.

## References
- HL7 FHIR R4/R5; HL7 v2 where applicable.
- IHE profiles relevant to devices (e.g., PCD-01, DEC).
- FDA interoperability guidance (2017).
- IEC 62304/ISO 14971 for risk integration.

## Changelog
- 1.0.0 (2026-01-04): Initial interoperability skill with standards use, validation, terminology, and security guidance.

## Audit History
- **2026-01-04**: Audit performed. Verified:
  - HL7 FHIR R4/R5 references accurate
  - IHE profiles (PCD-01, DEC) correctly mentioned
  - FDA interoperability guidance (2017) reference verified
  - SNOMED CT and LOINC terminology references appropriate
