---
skill_id: DOC-SCM
version: 1.0.0
last_updated: 2026-05-21
applies_to: [Class A, Class B, Class C]
jurisdiction: [FDA, EU MDR, Global]
prerequisites: [REG-IEC62304, DOC-CHANGE-CONTROL]
---

# Software Configuration Management

## Purpose
Implement identification, change control, and status accounting for software configuration items per IEC 62304:2006+A1:2015, Clause 8—ensuring reproducible baselines, controlled SOUP records, and retrievable history separate from change-request workflow details in `DOC-CHANGE-CONTROL`.

## When to Apply
- Establishing baselines for releases or milestones.
- Adding or updating SOUP, tools, requirements, design, code, or test artifacts.
- Audits requiring configuration identification and history.
- Before verification of configuration items (items under control prior to verify for Class B/C per 5.1.11).

## Requirements (testable)
1. Identification Scheme [Class A, B, C]: Define unique identification for configuration items and versions per development/configuration planning (5.1.9). Rationale: 8.1.1.
2. SOUP Records [Class A, B, C]: For each SOUP item under control, record title, supplier/manufacturer, and a unique designator (version, release date, patch, or equivalent). Rationale: 8.1.2.
3. System Configuration Document [Class A, B, C]: Document the set of configuration items and versions that constitute the released software system configuration. Rationale: 8.1.3.
4. Approved Changes Only [Class A, B, C]: Alter controlled items only after approved change requests (`DOC-CHANGE-CONTROL`). Rationale: 8.2.1.
5. Implement and Re-verify [Class A, B, C]: Implement changes per the request; repeat verification invalidated by the change (including system test and problem-resolution retest expectations). Rationale: 8.2.2–8.2.3.
6. Change Trace Records [Class A, B, C]: Maintain links between change requests, related problem reports, and approvals. Rationale: 8.2.4.
7. Status Accounting [Class A, B, C]: Keep retrievable history of controlled items including system configuration snapshots. Rationale: 8.3.

## Recommended Practices
- Store `system-config.yaml` at each release tag with hashes for binaries and SBOM.
- Include compilers, CI images, and signing tools in controlled items when they affect the build (5.1.10).
- Use semantic versioning for software items; immutable release tags in git.
- Automate baseline generation in CI after successful gated pipelines.

## Patterns
System configuration manifest (YAML):
```yaml
software_system: pump_firmware
release_version: 1.3.0
git_tag: v1.3.0
configuration_items:
  - id: CI-SRC-pump_control
    version: 1.3.0
    sha256: abc123...
  - id: CI-SOUP-tiny-rtos
    supplier: Example Corp
    designator: 1.4.2-patch1
  - id: CI-TOOL-gcc-arm
    designator: 12.2.rel1
soup:
  - title: tiny-rtos
    manufacturer: Example Corp
    designator: 1.4.2-patch1
```

Change trace snippet:
```yaml
change_trace:
  change_request: CR-201
  problem_reports: [PR-2026-088]
  approval: qa_alice 2026-05-20
  baseline_after: pump_firmware@1.3.1-rc1
```

## Anti-Patterns (risks)
- SOUP versions only in lockfiles without SCM records -> risk: audit and reproducibility gaps.
- Direct commits to release branches without change approval -> risk: 8.2.1 violation.
- No system configuration document per release -> risk: cannot reconstruct field builds.
- Missing history after force-push or tag deletion -> risk: 8.3 status accounting failure.

## Verification Checklist
- [ ] Identification scheme defined and applied to all controlled item types.
- [ ] SOUP items have title, supplier, and unique designator recorded.
- [ ] System configuration documented for each release baseline.
- [ ] Changes only via approved change requests; implementation matches request.
- [ ] Re-verification completed for invalidated tests/analyses.
- [ ] Change ↔ problem ↔ approval links maintained.
- [ ] Retrievable history available for items and system configurations.

## Traceability
- Configuration item IDs tie to `CR-###`, `PR-###`, release manifests, and `CICD-RELEASE` artifacts.
- Align with SDP configuration management planning (5.1.9).

## References
- IEC 62304:2006+A1:2015, Clause 8 (software configuration management process).
- IEC 62304:2006+A1:2015, 5.1.9–5.1.11 (planning and timing of control).
- `DOC-CHANGE-CONTROL` (change request workflow and impact analysis).
- `REG-IEC62304` (lifecycle hub).

## Changelog
- 1.0.0 (2026-05-21): Initial skill for IEC 62304 Clause 8 configuration management.
