---
skill_id: DOC-PROBLEM-RES
version: 1.0.0
last_updated: 2026-05-21
applies_to: [Class A, Class B, Class C]
jurisdiction: [FDA, EU MDR, Global]
prerequisites: [REG-IEC62304, REG-IEC62304-SWRM, DOC-CHANGE-CONTROL]
---

# Software Problem Resolution Process

## Purpose
Define how to record, investigate, resolve, and trend software problems (defects, anomalies, complaints) per IEC 62304:2006+A1:2015, Clause 9—linking safety evaluation, change control, verification closure, and test documentation.

## When to Apply
- Defects found in development, verification, manufacturing, or field use.
- Complaints or internal reports referencing software behaviour, crashes, or security issues.
- Anomalies from integration, system, or regression testing (5.6.8, 5.7.2).
- Periodic review of problem trends for quality and safety signals.

## Requirements (testable)
1. Problem Reports [Class A, B, C]: Create a problem report for each detected software problem; include criticality (performance, safety, security), affected products/versions, and context to support resolution. Rationale: 9.1.
2. Investigation [Class A, B, C]: Investigate causes where possible; evaluate relevance to safety using the software risk process; document outcomes; create change request(s) or document rationale for no action. Rationale: 9.2.
3. Stakeholder Communication [Class A, B, C]: Notify relevant parties of significant problems per manufacturer policy (interpretation). Rationale: 9.3.
4. Change Control Link [Class A, B, C]: Implement approved corrections through the change control process (Clause 8.2 / `DOC-CHANGE-CONTROL`). Rationale: 9.4.
5. Records and Risk File [Class A, B, C]: Retain problem reports and resolution records including verification; update risk management file when safety relevance changes. Rationale: 9.5.
6. Trend Analysis [Class A, B, C]: Periodically analyse problem reports for trends (recurring areas, SOUP, modules). Rationale: 9.6.
7. Resolution Verification [Class A, B, C]: Verify fixes—confirm problem closed, trends addressed, changes implemented in correct builds, and no new problems introduced. Rationale: 9.7.
8. Test Documentation on Retest [Class A, B, C]: After changes, test records include results, anomalies, software version tested, environment, tools, date, and tester identity (align with `DOC-TEST-DOCS`). Rationale: 9.8.

## Recommended Practices
- Use IDs `PR-###` for problem reports and link to `CR-###`, `DEF-###`, commits, and `TEST-###`.
- Separate security-critical from safety-critical criticality; escalate per QMS.
- Feed field problems from postmarket processes (`REG-POSTMKT-LABEL`) into the same problem pipeline.
- Re-assess software safety class when investigation shows misclassification (interpretation; see 6.2.2 note in standard).

## Patterns
Problem report (YAML):
```yaml
problem_report:
  id: PR-2026-088
  source: field_complaint
  software_version: 1.2.3
  criticality: safety
  summary: infusion continues 120 ms after door open
  investigation:
    cause: race between ISR and task in pump_control
    safety_evaluation: REG-IEC62304-SWRM 9.2 — links HZ-07
  disposition: change_required
  change_request: CR-201
```

Trend review log:
```markdown
## Problem trend review 2026-Q2
- 4/12 PRs tagged soup:tiny-rtos — escalate SOUP review
- 2/12 PRs door_sensor path — add TEST-415 regression
```

## Anti-Patterns (risks)
- Fixing code without a problem report or change record -> risk: audit trail and CAPA gaps.
- Closing reports without verification evidence -> risk: unresolved safety issues.
- No trend review -> risk: systemic defects undetected.
- Retest records missing version/environment -> risk: non-repeatable evidence (9.8).

## Verification Checklist
- [ ] Each software problem has a problem report with criticality and context.
- [ ] Investigation and safety evaluation documented; change request or no-action rationale recorded.
- [ ] Corrections implemented via approved change control.
- [ ] Resolution records and risk file updates retained.
- [ ] Trend analysis performed per schedule.
- [ ] Closure verification confirms fix and no new regressions.
- [ ] Retest documentation includes required record fields.

## Traceability
- Link `PR-###` ↔ `CR-###` ↔ commits/PRs ↔ `TEST-###` ↔ `HZ-###` / `REQ-###`.
- Integration and system test anomalies must enter this process (5.6.8, 5.7.2).

## References
- IEC 62304:2006+A1:2015, Clause 9 (software problem resolution process).
- IEC 62304:2006+A1:2015, 8.2 (change control; `DOC-SCM`, `DOC-CHANGE-CONTROL`).
- `REG-IEC62304-SWRM` (safety evaluation in 9.2).
- `DOC-TEST-DOCS` (5.7.5, 9.8 test records).

## Changelog
- 1.0.0 (2026-05-21): Initial skill for IEC 62304 Clause 9 problem resolution.
