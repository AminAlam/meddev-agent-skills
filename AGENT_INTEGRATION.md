# Agent Integration Guide

How to integrate `medical-device-agent-skills` into AI coding agents while respecting context limits, prerequisites, and jurisdiction/safety filters.

## Skill discovery
- File-based: traverse repo; index `SKILL.md` paths plus frontmatter fields.
- Metadata index: parse YAML frontmatter for `skill_id`, `applies_to`, `jurisdiction`, `prerequisites`, `version`.
- API-based: expose skills via a small service returning rendered sections and metadata; cache by `skill_id@version`.

## Selection algorithms
- Rules-based: match safety class, jurisdiction, and file types to `When to Apply`.
- Keyword/regex: detect domain cues (e.g., “SOUP”, “bootloader”, “BLE”) in diffs or files.
- Embedding similarity: embed diffs/plan text vs skill content; rerank by `applies_to`/`jurisdiction`.
- LLM classification: ask a router model to choose top-N skills given task + metadata.
- Hybrid: rules filter -> similarity -> LLM tie-break; enforce prerequisite closure.

## Context window management
- Prioritize: include only sections needed for the task (Requirements, Patterns, Anti-Patterns, Verification).
- Summarize: compress long sections; keep code examples intact where needed.
- Chain skills: load prerequisites first; deduplicate overlapping guidance.
- Scope by change set: map diffs to affected domains (e.g., RTOS, BLE, boot) and select matching skills.

## Prompt integration patterns
- System prompt injection: prepend selected skill snippets (requirements + verification) to system/developer prompts.
- Dynamic loading: fetch skills at tool time based on repository scan and plan.
- Skill chaining: resolve `prerequisites` and include them before dependents.

## Example: system prompt injection (pseudocode)
```python
skills = select_skills(diff, safety_class="Class B", jurisdiction=["FDA"])
ordered = topo_sort_with_prereqs(skills)
sections = extract_sections(ordered, ["Requirements","Patterns","Anti-Patterns","Verification Checklist"])
prompt = render_system_prompt(sections)
```

## Example: dynamic retrieval for a file
```python
if "bootloader" in file_path:
    load("security/secure-boot/SKILL.md")
if "wifi" in file_path:
    load("connectivity/wifi-medical/SKILL.md")
```

## Sample agent architecture
- Inputs: repo scan, diff, safety class, jurisdiction, task description.
- Router: rules + embeddings + LLM tie-breaker.
- Loader: fetch skills + prerequisites; chunk and rank sections.
- Planner: produce plan referencing skill requirements; map to verification.
- Executor: code generation with in-context skills; enforce checklists.
- Verifier: run tests/static analysis; tick verification checklist; produce traceability notes.

## Metrics for effectiveness
- Coverage: % of relevant skills loaded per task.
- Compliance adherence: checklist completion rate; static analysis/fuzz/unit pass rates.
- Defect rates: post-review findings attributable to missed requirements.
- Latency: added time from skill retrieval/formatting.
- Drift: skill version mismatch vs cached copies; audit via `skill_id@version`.

## Operational safeguards
- Pin versions (`skill_id@version`) in pipelines; alert on updates.
- Keep audit logs of skills injected per change (for traceability).
- Enforce jurisdiction/safety filters to avoid over/under-scoping guidance.

## Notes
- Skills supplement—not replace—formal regulatory review.
- When context is tight, favor Requirements + Verification + targeted Patterns.
