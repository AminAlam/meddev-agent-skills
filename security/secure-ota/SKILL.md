---
skill_id: SEC-SECURE-OTA
version: 1.0.0
last_updated: 2026-01-04
applies_to: [Class A, Class B, Class C]
jurisdiction: [Global]
prerequisites: [SEC-SECURE-BOOT, SEC-ENCRYPTION, SEC-KEYMGMT]
---

# Secure Over-the-Air Updates

## Purpose
Ensure OTA updates are authenticated, integrity-checked, atomic, and safely recoverable, with regulatory considerations for software changes.

## When to Apply
- Adding or modifying OTA/update mechanisms (WiFi/BLE/cellular/USB bootstrap).

## Requirements (testable)
1. Signed Packages: All update images are signed (ECDSA/Ed25519); verification before apply. Rationale: integrity/authenticity.
2. Transport Security: Fetch updates over TLS 1.3 (or strong 1.2) with server auth; consider mTLS for device auth. Rationale: in-transit protection.
3. Atomic Apply & Rollback: Use A/B or staging; ensure power loss-safe writes; rollback to known good on failure. Rationale: availability and safety.
4. Version & Anti-Rollback: Enforce monotonic versioning; reject older/vulnerable images. Rationale: prevent downgrades.
5. Manifest Validation: Validate length, hash, target slot, and compatibility before flashing. Rationale: prevent corruption/wrong target.
6. Policy & Approvals: Apply update policy (who/when); log approvals where required; align with change control and regulatory submission needs. Rationale: compliance.
7. Post-Update Verification: Self-test on first boot after update; revert if critical tests fail. Rationale: functional assurance.

## Recommended Practices
- Limit update window/bandwidth; throttle retries.
- Use delta updates only if integrity is protected end-to-end.
- Log update attempts/results with reasons; expose for service.
- Coordinate with secure boot keys and rotation plan.

## Patterns
Manifest structure (example):
```json
// REQ-OTA-MAN-01; TEST-OTA-03
{
  "version": 12,
  "slot": "B",
  "len": 262144,
  "hash": "f3ab...",
  "sig": "3045...",
  "compat": "hw:rev2"
}
```

Apply flow (pseudo):
```c
// REQ-OTA-APPLY-02; TEST-OTA-06
if (!verify_manifest(m) || !verify_sig(pkg, m->sig)) abort();
if (m->version <= current_version()) abort(); // anti-rollback
if (!write_slot(m->slot, pkg, m->len)) abort();
mark_pending(m->version, m->slot);
reboot();
```

Post-update self-test:
```c
// REQ-OTA-VERIFY-03; TEST-OTA-09
if (!run_startup_tests()) {
    rollback();
    log_event("OTA_FAIL_SELFTEST");
}
```

## Anti-Patterns (risks)
- Unsigned updates or signature ignored on failure -> risk: code injection.
- In-place single-slot updates without power-fail protection -> risk: bricking.
- No anti-rollback -> risk: reintroducing known vulnerabilities.
- Delta updates without end-to-end verification -> risk: patch tampering.
- Missing post-update self-test -> risk: latent defects in field.

## Verification Checklist
- [ ] Updates signed and verified; failures abort safely.
- [ ] Transport over TLS with server validation (and mTLS if required).
- [ ] Atomic apply/rollback path implemented; power-fail safe.
- [ ] Anti-rollback/version checks enforced.
- [ ] Manifest validated (length/hash/slot/compatibility).
- [ ] Update policy/approvals logged; change control followed.
- [ ] Post-update self-test executes; rollback on failure; results logged.

## Traceability
- `REQ-OTA-###` to `TEST-OTA-###`; link to secure boot requirements and change control records.

## References
- NIST SP 800-193 (firmware resiliency).
- FDA Cybersecurity Premarket Guidance (updates/patching).
- MCU/vendor A/B or DFU application notes.

## Changelog
- 1.0.0 (2026-01-04): Initial secure OTA skill with signing, atomicity, anti-rollback, and post-update verification.

## Audit History
- **2026-01-04**: Audit performed. Verified:
  - NIST SP 800-193 reference appropriate
  - A/B update patterns accurately described
  - Signature and manifest verification patterns technically sound
