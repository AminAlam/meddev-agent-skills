#include "therapy_controller.h"

/* Simple state machine to illustrate Class C control with traceability. */

typedef enum {
    TC_STATE_UNINIT = 0,
    TC_STATE_IDLE,
    TC_STATE_RUNNING,
} tc_state_t;

static tc_state_t g_state = TC_STATE_UNINIT;

tc_status_t therapy_controller_init(void) {
    g_state = TC_STATE_IDLE;
    return TC_OK;
}

tc_status_t therapy_controller_start(void) {
    if (g_state != TC_STATE_IDLE) {
        /* REQ-62304-102: start only from idle; safe refusal otherwise. */
        return TC_ERR_INVALID_STATE;
    }
    g_state = TC_STATE_RUNNING;
    return TC_OK;
}

tc_status_t therapy_controller_stop(void) {
    if (g_state != TC_STATE_RUNNING) {
        /* RISK-CTRL-19: stop is idempotent-safe; refuse if not running. */
        return TC_ERR_INVALID_STATE;
    }
    g_state = TC_STATE_IDLE;
    return TC_OK;
}

bool therapy_controller_is_running(void) {
    return g_state == TC_STATE_RUNNING;
}
