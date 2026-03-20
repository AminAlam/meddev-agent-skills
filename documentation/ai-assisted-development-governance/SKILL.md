---
skill_id: DOC-AI-GOV
version: 1.0.0
last_updated: 2026-03-20
applies_to: [Class A, Class B, Class C]
jurisdiction: [Global]
prerequisites: [REG-IEC62304, REG-ISO14971, DOC-TRACEABILITY]
---

# AI-Assisted Development Governance (LLM Coding Agents)

## Purpose
Define **governance** for **AI/LLM-assisted software development** (e.g., Cursor, Copilot, Claude): human review expectations, **evidence** that generated code is covered by requirements-based tests, **tool validation** for GxP-adjacent workflows, and alignment with **Computer Software Assurance (CSA)** principles (risk-based, critical thinking) without replacing your SOPs.

## When to Apply
- Teams using LLMs for code generation, refactor, or test synthesis in regulated projects.
- Establishing **AI usage policies** for design history / audit trail.
- Qualifying **IDE plugins** or **CI bots** that touch production or QMS repositories.

## Requirements (testable)
1. Policy: Document **where LLM assistance is allowed** (e.g., scaffolding vs safety-critical modules) and **required human review** gates per risk class. Rationale: controlled process.
2. Traceability: Every merged change must retain **author/reviewer identity**; LLM assistance **disclosed in commit or PR template** when policy requires. Rationale: audit trail.
3. Independent Review: For Class B/C changes, **second-person review** of generated patches focusing on **requirements coverage**, **failure modes**, and **misinterpreted specs**. Rationale: defect detection beyond automation.
4. Test Evidence: **No merge without tests** (or justified analysis) demonstrating **REQ→TEST** linkage for new behavior; forbid “LLM says it works” as evidence. Rationale: verification independence from generator.
5. Prompt & Context Hygiene: **No PHI/PII/proprietary trial data** in prompts; use **sanitized snippets**; pin **skill/context versions** (e.g., `SKILL.md` hashes) when claims depend on agent guidance. Rationale: confidentiality and reproducibility.
6. Tool Validation (GxP): For tools affecting **GMP/quality records**, apply **FDA CSA** approach: risk assessment, **intended use**, **testing records**, and **change control** when models or plugins update. Rationale: 21 CFR Part 11 / 820 alignment for QMS software.
7. Regression & Flakes: Treat LLM-generated tests like any other code — **deterministic CI**, seed control where needed, flake triage. Rationale: valid CI as design verification aid.
8. Record Retention: Store **PR descriptions**, **review comments**, and **test reports** as part of DHF/evidence; avoid relying on vendor chat logs as SOLE records. Rationale: durable evidence.

## Recommended Practices
- Use a **PR checklist**: `[ ] REQ IDs`, `[ ] tests added`, `[ ] reviewer not sole prompt author`, `[ ] no secrets in diff`.
- Snapshot **agent skill versions** in release notes when agent guidance materially influenced design.

## Patterns
PR template excerpt (markdown):
```markdown
## AI assistance
- [ ] No PHI/secrets in prompts or logs
- [ ] Assistant tools: Cursor 2.x + skills @ commit `abc1234`
- [ ] Reviewer verified REQ/TEST mapping for generated code
```

Commit message:
```
fix: debounce door sensor per REQ-62304-088

AI: scaffolded by LLM; reviewed by @jdoe; TEST-412 added
```

## Anti-Patterns (risks)
- **Blind merge** of generated safety-critical code — risk: latent defects and audit failure.
- Pasting **production credentials** into chat — risk: data breach and Part 11 issues.
- Skipping review because “coverage is high” — risk: wrong tests for the right requirement.

## Verification Checklist
- [ ] AI use policy acknowledged for the repo/product line.
- [ ] PRs show human reviewer distinct from sole prompt author where required.
- [ ] Requirements and tests updated for all generated behavior changes.
- [ ] No sensitive data in prompts or CI logs (spot audit).
- [ ] Tool/plugin major updates assessed under change control if GxP applies.

## Traceability
- Link `REQ-*` / `TEST-*` / PR URLs in change records; optional tag `AI-GEN` on commits for metrics (internal only).

## References
- FDA Guidance: “Computer Software Assurance for Production and Quality System Software” (2022).
- IEC 62304:2006+A1:2015 — software development process (human processes still apply).
- Internal QMS SOPs for design control and records (primary authority).

## Changelog
- 1.0.0 (2026-03-20): Initial skill for LLM-assisted dev governance, review, and CSA alignment.
