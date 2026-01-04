---
skill_id: TEST-COVERAGE
version: 1.0.0
last_updated: 2026-01-04
applies_to: [Class A, Class B, Class C]
jurisdiction: [Global]
prerequisites: [TEST-UNIT, TEST-INTEGRATION]
---

# Code Coverage Analysis

## Purpose
Measure and enforce coverage appropriate to safety class: statement/branch and MC/DC where applicable, with documented exclusions.

## When to Apply
- Unit and integration testing phases; before releases.
- After significant code changes affecting control logic.

## Requirements (testable)
1. Metrics: Collect statement and branch coverage; for Class C control logic, MC/DC where feasible. Rationale: evidence of test thoroughness.
2. Targets by Class: Define minimums (e.g., Class A: stmt≥80%, branch≥70; Class B: stmt≥90%, branch≥80; Class C: stmt≥95%, branch≥90, MC/DC for safety logic). Rationale: risk-based rigor.
3. Exclusions: Document and justify any excluded code (e.g., defensive assertions, unreachable hardware stubs); peer review exclusions. Rationale: transparency.
4. Tooling: Use consistent coverage tools; ensure build flags don’t alter behavior materially; keep artifacts. Rationale: reproducibility.
5. Gating: Block merges/releases when coverage regresses beyond thresholds without approved justification. Rationale: maintain bar.

## Recommended Practices
- Separate coverage runs for unit vs integration if needed; merge reports.
- Include tests for error paths to improve branch coverage.
- Periodically review high-risk modules for MC/DC attempts even if tooling is limited.

## Patterns
Coverage thresholds (example policy):
```text
Class B min: stmt 90%, branch 80%; MC/DC encouraged for control logic
```

Exclude rationale entry:
```yaml
# REQ-COV-EXCL-01
file: src/assert.c
region: fatal_halt()
reason: Safety halt path; not reachable in normal test. Verified by inspection.
approved_by: safety_reviewer
```

## Anti-Patterns (risks)
- Counting coverage with tests that do not assert outcomes -> risk: false confidence.
- Large unreviewed exclusion lists -> risk: untested critical logic.
- Using coverage flags that change optimization/behavior in unsafe ways -> risk: mismatch to production.

## Verification Checklist
- [ ] Coverage collected (stmt/branch; MC/DC where applicable) with defined thresholds by class.
- [ ] Exclusions documented, reviewed, and minimal.
- [ ] Coverage reports stored as artifacts; reproducible runs.
- [ ] Coverage gating enforced; regressions blocked or justified/approved.
- [ ] Error/edge paths tested to support branch/MC/DC.

## Traceability
- `REQ-COV-###` linked to coverage policy and reports per release; map safety-critical modules to MC/DC efforts.

## References
- DO-178C MC/DC concepts (informative); IEC 62304 verification rigor guidance.
- Tool docs (gcov/lcov, llvm-cov, commercial MC/DC tools).

## Changelog
- 1.0.0 (2026-01-04): Initial coverage skill with class-based thresholds and exclusion governance.

## Audit History
- **2026-01-04**: Audit performed. Verified:
  - MC/DC concepts correctly referenced from DO-178C as informative
  - Coverage thresholds by safety class are reasonable guidelines
  - gcov/lcov and llvm-cov tool references are accurate
