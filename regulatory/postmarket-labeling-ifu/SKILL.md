---
skill_id: REG-POSTMKT-LABEL
version: 1.0.1
last_updated: 2026-05-21
applies_to: [Class A, Class B, Class C]
jurisdiction: [FDA, EU MDR]
prerequisites: [REG-IEC62304, REG-ISO14971]
---

# Postmarket Surveillance, Complaints, Recalls, and Software Labeling

## Purpose
Connect **post-market** processes to software: **complaints**, **vigilance / MDR reporting**, **recalls and field corrections**, **cybersecurity coordinated disclosure** touchpoints, and **labeling / IFU** (including on-device strings, UDI display, and versioned patient/clinician instructions) so maintenance (IEC 62304 §6) and QMS **CAPA** stay coherent.

## When to Apply
- Triaging **customer complaints** that reference software behavior, crashes, or security.
- Deciding **reportability** (e.g., EU serious incident criteria; US MDR reports).
- **FSCA** / recall / UDI correction affecting distributed software.
- Updating **Instructions for Use**, GUI risk messaging, or **release notes** with safety information.
- Post-market **cybersecurity** vulnerability handling tied to deployed versions.

## Requirements (testable)
1. Complaint Intake: Record **software version**, **hardware rev**, **environment**, and **symptom** for each complaint; link to risk file and known anomalies; route into software maintenance feedback (IEC 62304 6.2.1). Rationale: investigation and trend analysis.
2. Investigation: Perform **root cause** analysis distinguishing **software defect**, **use error**, **SOUP/CVE**, and **environmental** factors; preserve records per QMS. Rationale: CAPA effectiveness.
3. Vigilance / Reporting: Apply **EU MDR** vigilance rules and **FDA MDR** reporting for device malfunctions; escalate per timelines when criteria met. Rationale: legal reporting.
4. Field Actions: For **FSCA** / recall, define **affected versions**, **corrective action** (patch, config, instructions), **customer communication**, and **effectiveness checks**. Rationale: patient safety.
5. Software Corrections & Removals: Track **21 CFR Part 806**-style distinctions (US) where applicable; document **recall strategy** including SaaS/OTA distribution. Rationale: regulatory consistency.
6. Labeling Control: Maintain **master label** and **IFU** under document control; **version** with software releases; verify UI strings match approved labeling for risks/warnings. Rationale: misbranding prevention.
7. UDI & Version Display: Show **UDI** / **version** per **MDCG 2018-1** (EU) and firm policy; ensure **About** screen / splash matches released build. Rationale: traceability to field units.
8. Postmarket Cybersecurity: Tie **CVE** handling, **SBOM** updates, and **patch deployment** to PMS and risk review (see FDA cybersecurity postmarket expectations). Rationale: sustained security state.

## Recommended Practices
- Single **field matrix**: version × region × config × known issues.
- Automate extraction of **displayed version** from build metadata into IFU appendices.

## Patterns
Complaint record (YAML):
```yaml
complaint:
  id: "CMP-2026-0142"
  sw_version: "2.3.1"
  text: "App crashed during upload"
  investigation: "ROOT-2026-044"
  linked_anomaly: "BUG-778"
  reportable: false
  capa: "CAPA-2026-09"
```

IFU change note:
```markdown
## Document history
| Rev | Software | Change |
|-----|----------|--------|
| H   | 2.3.1    | Clarified WiFi reconnection warning (HZ-USE-02) |
```

## Anti-Patterns (risks)
- Closing complaints as **user error** without usability/risk review — risk: missed use-related hazard.
- **Silent** on-screen text changes for risk warnings — risk: labeling/QMS violation.
- OTA fix without **version traceability** or **customer list** — risk: incomplete FSCA scope.

## Verification Checklist
- [ ] Complaint records include software version and investigation outcome.
- [ ] Reportability assessed per jurisdiction; submissions logged if required.
- [ ] Field actions documented with affected versions and communications.
- [ ] IFU/label revision matches released software; UI spot-checked.
- [ ] UDI/version display verified on device for the release build.
- [ ] Cybersecurity patches tied to risk review and customer notification policy.

## Traceability
- IDs: `CMP-*`, `FSCA-*`, `LBL-*`, `IFU-*`; link to `v*.*.*`, `BUG-*`, `HZ-*`.

## References
- IEC 62304:2006+A1:2015, 6.2 (feedback, problem reports, change communication); `DOC-SW-MAINT`, `DOC-PROBLEM-RES`.
- EU MDR 2017/745 — vigilance (Articles 87–92), PMS (Articles 83–86).
- FDA 21 CFR Part 803 (medical device reporting) — where applicable.
- FDA 21 CFR Part 806 (reports of corrections/removals).
- MDCG 2018-1 v3 — UDI for software (verify revision).
- FDA “Cybersecurity in Medical Devices” — postmarket expectations (current guidance).

## Changelog
- 1.0.1 (2026-05-21): Linked complaint intake to IEC 62304 maintenance process (6.2).
- 1.0.0 (2026-03-20): Initial skill for complaints, vigilance, recalls, labeling/IFU, cybersecurity PMS.
