---
skill_id: TEST-FUZZ
version: 1.0.0
last_updated: 2026-01-04
applies_to: [Class A, Class B, Class C]
jurisdiction: [Global]
prerequisites: [SEC-THREAT-MODELING, FW-EMBEDDED-C]
---

# Fuzz Testing for Medical Devices

## Purpose
Uncover robustness and security issues by fuzzing inputs/protocols relevant to medical devices (parsers, IPC, network/BLE/USB).

## When to Apply
- Parsers, protocol handlers, file/log importers, command decoders.
- After major changes to input handling or security-relevant code.

## Requirements (testable)
1. Target Selection: Identify fuzz targets from threat model and interfaces; prioritize safety/security-critical parsers. Rationale: focus on risk.
2. Harness Quality: Build minimal harness with input validation hooks and assertions; run on host where feasible. Rationale: effectiveness.
3. Sanitizers: Combine fuzzing with ASan/UBSan/MSan where possible. Rationale: detect memory/UB issues.
4. Corpus Management: Seed with structured samples; minimize corpus; store crashes with repro inputs. Rationale: coverage and triage.
5. Crash Triage: Deduplicate crashes; file defects with root cause and linkage to requirements/risks; fix or justify. Rationale: closure.
6. Coverage: Track coverage metrics; aim to improve over time; MC/DC not required but branch coverage helpful. Rationale: breadth of exploration.

## Recommended Practices
- Use lightweight protocol models to guide fuzzing (e.g., length fields, checksums).
- Run fuzzers in CI/nightly on host; for embedded-only code, fuzz extracted libs or use emulation where possible.
- Limit run time per PR; longer campaigns nightly/weekly.

## Patterns
LibFuzzer harness (C):
```c
// REQ-FUZZ-HAR-01; TEST-FUZZ-03
int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    if (size < sizeof(cmd_t)) return 0;
    if (!validate_msg((const msg_t *)data, size)) return 0;
    handle_cmd((const msg_t *)data);
    return 0;
}
```

Seed corpus entry (hex):
```text
// REQ-FUZZ-CORPUS-02
01 00 10 00 AA BB CC DD
```

## Anti-Patterns (risks)
- Fuzzing without sanitizers -> risk: missed memory/UB issues.
- No crash dedup/triage -> risk: unhandled defects.
- Unseeded fuzzing on structured protocols -> risk: slow/ineffective.
- Ignoring outputs/logs from fuzzer -> risk: silent failures.

## Verification Checklist
- [ ] Fuzz targets selected from threat model/interfaces.
- [ ] Harnesses include assertions/validations; run on host/emulated.
- [ ] Sanitizers enabled where possible during fuzzing.
- [ ] Corpus seeded and managed; crashes stored with repro.
- [ ] Crashes triaged/deduped; issues filed/resolved/justified.
- [ ] Coverage tracked; improvements monitored.

## Traceability
- `REQ-FUZZ-###` to fuzz harness/test IDs `TEST-FUZZ-###`; crash reports linked to defects and requirements.

## References
- AFL/LibFuzzer/oss-fuzz documentation.
- FDA cybersecurity guidance encourages robustness testing (informative).

## Changelog
- 1.0.0 (2026-01-04): Initial fuzz testing skill with harness, sanitizer, and triage guidance.

## Audit History
- **2026-01-04**: Audit performed. Verified:
  - AFL/LibFuzzer/oss-fuzz references are accurate
  - LLVMFuzzerTestOneInput harness pattern is syntactically correct
  - Sanitizer integration (ASan/UBSan/MSan) correctly described
