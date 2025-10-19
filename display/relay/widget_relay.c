#include "display/relay/widget_relay.h"
#include "display/relay/widget_relay_service.h"

#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(widget_relay_api, CONFIG_ZMK_LOG_LEVEL);

#if IS_ENABLED(CONFIG_ZMK_SPLIT) && !IS_ENABLED(CONFIG_ZMK_SPLIT_ROLE_CENTRAL)
// ============ PERIPHERAL SIDE ============

#include "display/widgets/widget_layer.h"
#include "display/widgets/widget_wpm.h"
#include "display/widgets/widget_signal.h"
#include "display/screens/screen_draw.h"

// Callback when data arrives from central
static void on_relay_data_received(struct widget_relay_data *data) {
    LOG_INF("Relay received - type: %d, value: %d", data->type, data->value);

    switch (data->type) {
        case WIDGET_RELAY_TYPE_LAYER:
            widget_layer_update(data->value);
            break;
        
        case WIDGET_RELAY_TYPE_WPM:
            widget_wpm_update(data->value);
            break;
        
        case WIDGET_RELAY_TYPE_SIGNAL_USB:
            widget_signal_update_usb(data->value != 0);
            break;
        
        case WIDGET_RELAY_TYPE_SIGNAL_BLE:
            widget_signal_update_conn(data->value != 0);
            break;
        
        case WIDGET_RELAY_TYPE_SIGNAL_PROFILE:
            widget_signal_update_device(data->value);
            break;
        
        default:
            LOG_WRN("Unknown relay type: %d", data->type);
            return;
    }

    // Trigger screen update
    screen_set_needs_redraw();
    screen_update();
}

void widget_relay_init(void) {
    widget_relay_service_init_peripheral(on_relay_data_received);
    LOG_INF("Widget relay initialized (peripheral)");
}

#else
// ============ CENTRAL SIDE ============

void widget_relay_init(void) {
    widget_relay_service_init_central();
    LOG_INF("Widget relay initialized (central)");
}

void widget_relay_send_layer(uint8_t layer) {
    struct widget_relay_data data = {
        .type = WIDGET_RELAY_TYPE_LAYER,
        .value = layer
    };
    widget_relay_send(&data);
}

void widget_relay_send_wpm(uint8_t wpm) {
    struct widget_relay_data data = {
        .type = WIDGET_RELAY_TYPE_WPM,
        .value = wpm
    };
    widget_relay_send(&data);
}

void widget_relay_send_signal_usb(bool connected) {
    struct widget_relay_data data = {
        .type = WIDGET_RELAY_TYPE_SIGNAL_USB,
        .value = connected ? 1 : 0
    };
    widget_relay_send(&data);
}

void widget_relay_send_signal_ble(bool connected) {
    struct widget_relay_data data = {
        .type = WIDGET_RELAY_TYPE_SIGNAL_BLE,
        .value = connected ? 1 : 0
    };
    widget_relay_send(&data);
}

void widget_relay_send_signal_profile(uint8_t profile) {
    struct widget_relay_data data = {
        .type = WIDGET_RELAY_TYPE_SIGNAL_PROFILE,
        .value = profile
    };
    widget_relay_send(&data);
}

#endif