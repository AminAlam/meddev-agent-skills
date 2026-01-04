---
skill_id: FW-HAL
version: 1.0.0
last_updated: 2026-01-04
applies_to: [Class A, Class B, Class C]
jurisdiction: [Global]
prerequisites: [FW-EMBEDDED-C]
---

# Hardware Abstraction Layer (HAL) Design

## Purpose
Provide patterns for HAL design that enable testability, portability, and safety: clear interfaces, separation from application logic, and mockability.

## When to Apply
- Designing or refactoring drivers and HAL for peripherals.
- Porting to new MCUs/boards or enabling unit tests with mocks.

## Requirements (testable)
1. Interface Clarity: Define HAL interfaces with explicit types, ranges, and error codes; no hidden globals. Rationale: predictable use.
2. Separation: Keep application logic free of direct register access; encapsulate hardware access in HAL modules. Rationale: portability and testability.
3. Initialization Contracts: Provide explicit init/deinit; fail clearly on config errors; avoid partial init without reporting. Rationale: safe startup.
4. Error Handling: HAL APIs return status; callers must handle; no silent failures. Rationale: reliability.
5. Mock Support: Provide mock/fake implementations for unit tests; avoid static coupling that prevents substitution. Rationale: testability.
6. Concurrency/ISR Safety: Document ISR-safe APIs; guard shared resources; avoid blocking in ISR-safe functions. Rationale: correctness under concurrency.

## Recommended Practices
- Use narrow, capability-based interfaces (e.g., `hal_uart_write`, `hal_uart_read`).
- Keep register definitions private; expose only needed abstractions.
- Version/config structures to allow forward-compatible changes.
- Provide compile-time selection of real vs mock HAL.

## Patterns
HAL interface (header):
```c
// REQ-HAL-IF-01; TEST-HAL-03
typedef enum { HAL_OK = 0, HAL_EINVAL, HAL_EIO, HAL_EBUSY } hal_status_t;

hal_status_t hal_uart_init(uint32_t baud);
hal_status_t hal_uart_write(const uint8_t *buf, size_t len, size_t *written);
hal_status_t hal_uart_read(uint8_t *buf, size_t len, size_t *read, uint32_t timeout_ms);
```

Mock implementation (test build):
```c
// REQ-HAL-MOCK-02; TEST-HAL-05
static size_t mock_written;
hal_status_t hal_uart_write(const uint8_t *buf, size_t len, size_t *written) {
    mock_written = len;
    *written = len;
    return HAL_OK;
}
```

Init with validation:
```c
// REQ-HAL-INIT-03; TEST-HAL-07
hal_status_t hal_uart_init(uint32_t baud) {
    if (baud < 1200 || baud > 921600) return HAL_EINVAL;
    // configure hardware ...
    return HAL_OK;
}
```

## Anti-Patterns (risks)
- Application code directly accesses registers -> risk: untestable, tight coupling.
- HAL APIs that silently ignore errors -> risk: hidden failures.
- No mocks -> risk: unit tests blocked or using real hardware unintentionally.
- APIs with implicit globals or side effects -> risk: nondeterminism and test fragility.

## Verification Checklist
- [ ] HAL interfaces defined with explicit types/ranges/error codes.
- [ ] Application code free of direct register access; uses HAL APIs.
- [ ] Init/deinit paths validate inputs and report errors.
- [ ] Errors propagated and handled by callers.
- [ ] Mock/fake HAL available and used in unit tests.
- [ ] ISR/concurrency characteristics documented; shared resources protected.

## Traceability
- Map `REQ-HAL-###` to tests (`TEST-HAL-###`) including mocks; link to portability requirements.

## References
- MISRA C for interface clarity and header hygiene.
- IEC 62304 design segregation and testability expectations.

## Changelog
- 1.0.0 (2026-01-04): Initial HAL design guidance with interfaces, mocks, and error handling.

## Audit History
- **2026-01-04**: Audit performed. Verified:
  - HAL patterns follow industry best practices for testability
  - Mock implementation examples are accurate
  - Error handling patterns are sound
