#include "rtos_safety.h"
#include <string.h>

static bool g_tasks_ok = true;
static bool g_watchdog_kicked = false;

bool queue_init(simple_queue_t *q, uint8_t *backing, size_t capacity, size_t elem_size) {
    if (!q || !backing || capacity == 0 || elem_size == 0) return false;
    q->buf = backing;
    q->capacity = capacity;
    q->elem_size = elem_size;
    q->head = q->tail = q->count = 0;
    return true;
}

bool queue_send(simple_queue_t *q, const void *elem) {
    if (!q || !elem) return false;
    if (q->count >= q->capacity) {
        return false; /* REQ-RTOS-IPC-02: bounded, fail if full */
    }
    size_t offset = q->tail * q->elem_size;
    memcpy(q->buf + offset, elem, q->elem_size);
    q->tail = (q->tail + 1U) % q->capacity;
    q->count++;
    return true;
}

bool queue_recv(simple_queue_t *q, void *out) {
    if (!q || !out) return false;
    if (q->count == 0) {
        return false;
    }
    size_t offset = q->head * q->elem_size;
    memcpy(out, q->buf + offset, q->elem_size);
    q->head = (q->head + 1U) % q->capacity;
    q->count--;
    return true;
}

bool critical_tasks_healthy(void) {
    return g_tasks_ok;
}

void set_task_health(bool ok) {
    g_tasks_ok = ok;
}

bool service_watchdog_if_healthy(void) {
    /* REQ-FT-WD-01: only kick if tasks are healthy. */
    if (!critical_tasks_healthy()) {
        g_watchdog_kicked = false;
        return false;
    }
    g_watchdog_kicked = true;
    return true;
}

/* Test hook */
bool watchdog_kicked(void) {
    return g_watchdog_kicked;
}

