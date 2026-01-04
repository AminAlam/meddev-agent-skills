#include <assert.h>
#include <string.h>
#include "rtos_safety.h"

/* TEST-RTOS-IPC-01: send/recv succeeds when not full/empty. */
static void test_queue_send_recv(void) {
    uint8_t backing[3 * sizeof(uint32_t)] = {0};
    simple_queue_t q;
    assert(queue_init(&q, backing, 3, sizeof(uint32_t)) == true);
    uint32_t v1 = 10, v2 = 20;
    uint32_t out = 0;
    assert(queue_send(&q, &v1) == true);
    assert(queue_send(&q, &v2) == true);
    assert(queue_recv(&q, &out) == true);
    assert(out == v1);
    assert(queue_recv(&q, &out) == true);
    assert(out == v2);
}

/* TEST-RTOS-IPC-02: bounded queue rejects overflow. */
static void test_queue_overflow(void) {
    uint8_t backing[2 * sizeof(uint32_t)] = {0};
    simple_queue_t q;
    assert(queue_init(&q, backing, 2, sizeof(uint32_t)) == true);
    uint32_t v = 0;
    assert(queue_send(&q, &v) == true);
    assert(queue_send(&q, &v) == true);
    assert(queue_send(&q, &v) == false); /* overflow rejected */
}

/* TEST-RTOS-WD-01: watchdog only kicks when healthy. */
static void test_watchdog_gating(void) {
    set_task_health(false);
    assert(service_watchdog_if_healthy() == false);
    assert(watchdog_kicked() == false);
    set_task_health(true);
    assert(service_watchdog_if_healthy() == true);
    assert(watchdog_kicked() == true);
}

int main(void) {
    test_queue_send_recv();
    test_queue_overflow();
    test_watchdog_gating();
    return 0;
}

