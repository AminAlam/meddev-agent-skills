---
skill_id: REG-SAMD-CLIN
version: 1.0.0
last_updated: 2026-03-20
applies_to: [Class A, Class B, Class C]
jurisdiction: [FDA, EU MDR, IMDRF]
prerequisites: [REG-ISO14971]
---

# SaMD, Intended Use, and Clinical Evaluation

## Purpose
Guide **Software as a Medical Device (SaMD)** and **software in devices** for **clinical evaluation** expectations: intended use, SaMD category (IMDRF framework), evidence of **analytical and clinical validity** where applicable, and alignment with **EU MDR Annex XIV** clinical evaluation and **FDA** premarket clinical/benefit-risk expectations for software-driven diagnostics and monitoring.

## When to Apply
- Standalone SaMD (no hardware) or software that drives clinical decisions.
- Changes to **intended medical purpose**, indications, or output claims.
- Preparing CER (EU) or clinical sections of **510(k)/De Novo/PMA** (US).
- Mapping SaMD **normalization of risk** (IMDRF) to ISO 14971.

## Requirements (testable)
1. Intended Use: Document **who, what, when, where, why** for the software function; freeze claims that drive classification and evidence. Rationale: drives regulatory pathway and clinical scope.
2. SaMD Category (IMDRF): Assign category per **SaMD: Possible Framework for Risk Categorization and Considerations** (N41) using **state of healthcare situation/condition** and **significance of information** provided; document rationale. Rationale: proportionate evidence.
3. Analytical Validation: For software processing inputs (signals, images, labs), define **analytical performance** (accuracy, precision, robustness) vs. **predetermined** acceptance criteria. Rationale: valid input-to-output mapping.
4. Clinical Validation: Define **clinical association** and, where applicable, **clinical validation** per state-of-the-art (e.g., concordance with reference, outcomes); tie to risk controls and labeling. Rationale: supports safety and performance claims.
5. EU Clinical Evaluation: Maintain **clinical evaluation** per **MDR Annex XIV** and relevant **MDCG** guidance; update with PMS data; link software changes to CER revision triggers. Rationale: MDR conformity.
6. US Premarket Clinical Evidence: Align with FDA expectations for the device type (e.g., **510(k) clinical data** when needed, **De Novo** clinical/benefit-risk, **PMA** clinical trials); cross-reference software V&V with clinical study protocols when software is the intervention. Rationale: submission completeness.
7. PMCF / Post-Market: Define **PMCF** needs for SaMD when residual risks or uncertainties exist (EU); plan real-world performance monitoring where claims require ongoing evidence. Rationale: lifecycle closure.

## Recommended Practices
- Maintain a **claim matrix**: each marketing claim → evidence source (bench, clinical study, literature).
- Version **modeling assumptions** (population, prevalence) with software releases when outputs are prevalence-sensitive.

## Patterns
Claim-to-evidence row (CSV excerpt):
```
CLAIM-ID,STATEMENT,EVIDENCE-REF,STATUS
CL-01,"Detects atrial fibrillation in adults 18+",VAL-AFIB-2025-03,approved
CL-02,"Suitable for emergency triage without clinician",,blocked_pending_CER
```

Intended use snippet (markdown):
```markdown
## Intended use
- Population: adults 22–80 with diagnosed hypertension under clinician care
- Function: trend BP and flag sustained elevations per rule-set RS-1.2
- Environment: home and outpatient; not for acute emergency diagnosis
- Output: notifications to patient and summary to clinician portal
```

## Anti-Patterns (risks)
- **Indication creep** in marketing without CER/DHF update — risk: misbranding / NB major NC.
- Conflating **verification** (software tests) with **clinical validation** — risk: insufficient clinical evidence for claims.
- Ignoring **regulatory class change** when SaMD function changes (e.g., Rule 11) — risk: wrong conformity route.

## Verification Checklist
- [ ] Intended use and indications match approved/declared scope.
- [ ] IMDRF SaMD category (or equivalent rationale) documented.
- [ ] Analytical/clinical validation plans and reports current for claimed performance.
- [ ] EU CER / US clinical sections cross-reference software version and risk file.
- [ ] PMCF/PMS triggers defined for residual clinical uncertainties.

## Traceability
- IDs: `CL-CLAIM-###`, `CER-###`, `VAL-CLIN-###`; link to `REQ-*`, `RISK-*`, release tags.

## References
- IMDRF/SaMD WG documents (e.g., SaMD categorization framework; key definitions).
- EU MDR 2017/745 Annex XIV (clinical evaluation); MDCG clinical evaluation guidance (verify current revision).
- FDA Guidance: “Content of Premarket Submissions for Device Software Functions” (2023).
- FDA Guidance: “Clinical Decision Support Software” (2022) — scope and enforcement policy (verify applicability).

## Changelog
- 1.0.0 (2026-03-20): Initial skill for SaMD intended use, IMDRF category, clinical evaluation linkage.
