#pragma once

#include <stdint.h>

// Widget data types
#define WIDGET_RELAY_TYPE_LAYER          0
#define WIDGET_RELAY_TYPE_WPM            1
#define WIDGET_RELAY_TYPE_SIGNAL_USB     2
#define WIDGET_RELAY_TYPE_SIGNAL_BLE     3
#define WIDGET_RELAY_TYPE_SIGNAL_PROFILE 4

// Initialize relay system
void widget_relay_init(void);

// Central side: Send widget data to peripheral
#if !IS_ENABLED(CONFIG_ZMK_SPLIT) || IS_ENABLED(CONFIG_ZMK_SPLIT_ROLE_CENTRAL)
void widget_relay_send_layer(uint8_t layer);
void widget_relay_send_wpm(uint8_t wpm);
void widget_relay_send_signal_usb(bool connected);
void widget_relay_send_signal_ble(bool connected);
void widget_relay_send_signal_profile(uint8_t profile);
#endif