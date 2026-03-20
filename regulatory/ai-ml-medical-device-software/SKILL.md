---
skill_id: REG-AIML-MDSW
version: 1.0.0
last_updated: 2026-03-20
applies_to: [Class A, Class B, Class C]
jurisdiction: [FDA, EU MDR]
prerequisites: [REG-ISO14971, REG-SAMD-CLIN]
---

# AI/ML-Based Medical Device Software (GMLP, Data, Change Control)

## Purpose
Address **machine learning inside the regulated product** (not LLM coding assistants): **Good Machine Learning Practice (GMLP)**, training/validation data integrity, **Predetermined Change Control Plans (PCCP)** where applicable, drift monitoring, and linking models to ISO 14971 and software lifecycle controls.

## When to Apply
- Trainable or locked models affecting diagnosis, triage, segmentation, prediction, or control.
- Changes to **training data**, **architecture**, **retraining cadence**, or **performance thresholds**.
- Preparing FDA AI/ML-enabled SaMD submissions or EU technical documentation with ML components.

## Requirements (testable)
1. GMLP Principles: Apply lifecycle practices across **data management, model development, evaluation, deployment, monitoring** per FDA GMLP-aligned expectations; document roles and controls. Rationale: trustworthy ML development.
2. Data Governance: Define **data provenance**, labeling quality, **representativeness**, bias controls, and train/val/test splits; version datasets with immutable references (hash, storage location). Rationale: reproducible evidence.
3. Model Documentation: Record **architecture**, hyperparameters, training environment, random seeds (where deterministic), and **evaluation metrics** with acceptance thresholds tied to risk controls. Rationale: verification baseline.
4. Verification & Validation: Map **software unit/integration tests** to non-ML components; use **locked test sets** and **clinical validation** (see `REG-SAMD-CLIN`) for performance claims; document **failure modes** (edge cases, adversarial inputs) where risks warrant. Rationale: layered evidence.
5. Explainability & Labeling: Provide **clinician-facing** description of outputs, limitations, and known failure modes in IFU/on-screen; align with risk communication. Rationale: safe decision support.
6. Predetermined Change Control (when used): If pursuing **PCCP** (FDA), pre-specify **modifications** (e.g., retraining bounds, data refresh rules), **verification** activities, and **reporting**; maintain traceability to releases. Rationale: controlled post-market learning within bounds.
7. Monitoring & Drift: Define **real-world performance monitoring**, **trigger thresholds** for investigation, and **risk management** updates when drift detected. Rationale: sustained safety/performance.
8. SOUP / Tooling: Treat ML frameworks and pretrained weights as **SOUP** where applicable (IEC 62304); record versions, known defects, and supply-chain risks. Rationale: provenance.

## Recommended Practices
- Freeze **model cards** per release (`MODELCARD-vX.Y.Z.md`) with metrics and datasets.
- Separate **development** experiments from **locked** validation runs (different data locks).

## Patterns
Model release record (YAML):
```yaml
model:
  id: "cxr-pneumo-v1.4.0"
  weights_sha256: "b3e9…c2"
  train_data: "ds-cxr-2025Q4@sha256:…"
  val_auc: 0.91
  val_threshold: 0.42
  known_limits: ["pediatric not validated", "AP only"]
  risk_links: ["RISK-CTRL-ML-02", "HZ-ML-01"]
```

Drift monitor hook (pseudo):
```python
# REQ-ML-MON-01: log inference score distribution for drift review (RISK-CTRL-ML-07)
def log_batch_scores(scores: list[float], model_id: str, build: str) -> None:
    telemetry.emit_histogram("model_scores", scores, tags={"model": model_id, "build": build})
```

## Anti-Patterns (risks)
- **Retraining in production** without change control — risk: unvalidated performance shift.
- Using **test set** for hyperparameter tuning — risk: optimistic bias; audit failure.
- Omitting **subpopulation** analysis when health equity risks exist — risk: harm in underserved groups.

## Verification Checklist
- [ ] Dataset versions hashed and referenced in DHF/technical file.
- [ ] Metrics and thresholds meet predefined acceptance; linked to risks.
- [ ] Model SOUP and training stack versions recorded.
- [ ] IFU limitations match validated use cases.
- [ ] PCCP or change control path defined for model updates.
- [ ] Monitoring thresholds and escalation paths documented.

## Traceability
- IDs: `DATASET-*`, `MODEL-*`, `ML-TEST-*`, `RISK-CTRL-ML-*`; link commits/releases to model artifacts.

## References
- FDA “Artificial Intelligence/Machine Learning (AI/ML)-Based Software as a Medical Device (SaMD) Action Plan” and related guidance (check current editions).
- FDA discussion paper / guidance on **Predetermined Change Control Plan** (verify latest titles).
- IMDRF “Machine Learning-enabled medical devices” work items (verify current).
- ISO/IEC 24028 (AI trustworthiness concepts) — supporting context, not a medical device standard alone.

## Changelog
- 1.0.0 (2026-03-20): Initial skill for GMLP, data governance, PCCP, drift monitoring, SOUP linkage.
