---
skill_id: REG-IEC62304
version: 1.0.0
last_updated: 2026-01-04
applies_to: [Class A, Class B, Class C]
jurisdiction: [FDA, EU MDR, Canada, UK]
prerequisites: [REG-ISO14971]
---

# IEC 62304 Medical Device Software Lifecycle

## Purpose
Provide actionable guidance to implement IEC 62304 lifecycle controls across planning, development, verification, release, and maintenance, with class-dependent rigor for Class A/B/C software items.

## When to Apply
- Code or design changes in regulated medical device software.
- Creation/maintenance of lifecycle deliverables (plans, requirements, architecture, tests).
- Introduction of SOUP components or third-party libraries.
- Release preparation or field corrective actions.
- Any change that affects traceability across requirements/design/code/tests.

## Requirements (testable)
1. Lifecycle Plan: Maintain a Software Development Plan (SDP) covering activities, roles, class, and tailoring per IEC 62304:2006+A1:2015 5.1; updated when scope or class changes. Rationale: defines required activities by class.
2. Safety Classification: Assign class (A/B/C) per system hazard analysis (link to ISO 14971); document rationale and impacted software items. Rationale: drives required controls.
3. Requirements Traceability: Bidirectional traceability from system/software requirements -> design -> code -> tests (unit/integration/system) per 5.2/5.3/5.5. Rationale: completeness and impact analysis.
4. Architecture & Design: Maintain software architecture (software items, interfaces, segregation) and detailed design for Class B/C items per 5.3; update when code structure changes. Rationale: enables targeted verification and segregation.
5. Unit Implementation & Verification: For each software unit, implement per design and verify with unit tests; Class B/C require documented procedures and results per 5.5. Rationale: detect defects early.
6. Integration Testing: Plan and execute integration tests for interfaces; Class B/C: documented procedures/results, defect tracking per 5.6. Rationale: verify component interactions.
7. System Testing: Execute system-level tests against software requirements; Class B/C require documented procedures and results per 5.7. Rationale: verify end-to-end behavior.
8. SOUP Control: Identify all SOUP, record version, provenance, known anomalies, and verification/mitigation per Section 8 (with initial identification per 5.3.3/5.3.4); assess impact on safety and cybersecurity. Rationale: control unknown provenance risk.
9. Configuration Management: Control items (requirements, design, code, tests, tools, SOUP) with unique identifiers, baselines, and change history per 5.8. Rationale: reproducibility and auditability.
10. Problem Resolution: Track problems/defects with status, root cause, class impact, and corrective actions per Section 9. Rationale: closed-loop defect handling.
11. Maintenance: Establish software maintenance process for modifications, including impact analysis, regression testing, and configuration updates per Section 6. Rationale: continued safety after deployment.
12. Release Controls: Define release criteria (tests passed, defects triaged, SBOM recorded); Class B/C require documented approval per 5.8. Rationale: safe distribution.

## Recommended Practices
- Keep a class-specific activity checklist in the repo; gate merges on completion.
- Use requirement IDs (e.g., `REQ-62304-###`) and hazard IDs (`HZ-###`) in code comments and tests.
- Maintain SBOM entries for SOUP with CVE monitoring.
- Automate traceability matrix generation (e.g., from annotations + test metadata).

## Patterns
Requirement/code/test traceability:
```c
// REQ-62304-102: Pump shall stop within 50 ms on door open (Class C)
// HZ-12, RISK-CTRL-33
bool pump_stop_on_door_open(void) {
    if (is_door_open()) {
        stop_motor(); // TEST-201 covers timing @ 50 ms
        return true;
    }
    return false;
}
```

SOUP documentation snippet (YAML):
```yaml
soup:
  - name: tiny-rtos
    version: 1.4.2
    function: scheduler, mutex, queues
    known_anomalies:
      - id: TR-77
        desc: priority inheritance bug on nested mutex
        mitigation: disabled nesting; wrapper enforces single-level
        verification: test/rtos_mutex_single_level.c
    provenance: https://example.com/releases/tiny-rtos-1.4.2.tar.gz
    classification_impact: Class C items use it for comms tasks
```

Integration test with requirement tag:
```c
// TEST-201 verifies REQ-62304-102 timing
TEST(PumpSafety, StopsWithin50msOnDoorOpen) {
    simulate_door_open();
    uint32_t t0 = timer_now_ms();
    pump_stop_on_door_open();
    ASSERT_LT(timer_now_ms() - t0, 50);
}
```

## Anti-Patterns (risks)
- Missing class rationale -> risk: incorrect activity tailoring; audit finding.
- Untracked SOUP versions -> risk: unmitigated vulnerabilities/bugs.
- Requirements in code comments only (no managed source) -> risk: loss of traceability.
- Untested interface changes -> risk: integration defects in Class B/C items.
- No linkage between defects and requirements/tests -> risk: incomplete verification and weak CAPA.

## Verification Checklist
- [ ] Safety class documented, reviewed, and linked to hazard analysis.
- [ ] SDP current; activities tailored for class and approved.
- [ ] Requirements traced to design, code, and tests; matrix generated.
- [ ] Architecture updated for new items/interfaces; segregation rationale recorded.
- [ ] Unit tests implemented for changed units; pass under `-Wall -Wextra -Werror`.
- [ ] Integration tests updated for interface changes; executed per 5.6.
- [ ] System tests updated for requirements/behavior changes; executed per 5.7.
- [ ] SOUP inventory updated (version, anomalies, mitigations, verification) per Section 8.
- [ ] Configuration items baselined; change records updated per 5.8.
- [ ] Defects logged with root cause and resolution; retest evidence present per Section 9.
- [ ] Maintenance process applied if modifying released software per Section 6.
- [ ] Release criteria met; approvals recorded; SBOM captured.

## Traceability
- Use stable IDs: requirements (`REQ-62304-###`), hazards (`HZ-###`), risks (`RISK-###`), controls (`RISK-CTRL-###`), tests (`TEST-###`), design elements (`DES-###`).
- Embed IDs in code comments and test names; store source-of-truth in requirements tool or `requirements.yaml`.
- Generate matrices (REQ↔DES↔CODE↔TEST) automatically where possible; store as artifacts per release.

## References
- IEC 62304:2006+A1:2015, clauses 4–9 (especially 5.1–5.8 for development, 6 for maintenance, 7 for risk management, 8 for SOUP, 9 for problem resolution).
- IEC TR 80002-1:2019 (application of risk management to software; second edition).
- FDA Guidance: "Content of Premarket Submissions for Device Software Functions" (2023) for documentation expectations.
- FDA Guidance: "Cybersecurity in Medical Devices: Quality System Considerations and Content of Premarket Submissions" (2023) for cybersecurity documentation.
- ISO 14971:2019 for hazard/risk linkage (see prerequisite skill).

**Note**: IEC 62304:2024 (Edition 2) may supersede IEC 62304:2006+A1:2015 when published; verify current applicable edition.

## Changelog
- 1.0.1 (2026-01-04): Audit corrections - fixed section references (5.9→Section 9 for problem resolution, added 5.7 for system testing, Section 6 for maintenance, Section 8 for SOUP), updated IEC TR 80002-1 to 2019 edition, corrected FDA guidance title to 2023 edition.
- 1.0.0 (2026-01-04): Initial comprehensive skill covering lifecycle planning, class tailoring, SOUP, traceability, and verification checklists.

## Audit History
- **2026-01-04**: Regulatory audit performed. Corrections applied:
  - Section 5.9 referenced for Problem Resolution was incorrect (no such section); corrected to Section 9
  - System testing (5.7) was missing; added as separate requirement
  - Maintenance process (Section 6) was missing; added
  - SOUP management reference expanded to include Section 8
  - IEC TR 80002-1:2009 updated to 2019 edition
  - FDA guidance title corrected from outdated 2005 guidance to current 2023 guidance
  - Added note about IEC 62304:2024 (Edition 2) pending publication
