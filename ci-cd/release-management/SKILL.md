---
skill_id: CICD-RELEASE
version: 1.0.0
last_updated: 2026-01-04
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
1. Versioning: Use semantic and/or regulated versioning; tie to configuration baselines; record in release notes. Rationale: traceability.
2. Branch Strategy: Maintain protected release branches; gate merges with tests/approvals; tag releases. Rationale: control and reproducibility.
3. Verification: Ensure required tests (unit/integration/HIL), coverage, SAST/DAST, and security scans pass for the release build. Rationale: assurance.
4. Approvals: Obtain required QA/RA and security approvals; document sign-offs. Rationale: governance.
5. Artifacts: Store signed binaries, SBOM, test reports, coverage, and trace matrices; include checksums. Rationale: auditability and integrity.
6. Post-Release: Monitor field metrics, incidents, and vulnerabilities; feed into PMS/risk files; patch policy defined. Rationale: lifecycle safety.

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
- [ ] Tests/coverage meet thresholds
- [ ] SAST/DAST clean or issues accepted with rationale
- [ ] SBOM generated and stored
- [ ] Approvals recorded
- [ ] Rollback plan documented
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
- IEC 62304 config/release expectations.
- FDA/MDR submission documentation for software versions.
- SLSA concepts for provenance (informative).

## Changelog
- 1.0.0 (2026-01-04): Initial release management skill with branching, verification, approvals, and monitoring.

## Audit History
- **2026-01-04**: Audit performed. Verified:
  - IEC 62304 config/release expectations correctly referenced
  - FDA/MDR submission documentation requirements appropriately noted
  - SLSA concepts correctly marked as informative
