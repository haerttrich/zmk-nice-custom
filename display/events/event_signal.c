#include "display/events/event_signal.h"
#include "display/common.h"
#include "display/widgets/widget_signal.h"
#include "display/screens/screen_layouts.h"

#if IS_ZMK
#if !IS_ENABLED(CONFIG_ZMK_SPLIT) || IS_ENABLED(CONFIG_ZMK_SPLIT_ROLE_CENTRAL)

#include <zmk/events/ble_active_profile_changed.h>
#include <zmk/ble.h>

#if IS_ENABLED(CONFIG_USB_DEVICE_STACK)
#include <zmk/events/usb_conn_state_changed.h>
#include <zmk/usb.h>
#endif

// USB connection listener
#if IS_ENABLED(CONFIG_USB_DEVICE_STACK)
static int usb_listener(const zmk_event_t *eh) {
    bool connected = zmk_usb_is_powered();
    widget_signal_update_usb(connected);
    screen_set_needs_redraw();
    return ZMK_EV_EVENT_BUBBLE;
}

ZMK_LISTENER(usb_listener, usb_listener);
ZMK_SUBSCRIPTION(usb_listener, zmk_usb_conn_state_changed);
#endif

// BLE connection listener
static int ble_listener(const zmk_event_t *eh) {
    bool connected = zmk_ble_active_profile_is_connected();
    widget_signal_update_conn(connected);
    screen_set_needs_redraw();
    return ZMK_EV_EVENT_BUBBLE;
}

ZMK_LISTENER(ble_listener, ble_listener);
ZMK_SUBSCRIPTION(ble_listener, zmk_ble_active_profile_changed);

// BLE profile/device listener  
static int device_listener(const zmk_event_t *eh) {
    uint8_t device = zmk_ble_active_profile_index();
    widget_signal_update_device(device + 1);
    screen_set_needs_redraw();
    return ZMK_EV_EVENT_BUBBLE;
}

ZMK_LISTENER(device_listener, device_listener);
ZMK_SUBSCRIPTION(device_listener, zmk_ble_active_profile_changed);

void event_signal_init(void) {
#if IS_ENABLED(CONFIG_USB_DEVICE_STACK)
    bool usb_active = zmk_usb_is_powered();
#else
    bool usb_active = false;
#endif
    bool connected = zmk_ble_active_profile_is_connected();
    uint8_t device = zmk_ble_active_profile_index();
    widget_signal_init(usb_active, connected, device + 1);
}

#endif
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