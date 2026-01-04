---
skill_id: SEC-ENCRYPTION
version: 1.0.0
last_updated: 2026-01-04
applies_to: [Class A, Class B, Class C]
jurisdiction: [Global]
prerequisites: []
---

# Encryption for Medical Devices

## Purpose
Guide selection and use of cryptography for medical devices: algorithms, key derivation, data at rest/in transit, library choice, and FIPS considerations.

## When to Apply
- Any handling of PHI/PII, credentials, or safety-control data.
- Transport security (BLE/WiFi/USB app-layer), storage encryption, OTA/update integrity.

## Requirements (testable)
1. Algorithms: Use modern primitives (AES-256-GCM or ChaCha20-Poly1305; SHA-256/384; P-256 or X25519 for key exchange). Rationale: strong security.
2. TLS: Use TLS 1.3 (or strong 1.2 with AEAD); disable legacy ciphers; validate server certs; prefer mTLS for devices. Rationale: confidentiality/integrity.
3. Key Derivation: Use HKDF (or SP800-108/Argon2 for passwords); never reuse keys/IVs; unique IV per message. Rationale: cryptographic safety.
4. Data at Rest: Encrypt PHI/secrets at rest; bind to device (e.g., hardware unique key or secure element); protect keys separately. Rationale: protect on theft/loss.
5. Key Storage: Store long-term keys in secure hardware if available; otherwise protect with KDF + sealed storage; avoid plaintext keys in flash. Rationale: key protection.
6. Randomness: Use hardware TRNG or approved DRBG seeded correctly; no `rand()`/LFSR. Rationale: unpredictability.
7. Library Selection: Use vetted libraries (mbedTLS, OpenSSL/BoringSSL, wolfSSL) with security updates; avoid homegrown crypto. Rationale: reduce defects.
8. Integrity/Authentication: Use AEAD for confidentiality+integrity; for integrity-only, use HMAC-SHA-256. Rationale: tamper detection.

## Recommended Practices
- Keep a crypto policy document listing allowed algorithms and parameters.
- Enforce certificate pinning where appropriate; rotate pins safely.
- Zeroize key material after use; avoid swapping sensitive buffers.
- Add versioning to encrypted blobs; include AEAD AAD with context.

## Patterns
AEAD encryption (pseudocode):
```c
// REQ-ENC-AEAD-01; TEST-ENC-04
int encrypt_payload(const uint8_t *pt, size_t pt_len,
                    const uint8_t *aad, size_t aad_len,
                    uint8_t *ct, uint8_t *tag) {
    uint8_t iv[12];
    get_random(iv, sizeof(iv)); // per-message IV
    return aes_gcm_encrypt(key, iv, pt, pt_len, aad, aad_len, ct, tag);
}
```

HKDF for session key:
```c
// REQ-ENC-KDF-02; TEST-ENC-06
hkdf_sha256(master_secret, salt, info, session_key, 32);
```

Randomness:
```c
// REQ-ENC-RAND-03; TEST-ENC-08
size_t n = hwrng_fill(buf, len);
```

## Anti-Patterns (risks)
- Using ECB/RC4/MD5/SHA1 -> risk: weak encryption/integrity.
- Reusing IVs/nonces -> risk: catastrophic AEAD failure.
- Homegrown crypto or unreviewed parameter changes -> risk: design flaws.
- Storing keys unprotected in flash -> risk: extraction and compromise.
- Using `rand()` for keys/IVs -> risk: predictable values.

## Verification Checklist
- [ ] Approved algorithms only (AES-GCM/ChaCha20-Poly1305, SHA-256+, P-256/X25519).
- [ ] TLS 1.3 (or hardened 1.2) with cert validation; weak ciphers disabled.
- [ ] HKDF/KDF used; IVs unique per message; no key/IV reuse.
- [ ] Data at rest encrypted; keys protected/bound to device; zeroization applied.
- [ ] Secure RNG/DRBG used; no `rand()`/LFSR.
- [ ] Vetted crypto library with updates; no homegrown primitives.
- [ ] AEAD or HMAC used for integrity/authentication; AAD/context applied.

## Traceability
- Requirements `REQ-ENC-###` to tests `TEST-ENC-###`; link to security risk controls and SBOM for crypto libs.

## References
- NIST SP 800-56, 800-57, 800-90 (DRBG), 800-38D (GCM).
- IETF RFCs: TLS 1.3 (8446), ChaCha20-Poly1305 (8439), HKDF (5869).
- FIPS 140-2/3 considerations when required.

## Changelog
- 1.0.0 (2026-01-04): Initial encryption skill with AEAD/TLS, KDF, RNG, and key protection guidance.

## Audit History
- **2026-01-04**: Audit performed. Verified:
  - Algorithm recommendations (AES-256-GCM, ChaCha20-Poly1305, SHA-256/384) are current and secure
  - TLS 1.3 preference with hardened TLS 1.2 fallback is accurate
  - NIST SP 800-series references (800-56, 800-57, 800-90, 800-38D) are appropriate
  - HKDF (RFC 5869) reference accurate
  - No deprecated algorithms recommended
