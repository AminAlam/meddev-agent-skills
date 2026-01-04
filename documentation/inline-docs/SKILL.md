---
skill_id: DOC-INLINE
version: 1.0.0
last_updated: 2026-01-04
applies_to: [Class A, Class B, Class C]
jurisdiction: [Global]
prerequisites: [DOC-CODE-COMMENTS, DOC-TRACEABILITY]
---

# Inline Documentation

## Purpose
Provide concise, high-value inline documentation practices (comments and short docblocks) that improve safety, maintainability, and traceability without cluttering code.

## When to Apply
- Safety-relevant code paths, interfaces, state machines, and algorithms.
- Boundary validations, error handling, and concurrency/interrupt sections.
- Any location requiring traceability to requirements/risks/tests.

## Requirements (testable)
1. Comment Value: Inline docs must add intent, rationale, constraints, or traceability—not restate code. Rationale: clarity without noise.
2. Traceability Tags: Use stable IDs (REQ-###, RISK-CTRL-###, TEST-###) adjacent to safety/requirement code. Rationale: audit and impact analysis.
3. Boundary Notes: Document assumptions (units, ranges, timing, concurrency/ISR safety) at boundaries. Rationale: correct usage and safety.
4. API Docblocks: Public APIs include purpose, params, ranges, return codes, side effects; keep brief and consistent. Rationale: safe integration.
5. Staleness Control: Remove/update comments when behavior changes; no inline history logs. Rationale: avoid misinformation.

## Recommended Practices
- Prefer short comments over long narratives; move detailed rationale to design docs, link by ID.
- Note non-obvious tradeoffs (performance vs safety) and mitigations.
- For concurrency/ISR-sensitive sections, document which locks/ordering guarantees apply.
- Keep language precise and ASCII; avoid ambiguous abbreviations.

## Patterns
Traceability + constraint:
```c
// REQ-PWR-BATT-01: shutdown <VBAT_CRIT; RISK-CTRL-55; TEST-PWR-04
if (vbat < VBAT_CRIT) { enter_safe_shutdown(); }
```

API docblock:
```c
/**
 * @brief Encrypt payload with device key (Class C path).
 * @param out must have room for len+TAG_LEN; len <= MAX_PAYLOAD.
 * @return 0 on success, -EIO on crypto failure.
 * REQ-ENC-AEAD-01, TEST-ENC-04
 */
int secure_encrypt(uint8_t *out, size_t len, const uint8_t *in);
```

Concurrency note:
```c
// Holds tx_mutex <= 2 ms; ISR-safe: no lock taken in ISR
```

## Anti-Patterns (risks)
- Comments that mirror code or go stale → risk: misleads reviewers.
- Missing range/unit notes on APIs → risk: misuse and safety defects.
- No traceability tags on safety logic → risk: audit gaps.
- Inline change logs → risk: divergence from VCS truth.

## Verification Checklist
- [ ] Comments add intent/constraints/traceability, not restate code.
- [ ] Traceability tags present on safety/requirement code.
- [ ] API docblocks include ranges, errors, side effects.
- [ ] Boundary assumptions (units/timing/concurrency) documented.
- [ ] Stale or inline history comments removed/updated.

## Traceability
- Use IDs from requirements/hazards/tests in inline comments; ensure they match external artifacts. Link to design docs by ID when more detail is needed.

## References
- IEC 62304 traceability expectations.
- ISO 14971 for risk-control linkage.
- DOC-CODE-COMMENTS and DOC-TRACEABILITY skills for complementary guidance.

## Changelog
- 1.0.0 (2026-01-04): Initial inline documentation skill with traceability, API docblocks, and boundary note guidance.

## Audit History
- **2026-01-04**: Audit performed. Verified:
  - IEC 62304 traceability expectations correctly referenced
  - ISO 14971 risk-control linkage accurate

