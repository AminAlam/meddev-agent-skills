# SKILL Schema

This document defines the required structure for every `SKILL.md`. Skills are designed for AI coding assistants: concise, actionable, and verifiable.

## 1) Metadata block (YAML frontmatter)
```yaml
skill_id: REG-IEC62304          # unique, stable identifier
version: 1.0.0                  # semantic version
last_updated: 2026-01-04        # ISO date
applies_to: [Class A, Class B]  # safety classes, explicit
jurisdiction: [FDA, EU MDR]     # regulatory scope
prerequisites: [REG-ISO14971]   # other skills to load first
```

## 2) Purpose
One paragraph explaining the scope and intent of the skill.

## 3) When to Apply
Bullet list of trigger conditions (file types, keywords, project contexts, safety classes).

## 4) Requirements
Numbered list of mandatory requirements with brief rationale; each must be testable.

## 5) Recommended Practices
Concise best practices that strengthen compliance/safety beyond minimum requirements.

## 6) Patterns
Code examples with comments explaining why they are correct in a medical-device context. Include traceability annotations (e.g., `// REQ-123`, `// RISK-45`).

## 7) Anti-Patterns
Examples of what not to do, with explicit risk or compliance impact called out.

## 8) Verification Checklist
Checkbox list (markdown `- [ ]`) that can be used during code review or automated checks. Each item must be objectively verifiable.

## 9) Traceability
Explain how to link requirements ↔ design ↔ code ↔ tests, including tag formats and repository conventions.

## 10) References
Authoritative sources with section numbers (standards, FDA guidance, MDCG, NIST, etc.). Note when guidance is interpretation.

## 11) Changelog
Versioned history of updates (date, author, summary).

## Authoring guidance
- Keep language concise and technical; avoid marketing language.
- State applicability by safety class and jurisdiction explicitly.
- Mark interpretations vs explicit standard text.
- Provide complete code snippets that compile cleanly (assume `-Wall -Wextra -Werror` or equivalent).
- Ensure every requirement has a verification path (test, checklist, static/dynamic analysis).
- Use ASCII unless domain content requires otherwise.
