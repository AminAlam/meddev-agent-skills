# Contributing

Thanks for helping improve medical-device-agent-skills. Contributions must maintain regulatory rigor, include runnable examples, and provide verification criteria.

## How to propose a new skill
- Open an issue describing the skill scope, jurisdiction, safety classes, and rationale.
- Draft the skill using `SKILL_SCHEMA.md` with complete metadata (skill_id, prerequisites, applies_to, jurisdiction).
- Include at least two runnable code examples (preferably in C/C++/Python) that reflect real device patterns and compile/lint cleanly.
- Provide verification checklists and traceability guidance.
- Cite standards/guidance with section numbers; mark interpretations explicitly.

## Updating an existing skill
- Describe the change, impacted sections, and reason (e.g., new guidance, correction, added example).
- Maintain backward traceability of changes in the skill changelog.
- Keep code examples warning-free under `-Wall -Wextra -Werror` (or equivalent).

## Pull request template
- Summary of changes and affected skills/files.
- Standards cited (with sections) and jurisdictions affected.
- New/updated code examples and how to run tests.
- Verification checklist updates.
- QA/RA or domain expert reviewers tagged.

## Review process
- At least one maintainer plus one regulatory/domain expert must approve.
- Check schema conformance (frontmatter, required sections).
- Validate examples compile/run/tests pass; ensure traceability annotations.
- Confirm verification checklist is actionable and complete.

## Skill quality bar
- References to authoritative sources (standards, FDA guidance, MDCG, IEC, NIST) with section numbers.
- Clear applicability by safety class and jurisdiction.
- Patterns and anti-patterns grounded in realistic device scenarios.
- Testable requirements and checklists; no vague statements.
- Traceability instructions (requirements ↔ design ↔ code ↔ tests).

## Style guide for skill writing
- Concise, technical language; no marketing claims.
- Note when guidance is interpretation vs explicit standard text.
- Call out jurisdictional differences.
- Use consistent headings per `SKILL_SCHEMA.md`.
- Code blocks should be minimal yet complete; include comments for medical-device context and traceability tags (e.g., `REQ-123`, `RISK-45`, `TEST-78`).

## Reporting issues or suggesting improvements
- Open an issue with: context, affected skill(s), expected vs observed guidance, and proposed fix.
- For urgent compliance gaps, label as `compliance-critical`.
