---
skill_id: REG-IEC62366
version: 1.0.0
last_updated: 2026-03-20
applies_to: [Class A, Class B, Class C]
jurisdiction: [FDA, EU MDR, Canada, UK]
prerequisites: [REG-ISO14971]
---

# IEC 62366 Usability Engineering for Medical Device Software

## Purpose
Implement **IEC 62366-1** usability engineering for software: identify **use-related risks**, iterate UI with **formative** evaluation, confirm risk controls with **summative** testing, and trace results to ISO 14971 and design/verification records.

## When to Apply
- Any user-facing software where **use error** could contribute to harm (embedded UI, mobile apps, SaMD web).
- New workflows, alarms, dosing, navigation, or language/label changes.
- EU MDR GSPR usability expectations; FDA human factors / human factors submission packages.

## Requirements (testable)
1. Use Specification: Define **intended users**, **use environments**, and **critical tasks** per IEC 62366-1; link to **hazard-related use scenarios**. Rationale: scope of evaluation.
2. User Interface Specification: Document UI elements that implement risk controls (labels, alarms, confirmations, defaults) per your design process; version with software. Rationale: controlled design outputs.
3. Formative Evaluation: For **non-final** UIs, run structured sessions; log defects/risks; iterate design before summative. Rationale: reduce residual use-error risk early.
4. Summative Evaluation: Execute **final** usability validation on representative users/tasks; pass/fail criteria tied to risk controls; record raw data and summaries. Rationale: objective evidence of safe use.
5. Risk Linkage: Map **use-related hazards** to ISO 14971 (`HZ-*`, `RISK-CTRL-*`); verify each control with summative or justified analysis. Rationale: closed-loop risk file.
6. Software Verification: Where UI implements a software requirement, link `REQ-*` to automated tests where possible and to usability study IDs for human-in-the-loop behavior. Rationale: dual path: technical + behavioral.
7. Labeling: Ensure on-screen strings and IFU excerpts match validated risk communication (warnings, contraindications). Rationale: consistency with labeling skill.

## Recommended Practices
- Maintain a **critical task list** with trace IDs (`UE-TASK-###`).
- Capture UI screenshots in summative reports with build IDs.
- Use simulated use environments (lighting, noise, gloves) when relevant.

## Patterns
Critical task trace (YAML):
```yaml
ue_task:
  id: UE-TASK-014
  description: "Confirm dose before start infusion"
  hazards: ["HZ-USE-03"]
  risk_controls: ["RISK-CTRL-UI-09"]
  ui_elements:
    - id: "screen_confirm_dose"
      build: "v2.3.1"
  summative: "UE-SUM-2026-02"
  result: pass
```

Automated UI test with traceability (Python pseudo):
```python
# REQ-UI-044: Confirm step shall block start until acknowledged (RISK-CTRL-UI-09)
def test_confirm_dose_requires_ack(screen):
    screen.enter_dose(10.0)
    assert not screen.can_start_infusion()
    screen.acknowledge_dose()
    assert screen.can_start_infusion()
```

## Anti-Patterns (risks)
- Skipping formative on “simple” UI — risk: late discovery of use errors.
- Summative with **developers** as stand-in users — risk: invalid evidence.
- Changing UI strings post-summative without impact analysis — risk: labeling drift and unvalidated risk communication.

## Verification Checklist
- [ ] Use specification and critical tasks documented and approved.
- [ ] Formative findings closed or mitigated before summative.
- [ ] Summative protocol executed; pass/fail per predefined criteria.
- [ ] Use-related risks updated in risk management file; residuals acceptable.
- [ ] UI build IDs and screenshots archived with release.
- [ ] REQ/RISK links updated for UI code and tests.

## Traceability
- IDs: `UE-TASK-###`, `UE-FORM-###`, `UE-SUM-###`; link to `HZ-*`, `REQ-*`, `TEST-*`, release `v*.*.*`.

## References
- IEC 62366-1:2015 (+ amendment), Medical devices — Application of usability engineering to medical devices.
- ISO 14971:2019 — risk management (use-related hazards).
- FDA Guidance: “Applying Human Factors and Usability Engineering to Medical Devices” (2016).
- EU MDR 2017/745 Annex I GSPRs (e.g., ergonomics, lay use where applicable).

## Changelog
- 1.0.0 (2026-03-20): Initial skill covering formative/summative, critical tasks, risk linkage.
