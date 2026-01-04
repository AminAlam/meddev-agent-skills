---
skill_id: SEC-SECURE-BOOT
version: 1.0.0
last_updated: 2026-01-04
applies_to: [Class A, Class B, Class C]
jurisdiction: [Global]
prerequisites: [SEC-ENCRYPTION, SEC-KEYMGMT]
---

# Secure Boot Implementation

## Purpose
Establish a root of trust and verify firmware integrity/authenticity from reset through handoff, including anti-rollback and recovery.

## When to Apply
- Bootloader design/updates; adding secure boot to devices; integrating OTA/update flows.

## Requirements (testable)
1. Root of Trust: Immutable boot ROM or fuse-backed root keys; verify first mutable stage signature. Rationale: trust anchor.
2. Signature Verification: Verify each stage (bootloader, app) with strong signature (e.g., ECDSA P-256, Ed25519); reject on failure. Rationale: authenticity/integrity.
3. Anti-Rollback: Enforce monotonic version/counter in secure storage; block rollback to vulnerable images. Rationale: prevent downgrade attacks.
4. Measured Boot/Logs: Record hash/version of loaded image; store for audit; optionally attest. Rationale: traceability and attestation.
5. Secure Updates Tie-in: Only install signed images; reuse verification path; fail-safe if verification fails. Rationale: consistent chain of trust.
6. Key Protection: Store verification keys in secure hardware or read-only region; support key rotation with dual-key or certificate chain. Rationale: prevent key tampering.
7. Recovery Path: Provide authenticated recovery image path; safe state if both primary/recovery invalid. Rationale: availability with integrity.

## Recommended Practices
- Use minimal bootloader; avoid network stacks in first stage.
- Keep signature verification constant-time; validate manifest (lengths, addresses).
- Separate signing keys (offline) from device-embedded verification keys.
- Log boot result and reason codes for field diagnostics.

## Patterns
Manifest verification (pseudo):
```c
// REQ-SBOOT-VERIFY-01; TEST-SBOOT-04
bool verify_image(const manifest_t *m) {
    if (m->len > MAX_IMG || m->entry < FLASH_BASE) return false;
    uint8_t hash[32];
    sha256(image_region(m), m->len, hash);
    return ecdsa_verify(m->sig, m->sig_len, hash, root_pubkey);
}
```

Anti-rollback check:
```c
// REQ-SBOOT-ROLL-02; TEST-SBOOT-06
if (m->version < stored_version()) {
    return false; // reject rollback
}
```

Boot log:
```c
// REQ-SBOOT-LOG-03; TEST-SBOOT-08
boot_log_t log = { .version = m->version, .status = BOOT_OK };
log_boot(&log);
```

## Anti-Patterns (risks)
- Accepting unsigned or self-signed images -> risk: code injection.
- Storing verification keys in writable flash without protection -> risk: key swap.
- No anti-rollback -> risk: reintroducing known vulnerabilities.
- Skipping length/region checks -> risk: overwrite/exec unintended memory.

## Verification Checklist
- [ ] Root key immutable or fuse-protected; first mutable stage verified.
- [ ] Each stage signature verified with approved algorithms; failures halt/enter safe recovery.
- [ ] Anti-rollback enforced with monotonic counter/version.
- [ ] Boot measurements logged; available for diagnostics/attestation.
- [ ] Update path uses same verification; unsigned images rejected.
- [ ] Verification keys protected; rotation process defined and tested.
- [ ] Recovery path authenticated; safe behavior if both images invalid.

## Traceability
- Requirements `REQ-SBOOT-###` linked to tests `TEST-SBOOT-###`; map to threat model controls.

## References
- NIST SP 800-193 (Platform Firmware Resiliency).
- MCU vendor secure boot app notes.
- FDA Cybersecurity Premarket Guidance (integrity of software).

## Changelog
- 1.0.0 (2026-01-04): Initial secure boot skill with root of trust, signature, anti-rollback, and recovery guidance.

## Audit History
- **2026-01-04**: Audit performed. Verified:
  - NIST SP 800-193 (Platform Firmware Resiliency) correctly referenced
  - Signature algorithm recommendations (ECDSA P-256, Ed25519) are current
  - Anti-rollback mechanisms accurately described
