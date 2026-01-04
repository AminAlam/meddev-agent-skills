---
skill_id: TEST-SAST
version: 1.0.0
last_updated: 2026-01-04
applies_to: [Class A, Class B, Class C]
jurisdiction: [Global]
prerequisites: [FW-EMBEDDED-C, FW-EMBEDDED-CPP]
---

# Static Analysis for Medical Devices

## Purpose
Use static analysis (SAST) to detect defects and nonconformities (MISRA, CERT) early, with triage and traceability appropriate to safety class.

## When to Apply
- On every merge/CI for safety-related code.
- Before releases and after major refactors.

## Requirements (testable)
1. Tooling: Run at least one configured SAST tool (e.g., PC-lint, Coverity, clang-tidy) and MISRA checker; warnings-as-errors for safety code. Rationale: defect prevention.
2. Rule Sets: Enable MISRA C/C++ rules (profiled if needed) and relevant CERT checks; document deviations. Rationale: coding standard conformance.
3. Triage: Review findings, classify (true/false positive), and track to closure; justify any suppressions. Rationale: accountability.
4. Baseline Control: Maintain clean baselines; prevent reintroduction of suppressed/closed issues. Rationale: prevent regression.
5. Integration: Run in CI; fail builds on new high/medium findings for safety code. Rationale: continuous enforcement.

## Recommended Practices
- Use project-specific suppressions in config files, not inline, unless localized rationale is needed.
- Periodically refresh tool versions/rulesets.
- Combine SAST with formatting/lint to reduce noise.

## Patterns
clang-tidy config snippet:
```yaml
Checks: '-*,bugprone-*,cert-*,cppcoreguidelines-*,clang-analyzer-*'
WarningsAsErrors: 'bugprone-*,cert-*,clang-analyzer-*'
HeaderFilterRegex: 'src/.*'
```

MISRA deviation record (YAML):
```yaml
id: MISRA-DEV-12
rule: MISRA C:2012 17.7
location: src/hal/uart.c:88
rationale: driver API requires function-like macro; wrapper added; risk minimal
approval: safety_officer_1
```

## Anti-Patterns (risks)
- Ignoring warnings or mass-suppressing -> risk: latent defects.
- Inline suppressions without rationale -> risk: hidden issues.
- Stale tool versions/rules -> risk: missed checks.
- Allowing new warnings to accumulate -> risk: erosion of quality bar.

## Verification Checklist
- [ ] SAST and MISRA checks run in CI; warnings-as-errors for safety code.
- [ ] Rule sets configured and documented; deviations recorded with rationale/approval.
- [ ] Findings triaged and tracked; no unreviewed findings in safety code.
- [ ] Baseline maintained; new findings gate merges/releases.
- [ ] Tool versions/rules kept current.

## Traceability
- Link SAST findings to requirements/risks where relevant; store reports as build artifacts per release.

## References
- MISRA C:2012 / MISRA C++.
- CERT C/C++.
- FDA cybersecurity guidance encourages static analysis use.

## Changelog
- 1.0.0 (2026-01-04): Initial static analysis skill with MISRA and triage expectations.

## Audit History
- **2026-01-04**: Audit performed. Verified:
  - MISRA C:2012 and MISRA C++ references accurate
  - CERT C/C++ correctly referenced
  - Tool mentions (PC-lint, Coverity, clang-tidy) are appropriate
  - clang-tidy config example is syntactically correct
