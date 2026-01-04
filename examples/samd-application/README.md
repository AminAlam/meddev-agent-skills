# SAMD Application Example (Diagnostics)

Demonstrates Python-side diagnostic logic with traceability to requirements and risk controls, plus pytest-based tests. Intended for devices that offload analytics to a SAMD + Python environment.

## Applied skills
- `documentation/test-docs/SKILL.md` (plans/protocols)
- `documentation/code-comments/SKILL.md` (trace tags)
- `testing/unit-testing/SKILL.md` (AAA, negative cases)
- `data/data-integrity/SKILL.md` (validation, checks)

## Files
- `diagnostic_algorithm.py`: Simple diagnostic evaluator with input validation and thresholds.
- `test_diagnostic_algorithm.py`: Pytest tests covering normal and error paths.

## Run tests
```bash
python3 -m pytest -q
```

## Traceability cues
- Uses requirement tags like `REQ-DIAG-01` and test tags `TEST-DIAG-01` in comments near logic and tests.***
