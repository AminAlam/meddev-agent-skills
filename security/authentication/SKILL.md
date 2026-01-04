---
skill_id: SEC-AUTH
version: 1.0.0
last_updated: 2026-01-04
applies_to: [Class A, Class B, Class C]
jurisdiction: [Global]
prerequisites: [SEC-ENCRYPTION, REG-ISO14971]
---

# Authentication for Medical Devices

## Purpose
Define secure user/device authentication, session management, and RBAC suitable for medical device risk profiles.

## When to Apply
- User login, device-to-cloud or device-to-device auth, local service access.
- Any control or PHI access path.

## Requirements (testable)
1. Unique Identities: No shared accounts; per-user/per-device identifiers. Rationale: accountability.
2. Credential Protection: Store secrets hashed with strong KDF (argon2/bcrypt/scrypt) for users; protect device keys in secure element/TPM if available. Rationale: resist compromise.
3. MFA Where Feasible: Apply MFA for remote administrative access and high-risk actions. Rationale: reduce takeover risk.
4. Mutual Authentication: Use mTLS or equivalent for device↔server; verify server certs; validate device cert. Rationale: prevent MITM/rogue services.
5. Session Management: Short-lived tokens; refresh with rotation; revoke on logout/compromise; bind tokens to device/user context. Rationale: limit exposure.
6. RBAC: Enforce least privilege roles; gate safety-critical actions to authorized roles; log privilege escalations. Rationale: control misuse.
7. Rate Limiting/Lockout: Apply rate limits to auth endpoints; lockout/backoff on repeated failures (with clinical safety consideration). Rationale: brute-force resistance.

## Recommended Practices
- Use hardware-backed key storage for device identity.
- Rotate credentials/keys; define expiry and revocation process.
- Log auth successes/failures without storing secrets; monitor anomalies.
- Provide offline/maintenance access controls with separate audit trail.

## Patterns
Password hashing (server-side example):
```python
# REQ-AUTH-CRED-01; TEST-AUTH-04
hashed = argon2_hash(password, opslimit=4, memlimit=64*1024)
```

mTLS connection setup (pseudo):
```c
// REQ-AUTH-MTLS-02; TEST-AUTH-06
tls_set_client_cert(ctx, device_cert, device_key);
tls_set_ca(ctx, ca_cert);
tls_require_server_auth(ctx, true);
```

Role check:
```c
// REQ-AUTH-RBAC-03; TEST-AUTH-08
if (!user_has_role(user, ROLE_CLINICIAN)) return ERR_FORBIDDEN;
```

## Anti-Patterns (risks)
- Shared credentials across users/devices -> risk: no accountability.
- Storing passwords in plaintext or weak hash (MD5/SHA1) -> risk: compromise.
- No server cert validation in TLS -> risk: MITM.
- Long-lived bearer tokens without rotation -> risk: replay/takeover.

## Verification Checklist
- [ ] Unique user/device IDs; no shared accounts.
- [ ] Strong password hashing; device keys protected (secure element/TPM if available).
- [ ] MFA applied for high-risk/remote admin actions.
- [ ] Mutual auth for device↔server; server certs validated.
- [ ] Sessions/tokens short-lived; rotation and revocation implemented.
- [ ] RBAC enforced with least privilege; critical actions gated.
- [ ] Rate limiting/backoff/lockout with safety-aware thresholds.
- [ ] Auth events logged (no secrets); anomalies monitored.

## Traceability
- Requirements `REQ-AUTH-###` mapped to tests `TEST-AUTH-###`; link to security risk controls and threat model items.

## References
- NIST SP 800-63 for auth assurance (informative).
- FDA Cybersecurity Premarket Guidance.
- IEC 62443 identity/authentication requirements.

## Changelog
- 1.0.0 (2026-01-04): Initial authentication skill with mTLS, RBAC, MFA, and credential handling.

## Audit History
- **2026-01-04**: Audit performed. Verified:
  - NIST SP 800-63 reference appropriate for authentication assurance levels
  - KDF recommendations (argon2/bcrypt/scrypt) are current best practices
  - mTLS patterns technically accurate
