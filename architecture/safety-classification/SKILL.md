---
skill_id: ARCH-SAFETY-CLASS
version: 1.0.0
last_updated: 2026-01-04
applies_to: [Class A, Class B, Class C]
jurisdiction: [FDA, EU MDR, Global]
prerequisites: [REG-IEC62304, REG-ISO14971]
---

# Software Safety Classification and Architectural Impact

## Purpose
Define how safety classification (IEC 62304 Class A/B/C) influences architecture, segregation, documentation, and testing, ensuring controls scale with risk.

## When to Apply
- Early architecture/design decisions.
- Changes that alter hazard exposure, control placement, or interfaces.
- Integration of new SOUP/components affecting safety pathways.

## Requirements (testable)
1. Classification Derivation: Derive software item class from hazard analysis; document rationale and links to hazards/controls. Rationale: correct activity tailoring.
2. Segregation: Separate higher-class items from lower-class items via process/memory/interface boundaries; document mechanisms. Rationale: containment of failures.
3. Interface Contracts: Define strict, validated interfaces between classes; include timeouts, bounds, and error handling. Rationale: prevent propagation of faults.
4. Evidence by Class: Class B/C require formal architecture description, design detail, and stronger verification (unit+integration+system); Class A can be lighter but traceable. Rationale: proportional rigor.
5. Change Impact: Reassess classification and segregation when interfaces or functionality change. Rationale: keep controls current.
6. Tool/SOUP Usage: Evaluate tools/SOUP by class impact; add mitigations or evidence where used in Class B/C items. Rationale: control dependencies.

## Recommended Practices
- Maintain a per-item class table with justification and segregation method.
- Use MPU/MMU regions or process isolation for Class C vs non-safety code.
- Apply defensive serialization and checksum on inter-partition messages.
- Keep class-aware test coverage goals (e.g., MC/DC for Class C control logic).

## Patterns
Segregation note (YAML):
```yaml
item: pump_control_task
class: Class C
segregation: MPU region RO code, RW data; runs in high-priority partition
interfaces: msg queue from ui_task (Class B), validated length + CRC
tests: TEST-IC-12 (queue bounds), TEST-IC-13 (CRC failure path)
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
- Treating whole system as lowest class -> risk: under-verified safety functions.
- Shared memory between Class C and utility code without protection -> risk: corruption.
- Unbounded, unvalidated messaging across classes -> risk: fault propagation.
- No re-evaluation of class after feature changes -> risk: stale controls.

## Verification Checklist
- [ ] Class per item documented with hazard linkage and rationale.
- [ ] Segregation mechanisms implemented and reviewed (MPU/MMU/process/IPC).
- [ ] Interfaces across classes validated (size, CRC, timeout, error handling).
- [ ] Verification level aligns to class (coverage, test types).
- [ ] SOUP/tool impacts on Class B/C items assessed and mitigated.
- [ ] Change impact analysis performed on classification/segregation.

## Traceability
- Link item class entries to hazards (`HZ-###`), controls (`RISK-CTRL-###`), and tests.
- Maintain a class table under configuration control; reference in architecture docs.

## References
- IEC 62304:2006+A1:2015 (classification and activity tailoring per Annex A Tables A.1-A.7).
- ISO 14971:2019 (hazard/risk basis).
- IEC TR 80002-1:2019 (software risk considerations; second edition).

## Changelog
- 1.0.1 (2026-01-04): Audit correction - updated IEC TR 80002-1 to 2019 edition.
- 1.0.0 (2026-01-04): Initial skill covering class derivation, segregation, interfaces, and verification expectations.

## Audit History
- **2026-01-04**: Audit performed. IEC TR 80002-1:2009 updated to 2019 edition.
