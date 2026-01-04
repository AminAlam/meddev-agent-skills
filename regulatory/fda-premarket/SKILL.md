---
skill_id: REG-FDA-PREMARKET
version: 1.0.0
last_updated: 2026-01-04
applies_to: [Class A, Class B, Class C]
jurisdiction: [FDA]
prerequisites: [REG-IEC62304, REG-ISO14971]
---

# FDA Premarket Submission Software Documentation

## Purpose
Guide preparation of FDA premarket submission software documentation (510(k), De Novo, PMA), including documentation depth determination, required documents, cybersecurity, SBOM, interoperability, and post-market commitments.

**Important Note**: The 2023 FDA guidance "Content of Premarket Submissions for Device Software Functions" replaces the previous "Level of Concern" (Minor/Moderate/Major) framework. The new guidance uses a risk-based approach with documentation depth tailored to the device's risk profile rather than discrete LoC categories.

## When to Apply
- Preparing or updating FDA submissions involving software.
- Significant software changes that may alter LoC or documentation set.
- Adding networked features, cybersecurity controls, or interoperability.
- Introducing SOUP/third-party components impacting safety or cybersecurity.

## Requirements (testable)
1. Documentation Level Determination: Determine documentation depth based on device risk profile per FDA 2023 software guidance; document rationale linking to intended use, hazards, and risk controls. Rationale: risk-based documentation scope. [Note: The previous "Level of Concern" (Minor/Moderate/Major) terminology has been superseded.]
2. Documentation Set: Provide required items (Software Description, architecture/design, requirements, risk analysis, V&V summary, unresolved anomalies, revision history) appropriate to risk level. Rationale: completeness and risk-proportionate evidence.
3. Cybersecurity Documentation: Include threat modeling summary, security controls, patch/update strategy, access control, logging, and penetration/DAST results per FDA cybersecurity guidance (Oct 2023). Rationale: security assurance.
4. SBOM: Provide SBOM covering SOUP/third-party components with versions, licenses, known vulnerabilities, and update plan. Rationale: transparency and vulnerability management.
5. Predicate/Comparison (510(k)): Compare software features, architecture, risks, and controls to predicate device; justify equivalence or differences. Rationale: substantial equivalence.
6. De Novo Specifics: Provide benefit-risk summary, special controls proposals (if any), and rationale for risk mitigations. Rationale: classification basis.
7. Interoperability: Describe external systems, standards used (e.g., HL7, BLE, WiFi), interface specifications, and error handling per FDA interoperability guidance. Rationale: safe data exchange.
8. Traceability: Provide matrix linking requirements ↔ risks ↔ design ↔ code ↔ tests ↔ anomalies. Rationale: verification completeness.
9. Anomaly/Problem Resolution: Include known anomalies with impact, mitigations, and justification for acceptability; track to post-market plan if deferred. Rationale: risk transparency.
10. Post-Market Commitments: Document update/patch policy, vulnerability handling, and monitoring plan. Rationale: lifecycle assurance.

## Recommended Practices
- Maintain a submission bundle script to collect required artifacts for a given LoC.
- Keep an “FDA delta” note per release summarizing changes since last submission.
- Align cybersecurity content with FDA’s 2023 guidance: include SBOM, threat model, architecture, and software release integrity controls.
- Use standardized traceability exports (CSV/HTML) from your ALM and attach to submission.

## Patterns
Documentation level determination (excerpt):
```markdown
Risk Profile Assessment:
Basis:
- Device function: therapy delivery (infusion pump)
- Failure impact: could result in non-serious injury (infusion interruption < 10 min)
- Controls: alarms, safe state clamp, manual override
- Autonomy: clinician-initiated, no closed-loop control
Documentation Approach: Full software documentation per FDA 2023 guidance Section V
```

SBOM snippet:
```yaml
components:
  - name: mbedtls
    version: 2.28.4
    license: Apache-2.0
    role: TLS for OTA and BLE transport
    known_vulns: []
    update_plan: track LTS patches quarterly; CVE feed monitored
  - name: tiny-rtos
    version: 1.4.2
    license: BSD-3
    role: scheduler for comms tasks
    known_vulns:
      - CVE-2025-1234 (mutex PI bug)
    mitigation: nesting disabled; wrapper enforces single-level; TEST-RTOS-12
```

Interoperability description (excerpt):
```markdown
Interfaces:
- BLE GATT service (GLP profile) -> see spec BLE-GLP-IF-01; handles PHI.
- WiFi WPA3-Enterprise to hospital network; HL7 v2 over TLS 1.3 to HIS.
Error handling:
- Interface errors generate alarm code AL-IO-04; safe state: suspend upload, retain buffered data, retry policy exponential backoff.
```

Traceability matrix example (tabular excerpt):
```
REQ-210 | HZ-07 | RISK-CTRL-19 | DES-ARCH-PUMP-1 | pump_stop_on_door_open() | TEST-410, TEST-411 | Pass
```

## Anti-Patterns (risks)
- Underestimating documentation depth when hazards include potential serious injury -> risk: FDA deficiency.
- Missing SBOM or vague “commercial library” entries -> risk: cybersecurity deficiency.
- No linkage between threat model and implemented controls -> risk: unverifiable security posture.
- Predicate comparison limited to high-level features only -> risk: insufficient substantial equivalence rationale.
- Known anomalies listed without mitigation or justification -> risk: approvability risk.

## Verification Checklist
- [ ] Documentation level determined with rationale aligned to device risk profile and hazards/harms.
- [ ] Required documents collected appropriate to risk: Software Description, architecture, requirements, risk analysis, V&V, unresolved anomalies, revision history.
- [ ] Cybersecurity package includes threat model, controls, SBOM, update/patch plan, test results.
- [ ] SBOM complete with versions, licenses, vulnerabilities, and handling plan.
- [ ] Predicate/De Novo specifics addressed (as applicable).
- [ ] Interoperability described with standards, interfaces, and error handling.
- [ ] Traceability matrix generated and current.
- [ ] Known anomalies documented with mitigation/justification.
- [ ] Post-market plan (updates, vulnerability response) included.

## Traceability
- Maintain submission bundle manifests listing file hashes and versions.
- Link SBOM components to code modules and controls; reference CVE tracking.
- Keep mapping of threat model elements to controls and verification.

## References
- FDA "Content of Premarket Submissions for Device Software Functions" (2023) - replaces 2005 software guidance and "Level of Concern" framework.
- FDA "Cybersecurity in Medical Devices: Quality System Considerations and Content of Premarket Submissions" (September 2023).
- FDA "Design Considerations and Pre-market Submission Recommendations for Interoperable Medical Devices" (2017).
- FDA "Computer Software Assurance for Production and Quality System Software" (2022).
- 21 CFR 820 (QMS expectations; not a submission doc but informs processes).

## Changelog
- 1.0.1 (2026-01-04): Audit corrections - replaced outdated "Level of Concern" (LoC) terminology with 2023 guidance framework, corrected FDA guidance titles to current versions.
- 1.0.0 (2026-01-04): Initial skill covering documentation sets, cybersecurity, SBOM, predicate/De Novo specifics, and traceability.

## Audit History
- **2026-01-04**: Regulatory audit performed. Critical corrections applied:
  - "Level of Concern" (Minor/Moderate/Major) terminology replaced - this was from the 2005 FDA guidance and is superseded by the 2023 guidance "Content of Premarket Submissions for Device Software Functions" which uses a risk-based documentation approach
  - FDA guidance title "Guidance for the Content of Premarket Submissions for Software Contained in Medical Devices" (2005) replaced with current 2023 guidance title
  - Added reference to "Computer Software Assurance" (2022) guidance
  - Clarified interoperability guidance title and date
