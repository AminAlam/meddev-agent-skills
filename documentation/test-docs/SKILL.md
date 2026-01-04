---
skill_id: DOC-TEST-DOCS
version: 1.0.0
last_updated: 2026-01-04
applies_to: [Class A, Class B, Class C]
jurisdiction: [Global]
prerequisites: [TEST-UNIT, TEST-INTEGRATION, DOC-INLINE]
---

# Test Documentation

## Purpose
Define structure and content for test plans, protocols, and reports that support regulatory submissions and internal verification.

## When to Apply
- Planning and executing verification/validation across unit, integration, system, and HIL.
- Preparing evidence for submissions or audits.

## Requirements (testable)
1. Test Plan: Objectives, scope, environment, roles, entry/exit criteria, and traceability to requirements/risks. Rationale: structured verification.
2. Protocols: Step-by-step procedures, inputs, expected results, and acceptance criteria; include negative cases. Rationale: repeatability.
3. Reports: Actual results, deviations, defects, and conclusion vs acceptance criteria. Rationale: evidence of execution.
4. Traceability: Each test case links to requirements/hazards; matrices maintained. Rationale: completeness.
5. Configuration Control: Environments, tools, and versions recorded; reproducible setups. Rationale: consistency.

## Recommended Practices
- Use IDs for test plans (`TPL-###`), cases (`TC-###`), protocols (`TPR-###`), and reports (`TRP-###`).
- Include data sets and seeds where applicable.
- For automation, capture logs and artifacts (coverage, waveforms, power traces).

## Patterns
Test plan snippet (Markdown):
```markdown
TPL-210: Pump Safety Verification Plan
Scope: Class C control loop, door-open safety
Entry: unit/int tests pass; firmware v1.3.0
Exit: all TC pass; defects triaged; coverage targets met
Trace: REQ-62304-102, HZ-07, RISK-CTRL-19
```

Protocol entry (table):
```
Step | Action | Expected
1 | Open door sensor | Motor stops within 50 ms; alarm active
```

Report excerpt:
```markdown
TRP-210 Result: PASS
Deviations: None
Defects: DEF-88 (UI lag) - not safety relevant
```

## Anti-Patterns (risks)
- Missing traceability -> risk: unverifiable coverage.
- Only positive tests documented -> risk: gaps in error handling evidence.
- Uncontrolled environments -> risk: irreproducible results.
- Reports without deviations/defects -> risk: incomplete transparency.

## Verification Checklist
- [ ] Test plan exists with scope, criteria, and traceability.
- [ ] Protocols include steps, inputs, expected results (positive/negative).
- [ ] Reports capture actual results, deviations, defects, and conclusions.
- [ ] Environments/tools/configurations recorded.
- [ ] Traceability matrix maintained requirements↔tests.

## Traceability
- IDs (`TPL-###`, `TC-###`, `TPR-###`, `TRP-###`) linked to `REQ-###` and `HZ-###`; stored with release artifacts.

## References
- IEC 62304 verification documentation expectations.
- FDA/MDR submission formats for test evidence (device-specific).

## Changelog
- 1.0.0 (2026-01-04): Initial test documentation skill with plans, protocols, and reports.

## Audit History
- **2026-01-04**: Audit performed. Verified:
  - IEC 62304 verification documentation expectations accurate
  - FDA/MDR submission format references appropriate
