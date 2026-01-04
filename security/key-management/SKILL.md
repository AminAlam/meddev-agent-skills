---
skill_id: SEC-KEYMGMT
version: 1.0.0
last_updated: 2026-01-04
applies_to: [Class A, Class B, Class C]
jurisdiction: [Global]
prerequisites: [SEC-ENCRYPTION]
---

# Cryptographic Key Management

## Purpose
Define generation, storage, rotation, revocation, and provisioning of cryptographic keys for medical devices, supporting secure boot, OTA, and comms.

## When to Apply
- Any feature using crypto keys (identity, TLS, signing, storage encryption).
- Manufacturing provisioning and field updates.

## Requirements (testable)
1. Key Generation: Use secure RNG; generate offline for signing roots; on-device keys generated with TRNG and protected storage. Rationale: entropy and control.
2. Storage: Protect private keys in secure element/TPM or sealed storage; separate code/data privileges; no plaintext keys. Rationale: prevent extraction.
3. Rotation: Support key rotation for device credentials and signing keys; define processes and grace periods. Rationale: limit exposure window.
4. Revocation: Support revocation lists or status checks (OCSP/CRL/pinned rotation) for server and device certs. Rationale: remove compromised keys.
5. Injection/Provisioning: Secure manufacturing key injection with audit trails; no reuse of device keys across units. Rationale: uniqueness and traceability.
6. Backup/Escrow: Avoid escrow of signing keys; if operational keys need backup, encrypt and control access with least privilege. Rationale: minimize insider risk.
7. Separation of Duties: Keep signing keys offline; use intermediate for production signing; limit personnel access. Rationale: reduce key misuse.

## Recommended Practices
- Use short-lived device certificates; renew automatically before expiry.
- Pinning with rotation: maintain old+new pins during transition.
- Wipe keys on device decommission or secure reset.
- Document key lifecycle in a key management policy.

## Patterns
Key derivation for per-session keys:
```c
// REQ-KEY-KDF-01; TEST-KEY-04
hkdf_sha256(master_key, salt, info, session_key, 32);
```

Provisioning record (YAML):
```yaml
# REQ-KEY-PROV-02
device_id: DEV12345
keys:
  identity_cert: sha256:abcd...
  bootstrap_ca: sha256:1234...
date: 2026-01-04
operator: line-3
```

Revocation check (pseudo):
```c
// REQ-KEY-REV-03; TEST-KEY-07
if (cert_is_revoked(peer_cert) || expired(peer_cert)) {
    reject_connection();
}
```

## Anti-Patterns (risks)
- Shared device keys across fleet -> risk: systemic compromise.
- Plaintext private keys in flash -> risk: easy extraction.
- No rotation path -> risk: long-lived compromise.
- Root signing key online -> risk: theft/unauthorized signing.

## Verification Checklist
- [ ] Keys generated with secure RNG; roots offline; device keys unique.
- [ ] Private keys stored in secure hardware or sealed storage; not plaintext.
- [ ] Rotation supported and tested; transition periods defined.
- [ ] Revocation supported (CRL/OCSP/pins); rejection on revoked/expired.
- [ ] Manufacturing provisioning secure; audit trail kept; no shared keys.
- [ ] Key lifecycle documented; separation of duties enforced for signing keys.

## Traceability
- Requirements `REQ-KEY-###` to tests `TEST-KEY-###`; link to secure boot/OTA/auth requirements.
- Provisioning and rotation events logged with IDs and timestamps.

## References
- NIST SP 800-57 (key management).
- NIST SP 800-132 (password-based KDF); 800-56 for key agreement.
- FIPS 140-2/3 for module considerations when required.

## Changelog
- 1.0.0 (2026-01-04): Initial key management skill covering generation, storage, rotation, and revocation.

## Audit History
- **2026-01-04**: Audit performed. Verified:
  - NIST SP 800-57 (key management) correctly referenced
  - NIST SP 800-132 (password-based KDF) and 800-56 (key agreement) appropriate
  - FIPS 140-2/3 considerations correctly noted for applicable environments
