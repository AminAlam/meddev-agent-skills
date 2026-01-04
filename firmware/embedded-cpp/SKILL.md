---
skill_id: FW-EMBEDDED-CPP
version: 1.0.0
last_updated: 2026-01-04
applies_to: [Class A, Class B, Class C]
jurisdiction: [Global]
prerequisites: [FW-EMBEDDED-C]
---

# Embedded C++ Coding Standards for Medical Devices

## Purpose
Define a constrained C++ subset suitable for medical device firmware, aligned to MISRA C++ guidance: safe types, RAII, limited dynamic features, and predictable behavior.

## When to Apply
- C++ firmware modules, drivers, and application logic in safety-related systems.
- Code reviews and new module development using C++ on MCUs/RTOS.

## Requirements (testable)
1. Feature Set: No exceptions in safety-critical paths; RTTI disabled unless justified; avoid dynamic_cast on polymorphic hierarchies in critical code. Rationale: predictability and size.
2. Memory: Prefer static allocation; where dynamic is needed, use RAII and bounded allocators/pools; no raw `new`/`delete` in safety paths. Rationale: determinism.
3. Ownership: Use smart pointers (`unique_ptr` where supported); avoid shared ownership in critical code; no cycles. Rationale: leak/alias safety.
4. Templates: Use templates for type safety and zero-cost abstractions; avoid template metaprogramming that obscures behavior; ensure instantiations are bounded. Rationale: clarity and analyzability.
5. Constructors/Destructors: Keep trivial/constexpr where possible; no logic that can fail silently; avoid throwing constructors. Rationale: predictable init.
6. Concurrency: If using `std::atomic`/RTOS primitives, ensure memory orderings are explicit; avoid `volatile` for concurrency except for HW-mapped registers. Rationale: correctness.
7. Namespaces/Headers: Use namespaces to avoid collisions; headers self-contained; no using-directives in headers. Rationale: hygiene.
8. Static Analysis: Run MISRA C++ checks; treat warnings as errors; deviations documented. Rationale: defect prevention.

## Recommended Practices
- Favor `enum class` for scoped enums.
- Prefer `constexpr` for configuration constants.
- Use `span`-like views (or simple pointer+len structs) instead of raw pointers.
- Keep vtables/polymorphism out of ISR/critical loops; prefer CRTP/static dispatch.

## Patterns
RAII guard for peripheral enable:
```cpp
// REQ-CPP-RAII-01; TEST-CPP-03
class PeripheralGuard {
 public:
  PeripheralGuard() { periph_enable(); }
  ~PeripheralGuard() { periph_disable(); }
  PeripheralGuard(const PeripheralGuard&) = delete;
  PeripheralGuard& operator=(const PeripheralGuard&) = delete;
};
```

Bounded buffer view:
```cpp
// REQ-CPP-API-02; TEST-CPP-05
struct BufferView {
  uint8_t* data;
  size_t len;
};

bool copy_bounded(BufferView dst, BufferView src) {
  if (src.len > dst.len) return false;
  std::copy(src.data, src.data + src.len, dst.data);
  return true;
}
```

No-exception init:
```cpp
// REQ-CPP-INIT-03; TEST-CPP-07
class Sensor {
 public:
  bool init() noexcept {
    return hw_init() == 0;
  }
};
```

## Anti-Patterns (risks)
- Exceptions in ISRs or critical loops -> risk: uncontrolled unwinding.
- Raw owning pointers with manual `delete` -> risk: leaks/double-free.
- Unbounded template instantiations causing code bloat -> risk: flash overflow and review difficulty.
- Using directives in headers -> risk: namespace pollution.
- RTTI/dynamic_cast in timing-critical code -> risk: overhead and unpredictability.

## Verification Checklist
- [ ] Exceptions disabled/unused in safety paths; RTTI disabled or justified.
- [ ] Dynamic allocation avoided; where used, RAII + bounded pools; no raw new/delete.
- [ ] Ownership clear; `unique_ptr` or value semantics; no shared cycles.
- [ ] Template use bounded and readable; avoids heavy metaprogramming.
- [ ] Constructors/destructors simple, non-throwing; init outcomes explicit.
- [ ] Concurrency primitives used with explicit memory orders; volatile only for HW.
- [ ] Headers clean: guards, self-contained, no using-directives.
- [ ] MISRA C++/SAST run; deviations documented; warnings treated as errors.

## Traceability
- Use `REQ-CPP-###` and `TEST-CPP-###` tags; link MISRA deviation records to requirements.

## References
- MISRA C++:2023 (current edition) - major update from MISRA C++:2008.
- MISRA C++:2008 (legacy projects).
- AUTOSAR C++14 (informative for safer subset concepts).
- IEC 62304 implementation discipline.

## Changelog
- 1.0.1 (2026-01-04): Audit correction - updated MISRA C++ reference from 2008 to 2023 edition.
- 1.0.0 (2026-01-04): Initial embedded C++ subset with RAII, bounded templates, and no-exception guidance.

## Audit History
- **2026-01-04**: Audit performed. Corrections:
  - MISRA C++:2008 is now significantly outdated; MISRA C++:2023 added as current reference
  - AUTOSAR C++14 reference verified as appropriate informative source
