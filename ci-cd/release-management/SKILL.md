---
skill_id: CICD-RELEASE
version: 1.1.0
last_updated: 2026-05-21
applies_to: [Class A, Class B, Class C]
jurisdiction: [FDA, EU MDR, Global]
prerequisites: [REG-IEC62304, REG-ISO14971, SEC-SECURE-OTA]
---

# Release Management

## Purpose
Define controlled release process for medical device software: versioning, branching, verification, approvals, documentation, and post-release monitoring.

## When to Apply
- Preparing any software release or field update.

## Requirements (testable)
1. Verification Complete [Class A, B, C]: Ensure all software verification activities for the release are complete and results evaluated before release. Rationale: 5.8.1.
2. Residual Anomalies [Class A, B, C]: Document all known residual anomalies. Rationale: 5.8.2.
3. Anomaly Risk Evaluation [Class B, C]: Evaluate residual anomalies so they do not contribute to unacceptable risk. Rationale: 5.8.3.
4. Released Version [Class A, B, C]: Document the software version being released. Rationale: 5.8.4.
5. Build Procedure [Class B, C]: Document procedure and environment used to create released software. Rationale: 5.8.5.
6. Plan Completion [Class B, C]: Confirm development or maintenance plan activities and associated documentation are complete. Rationale: 5.8.6.
7. Archive [Class A, B, C]: Archive software, configuration items, and documentation for required retention period. Rationale: 5.8.7.
8. Reliable Delivery [Class A, B, C]: Use procedures to deliver released software without corruption or unauthorized change (media, OTA, SaaS as applicable). Rationale: 5.8.8.
9. Branch Strategy: Protected release branches; gated merges; immutable tags. Rationale: reproducibility with `DOC-SCM`.
10. Artifacts: Signed binaries, SBOM, test reports, coverage, trace matrices, checksums. Rationale: auditability.
11. Post-Release: Monitor field feedback per `DOC-SW-MAINT` and `REG-POSTMKT-LABEL`. Rationale: Clause 6.

## Recommended Practices
- Maintain a release checklist template.
- Generate human-readable and machine-readable release manifests.
- Align release cadence with regulatory submission plans when applicable.
- Include rollback plan for field updates.

## Patterns
Release manifest (YAML):
```yaml
version: 1.3.0
git_tag: v1.3.0
artifacts:
  - fw.bin
  - fw.bin.sig
  - sbom.json
checksums:
  fw.bin: sha256:...
approvals:
  qa: alice
  ra: bob
tests: [unit.xml, integ.xml, hil.xml]
```

Release checklist (excerpt):
```
- [ ] All verification complete and evaluated (5.8.1)
- [ ] Residual anomalies documented and risk-evaluated B/C (5.8.2–5.8.3)
- [ ] Version and build procedure recorded (5.8.4–5.8.5)
- [ ] SDP/maintenance activities complete (5.8.6)
- [ ] Archive and delivery controls executed (5.8.7–5.8.8)
- [ ] SBOM and trace matrices stored
```

## Anti-Patterns (risks)
- Ad-hoc releases without baselines/tags -> risk: irreproducible builds.
- Missing approvals -> risk: compliance gap.
- Shipping without security/verification checks -> risk: defects in field.
- No rollback plan -> risk: prolonged outage/safety impact.

## Verification Checklist
- [ ] Version/tag assigned; branch protected; reproducible build recorded.
- [ ] Required verification passed; SAST/DAST/coverage within thresholds.
- [ ] Approvals captured (QA/RA/security).
- [ ] Artifacts signed, checksummed, SBOM and trace matrices stored.
- [ ] Post-release monitoring plan in place; rollback plan defined.

## Traceability
- Link release tag to build metadata, change requests, test reports, SBOM, and approvals; store manifest with artifacts.

## References
- IEC 62304:2006+A1:2015, 5.8 (software release).
- `DOC-SCM`, `DOC-SW-MAINT`, `DOC-TEST-DOCS`.
- FDA/MDR submission documentation for software versions.
- SLSA concepts for provenance (informative).

## Changelog
- 1.1.0 (2026-05-21): Mapped requirements to 5.8.1–5.8.8.
- 1.0.0 (2026-01-04): Initial release management skill with branching, verification, approvals, and monitoring.

## Audit History
- **2026-01-04**: Audit performed. Verified:
  - IEC 62304 config/release expectations correctly referenced
  - FDA/MDR submission documentation requirements appropriately noted
  - SLSA concepts correctly marked as informative
