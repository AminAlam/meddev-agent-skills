---
skill_id: DOC-SW-MAINT
version: 1.0.0
last_updated: 2026-05-21
applies_to: [Class A, Class B, Class C]
jurisdiction: [FDA, EU MDR, Global]
prerequisites: [REG-IEC62304, DOC-PROBLEM-RES, DOC-SCM]
---

# Software Maintenance Process

## Purpose
Guide post-release software maintenance per IEC 62304:2006+A1:2015, Clause 6—planning feedback handling, evaluating problems and changes, re-applying development activities when needed, and re-releasing under the same controls as initial release (5.8).

## When to Apply
- Software already released for intended use (field, hospital, or patient environment).
- Processing complaints, support tickets, or internal post-release defect reports.
- SOUP upgrades, security patches, obsolescence, or regulatory-driven software updates.
- Coordinating maintenance with postmarket surveillance (`REG-POSTMKT-LABEL`).

## Requirements (testable)
1. Maintenance Plan [Class A, B, C]: Maintain a software maintenance plan covering feedback receipt/documentation/evaluation/resolution/tracking; criteria for what constitutes a problem; use of software risk management; problem resolution process; configuration management for modifications; and evaluation/implementation of SOUP upgrades, fixes, patches, and obsolescence. Rationale: 6.1.
2. Monitor Feedback [Class A, B, C]: Monitor feedback on released software. Rationale: 6.2.1.1.
3. Evaluate Feedback [Class A, B, C]: Document and evaluate feedback to determine if a problem exists; record problems as problem reports including adverse events and specification deviations. Rationale: 6.2.1.2–6.2.1.3.
4. Safety Impact [Class A, B, C]: Evaluate each problem report for effect on safety of released software and whether a change is required. Rationale: 6.2.1.3.
5. Problem Process [Class A, B, C]: Address problem reports via `DOC-PROBLEM-RES`. Rationale: 6.2.2.
6. Change Request Analysis [Class A, B, C]: Beyond Clause 9 analysis, evaluate each change request for impact on organization, released software, and interfacing systems. Rationale: 6.2.3.
7. Approve Changes [Class A, B, C]: Evaluate and approve change requests that modify released software. Rationale: 6.2.4.
8. User and Regulator Communication [Class A, B, C]: Identify approved changes affecting released software; inform users and regulators per local rules when required (see `REG-POSTMKT-LABEL` for reporting detail). Rationale: 6.2.5 (interpretation).
9. Re-apply Development [Class A, B, C]: Identify and perform applicable Clause 5 activities affected by the modification. Rationale: 6.3.1.
10. Re-release [Class A, B, C]: Release modifications per software release requirements (`CICD-RELEASE`, 5.8). Rationale: 6.3.2.
11. Risk on Changes [Class A, B, C]: Perform software risk management for changes per 7.4 (`REG-IEC62304-SWRM`). Rationale: 6.3.1 note / 7.4.

## Recommended Practices
- Single intake queue merging complaints, support, and internal findings with `PR-###` IDs.
- Maintenance plan version-controlled alongside SDP.
- Define SOUP patch SLAs by safety class and exposure.
- Use modification kits (partial updates) only when release process still satisfies 5.8 and configuration baselines.

## Patterns
Maintenance plan excerpt (YAML):
```yaml
maintenance_plan:
  product: InfusionPump-X
  feedback_channels: [complaints, service_portal, security@company.com]
  problem_criteria: |
    Any reproducible deviation from released spec or any safety/security signal
  processes:
    risk: REG-IEC62304-SWRM
    problems: DOC-PROBLEM-RES
    configuration: DOC-SCM
  soup_policy:
    review_cadence: quarterly
    critical_soup: [tiny-rtos, mbedtls]
```

Released change flow:
```markdown
1. Feedback -> PR-2026-120
2. Safety eval -> change required -> CR-220 approved
3. Repeat 5.5–5.7 scope per impact analysis
4. 7.4 risk analysis -> REG-IEC62304-SWRM
5. Release v1.3.1 per CICD-RELEASE / 5.8
```

## Anti-Patterns (risks)
- Field patches without maintenance plan or problem reports -> risk: uncontrolled post-market software.
- Skipping 6.2.3 system/org impact analysis -> risk: hospital integration or QMS breaks.
- SOUP updates without regression or risk re-analysis -> risk: new causes or broken controls.
- Re-release without 5.8 checks -> risk: incomplete verification or wrong build in field.

## Verification Checklist
- [ ] Maintenance plan current and addresses 6.1 elements.
- [ ] Feedback monitored and evaluated; problems recorded as problem reports.
- [ ] Safety impact assessed per problem; changes approved before implementation.
- [ ] Change requests analysed for org/system impact.
- [ ] User/regulator communication planned where required.
- [ ] Applicable Clause 5 activities and 7.4 risk analysis completed for modifications.
- [ ] Re-release satisfies 5.8 / release management checklist.

## Traceability
- Link maintenance records to `PR-###`, `CR-###`, release versions, and postmarket records.
- See `REG-POSTMKT-LABEL` for vigilance and FSCA specifics.

## References
- IEC 62304:2006+A1:2015, Clause 6 (software maintenance process).
- IEC 62304:2006+A1:2015, 5.8 (re-release).
- `DOC-PROBLEM-RES`, `DOC-SCM`, `DOC-CHANGE-CONTROL`, `CICD-RELEASE`.
- `REG-POSTMKT-LABEL` (complaints, vigilance, field actions).

## Changelog
- 1.0.0 (2026-05-21): Initial skill for IEC 62304 Clause 6 software maintenance.
