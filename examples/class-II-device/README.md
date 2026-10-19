# Class II Device Example (Infusion Pump Control Slice)

Demonstrates how to apply skills for a Class II, IEC 62304 Class C software item: safety classification, defensive design, IEC 62304 lifecycle traceability, ISO 14971 risk controls, and unit testing.

## Applied skills
- `skills/meddev-iec-62304/SKILL.md` (lifecycle, traceability, SOUP)
- `skills/meddev-iso-14971/SKILL.md` (risk controls, safe state)
- `skills/meddev-safety-classification/SKILL.md` (Class C item segregation)
- `skills/meddev-state-machines/SKILL.md` (simple start/stop)
- `skills/meddev-defensive-design/SKILL.md` (input validation)
- `skills/meddev-embedded-c/SKILL.md` (MISRA-aligned C)
- `skills/meddev-unit-testing/SKILL.md` (AAA, traceability)

## What’s included
- `therapy_controller.h/.c`: Minimal therapy control API with state and guards.
- `therapy_controller_test.c`: Unit-style test harness validating behavior.

## How to build/test (host)
```bash
cc -Wall -Wextra -Werror -std=c11 -c therapy_controller.c
cc -Wall -Wextra -Werror -std=c11 therapy_controller_test.c therapy_controller.o -o therapy_test
./therapy_test
```

## Traceability cues
- Requirement tags like `REQ-62304-102` and risk control `RISK-CTRL-19` are embedded in comments near the logic and tests.
- Safe-state behavior is represented by refusing to run or stopping cleanly on invalid transitions.
