---
skill_id: DOC-DESIGN-DOCS
version: 1.0.0
last_updated: 2026-01-04
applies_to: [Class A, Class B, Class C]
jurisdiction: [Global]
prerequisites: [REG-IEC62304, REG-ISO14971, DOC-INLINE]
---

# Design Documentation (SAD/SDD)

## Purpose
Guide creation and maintenance of Software Architecture (SAD) and Design Descriptions (SDD) that support safety, traceability, and compliance.

## When to Apply
- New systems/features; major refactors; architecture changes.
- Prior to safety classification decisions and verification planning.

## Requirements (testable)
1. Architecture Views: Document components, interfaces, data flows, and deployment; include safety segregation and trust boundaries. Rationale: clarity and verification.
2. Design Detail: For Class B/C items, provide module-level design (algorithms, state machines, timing constraints, error handling). Rationale: supports verification and hazard control.
3. Traceability: Link design elements to requirements, hazards, and tests; maintain IDs consistently. Rationale: compliance.
4. SOUP Documentation: Identify SOUP, versions, roles, known issues, and mitigations. Rationale: provenance and risk control.
5. Interfaces: Specify contracts (types, ranges, timing, errors); align with implementation. Rationale: interoperability and safety.
6. Updates: Keep design docs current with code; change control applied. Rationale: prevent drift.

## Recommended Practices
- Use lightweight but structured docs; diagrams with textual descriptions.
- Keep a living “architecture decisions” log for significant choices.
- Version diagrams; keep source (e.g., PlantUML) in repo.

## Patterns
Architecture snippet (YAML):
```yaml
component: pump_control
class: Class C
interfaces:
  - name: ui_cmd_queue
    type: message_queue
    validation: len, CRC, bounds
hazards: [HZ-07]
controls: [RISK-CTRL-19]
```

SOUP entry:
```yaml
name: tiny-rtos
version: 1.4.2
role: scheduler
known_issues:
  - id: TR-77
    mitigation: disable nested mutex
    verification: TEST-RTOS-12
```

## Anti-Patterns (risks)
- Outdated design docs after code changes -> risk: audit gaps, wrong verification scope.
- Missing interface specs -> risk: integration defects.
- Undocumented SOUP -> risk: unmanaged vulnerabilities.
- No mapping to requirements/hazards -> risk: traceability failure.

## Verification Checklist
- [ ] Architecture views include safety segregation and trust boundaries.
- [ ] Module designs documented for Class B/C, including state/timing/error handling.
- [ ] Design elements linked to requirements/hazards/tests.
- [ ] SOUP documented with mitigations and verification.
- [ ] Interface contracts specified (types/ranges/timing/errors).
- [ ] Docs updated with changes; under change control.

## Traceability
- Use IDs for design elements (`DES-###`) linked to `REQ-###`, `HZ-###`, `TEST-###`.
- Keep diagrams and text under version control; include in baselines/releases.

## References
- IEC 62304 (architecture/design documentation).
- ISO 14971 (hazard linkage).
- FDA/MDR tech file expectations (architecture, SOUP).

## Changelog
- 1.0.0 (2026-01-04): Initial design documentation skill with architecture views, SOUP, and traceability.

## Audit History
- **2026-01-04**: Audit performed. Verified:
  - IEC 62304 architecture/design documentation requirements accurate
  - ISO 14971 hazard linkage requirements correct
  - FDA/MDR tech file expectations appropriately noted
