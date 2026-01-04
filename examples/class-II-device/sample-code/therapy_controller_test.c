#include <assert.h>
#include "therapy_controller.h"

/* TEST-410 covers REQ-62304-102 start/stop; RISK-CTRL-19 safe stop. */
int main(void) {
    assert(therapy_controller_init() == TC_OK);
    assert(!therapy_controller_is_running());

    assert(therapy_controller_start() == TC_OK);
    assert(therapy_controller_is_running());

    /* Starting again should fail safely. */
    assert(therapy_controller_start() == TC_ERR_INVALID_STATE);

    assert(therapy_controller_stop() == TC_OK);
    assert(!therapy_controller_is_running());

    /* Stopping again should fail safely. */
    assert(therapy_controller_stop() == TC_ERR_INVALID_STATE);

    return 0;
}
