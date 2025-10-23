#include "display/common.h"
#include "display/events/event_wpm.h"
#include "display/widgets/widget_wpm.h"
#include "display/screens/screen_draw.h"

#ifdef CONFIG_ZMK_DISPLAY
#if !IS_ENABLED(CONFIG_ZMK_SPLIT) || IS_ENABLED(CONFIG_ZMK_SPLIT_ROLE_CENTRAL)

#include <zmk/events/wpm_state_changed.h>
#include <zmk/wpm.h>

static int wpm_listener(const zmk_event_t *eh) {
    uint8_t wpm = zmk_wpm_get_state();
    widget_wpm_update(wpm);
    screen_set_needs_redraw();
    screen_update();

    return ZMK_EV_EVENT_BUBBLE;
}

ZMK_LISTENER(wpm_listener, wpm_listener);
ZMK_SUBSCRIPTION(wpm_listener, zmk_wpm_state_changed);

void event_wpm_init(void) {
    uint8_t wpm = zmk_wpm_get_state();
    widget_wpm_init(wpm);
}

#else
void event_wpm_init(void) {
    widget_wpm_init(0);
}
#endif
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
    screen_update(); 
}

void event_wpm_init(void) {
    widget_wpm_init(45);
    sim_wpm = 45;
    lv_timer_create(sim_wpm_timer_cb, 500, NULL);
}
#endif