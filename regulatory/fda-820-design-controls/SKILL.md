---
skill_id: REG-FDA820
version: 1.0.0
last_updated: 2026-03-20
applies_to: [Class A, Class B, Class C]
jurisdiction: [FDA]
prerequisites: [REG-IEC62304, REG-ISO14971]
---

# FDA Design Controls and Software Validation (21 CFR 820.30)

## Purpose
Map **21 CFR Part 820 Subpart C — Design Controls** to software lifecycle work: design planning, inputs, outputs, review, verification, validation, transfer, and DHF/DMR links, including how **software validation** (intended use / risk controls) complements **verification** (requirements and specs). Includes a concise **ISO 13485:2016** slice where it overlaps QMS expectations for design and risk (interpretation; align with your notified-body MDSAP scope for EU).

## When to Apply
- Defining or updating design procedures, DHF artifacts, or release records for US market devices.
- Interpreting “validation” vs “verification” for software in FDA QMS language.
- Connecting IEC 62304 deliverables to **820.30** design control records.
- Preparing for ISO 13485 audits that reference design control (Clause 7.3).

## Requirements (testable)
1. Design Plan: Establish and maintain a **design and development plan** per **820.30(b)**; scope, responsibilities, interfaces, and review gates; update when software scope or class changes. Rationale: controlled design process.
2. Design Inputs: Capture **physical and performance requirements** from intended use and safety/risk; trace to **820.30(c)** records. Software inputs include functional, safety, security, usability, and regulatory constraints. Rationale: correct inputs drive correct outputs.
3. Design Outputs: Document **820.30(d)** outputs (specs, code baselines, build artifacts) that meet design inputs; include acceptance criteria for verification. Rationale: objective evidence of “what was built.”
4. Design Review: Hold **820.30(e)** reviews at planned stages; record participants, decisions, and action items for software architecture and major changes. Rationale: defect prevention.
5. Design Verification: Demonstrate **820.30(f)** that design outputs meet design inputs (tests, analysis, inspection). Map to unit/integration/system tests and static analysis. Rationale: “did we build it right?”
6. Design Validation: Demonstrate **820.30(g)** that **approved device meets user needs and intended use** under simulated or actual use as appropriate; include risk-related use scenarios. For software, often **clinical/ summative usability** and end-to-end clinical workflows where applicable. Rationale: “did we build the right thing?”
7. Design Transfer: Ensure **820.30(h)** transfer to manufacturing / deployment (including cloud release procedures) with verified procedures and training. Rationale: reproducible release.
8. Design History File (DHF): Maintain **820.30(j)** compilation of records for each design or type; link to SDD, tests, reviews, risk file, and change records. Rationale: audit trail.
9. Device Master Record (DMR): Where applicable, ensure **820.181** DMR entries for released software (labels, IFU, build IDs) are consistent with validated design. Rationale: correct field configuration.
10. ISO 13485 alignment (slice): Where QMS is ISO 13485-certified, map **7.3 Design and development** and **4.1.6** (software used in QMS) to your procedures; document software validation for **GMP/QMS** tools per FDA **Computer Software Assurance** guidance when those tools affect production/quality records. Rationale: single coherent QMS story.

## Recommended Practices
- Maintain a one-page **820.30 ↔ IEC 62304** mapping table (SDP ↔ design plan, SOUP ↔ design input/output, etc.).
- Separate **verification matrix** (REQ→test) from **validation summary** (intended use / risk / use scenarios).
- Baseline software **build IDs** in DHF per release.

## Patterns
DHF index entry (YAML):
```yaml
dhf:
  device: "Pump-Controller-SW"
  design_plan_ref: "DOC-DSP-001 rev C"
  inputs_ref: ["REQ-SYS-001", "RMF-2026"]
  outputs_ref: ["SAD-001", "SDD-002", "tag: v2.3.1"]
  verification:
    summary: "reports/VV-REPORT-2.3.1.pdf"
    matrix: "trace/req-test-matrix.csv"
  validation:
    summary: "reports/VAL-SUMMARY-2.3.1.pdf"
    note: "Intended use + clinical workflow scenarios; links to IEC 62366 summative tests if UI"
  reviews:
    - id: "DR-2026-01"
      date: "2026-01-04"
      attendees: ["SE", "QA", "RA"]
```

Commit message tying to design controls:
```
feat: door interlock stop within 50 ms

820.30: design output + verification for REQ-62304-102
DHF: VV-REPORT updated; see TEST-201, TEST-202
```

## Anti-Patterns (risks)
- Calling integration tests “validation” only — risk: missing **intended use** evidence under 820.30(g).
- DHF references only code without **inputs/outputs** linkage — risk: 483 observations on incomplete design controls.
- Skipping **design transfer** for cloud/SaaS deployments — risk: production/tenant config drift.

## Verification Checklist
- [ ] Design plan current; reviews documented for major software milestones.
- [ ] Design inputs traceable to risks and intended use; approved.
- [ ] Design outputs (specs, builds) linked to inputs; acceptance criteria defined.
- [ ] Verification evidence (tests, analysis) covers design outputs vs inputs.
- [ ] Validation summary addresses user needs / intended use (not only unit tests).
- [ ] Design transfer records exist for manufacturing/deployment.
- [ ] DHF contains or references required records for the software release.
- [ ] DMR/labeling consistent with released software version.

## Traceability
- Tag DHF artifacts with release `vX.Y.Z`; link `REQ-*` to `TEST-*` and validation `VAL-*` or `SUM-UE-*` (usability).
- Map `RISK-CTRL-*` to both verification (technical) and validation (use-related) where applicable.

## References
- 21 CFR Part 820, Subpart C — Design controls (§820.30).
- 21 CFR Part 820, Subpart M — Records (§820.181 DMR).
- FDA Guidance: “General Principles of Software Validation” (2002) — validation philosophy (interpretation; not superseded for QMS concepts).
- FDA Guidance: “Computer Software Assurance for Production and Quality System Software” (2022).
- ISO 13485:2016, clauses 4.1.6 (software in QMS), 7.3 (design and development), 7.4 (purchasing) as applicable.
- IEC 62304:2006+A1:2015 — software lifecycle (often implemented under design controls).

## Changelog
- 1.0.0 (2026-03-20): Initial skill covering 820.30, DHF, verification vs validation, ISO 13485 slice.
