---
skill_id: REG-IEC62304-SWRM
version: 1.0.0
last_updated: 2026-05-21
applies_to: [Class A, Class B, Class C]
jurisdiction: [FDA, EU MDR, Canada, UK]
prerequisites: [REG-ISO14971, REG-IEC62304]
---

# IEC 62304 Software Risk Management Process

## Purpose
Guide implementation of the software-specific risk management process (IEC 62304:2006+A1:2015, Clause 7) alongside ISO 14971:2019—identifying how software items contribute to hazardous situations, defining and verifying software risk controls, and re-analysing risk when software changes.

## When to Apply
- Architecture or requirements work for Class B/C software items.
- Introducing or updating SOUP, interfaces, or control logic that mitigates hazards.
- Any software change that may add causes, weaken controls, or alter hazardous situations (7.4).
- Linking hazard analysis outputs to software requirements and tests.

## Requirements (testable)
1. Hazardous-Situation Mapping [Class B, C]: For each hazardous situation from device risk analysis, identify software items that could contribute (direct failure or failure of a software-implemented control). Rationale: scoped software risk analysis per 7.1.1.
2. Potential Causes [Class B, C]: Document plausible causes per item—including specification gaps, implementation defects, third-party library (SOUP) behaviour, hardware interactions, and foreseeable misuse. Rationale: 7.1.2.
3. SOUP Anomaly Review [Class B, C]: When SOUP failure is a potential cause, review supplier-published anomaly/issue lists for the version in use and assess whether known issues could lead to a hazardous situation. Rationale: 7.1.3.
4. Risk File Records [Class B, C]: Record identified causes and related items in the risk management file (ISO 14971). Rationale: 7.1.4.
5. Control Definition [Class B, C]: For each documented cause, define risk control measures per ISO 14971; note whether implemented in software, hardware, procedures, or labelling. Rationale: 7.2.1.
6. Software-Implemented Controls [Class B, C]: When a control is implemented in software—add to software requirements, assign safety class to the implementing item based on the risk the control addresses, and develop per Clause 5. Rationale: 7.2.2.
7. Control Verification [Class B, C]: Verify each software-related control and document results; review whether the control could introduce a new hazardous situation. Rationale: 7.3.1.
8. Software Hazard Traceability [Class B, C]: Maintain trace links: hazardous situation → software item → cause → control → verification evidence. Rationale: 7.3.3.
9. Change Impact — New Causes [Class A, B, C]: On software or SOUP change, analyse whether new potential causes or hazardous contributions are introduced. Rationale: 7.4.1.
10. Change Impact — Existing Controls [Class B, C]: Analyse whether the change could interfere with existing software risk controls. Rationale: 7.4.2.
11. Re-run Risk Activities [Class B, C]: After change analysis, repeat relevant 7.1–7.3 activities when analysis shows new or weakened risk. Rationale: 7.4.3.

## Recommended Practices
- Keep `risk-register.yaml` entries keyed by `HZ-###`, `RISK-CTRL-###`, and software item names.
- Pair each software control with at least one negative-path test.
- Reconcile SOUP CVE/advisory feeds with the formal anomaly list review.
- For controls that only run in software, avoid assigning a lower class than the risk they address.

## Patterns
Software cause and control (YAML):
```yaml
hazardous_situation: HZ-07
software_item: pump_control
potential_causes:
  - id: CAUSE-07a
    type: implementation_defect
    desc: rate limit not applied on low battery path
  - id: CAUSE-07b
    type: soup
    soup: tiny-rtos@1.4.2
    desc: timer drift under load (supplier anomaly TR-12 reviewed 2026-05-01)
risk_controls:
  - id: RISK-CTRL-19
    location: software
    requirement: REQ-62304-102
    verification: [TEST-410, TEST-411]
```

Control verification note:
```markdown
RISK-CTRL-19 verification: TEST-410 PASS, TEST-411 PASS
New hazardous situation review: none identified
```

## Anti-Patterns (risks)
- Treating ISO 14971 file as complete without Clause 7 software cause analysis -> risk: missing software-specific causes.
- Skipping SOUP supplier anomaly review -> risk: known defects unmitigated.
- Lowering item class below the risk addressed by a software control -> risk: under-verification of critical mitigations.
- Change merges without 7.4 analysis -> risk: silent control breakage.

## Verification Checklist
- [ ] Software items mapped to hazardous situations for Class B/C scope.
- [ ] Potential causes documented per item; SOUP causes include supplier anomaly review.
- [ ] Controls defined; software controls reflected in requirements with appropriate class.
- [ ] Each software control has documented verification; new hazardous situations considered.
- [ ] Trace chain recorded: situation → item → cause → control → verification.
- [ ] Software/SOUP changes include 7.4.1 analysis; B/C changes include 7.4.2–7.4.3 when applicable.

## Traceability
- Use `HZ-###`, `CAUSE-###`, `RISK-CTRL-###`, `REQ-###`, `TEST-###` consistently with `REG-ISO14971` and `DOC-TRACEABILITY`.
- Store Clause 7 records in the risk management file or linked artifacts under configuration control.

## References
- IEC 62304:2006+A1:2015, Clause 7 (software risk management process).
- ISO 14971:2019 (device risk management; prerequisite skill `REG-ISO14971`).
- IEC TR 80002-1:2019 (application of risk management to medical device software; informative).
- `REG-IEC62304` (lifecycle hub), `ARCH-SAFETY-CLASS` (classification), `DOC-SW-REQ` (5.2 risk controls in requirements).

## Changelog
- 1.0.0 (2026-05-21): Initial skill for IEC 62304 Clause 7 software risk management process.
