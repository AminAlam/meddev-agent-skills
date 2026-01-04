# BLE Peripheral Example

Demonstrates secure BLE service setup with LE Secure Connections, characteristic permissions, and basic security enabling per BLE medical connectivity skill.

## Applied skills
- `connectivity/ble-medical/SKILL.md` (security mode, GATT perms, validation)
- `security/authentication/SKILL.md` (mutual auth concepts)
- `security/encryption/SKILL.md` (LESC/TLS analogies)
- `documentation/code-comments/SKILL.md` (trace tags)

## Files
- `ble_service.h/.c`: Service init stub with secure characteristic policy.
- `ble_security.c`: Security enablement stub (LE Secure Connections).

## Build (host stub)
```bash
cc -Wall -Wextra -Werror -std=c11 -c ble_service.c
cc -Wall -Wextra -Werror -std=c11 -c ble_security.c
```

## Traceability cues
- Comments include requirement-style tags (e.g., `REQ-BLE-SEC-01`, `REQ-BLE-GATT-02`) near the implementation stubs. Actual platform BLE stack integration would replace the stubs.***
