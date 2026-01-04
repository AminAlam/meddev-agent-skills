#ifndef THERAPY_CONTROLLER_H
#define THERAPY_CONTROLLER_H

#include <stdbool.h>
#include <stdint.h>

/* REQ-62304-102: Control shall start only from idle and stop on command.
 * RISK-CTRL-19: Maintain safe state when stop is requested. */

typedef enum {
    TC_OK = 0,
    TC_ERR_INVALID_STATE = -1,
} tc_status_t;

tc_status_t therapy_controller_init(void);
tc_status_t therapy_controller_start(void);
tc_status_t therapy_controller_stop(void);
bool therapy_controller_is_running(void);

#endif /* THERAPY_CONTROLLER_H */
