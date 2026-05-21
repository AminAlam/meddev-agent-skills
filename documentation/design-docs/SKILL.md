---
skill_id: DOC-DESIGN-DOCS
version: 1.1.0
last_updated: 2026-05-21
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
1. Architecture from Requirements [Class B, C]: Document structure and software items that implement software requirements; verify architecture implements requirements including risk controls. Rationale: 5.3.1, 5.3.6 a.
2. Interface Architecture [Class B, C]: Document interfaces between items and between items and external hardware/software. Rationale: 5.3.2, 5.3.6 b.
3. SOUP Specifications [Class B, C]: For each SOUP item, document functional/performance needs for intended use and required system hardware/software to run it. Rationale: 5.3.3–5.3.4, 5.3.6 c.
4. Risk-Control Segregation [Class C]: Identify segregation between items required for risk control and how effectiveness is ensured. Rationale: 5.3.5.
5. Unit Decomposition [Class B, C]: Subdivide software to software units per architecture. Rationale: 5.4.1.
6. Detailed Design [Class C]: Document unit and interface design sufficient for correct implementation; verify against architecture without contradiction. Rationale: 5.4.2–5.4.4.
7. Traceability: Link design elements to requirements, hazards, and tests. Rationale: 5.3.6, 7.3.3.
8. Updates: Keep design docs current with code under change/configuration control. Rationale: prevent drift.

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
- [ ] Class B/C: architecture implements requirements and supports interfaces (5.3.6).
- [ ] Class B/C: SOUP functional and platform needs documented.
- [ ] Class C: segregation for risk control documented (5.3.5).
- [ ] Class C: detailed unit/interface design and verification against architecture (5.4).
- [ ] Design elements linked to requirements/hazards/tests.
- [ ] Docs updated with changes; under `DOC-SCM` / change control.

## Traceability
- Use IDs for design elements (`DES-###`) linked to `REQ-###`, `HZ-###`, `TEST-###`.
- Keep diagrams and text under version control; include in baselines/releases.

## References
- IEC 62304:2006+A1:2015, 5.3–5.4 (architectural and detailed design).
- ISO 14971:2019 (hazard linkage).
- `DOC-SW-REQ`, `ARCH-SAFETY-CLASS`, `REG-IEC62304-SWRM`.
- FDA/MDR tech file expectations (architecture, SOUP).

## Changelog
- 1.1.0 (2026-05-21): Split 5.3 architecture vs 5.4 detailed design; SOUP and Class C segregation aligned to IEC 62304.
- 1.0.0 (2026-01-04): Initial design documentation skill with architecture views, SOUP, and traceability.

## Audit History
- **2026-01-04**: Audit performed. Verified:
  - IEC 62304 architecture/design documentation requirements accurate
  - ISO 14971 hazard linkage requirements correct
  - FDA/MDR tech file expectations appropriately noted
