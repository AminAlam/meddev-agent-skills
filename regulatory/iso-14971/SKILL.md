---
skill_id: REG-ISO14971
version: 1.0.0
last_updated: 2026-01-04
applies_to: [Class A, Class B, Class C]
jurisdiction: [FDA, EU MDR, Canada, UK]
prerequisites: []
---

# ISO 14971 Risk Management for Software

## Purpose
Integrate ISO 14971:2019 risk management into software development: hazard identification, risk evaluation, control implementation in code, verification of effectiveness, and documentation of residual risk.

## When to Apply
- Any change affecting hazards, controls, or mitigations.
- New features, interfaces, or protocols.
- Safety classification updates or architecture changes.
- Cybersecurity-relevant changes (maps into threat modeling skill if used).

## Requirements (testable)
1. Hazard Identification: Maintain a software hazard list with causes, sequences, and harms per ISO 14971:2019 5–6. Rationale: foundation for controls.
2. Risk Evaluation: Use defined criteria for severity/probability; classify risks and document rationale. Rationale: consistent decisions.
3. Risk Control Implementation: For each unacceptable risk, implement controls in design/code with explicit link to `RISK-CTRL-###` per 7. Rationale: traceable controls.
4. Verification of Controls: Each control has verification evidence (test, analysis, inspection) showing risk reduction per 8. Rationale: effectiveness.
5. Residual Risk: Record residual risk acceptability and justification; escalate if aggregate risk changes per 8. Rationale: decision visibility.
6. Safe State Definition: Define and implement safe states for hazardous conditions; test transitions. Rationale: bounded failure behavior.
7. Fault Handling: Link fault handlers to hazards/controls and verify logging/annunciation where applicable. Rationale: detect/respond to faults.
8. Documentation: Maintain risk management file artifacts updated with changes (hazards, controls, verification, residuals). Rationale: auditability.
9. Commit Traceability: Commits modifying controls or hazards must include IDs (`RISK-###`, `RISK-CTRL-###`, `REQ-###`). Rationale: change traceability.

## Recommended Practices
- Keep a single source of truth: `risk-register.yaml` with hazards, controls, verification.
- Use templated commit messages: `RISK: RISK-12 mitigated via RISK-CTRL-7; TEST-305 added`.
- Align safe-state logic with architecture segregation (see safety-classification skill).
- Pair risk controls with monitoring/diagnostics to detect degradation.

## Patterns
Risk control with traceability and safe state:
```c
// HZ-07: Over-infusion; RISK-CTRL-19: clamp and alarm within 100 ms
// REQ-221, TEST-410 covers timing
bool enforce_over_infusion_limit(float rate_ml_per_hr) {
    if (rate_ml_per_hr > MAX_RATE_ML_PER_HR) {
        clamp_line();            // physical mitigation
        alarm_over_rate();       // user mitigation
        enter_safe_state();      // safe state: pump stopped, alarm latched
        return false;
    }
    return true;
}
```

Residual risk documentation (YAML):
```yaml
hazard: HZ-07
control: RISK-CTRL-19
verification:
  - TEST-410: timing <100 ms pass
  - TEST-411: alarm annunciation pass
residual_risk: acceptable_per_policy_RP-02
justification: Meets severity/probability target after control per table RM-1
```

Commit message format:
```
feat: enforce over-infusion limit

RISK: HZ-07 mitigated by RISK-CTRL-19
REQ: REQ-221 updated
TEST: TEST-410 added, TEST-411 updated
```

## Anti-Patterns (risks)
- Generic “improved safety” commits without IDs -> risk: lost traceability.
- Controls implemented without verification -> risk: unproven effectiveness.
- Safe state undefined or unreachable -> risk: uncontrolled hazardous behavior.
- Fault handlers that log only -> risk: no actual mitigation.
- Residual risk not reassessed after change -> risk: aggregate risk drift.

## Verification Checklist
- [ ] Hazards updated for new/changed functionality; causes and harms documented.
- [ ] Risk evaluation uses defined criteria; severity/probability recorded.
- [ ] Controls mapped to hazards with IDs (`RISK-CTRL-###`) and implemented.
- [ ] Verification evidence exists and passes for each control.
- [ ] Safe states defined, reachable, and tested for hazardous conditions.
- [ ] Fault handling paths tied to hazards; logging/annunciation verified.
- [ ] Residual risk acceptability documented; escalation performed if needed.
- [ ] Commits touching hazards/controls include IDs in message.
- [ ] Risk management file artifacts regenerated/baselined after change.

## Traceability
- Use stable IDs: hazards (`HZ-###`), controls (`RISK-CTRL-###`), requirements (`REQ-###`), tests (`TEST-###`).
- Embed IDs in code comments, test names, and commit messages.
- Maintain `risk-register.yaml` or equivalent; generate hazard->control->verification views.

## References
- ISO 14971:2019, clauses 4–10 (risk management process).
- IEC TR 80002-1:2019 (guidance on applying ISO 14971 to software; second edition).
- FDA Guidance: "Content of Premarket Submissions for Device Software Functions" (2023) for submission expectations.
- FDA Guidance: "Cybersecurity in Medical Devices" (2023) for security risk management alignment.
- MDCG 2019-16 (guidance on cybersecurity for medical devices; EU MDR context).

## Changelog
- 1.0.1 (2026-01-04): Audit corrections - updated IEC TR 80002-1 to 2019 edition, clarified FDA guidance references.
- 1.0.0 (2026-01-04): Initial skill with hazard/control patterns, safe state guidance, commit traceability, and verification checklist.

## Audit History
- **2026-01-04**: Regulatory audit performed. Corrections applied:
  - IEC TR 80002-1:2009 updated to 2019 edition (second edition)
  - Generic "FDA premarket software guidance" replaced with specific 2023 guidance titles
