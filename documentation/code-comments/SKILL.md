---
skill_id: DOC-CODE-COMMENTS
version: 1.0.0
last_updated: 2026-01-04
applies_to: [Class A, Class B, Class C]
jurisdiction: [Global]
prerequisites: [REG-ISO14971, REG-IEC62304, DOC-INLINE]
---

# Code Documentation for Traceability

## Purpose
Provide conventions for code comments that support traceability to requirements, risks, and tests, while maintaining clarity and brevity.

## When to Apply
- Any safety-related code, interfaces, or tests.
- When implementing or modifying requirements or risk controls.

## Requirements (testable)
1. Traceability Tags: Use stable IDs (e.g., `REQ-###`, `RISK-CTRL-###`, `TEST-###`) in comments near implementing code. Rationale: link code to artifacts.
2. Minimal Necessary Comments: Explain intent, constraints, and safety context; avoid restating obvious code. Rationale: clarity without noise.
3. API Documentation: Public interfaces documented with purpose, parameters, ranges, error codes, and side effects. Rationale: correct usage.
4. Change History: Avoid inline history; rely on VCS; only note rationale when non-obvious decisions impact safety. Rationale: reduce clutter.
5. Generated Docs: Use Doxygen/Javadoc-style only where toolchains consume it; keep tags consistent. Rationale: consistency.

## Recommended Practices
- Co-locate traceability tags with logic they cover.
- Note assumptions and safety limits (ranges, timing).
- Keep comments in ASCII; avoid ambiguous abbreviations.
- Remove stale comments during refactors.

## Patterns
Traceability on requirement and risk control:
```c
// REQ-221: stop pump within 50 ms on door open; RISK-CTRL-19; TEST-410
bool pump_stop_on_door_open(void) {
    ...
}
```

API doc example:
```c
/**
 * @brief Set infusion rate.
 * @param ml_per_hr range [0, MAX_FLOW]; clamps and alarms if exceeded.
 * @return 0 on success, -ERANGE if clamped.
 * REQ-300, RISK-CTRL-27
 */
int set_flow(float ml_per_hr);
```

## Anti-Patterns (risks)
- No traceability tags -> risk: lost linkage in audits/impact analysis.
- Commenting the obvious or mismatched comments -> risk: clutter/confusion.
- Inline change logs instead of VCS -> risk: divergence.
- Missing parameter ranges -> risk: misuse of APIs.

## Verification Checklist
- [ ] Requirements/risk/test IDs present where applicable.
- [ ] Comments capture intent/constraints, not restating code.
- [ ] Public APIs documented with params, ranges, errors.
- [ ] Stale/misleading comments removed.
- [ ] Documentation style consistent (Doxygen/Javadoc if used).

## Traceability
- Tags `REQ-###`, `RISK-CTRL-###`, `TEST-###` aligned with external artifacts; code review enforces presence on safety-relevant sections.

## References
- IEC 62304 traceability expectations.
- ISO 14971 linkage of controls to implementation.

## Changelog
- 1.0.0 (2026-01-04): Initial code comment/traceability guidance.

## Audit History
- **2026-01-04**: Audit performed. Verified:
  - IEC 62304 traceability expectations correctly referenced
  - ISO 14971 linkage requirements accurate
