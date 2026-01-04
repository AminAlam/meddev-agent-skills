#ifndef RTOS_SAFETY_H
#define RTOS_SAFETY_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/* Simple bounded queue to illustrate REQ-RTOS-IPC-02. */
typedef struct {
    uint8_t *buf;
    size_t elem_size;
    size_t capacity;
    size_t head;
    size_t tail;
    size_t count;
} simple_queue_t;

bool queue_init(simple_queue_t *q, uint8_t *backing, size_t capacity, size_t elem_size);
bool queue_send(simple_queue_t *q, const void *elem); /* REQ-RTOS-IPC-02 */
bool queue_recv(simple_queue_t *q, void *out);        /* simulated timeout not needed here */

/* Watchdog gating: REQ-FT-WD-01 */
bool critical_tasks_healthy(void);
void set_task_health(bool ok);
bool service_watchdog_if_healthy(void);
bool watchdog_kicked(void); /* test hook */

#endif /* RTOS_SAFETY_H */

