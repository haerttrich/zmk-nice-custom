#include "display/common.h"
#include "display/events/event_layer.h"
#include "display/widgets/widget_layer.h"
#include "display/screens/screen_draw.h"

#ifdef CONFIG_ZMK_DISPLAY
#if !IS_ENABLED(CONFIG_ZMK_SPLIT) || IS_ENABLED(CONFIG_ZMK_SPLIT_ROLE_CENTRAL)

#include <zmk/events/layer_state_changed.h>
#include <zmk/keymap.h>

static int layer_listener(const zmk_event_t *eh) {
    uint8_t layer = zmk_keymap_highest_layer_active();
    widget_layer_update(layer);
    screen_set_needs_redraw();
    screen_update(); 
    
    return ZMK_EV_EVENT_BUBBLE;
}

ZMK_LISTENER(layer_listener, layer_listener);
ZMK_SUBSCRIPTION(layer_listener, zmk_layer_state_changed);

void event_layer_init(void) {
    uint8_t layer = zmk_keymap_highest_layer_active();
    widget_layer_init(layer);
    screen_set_needs_redraw();
}
#else
// void event_layer_init(void) {
//     widget_layer_init(0); 
//     screen_set_needs_redraw();
// }
#include <zmk/events/layer_state_changed.h>
#include <zmk/keymap.h>

static int layer_listener(const zmk_event_t *eh) {
    uint8_t layer = zmk_keymap_highest_layer_active();
    widget_layer_update(layer);
    screen_set_needs_redraw();
    screen_update(); 
    
    return ZMK_EV_EVENT_BUBBLE;
}

ZMK_LISTENER(layer_listener, layer_listener);
ZMK_SUBSCRIPTION(layer_listener, zmk_layer_state_changed);

void event_layer_init(void) {
    uint8_t layer = zmk_keymap_highest_layer_active();
    widget_layer_init(layer);
    screen_set_needs_redraw();
}
#endif
#else
#include <lvgl.h>

static uint8_t sim_current_layer = 0;

static void sim_layer_timer_cb(lv_timer_t *timer) {
    sim_current_layer = (sim_current_layer + 1) % 9;
    widget_layer_update(sim_current_layer);
    screen_set_needs_redraw();
    screen_update(); 
}

void event_layer_init(void) {
    widget_layer_init(0);
    lv_timer_create(sim_layer_timer_cb, 1000, NULL);
}
#endif