---
skill_id: DOC-SW-REQ
version: 1.0.0
last_updated: 2026-05-21
applies_to: [Class A, Class B, Class C]
jurisdiction: [FDA, EU MDR, Global]
prerequisites: [REG-IEC62304, REG-ISO14971]
---

# Software Requirements Analysis

## Purpose
Guide creation, verification, and maintenance of software system requirements derived from system needs (IEC 62304:2006+A1:2015, 5.2)—with content appropriate to the device, risk controls embedded for Class B/C, and evidence that requirements are testable and traceable.

## When to Apply
- Defining or updating software requirements before design or implementation.
- Refactoring features that change inputs, outputs, alarms, security, or clinical behaviour.
- Adding SOUP, connectivity, or UI flows that need explicit software requirements.
- Preparing verification plans that must cover all software requirements (5.7).

## Requirements (testable)
1. Derive from System Needs [Class A, B, C]: Document software system requirements from system-level needs; for software-only devices, align system and software requirement sets explicitly. Rationale: 5.2.1.
2. Content Coverage [Class A, B, C]: Address applicable categories—functional capability, inputs/outputs, external interfaces, software-driven alarms/warnings/messages, security, user-interface behaviour, data structures, installation/site constraints, operation/maintenance, IT-network behaviour, user maintenance, and applicable regulatory needs. Rationale: 5.2.2 (interpretation: engineering checklist, not exhaustive copy).
3. Risk Controls in Requirements [Class B, C]: Include software-implemented risk control measures in requirements when identified by risk management. Rationale: 5.2.3.
4. Re-evaluate Device Risk [Class A, B, C]: When software requirements are established or materially changed, re-evaluate device risk analysis and update as needed. Rationale: 5.2.4.
5. Keep System Requirements Current [Class A, B, C]: Re-evaluate and update related system requirements when software requirements change. Rationale: 5.2.5.
6. Requirements Verification [Class A, B, C]: Verify and document that software requirements implement system needs (including risk controls), are non-contradictory, unambiguous, testable, uniquely identified, and traceable to system requirements or other approved sources. Rationale: 5.2.6.

## Recommended Practices
- Use stable IDs (`REQ-62304-###`) in a managed file (e.g. `requirements.yaml`), not only in code comments.
- Add explicit negative, boundary, and security abuse cases per requirement where safety-relevant.
- Tag requirements with safety class of the implementing item when known.
- Cross-reference usability needs (IEC 62366) and cybersecurity expectations in dedicated requirement subsections.

## Patterns
Requirement entry (YAML):
```yaml
requirements:
  - id: REQ-62304-102
    class: Class C
    summary: Stop infusion within 50 ms when door open sensor asserts
    sources: [SYS-REQ-44]
    risk_controls: [RISK-CTRL-19]
    categories: [functional, alarms, timing]
    verification: [TEST-201, TEST-410]
    negative_cases:
      - sensor bounce within 50 ms window
      - door open during self-test
```

Security and network excerpt:
```yaml
  - id: REQ-62304-210
    class: Class B
    summary: Reject BLE pairing without LE Secure Connections
    categories: [security, interfaces]
    verification: [TEST-BLE-03]
```

## Anti-Patterns (risks)
- Requirements only in tickets or chat, not under configuration control -> risk: traceability and audit gaps.
- Vague acceptance criteria ("fast enough", "secure") -> risk: 5.2.6 verification failure.
- Missing risk control requirements for Class B/C -> risk: controls implemented but not verified against needs.
- System requirements not updated when software scope grows -> risk: device-level inconsistency.

## Verification Checklist
- [ ] Software requirements derived from documented system needs.
- [ ] Applicable content categories addressed for the device type.
- [ ] Class B/C: software risk controls reflected in requirements.
- [ ] Device risk analysis re-evaluated after requirement changes.
- [ ] System requirements updated when software requirements change.
- [ ] Verification record shows testability, uniqueness, consistency, and traceability.

## Traceability
- Map `REQ-###` ↔ `SYS-REQ-###` ↔ `HZ-###` / `RISK-CTRL-###` ↔ `TEST-###` ↔ design (`DES-###`).
- See `DOC-TRACEABILITY` for matrix conventions.

## References
- IEC 62304:2006+A1:2015, 5.2 (software requirements analysis).
- ISO 14971:2019 (risk control inputs to requirements).
- `REG-IEC62304-SWRM` (Clause 7 controls in requirements).
- ISO/IEC 25010 (informative quality characteristics for requirement completeness).

## Changelog
- 1.0.0 (2026-05-21): Initial skill for IEC 62304 5.2 software requirements analysis.
