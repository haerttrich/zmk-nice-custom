#include "display/events/event_battery.h"
#include "display/common.h"
#include "display/widgets/widget_battery.h"
#include "display/screens/screen_layouts.h"

#if IS_ZMK

#include <zmk/events/battery_state_changed.h>
#include <zmk/battery.h>

static int battery_listener(const zmk_event_t *eh) {
    uint8_t percentage = zmk_battery_state_of_charge();
    widget_battery_update(percentage);
    screen_set_needs_redraw();
    zmk_display_status_screen_update();
    return ZMK_EV_EVENT_BUBBLE;
}

ZMK_LISTENER(battery_listener, battery_listener);
ZMK_SUBSCRIPTION(battery_listener, zmk_battery_state_changed);

void event_battery_init(void) {
    uint8_t percentage = zmk_battery_state_of_charge();
    widget_battery_init(percentage);
    screen_set_needs_redraw();
    zmk_display_status_screen_update();
}
#else
#include <lvgl.h>

static uint8_t sim_battery = 100;

static void sim_battery_timer_cb(lv_timer_t *timer) {
    sim_battery += 5;
    if (sim_battery >= 100) {
        sim_battery = 100;
    }
    widget_battery_update(sim_battery);
    screen_set_needs_redraw();
}

void event_battery_init(void) {
    widget_battery_init(100);
    lv_timer_create(sim_battery_timer_cb, 1000, NULL);
}
#endif