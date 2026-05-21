# Agent Integration Guide

How to integrate `medical-device-agent-skills` into AI coding agents while respecting context limits, prerequisites, and jurisdiction/safety filters.

## Skill discovery
- File-based: traverse repo; index `SKILL.md` paths plus frontmatter fields.
- Metadata index: parse YAML frontmatter for `skill_id`, `applies_to`, `jurisdiction`, `prerequisites`, `version`.
- API-based: expose skills via a small service returning rendered sections and metadata; cache by `skill_id@version`.

## Selection algorithms
- Rules-based: match safety class, jurisdiction, and file types to `When to Apply`.
- Keyword/regex: detect domain cues (e.g., "SOUP", "bootloader", "BLE") in diffs or files.
- Embedding similarity: embed diffs/plan text vs skill content; rerank by `applies_to`/`jurisdiction`.
- LLM classification: ask a router model to choose top-N skills given task + metadata.
- Hybrid: rules filter -> similarity -> LLM tie-break; enforce prerequisite closure.

## Context window management
- Prioritize: include only sections needed for the task (Requirements, Patterns, Anti-Patterns, Verification).
- Summarize: compress long sections; keep code examples intact where needed.
- Chain skills: load prerequisites first; deduplicate overlapping guidance.
- Scope by change set: map diffs to affected domains (e.g., RTOS, BLE, boot) and select matching skills.

## IEC 62304 recommended load order

For regulated medical device software work, resolve prerequisites in this order (interpretation):

```
REG-ISO14971
  └── REG-IEC62304                    # lifecycle hub
        ├── ARCH-SAFETY-CLASS         # 4.3 classification
        ├── REG-IEC62304-SWRM         # Clause 7 (Class B/C focus)
        ├── REG-IEC62304-LEGACY       # 4.4 when applicable only
        ├── DOC-SW-REQ                # 5.2
        ├── DOC-DESIGN-DOCS           # 5.3–5.4
        ├── DOC-SCM                   # Clause 8
        ├── DOC-CHANGE-CONTROL        # 8.2 / change requests
        ├── DOC-PROBLEM-RES           # Clause 9
        ├── DOC-SW-MAINT              # Clause 6 (post-release)
        ├── DOC-TEST-DOCS             # 5.7.5, 9.8
        └── DOC-TRACEABILITY
              └── implementation skills (TEST-*, FW-*, CICD-*, SEC-*)
```

Filter by `applies_to`: Class A work may omit Class C-only skills (detailed design 5.4, 5.3.5 segregation) unless items are unclassified (default Class C per 4.3 g).

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
- Do not paste copyrighted standard text into prompts; use skills as paraphrased guidance with clause references.

## Notes
- Skills supplement—not replace—formal regulatory review and licensed standard documents.
- When context is tight, favor Requirements + Verification + targeted Patterns.
- For AI-assisted development, see `DOC-AI-GOV` for skill version pinning and class-appropriate 62304 loading.
