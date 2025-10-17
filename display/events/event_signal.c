#include "display/events/event_signal.h"
#include "display/common.h"
#include "display/widgets/widget_signal.h"
#include "display/screens/screen_layouts.h"

#if IS_ZMK
#include <zmk/events/endpoint_changed.h>
#include <zmk/events/ble_active_profile_changed.h>
#include <zmk/ble.h>
#include <zmk/usb.h>
#include <zmk/endpoints.h>

static int endpoint_listener(const zmk_event_t *eh) {
    bool usb_active = (zmk_endpoints_selected() == ZMK_ENDPOINT_USB);
    widget_signal_update_usb(usb_active);
    screen_set_needs_redraw();
    return ZMK_EV_EVENT_BUBBLE;
}

ZMK_LISTENER(endpoint_listener, endpoint_listener);
ZMK_SUBSCRIPTION(endpoint_listener, zmk_endpoint_changed);

static int ble_listener(const zmk_event_t *eh) {
    bool connected = zmk_ble_active_profile_is_connected();
    widget_signal_update_conn(connected);
    screen_set_needs_redraw();
    return ZMK_EV_EVENT_BUBBLE;
}

ZMK_LISTENER(ble_listener, ble_listener);
ZMK_SUBSCRIPTION(ble_listener, zmk_ble_active_profile_changed);

static int device_listener(const zmk_event_t *eh) {
    const struct zmk_ble_active_profile_changed *ev = as_zmk_ble_active_profile_changed(eh);
    uint8_t device = ev->profile; 
    widget_signal_update_device(device + 1);
    screen_set_needs_redraw();
    return ZMK_EV_EVENT_BUBBLE;
}

ZMK_LISTENER(device_listener, device_listener);
ZMK_SUBSCRIPTION(device_listener, zmk_ble_active_profile_changed);

void event_signal_init(void) {
    bool usb_active = (zmk_endpoints_selected() == ZMK_ENDPOINT_USB);
    bool connected = zmk_ble_active_profile_is_connected();
    uint8_t device = 1;
    widget_signal_init(usb_active, connected, device);
}
#else
#include <lvgl.h>

static bool usb_conn = false;
static bool ble_conn = true;
static uint8_t device = 1;

static void sim_signal_timer_cb(lv_timer_t *timer) {
    usb_conn = !usb_conn;
    device = ((device) % 4) + 1;
    widget_signal_update_usb(usb_conn);
    widget_signal_update_device(device);
    screen_set_needs_redraw();
}

void event_signal_init(void) {
    widget_signal_init(true, true, 1);
    lv_timer_create(sim_signal_timer_cb, 1000, NULL);
}
#endif