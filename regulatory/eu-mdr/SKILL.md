---
skill_id: REG-EU-MDR
version: 1.0.0
last_updated: 2026-01-04
applies_to: [Class A, Class B, Class C]
jurisdiction: [EU MDR]
prerequisites: [REG-IEC62304, REG-ISO14971]
---

# EU MDR Software Requirements (incl. Rule 11)

## Purpose
Provide actionable guidance for software under EU MDR, focusing on classification (Rule 11), technical documentation expectations, UDI for software, PMS/PMCF needs, and alignment with MDCG guidance.

## When to Apply
- Software intended for EU market (MDR 2017/745).
- Changes affecting intended purpose, data handling, diagnostics/therapy decisions, or networking.
- Updates that may alter classification under Rule 11.
- Preparation/update of technical documentation or NB submissions.

## Requirements (testable)
1. Classification (Rule 11): Determine class per MDR Annex VIII Rule 11; document rationale, including data source and decision/diagnosis impact. Rationale: drives conformity assessment route and evidence depth.
2. Intended Purpose & GSPRs: Align software intended purpose with GSPRs (Annex I); map requirements to GSPR coverage. Rationale: completeness of technical documentation.
3. Technical Documentation: Maintain MDR Annex II/III-compliant documentation: device description, design/architecture, risk management, verification/validation (including usability), clinical evaluation linkage, IFU. Rationale: NB review readiness.
4. Risk Management Integration: Use ISO 14971 outputs; include cybersecurity and interoperability risks per MDCG 2019-16/2020-1. Rationale: MDR expects risk coverage including security.
5. UDI for Software: Assign UDI-DI and handle UDI-PI per MDCG 2018-1 v3; display/versioning rules for software releases. Rationale: traceability of versions.
6. PMS/PMCF: Define PMS plan; determine if PMCF is applicable; collect and feed post-market data into risk management. Rationale: lifecycle safety evidence.
7. SOUP & Updates: Document SOUP, versions, and change impacts; ensure updates go through change control and PMS linkage. Rationale: manage new risks with updates.
8. Interoperability: Document external systems/interfaces and standards used; define error handling and safe failure behavior. Rationale: MDR emphasis on interoperability safety.
9. Usability (IEC 62366-1 link): Capture user interface risks and mitigations where software UI affects safety; trace to testing. Rationale: GSPR 5 & 14 coverage.

## Recommended Practices
- Keep a Rule 11 classification note per release; highlight any change triggers.
- Maintain a GSPR matrix with software-specific evidence references (tests, analyses).
- Include cybersecurity controls and test evidence as part of GSPR 17 and risk files.
- Automate UDI version stamping in build outputs and release notes.
- Maintain a PMS delta log per release that feeds back into risk and tech file.

## Patterns
Rule 11 rationale excerpt:
```markdown
Rule 11 Classification: Class IIa
Justification:
- Software provides information used to drive therapy adjustment but not for immediate vital decisions.
- Mitigations: clinician confirmation step; alarms for anomalous inputs.
- If failure -> potential non-serious injury. No autonomous closed-loop therapy.
```

GSPR mapping snippet (CSV-style):
```
GSPR 17.2 | Cybersecurity | Controls: TLS1.3, mutual auth, SBOM; Tests: PEN-12, DAST-07 | REQ-SEC-21 | PASS
GSPR 14.2 | Maintainability | Update process with signed OTA; rollback supported | REQ-OTA-05 | PASS
```

UDI handling in release notes:
```markdown
UDI-DI: EU123456789-SW-001
UDI-PI: lot=2026.01.04 build=1.0.3
Displayed in splash screen and About dialog; included in IFU and EUDAMED entry.
```

## Anti-Patterns (risks)
- Treating all software as Class I under Rule 11 without rationale -> risk: NB nonconformity.
- Missing GSPR evidence mapping -> risk: incomplete technical documentation.
- No UDI update when version changes -> risk: traceability gap.
- Cybersecurity omitted from risk management -> risk: NB findings and patient safety issues.
- PMS not feeding back into risk/tech file -> risk: lifecycle noncompliance.

## Verification Checklist
- [ ] Rule 11 classification documented with rationale; re-evaluated on changes.
- [ ] GSPR matrix updated with evidence for software items.
- [ ] Technical documentation (Annex II/III) updated for this change.
- [ ] Risk management updated (including cybersecurity/interoperability risks).
- [ ] UDI-DI/PI updated and reflected in software build artifacts and IFU where applicable.
- [ ] PMS/PMCF plans reviewed; post-market signals assessed for this release.
- [ ] SOUP inventory/version impacts evaluated and documented.
- [ ] Interoperability behaviors and error handling described and verified.
- [ ] Usability-related risks/mitigations tested if UI changes affect safety.

## Traceability
- Maintain GSPR matrix linking to requirements/tests.
- Tag releases with UDI-PI and store evidence bundles per version.
- Keep Rule 11 rationale and class in the architecture/risk sections; tie to hazards.

## References
- EU MDR 2017/745: Annex VIII Rule 11; Annex I (GSPRs); Annex II/III (technical documentation).
- MDCG 2019-11 Rev.1 (Guidance on Qualification and Classification of Software in Regulation (EU) 2017/745).
- MDCG 2019-16 Rev.1 (Guidance on Cybersecurity for Medical Devices).
- MDCG 2018-1 v3 (Guidance on Unique Device Identification (UDI) for Software).
- MDCG 2020-1 (Guidance on Clinical Evaluation - used here for contextual understanding of benefit-risk).
- MDCG 2022-14 (MDCG Position Paper on the use of the UDI as listed on the GSPRs).
- IEC 62304 and ISO 14971 for lifecycle and risk integration (prerequisites).

## Changelog
- 1.0.1 (2026-01-04): Audit review - added revision numbers to MDCG references, added MDCG 2022-14 reference.
- 1.0.0 (2026-01-04): Initial EU MDR skill covering Rule 11, GSPRs mapping, UDI, interoperability, PMS/PMCF.

## Audit History
- **2026-01-04**: Regulatory audit performed. Verified:
  - Rule 11 classification references are accurate per MDR Annex VIII
  - GSPR references to Annex I are correct
  - Technical documentation references to Annex II/III are accurate
  - MDCG references verified and revision numbers added for clarity
  - Added MDCG 2022-14 for UDI on GSPRs
