#ifndef BLE_SERVICE_H
#define BLE_SERVICE_H

#include <stdint.h>
#include <stdbool.h>

/* REQ-BLE-GATT-02: GATT service must enforce authenticated, encrypted access. */

bool ble_service_init(uint16_t service_uuid);

#endif /* BLE_SERVICE_H */
