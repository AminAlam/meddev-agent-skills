---
skill_id: DOC-TRACEABILITY
version: 1.0.0
last_updated: 2026-01-04
applies_to: [Class A, Class B, Class C]
jurisdiction: [Global]
prerequisites: [REG-IEC62304, REG-ISO14971, DOC-INLINE]
---

# Requirements Traceability

## Purpose
Ensure bidirectional traceability between requirements, hazards/risks, design, code, tests, and anomalies for medical device software.

## When to Apply
- All lifecycle phases; especially during changes and release preparation.

## Requirements (testable)
1. ID Schema: Use stable IDs for requirements (`REQ-###`), hazards (`HZ-###`), risks/controls (`RISK-CTRL-###`), design (`DES-###`), tests (`TEST-###`), and anomalies (`ANOM-###`). Rationale: unambiguous linkage.
2. Bidirectionality: Maintain trace both forward (REQ->DES->CODE->TEST) and backward (TEST->REQ). Rationale: completeness and impact analysis.
3. Automation: Generate traceability matrices from managed artifacts (reqs tool + code tags + test metadata). Rationale: reduce drift.
4. Change Impact: For each change, update trace links and assess affected items/tests. Rationale: controlled updates.
5. Evidence Storage: Store trace outputs as release artifacts; version them with builds. Rationale: auditability.

## Recommended Practices
- Keep a `traceability.yaml` or use ALM exports to CSV/HTML for submissions.
- Include trace tags in code comments and test names.
- Integrate trace checks in CI (e.g., missing links).

## Patterns
Traceability entry (YAML):
```yaml
# REQ-TRC-01
REQ-62304-102:
  design: [DES-PUMP-01]
  code: [pump_stop_on_door_open]
  tests: [TEST-410, TEST-411]
  hazards: [HZ-07]
  risks: [RISK-CTRL-19]
```

CI check (concept):
```text
Validate: every TEST-* references a REQ-*; fail build on missing link.
```

## Anti-Patterns (risks)
- Trace only in one direction -> risk: missing coverage.
- Manual spreadsheets without automation -> risk: drift and errors.
- Unlabeled code/tests -> risk: broken trace in audits.
- Trace outputs not baselined -> risk: mismatch to released build.

## Verification Checklist
- [ ] IDs consistent and present across artifacts.
- [ ] Forward/backward traces maintained; gaps resolved.
- [ ] Trace matrices generated automatically and stored per release.
- [ ] Change impact updates traces and triggers required tests.
- [ ] CI checks for missing/invalid links in code/tests.

## Traceability
- Central `traceability.yaml`/tool export; code/test tags; release-stored matrices.

## References
- IEC 62304 traceability (5.1–5.6).
- ISO 14971 for hazard-to-control linkage.
- FDA/MDR submission expectations for trace matrices.

## Changelog
- 1.0.0 (2026-01-04): Initial traceability skill with IDs, automation, and CI checks.

## Audit History
- **2026-01-04**: Audit performed. Verified:
  - IEC 62304 traceability (5.1-5.6) references accurate
  - ISO 14971 hazard-to-control linkage correctly noted
  - FDA/MDR trace matrix expectations appropriate
