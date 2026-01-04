#include "secure_boot.h"

/* Simple static storage for demo purposes. */
static uint32_t g_stored_version = 0;

uint32_t stored_version(void) {
    return g_stored_version;
}

void set_stored_version(uint32_t v) {
    g_stored_version = v;
}

bool verify_manifest(const manifest_t *m) {
    if (m == NULL) {
        return false;
    }
    if (m->image_len == 0 || m->image_len > m->max_len) {
        return false; /* REQ-SBOOT-VERIFY-01: length bounds */
    }
    if (!m->sig_valid) {
        return false; /* Signature must be valid */
    }
    return true;
}

bool enforce_anti_rollback(const manifest_t *m) {
    return m != NULL && m->version > stored_version();
}

bool apply_update(const manifest_t *m) {
    /* REQ-OTA-APPLY-02: only apply if verified and not rollback. */
    if (!verify_manifest(m)) {
        return false;
    }
    if (!enforce_anti_rollback(m)) {
        return false;
    }
    /* Simulate atomic write and version bump. */
    set_stored_version(m->version);
    return true;
}

