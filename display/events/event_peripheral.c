#if IS_ENABLED(CONFIG_ZMK_SPLIT) && !IS_ENABLED(CONFIG_ZMK_SPLIT_ROLE_CENTRAL)

#include <zmk/events/split_peripheral_status_changed.h>
#include <zmk/split/bluetooth/peripheral.h>

// Connection to central status
static int peripheral_listener(const zmk_event_t *eh) {
    bool connected = zmk_split_bt_peripheral_is_connected();
    widget_peripheral_update(connected);
    screen_set_needs_redraw();
    return ZMK_EV_EVENT_BUBBLE;
}

ZMK_LISTENER(peripheral_listener, peripheral_listener);
ZMK_SUBSCRIPTION(peripheral_listener, zmk_split_peripheral_status_changed);

void event_peripheral_init(void) {
    bool connected = zmk_split_bt_peripheral_is_connected();
    widget_peripheral_init(connected);
}

#endif 