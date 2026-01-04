---
skill_id: CICD-AUTO-TEST
version: 1.0.0
last_updated: 2026-01-04
applies_to: [Class A, Class B, Class C]
jurisdiction: [Global]
prerequisites: [TEST-UNIT, TEST-INTEGRATION]
---

# Automated Testing in CI/CD

## Purpose
Define how to automate tests (unit, integration, system/HIL where feasible) in CI/CD pipelines for medical devices with gating and evidence capture.

## When to Apply
- Setting up or updating test stages in CI/CD.

## Requirements (testable)
1. Scope: Include unit, integration, and where possible system/HIL or simulators; prioritize safety-related modules. Rationale: coverage of risk areas.
2. Gating: Fail pipeline on test failures; no ignored failures for safety code. Rationale: prevent regressions.
3. Artifacts: Store test results (JUnit/XML), logs, coverage, and evidence; retain per release. Rationale: auditability.
4. Flake Management: Detect and address flaky tests; quarantine with issue filed and timeline; do not ignore. Rationale: trustworthiness.
5. Hardware Tests: If hardware required, provide conditional stages and fallbacks (sim); schedule regular hardware runs (nightly). Rationale: practicality with coverage.

## Recommended Practices
- Tag tests by type/priority; run critical ones on every commit.
- Use retries sparingly and only for known flaky, with tracking.
- Parallelize to keep feedback fast.
- Use containerized or pinned environments.

## Patterns
CI job snippet:
```yaml
test:
  script: [ "ctest --output-on-failure" ]
  artifacts:
    when: always
    paths: [ "build/test-results.xml", "coverage/" ]
```

Flake tracking entry:
```yaml
test_id: TEST-INT-210
status: flaky
issue: QA-1234
expires: 2026-02-01
```

## Anti-Patterns (risks)
- Allowing tests to fail without blocking or tracking -> risk: regressions.
- No artifacts/logs retained -> risk: unverifiable results.
- Silent retries masking real failures -> risk: shipping defects.

## Verification Checklist
- [ ] Unit/integration (and sim/HIL if available) tests run in CI.
- [ ] Failures gate merges; no ignored failures for safety code.
- [ ] Results/logs/coverage stored as artifacts per run/release.
- [ ] Flaky tests tracked with issues and timelines.
- [ ] Hardware-dependent tests scheduled; sim fallback provided.

## Traceability
- Link CI test runs to test IDs (`TEST-###`) and requirements; store artifacts with release metadata.

## References
- IEC 62304 verification expectations.
- FDA/MDR submission evidence needs.

## Changelog
- 1.0.0 (2026-01-04): Initial automated testing skill with gating and artifact capture.

## Audit History
- **2026-01-04**: Audit performed. Verified:
  - IEC 62304 verification expectations correctly referenced
  - CI/CD patterns follow industry best practices for regulated environments
