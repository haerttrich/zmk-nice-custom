#include "display/events/event_wpm.h"
#include "display/common.h"
#include "display/widgets/widget_wpm.h"
#include "display/screens/screen_layouts.h"

#if IS_ZMK && defined(CONFIG_ZMK_WPM)
/*
#include <zmk/events/wpm_state_changed.h>

static int wpm_listener(const zmk_event_t *eh) {
    ARG_UNUSED(eh);
    const struct zmk_wpm_state_changed *ev = as_zmk_wpm_state_changed(eh);
    widget_wpm_update(ev->state);
    screen_set_needs_redraw();
    return ZMK_EV_EVENT_BUBBLE;
}

ZMK_LISTENER(wpm_listener, wpm_listener);
ZMK_SUBSCRIPTION(wpm_listener, zmk_wpm_state_changed);

void event_wpm_init(void) {
    widget_wpm_init(0);
} */
void event_wpm_init(void) {
    widget_wpm_init(80);
}
#else
#include <lvgl.h>
#include <stdlib.h>

static uint16_t sim_wpm = 0;

static void sim_wpm_timer_cb(lv_timer_t *timer) {
    int change = (rand() % 21) - 10;
    sim_wpm += change;
    if (sim_wpm > 120) sim_wpm = 120;
    if (sim_wpm < 0) sim_wpm = 0;
    widget_wpm_update(sim_wpm);
    screen_set_needs_redraw();
}

void event_wpm_init(void) {
    widget_wpm_init(45);
    sim_wpm = 45;
    lv_timer_create(sim_wpm_timer_cb, 500, NULL);
}
#endif