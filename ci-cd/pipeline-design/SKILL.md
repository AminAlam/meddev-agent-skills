---
skill_id: CICD-PIPELINE
version: 1.0.0
last_updated: 2026-01-04
applies_to: [Class A, Class B, Class C]
jurisdiction: [Global]
prerequisites: [REG-IEC62304, SEC-THREAT-MODELING]
---

# CI/CD Pipeline Design for Medical Devices

## Purpose
Define regulated-friendly CI/CD pipelines with compliance checks, artifact management, and auditability for medical device software.

## When to Apply
- Establishing or modifying pipelines for regulated codebases.

## Requirements (testable)
1. Stages: Include lint/SAST, build, unit/integration tests, coverage, package signing, and artifact archival. Rationale: comprehensive verification.
2. Traceability: Capture build provenance (commit, toolchain versions, dependencies) and tie artifacts to requirements/tests. Rationale: auditability.
3. Access Control: Restrict pipeline credentials; separate duties for signing and deployment; no shared secrets. Rationale: security.
4. Artifact Integrity: Sign build artifacts; store immutably with checksums and SBOM. Rationale: integrity and provenance.
5. Environment Parity: Align CI and release build environments; pin toolchain versions. Rationale: reproducibility.
6. Audit Trail: Log pipeline runs, approvals, and results; retain for submissions. Rationale: compliance evidence.

## Recommended Practices
- Use templates for regulated projects with required stages preconfigured.
- Run security scans (SAST/DAST/depscan) regularly; fail on high findings.
- Gate releases on tests/coverage and change control approvals.
- Store SBOM and test/coverage reports with artifacts.

## Patterns
Pipeline stages (concept):
```
stages: [lint, build, test, coverage, package, sign, publish]
```

Provenance record (YAML):
```yaml
build_id: 1234
commit: abcdef
toolchain: gcc-13.2
artifacts:
  - path: fw.bin
    sha256: ...
sbom: sbom.json
tests: [unit.xml, integ.xml]
```

## Anti-Patterns (risks)
- Unauthenticated artifact storage -> risk: tampering.
- Mutable build environments -> risk: irreproducible builds.
- Skipping security scans -> risk: latent vulnerabilities.
- No audit logs -> risk: submission/audit gaps.

## Verification Checklist
- [ ] Pipeline includes lint/SAST, tests, coverage, signing, and artifact archival.
- [ ] Provenance recorded (commit, toolchain, deps) and stored with artifacts.
- [ ] Credentials/secrets controlled; signing isolated; no shared secrets.
- [ ] Artifacts signed/checksummed; SBOM stored.
- [ ] CI/release environments pinned and documented.
- [ ] Pipeline runs and approvals logged and retained.

## Traceability
- Link pipeline runs to change requests/commits and test reports; store build metadata with release.

## References
- IEC 62304 config/verification expectations.
- SLSA (Supply-chain Levels for Software Artifacts) as informative.
- FDA cybersecurity guidance (integrity, SBOM).

## Changelog
- 1.0.0 (2026-01-04): Initial pipeline design skill with stages, integrity, and audit trail.

## Audit History
- **2026-01-04**: Audit performed. Verified:
  - IEC 62304 config/verification expectations correctly referenced
  - SLSA (Supply-chain Levels for Software Artifacts) appropriately marked as informative
  - FDA cybersecurity guidance references accurate
