---
skill_id: DATA-INTEGRITY
version: 1.0.0
last_updated: 2026-01-04
applies_to: [Class A, Class B, Class C]
jurisdiction: [Global]
prerequisites: [SEC-ENCRYPTION]
---

# Data Integrity

## Purpose
Ensure integrity of data in storage and transmission using checksums/CRCs/ECC, validation, and redundancy where needed for medical devices.

## When to Apply
- Storing or transmitting patient/therapy data, logs, configs, firmware.
- Safety-critical control or sensor data paths.

## Requirements (testable)
1. Checksums/CRCs: Apply CRC or MAC to critical data blobs and messages; verify before use. Rationale: detect corruption.
2. ECC/Redundancy: Use ECC or redundancy for persistent storage where feasible; handle correction/failure paths. Rationale: reliability.
3. Input Validation: Validate size/range/format before processing; reject malformed data. Rationale: prevent misuse and corruption.
4. Error Handling: On integrity failure, enter safe handling (retry, request retransmit, or safe state); log event. Rationale: safe recovery.
5. Versioning: Version stored data formats; migrate safely; verify after migration. Rationale: compatibility and integrity.

## Recommended Practices
- Include length and CRC fields in messages; keep CRC separate from payload.
- Use HMAC for integrity when authenticity is also needed.
- Periodically scrub/read-verify important data (configs/calibration) to detect bitrot.

## Patterns
CRC on message:
```c
// REQ-DINT-CRC-01; TEST-DINT-03
bool validate_msg(const uint8_t *buf, size_t len, uint16_t expected_crc) {
    return crc16(buf, len) == expected_crc;
}
```

ECC status handling:
```c
// REQ-DINT-ECC-02; TEST-DINT-05
if (ecc_corrected) log_event("ECC_CORRECTED");
if (ecc_uncorrectable) { enter_safe_state(); }
```

Versioned config:
```yaml
# REQ-DINT-VERS-03
config_version: 2
fields:
  - name: calib_factor
    crc: 0xABCD
```

## Anti-Patterns (risks)
- No integrity check on stored configs -> risk: silent corruption affecting therapy.
- Ignoring CRC failures -> risk: using bad data.
- Mixing versioned/unversioned data without migration -> risk: misinterpretation.

## Verification Checklist
- [ ] CRC/HMAC applied to critical data/messages and verified.
- [ ] ECC/redundancy used where feasible; correction paths handled.
- [ ] Inputs validated; malformed data rejected safely.
- [ ] Integrity failures trigger safe handling and logging.
- [ ] Data formats versioned; migrations verified.

## Traceability
- `REQ-DINT-###` to `TEST-DINT-###`; logs of integrity failures retained.

## References
- IEC 62304 (data/control integrity expectations).
- NIST SP 800-38 (for MAC modes) as informative.

## Changelog
- 1.0.0 (2026-01-04): Initial data integrity skill with CRC/ECC, validation, and versioning.

## Audit History
- **2026-01-04**: Audit performed. Verified:
  - NIST SP 800-38 reference for MAC modes appropriate as informative
  - CRC and ECC patterns technically accurate
