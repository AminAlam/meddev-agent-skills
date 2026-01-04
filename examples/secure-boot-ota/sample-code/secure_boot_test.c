#include <assert.h>
#include "secure_boot.h"

/* TEST-SBOOT-01: valid manifest applies and bumps version. */
static void test_valid_apply(void) {
    manifest_t m = {.version = 5, .image_len = 1024, .max_len = 2048, .sig_valid = true};
    set_stored_version(4);
    assert(apply_update(&m) == true);
    assert(stored_version() == 5);
}

/* TEST-SBOOT-02: reject bad signature. */
static void test_bad_signature(void) {
    manifest_t m = {.version = 6, .image_len = 1024, .max_len = 2048, .sig_valid = false};
    set_stored_version(5);
    assert(apply_update(&m) == false);
    assert(stored_version() == 5);
}

/* TEST-SBOOT-03: reject rollback. */
static void test_rollback_rejected(void) {
    manifest_t m = {.version = 3, .image_len = 1024, .max_len = 2048, .sig_valid = true};
    set_stored_version(5);
    assert(apply_update(&m) == false);
    assert(stored_version() == 5);
}

/* TEST-SBOOT-04: reject oversized image. */
static void test_oversize_rejected(void) {
    manifest_t m = {.version = 7, .image_len = 4096, .max_len = 2048, .sig_valid = true};
    set_stored_version(5);
    assert(apply_update(&m) == false);
    assert(stored_version() == 5);
}

int main(void) {
    test_valid_apply();
    test_bad_signature();
    test_rollback_rejected();
    test_oversize_rejected();
    return 0;
}

