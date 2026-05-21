---
skill_id: REG-IEC62304-LEGACY
version: 1.0.0
last_updated: 2026-05-21
applies_to: [Class A, Class B, Class C]
jurisdiction: [FDA, EU MDR, Canada, UK]
prerequisites: [REG-IEC62304, REG-ISO14971]
---

# IEC 62304 Legacy Software (Amendment A1)

## Purpose
Guide use of the legacy software pathway (IEC 62304:2006+A1:2015, 4.4) when device software was legally marketed before full lifecycle evidence existed—balancing continued use with gap analysis, risk management, and targeted closure activities instead of re-running all of Clauses 5–9 from scratch.

## When to Apply
- Maintaining or modifying software placed on the market without adequate objective evidence of full IEC 62304 compliance.
- EU MDR transitions or legacy device software updates.
- Deciding whether to use 4.4 versus full development/maintenance processes for an existing codebase.
- Post-market feedback on long-lived products with incomplete design history files.

## Requirements (testable)
1. Eligibility Decision [Class A, B, C]: Document that software qualifies as legacy per manufacturer criteria (market history, evidence gaps); record version under evaluation. Rationale: 4.4.1.
2. Post-Market Risk Review [Class A, B, C]: Review internal and user feedback (incidents, near-incidents) for legacy software; perform risk management on continued use including architecture integration, validity of existing controls, hazardous situations, causes, and needed controls. Rationale: 4.4.2.
3. Gap Analysis [Class B, C]: Against assigned safety class, compare available deliverables to those expected from 5.2, 5.3, 5.7, and Clause 7; assess continuing validity of existing artifacts. Rationale: 4.4.3.
4. Gap Prioritization [Class B, C]: Evaluate risk reduction from creating missing deliverables; decide which deliverables and activities to perform—minimum includes software system test records (5.7.5). Rationale: 4.4.3 d–e.
5. Gap Closure Plan [Class B, C]: Establish and execute a plan to produce needed deliverables; use existing objective evidence where it satisfies needs without repeating all development activities. Rationale: 4.4.4 a.
6. Problem Process for Legacy [Class A, B, C]: Handle legacy defects and deliverable gaps through the software problem resolution process (`DOC-PROBLEM-RES`). Rationale: 4.4.4 b.
7. Changes via Maintenance [Class A, B, C]: Modify legacy software through the maintenance process (Clause 6 / `DOC-SW-MAINT`), not ad hoc releases. Rationale: 4.4.4 c.
8. Continued-Use Rationale [Class A, B, C]: Document legacy software version and rationale for continued use based on 4.4 outputs. Rationale: 4.4.5.

## Recommended Practices
- Maintain a gap matrix spreadsheet or YAML keyed by clause and deliverable type.
- Prioritize gaps that affect risk controls and system test evidence before nice-to-have design detail.
- Align gap closure plan with software maintenance plan (6.1).
- Re-classify items if gap analysis reveals mis-assigned safety class.

## Patterns
Gap matrix (YAML):
```yaml
legacy_software:
  product: InfusionPump-X
  version: 2.1.0
  assigned_class: Class C
gaps:
  - clause: 5.2
    deliverable: software_requirements_spec
    status: partial
    action: extract from code + tests; formalize REQ IDs
  - clause: 5.7.5
    deliverable: system_test_records
    status: missing
    action: execute SYS-TEST-2026-01 protocol (mandatory minimum)
  - clause: 7.3.3
    deliverable: software_hazard_trace
    status: missing
    action: workshop with RA; link to REG-IEC62304-SWRM
continued_use_rationale: |
  Gap closure plan GP-LEG-01 approved 2026-05-15; residual risk acceptable per RM-2026-12
```

## Anti-Patterns (risks)
- Claiming 4.4 to avoid all lifecycle work without gap analysis -> risk: noncompliance and patient safety gaps.
- No system test records for legacy Class B/C -> risk: fails minimum 4.4.3 expectation.
- Legacy patches outside maintenance and change control -> risk: uncontrolled field software.
- Ignoring post-market incidents in 4.4.2 review -> risk: outdated risk picture.

## Verification Checklist
- [ ] Legacy eligibility and version documented.
- [ ] Post-market and internal feedback reviewed; risk management on continued use updated.
- [ ] Gap analysis completed vs class for 5.2, 5.3, 5.7, Clause 7.
- [ ] Missing deliverables prioritized; minimum system test records addressed.
- [ ] Gap closure plan approved and in progress or complete.
- [ ] Legacy problems use problem resolution process; changes use maintenance process.
- [ ] Continued-use rationale recorded with version.

## Traceability
- Link gap items to `REQ-###`, `TEST-###`, `PR-###`, and risk file entries.
- Reference gap plan ID in change requests affecting legacy code.

## References
- IEC 62304:2006+A1:2015, 4.4 (legacy software).
- IEC 62304:2006+A1:2015, 5.2, 5.3, 5.7, Clause 7 (gap analysis scope).
- `REG-IEC62304`, `DOC-SW-MAINT`, `DOC-PROBLEM-RES`, `REG-ISO14971`.

## Changelog
- 1.0.0 (2026-05-21): Initial skill for IEC 62304 A1 legacy software (4.4).
