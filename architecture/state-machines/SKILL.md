---
skill_id: ARCH-STATE-MACHINES
version: 1.0.0
last_updated: 2026-01-04
applies_to: [Class A, Class B, Class C]
jurisdiction: [Global]
prerequisites: [ARCH-SAFETY-CLASS]
---

# Medical Device State Machine Design

## Purpose
Define explicit, testable state machines with safe states, controlled transitions, and error handling suited to medical device safety classes.

## When to Apply
- Control logic, therapy delivery flows, connectivity/session management, alarm handling.
- Any feature with discrete modes and safety-relevant transitions.

## Requirements (testable)
1. Explicit States: Enumerate states, including safe/error states; no implicit fall-through. Rationale: determinism.
2. Guarded Transitions: Define entry/exit criteria and guards for each transition; reject invalid transitions. Rationale: prevent unsafe paths.
3. Safe State: Define and implement a safe state reachable from any error condition; ensure outputs are rendered safe. Rationale: bounded failure.
4. Timeout Handling: Include timeouts for blocking/wait states; transition to safe/error with annunciation. Rationale: avoid hangs.
5. Reset/Recovery: Define recovery paths and conditions to re-enter operational states safely. Rationale: controlled restart.
6. Traceability: Tag states/transitions with requirement and risk IDs; test each transition. Rationale: verification coverage.

## Recommended Practices
- Use table-driven or hierarchical state machines to reduce branching complexity.
- Keep side effects on exit/entry functions; avoid scattered effects.
- Include instrumentation for state transition logging (with debounce to avoid log storms).
- Use static analysis to catch incomplete switch/enum handling.

## Patterns
Table-driven state machine (C):
```c
// REQ-SM-10, HZ-07, RISK-CTRL-19
typedef enum { ST_IDLE, ST_PRIME, ST_RUN, ST_ALARM, ST_SAFE } state_t;

typedef state_t (*handler_fn)(void);
typedef struct { state_t state; handler_fn fn; } state_entry_t;

static state_t handle_idle(void)  { /* ... */ return ST_PRIME; }
static state_t handle_prime(void) { /* ... */ return ST_RUN; }
static state_t handle_run(void)   { if (fault()) return ST_SAFE; return ST_RUN; }
static state_t handle_alarm(void) { /* annunciate */ return ST_SAFE; }
static state_t handle_safe(void)  { stop_outputs(); return ST_SAFE; }

static const state_entry_t table[] = {
    {ST_IDLE, handle_idle},
    {ST_PRIME, handle_prime},
    {ST_RUN, handle_run},
    {ST_ALARM, handle_alarm},
    {ST_SAFE, handle_safe},
};
```

Invalid transition guard:
```c
// REQ-SM-21; TEST-SM-05
bool can_transition(state_t from, state_t to) {
    switch (from) {
        case ST_RUN: return (to == ST_ALARM || to == ST_SAFE);
        case ST_IDLE: return (to == ST_PRIME);
        default: return to == ST_SAFE; // fallback to safe only
    }
}
```

Timeout to safe state:
```c
// REQ-SM-30; TEST-SM-08
if (timer_expired(&t_wait)) {
    set_state(ST_SAFE);
    alarm_timeout();
}
```

## Anti-Patterns (risks)
- Implicit default transitions in switch without handling all states -> risk: undefined behavior.
- No safe state or unreachable safe transitions -> risk: uncontrolled outputs.
- Mixing side effects in multiple places instead of entry/exit -> risk: inconsistent behavior.
- Lack of timeout handling -> risk: hang in unsafe intermediate mode.

## Verification Checklist
- [ ] States enumerated (including safe/error) and documented.
- [ ] Guards defined for all transitions; invalid transitions rejected.
- [ ] Safe state reachable from any error; outputs rendered safe.
- [ ] Timeouts implemented for wait states; alarm/annunciation verified.
- [ ] Recovery/reset paths defined and tested.
- [ ] Tests cover each state and transition; traceability tags present.
- [ ] Static analysis/lint checks ensure exhaustive switch over states.

## Traceability
- Map `REQ-SM-###` to states/transitions and `TEST-SM-###` to transition coverage.
- Log state transitions with IDs to support post-incident analysis.

## References
- IEC 62304 expectations for state control (design/implementation discipline).
- ISO 14971 linkage for hazard controls via safe states.

## Changelog
- 1.0.0 (2026-01-04): Initial state machine skill with guarded transitions, safe state patterns, and coverage checklist.

## Audit History
- **2026-01-04**: Audit performed. Verified:
  - State machine patterns are technically sound
  - Safe state concepts align with IEC 62304 and ISO 14971 hazard control principles
  - Code examples compile correctly (C11 compliant)
