---
skill_id: ARCH-SAFETY-CLASS
version: 1.1.0
last_updated: 2026-05-21
applies_to: [Class A, Class B, Class C]
jurisdiction: [FDA, EU MDR, Global]
prerequisites: [REG-IEC62304, REG-ISO14971]
---

# Software Safety Classification and Architectural Impact

## Purpose
Define how IEC 62304:2006+A1:2015 safety classification (Class A/B/C per 4.3) influences architecture, segregation, documentation, and testing—ensuring activity rigor scales with harm severity and software items are decomposed with defensible class assignments.

## When to Apply
- Early architecture and system hazard analysis.
- Decomposing a software system into items or units.
- Changes that alter hazard exposure, control placement, interfaces, or SOUP on safety paths.
- Problem investigations that suggest misclassification (see `DOC-PROBLEM-RES`).

## Requirements (testable)
1. Classification Flow [Class A, B, C]: Assign class from whether software can contribute to a hazardous situation and resulting harm severity after considering risk controls **outside** the software item only (hardware, independent software, procedures, etc.). Rationale: 4.3 a (interpretation).
2. Failure Assumption [Class A, B, C]: Treat software failure as possible when analysing contribution to hazardous situations; do not rely on probability of software failure to reduce class at assignment time. Rationale: 4.3 note (interpretation).
3. Class A [Class A]: Class A when software cannot contribute to a hazardous situation, or contribution does not yield unacceptable risk after external controls. Rationale: 4.3 a.
4. Class B [Class B]: Class B when contribution can yield unacceptable risk with serious injury not expected (non–serious injury harm). Rationale: 4.3 a.
5. Class C [Class C]: Class C when contribution can yield death or serious injury. Rationale: 4.3 a.
6. Re-classification [Class A, B, C]: Additional external controls may be added and class reassigned with documented rationale. Rationale: 4.3 a (second paragraph).
7. Risk File Record [Class A, B, C]: Document assigned class for each software system in the risk management file. Rationale: 4.3 c.
8. Decomposition [Class A, B, C]: Decomposed items inherit parent class unless documented rationale and segregation justify a different class. Rationale: 4.3 d–e.
9. Group Rule [Class A, B, C]: When applying processes to a group of items, use requirements of the highest class in the group unless lower class is justified in the risk file. Rationale: 4.3 f.
10. Default Class C [Class A, B, C]: Until class is assigned, apply Class C requirements. Rationale: 4.3 g.
11. Segregation [Class B, C]: Separate higher-class items from lower-class via process/memory/interface boundaries; Class C document segregation needed for risk control (5.3.5). Rationale: 4.3 d, 5.3.5.
12. Interface Contracts [Class B, C]: Validate interfaces between classes (bounds, timeouts, errors, integrity checks). Rationale: architectural risk control.
13. Evidence by Class [Class A, B, C]: Tailor architecture detail, design depth, and verification per Annex A class mapping (informative Table A.1); Class B/C architecture and integration; Class C detailed design and enhanced unit criteria. Rationale: 5.3–5.5.
14. Software Risk Controls [Class B, C]: Items implementing risk controls are classified based on the risk the control mitigates; develop per Clause 5. Rationale: 7.2.2. Skill: `REG-IEC62304-SWRM`.
15. Change Impact [Class A, B, C]: Reassess classification and segregation when functionality, interfaces, or hazards change. Rationale: 4.3, 6.2.2 (interpretation).

## Recommended Practices
- Maintain a per-item class table with justification, segregation method, and hazard links.
- Use MPU/MMU regions or process isolation for Class C vs non-safety code.
- Apply defensive serialization and checksum on inter-partition messages.
- Keep class-aware test depth (informative: MC/DC for Class C control logic where justified).
- Draw a decision diagram in the risk file (interpretation of 4.3 flow) without copying standard figures.

## Patterns
Class table (YAML):
```yaml
software_system: pump_firmware
system_class: Class C
rationale: HZ-07 serious injury if over-infusion; external clamp not sole mitigation
items:
  - name: pump_control
    class: Class C
    inherits: pump_firmware
    segregation: dedicated MPU region; no shared stack with ui_task
  - name: ui_task
    class: Class B
    rationale: segregated; failure cannot corrupt pump_control memory (DES-SEG-02)
```

Interface validation snippet:
```c
// CLASS C boundary; REQ-IF-01; TEST-IC-12
int handle_cmd(const cmd_t *cmd, size_t len) {
    if (len != sizeof(cmd_t)) return -1;
    if (!crc_ok(cmd, len)) return -2;
    return dispatch(cmd);
}
```

## Anti-Patterns (risks)
- Whole product labeled Class A without hazardous-situation analysis -> risk: under-verification.
- Using software reliability estimates to lower class at assignment -> risk: contradicts 4.3 failure assumption.
- Shared memory between Class C and utility code without protection -> risk: corruption.
- Decomposition to lower class without segregation evidence -> risk: audit challenge on 4.3 d.
- Risk-control software left at Class A -> risk: weak verification of mitigations (7.2.2).

## Verification Checklist
- [ ] System class documented in risk file with hazard linkage.
- [ ] Classification assumptions documented (external controls, failure treatment).
- [ ] Item-level classes documented; decomposition rationale where class differs.
- [ ] Group/process tailoring uses highest class unless risk-file exception.
- [ ] Until complete analysis, Class C controls applied.
- [ ] Segregation mechanisms implemented and reviewed for B/C (C: risk-control segregation).
- [ ] Interfaces across classes validated.
- [ ] Verification depth matches class; software risk controls classified per mitigated risk.
- [ ] Re-assessment performed after significant changes or problems.

## Traceability
- Link item class entries to hazards (`HZ-###`), controls (`RISK-CTRL-###`), and tests (`TEST-###`).
- Maintain class table under configuration control (`DOC-SCM`); reference in `DOC-DESIGN-DOCS`.

## References
- IEC 62304:2006+A1:2015, 4.3 (software safety classification).
- IEC 62304:2006+A1:2015, Annex A Table A.1 (informative class summary—clause IDs only).
- ISO 14971:2019 (`REG-ISO14971`).
- IEC TR 80002-1:2019 (informative).
- `REG-IEC62304-SWRM` (7.2.2 risk controls in software).

## Changelog
- 1.1.0 (2026-05-21): Aligned with 4.3 assignment rules, decomposition, default Class C, 7.2.2 control classification.
- 1.0.1 (2026-01-04): Audit correction - updated IEC TR 80002-1 to 2019 edition.
- 1.0.0 (2026-01-04): Initial skill covering class derivation, segregation, interfaces, and verification expectations.

## Audit History
- **2026-05-21**: IEC 62304 4.3 alignment pass.
- **2026-01-04**: Audit performed. IEC TR 80002-1:2009 updated to 2019 edition.
