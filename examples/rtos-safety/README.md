# RTOS Safety Example

Demonstrates RTOS-aligned patterns without external RTOS dependencies: bounded message queue, watchdog servicing only when health checks pass, and task health monitoring.

Aligned skills:
- `firmware/rtos-patterns/SKILL.md`
- `architecture/fault-tolerance/SKILL.md`
- `architecture/defensive-design/SKILL.md`
- `testing/unit-testing/SKILL.md`

## Files
- `rtos_safety.h/.c`: Bounded queue send/receive with timeouts simulated, watchdog service gated on task health.
- `rtos_safety_test.c`: Assertions covering queue overflow, successful send/receive, and watchdog gating behavior.

## Build/Test (host)
```bash
cc -Wall -Wextra -Werror -std=c11 -c sample-code/rtos_safety.c -o /tmp/rtos_safety.o
cc -Wall -Wextra -Werror -std=c11 sample-code/rtos_safety_test.c /tmp/rtos_safety.o -o /tmp/rtos_safety_test
/tmp/rtos_safety_test
```

## Traceability cues
- Requirements: `REQ-RTOS-IPC-02` (bounded queue), `REQ-RTOS-TIME-04` (timeouts), `REQ-FT-WD-01` (watchdog gating).
- Tests: `TEST-RTOS-IPC-*`, `TEST-RTOS-WD-*`.***

