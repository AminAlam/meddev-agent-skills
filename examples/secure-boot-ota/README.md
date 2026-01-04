# Secure Boot + OTA Example

Demonstrates manifest validation, anti-rollback, and safe apply/rollback logic for firmware updates, aligned with:
- `security/secure-boot/SKILL.md`
- `security/secure-ota/SKILL.md`
- `security/key-management/SKILL.md`
- `documentation/traceability/SKILL.md`

## Files
- `secure_boot.h/.c`: Manifest validation, anti-rollback check, and simulated apply.
- `secure_boot_test.c`: Assertions for good/bad manifests, rollback rejection, and failed signatures.

## Build/Test (host)
```bash
cc -Wall -Wextra -Werror -std=c11 -c sample-code/secure_boot.c -o /tmp/secure_boot.o
cc -Wall -Wextra -Werror -std=c11 sample-code/secure_boot_test.c /tmp/secure_boot.o -o /tmp/secure_boot_test
/tmp/secure_boot_test
```

## Traceability cues
- Requirement tags: `REQ-SBOOT-VERIFY-01`, `REQ-OTA-APPLY-02`, `REQ-SBOOT-ROLL-02`.
- Tests tagged with `TEST-SBOOT-*` illustrating verification of signature failure, anti-rollback, and manifest validation.***

