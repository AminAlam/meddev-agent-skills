---
skill_id: DOC-CHANGE-CONTROL
version: 1.1.0
last_updated: 2026-05-21
applies_to: [Class A, Class B, Class C]
jurisdiction: [FDA, EU MDR, Global]
prerequisites: [REG-IEC62304, REG-ISO14971, DOC-INLINE, DOC-SCM]
---

# Change Control Process

## Purpose
Define controlled change-request workflow for software: impact analysis, approvals, verification scope, and regulatory submission flags. Configuration identification and baselines are in `DOC-SCM` (IEC 62304 Clause 8.1, 8.3); approved implementation and re-verification align with 8.2.

## When to Apply
- Any change to safety-relevant software, requirements, design, tests, or configuration items.
- Defect fixes, updates, refactors, and dependency/SOUP updates.

## Requirements (testable)
1. Change Request: Document change description, rationale, items affected, and trace links (requirements, hazards, tests). Rationale: clarity.
2. Impact Analysis: Assess safety, cybersecurity, interoperability, documentation, and submission impact (FDA/MDR). Rationale: risk-aware decisions.
3. Approval: Obtain appropriate approvals (engineering + QA/RA) before implementation for safety-relevant changes. Rationale: governance.
4. Verification: Define and execute verification/validation scope for the change; include regression tests. Rationale: assurance.
5. Problem Linkage: Link change requests to related problem reports when applicable. Rationale: 8.2.4.
6. SCM Handoff: After approval, implement via `DOC-SCM` (baselines, item versions, re-verification). Rationale: 8.2.2–8.2.3.
7. Submission Considerations: Flag changes that may trigger regulatory submission/update; record decision. Rationale: compliance.
8. Released Software [Class A, B, C]: For post-release changes, also perform maintenance impact analysis per `DOC-SW-MAINT` (6.2.3). Rationale: 6.2.

## Recommended Practices
- Use templates for change requests with required fields.
- Include SBOM updates when dependencies change.
- Capture change risk level (minor/major) and tailor verification accordingly.
- Link commits/PRs to change request IDs.

## Patterns
Change request (YAML):
```yaml
CR-145:
  description: Fix over-infusion timing edge case
  rationale: observed jitter at low battery
  affects: [REQ-62304-102, RISK-CTRL-19, TEST-410]
  risk: major
  submission_impact: no (reviewed QA/RA)
```

Verification entry:
```markdown
Tests: TEST-410, TEST-411 rerun; new TEST-415 added for low-batt timing
Result: PASS
```

## Anti-Patterns (risks)
- Implementing changes without impact analysis -> risk: missed verification, submission gaps.
- Skipping approvals for safety changes -> risk: noncompliance.
- No linkage to tests/requirements -> risk: lost traceability.
- Not updating SBOM after dependency changes -> risk: unmanaged vulnerabilities.

## Verification Checklist
- [ ] Change request recorded with rationale and affected artifacts.
- [ ] Impact analysis completed (safety, cyber, interoperability, submission).
- [ ] Approvals obtained per policy for safety-relevant changes.
- [ ] Verification/regression defined and executed; results recorded.
- [ ] Change linked to problem report(s) when applicable (8.2.4).
- [ ] SCM baseline updated; re-verification completed per `DOC-SCM`.
- [ ] Submission impact decision documented.
- [ ] Post-release changes: maintenance impact per `DOC-SW-MAINT` when applicable.

## Traceability
- Change IDs (`CR-###`) linked to `PR-###`, requirements, risks, commits/PRs, and test evidence.
- Store decisions and approvals with release artifacts.

## References
- IEC 62304:2006+A1:2015, 8.2 (change control); 6.2.3–6.2.4 (released software).
- `DOC-SCM`, `DOC-PROBLEM-RES`, `DOC-SW-MAINT`.
- FDA/MDR expectations for software change impact and documentation.

## Changelog
- 1.1.0 (2026-05-21): Scoped to change requests; SCM and problem links; maintenance cross-ref.
- 1.0.0 (2026-01-04): Initial change control skill with impact analysis and approval process.

## Audit History
- **2026-01-04**: Audit performed. Verified:
  - IEC 62304 configuration management and change control references accurate
  - FDA/MDR change impact documentation expectations correctly noted
