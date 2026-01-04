#ifndef SECURE_BOOT_H
#define SECURE_BOOT_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/* Manifest for an update image. */
typedef struct {
    uint32_t version;      /* monotonic */
    uint32_t image_len;    /* bytes */
    uint32_t max_len;      /* slot capacity */
    bool sig_valid;        /* result of signature check (stubbed here) */
} manifest_t;

/* Stored version counter (would normally be secure storage). */
uint32_t stored_version(void);
void set_stored_version(uint32_t v);

/* Verification and apply pipeline. */
bool verify_manifest(const manifest_t *m);               /* REQ-SBOOT-VERIFY-01 */
bool enforce_anti_rollback(const manifest_t *m);         /* REQ-SBOOT-ROLL-02 */
bool apply_update(const manifest_t *m);                  /* REQ-OTA-APPLY-02 */

#endif /* SECURE_BOOT_H */

