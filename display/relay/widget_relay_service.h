#pragma once

#include <zephyr/kernel.h>
#include <zephyr/bluetooth/gatt.h>
#include <stdint.h>

// Widget data packet structure
struct widget_relay_data {
    uint8_t type;    // 0=layer, 1=wpm, 2=signal_usb, 3=signal_ble, 4=signal_profile
    uint8_t value;   // The actual data
} __packed;

// Central side: Register as GATT client to send data
#if !IS_ENABLED(CONFIG_ZMK_SPLIT) || IS_ENABLED(CONFIG_ZMK_SPLIT_ROLE_CENTRAL)
int widget_relay_service_init_central(void);
int widget_relay_send(struct widget_relay_data *data);
#endif

// Peripheral side: Register as GATT server to receive data
#if IS_ENABLED(CONFIG_ZMK_SPLIT) && !IS_ENABLED(CONFIG_ZMK_SPLIT_ROLE_CENTRAL)
typedef void (*widget_relay_callback_t)(struct widget_relay_data *data);
int widget_relay_service_init_peripheral(widget_relay_callback_t callback);
#endif