#include "screen_layouts.h"
#include "display/common.h"
#include "display/display_config.h"

#include "display/widgets/widget_layer.h"
#include "display/widgets/widget_battery.h"
#include "display/widgets/widget_wpm.h"
#include "display/widgets/widget_signal.h"
#include "display/widgets/widget_miryoku.h"
#include "display/widgets/widget_maha.h"

#include "display/events/event_layer.h"
#include "display/events/event_battery.h"
#include "display/events/event_wpm.h"
#include "display/events/event_signal.h"

static bool needs_redraw = false;
static bool layer_event_initialized = false;
static bool battery_event_initialized = false;
static bool wpm_event_initialized = false;
static bool signal_event_initialized = false;

void screen_set_needs_redraw(void) {
    needs_redraw = true;
}

bool screen_needs_redraw(void) {
    return needs_redraw;
}

void screen_clear_redraw_flag(void) {
    needs_redraw = false;
}

static void draw_widget(lv_obj_t *canvas, widget_config_t *config) {
    if (!config->enabled) return;
    int16_t v = config->v_position;
    
    switch (config->type) {
        case WIDGET_MAHA_LOGO:
            widget_maha_logo_draw(canvas, v);
            break;
            
        case WIDGET_MIRYOKU_LOGO:
            widget_miryoku_logo_draw(canvas, v);
            break;
            
        case WIDGET_LAYER_INDICATOR:
            widget_layer_indicator_draw(canvas, v);
            if (!layer_event_initialized) {
                event_layer_init();
                layer_event_initialized = true;
            }
            break;
            
        case WIDGET_WPM:
            widget_wpm_draw(canvas, v);
            if (!wpm_event_initialized) {
                // event_wpm_init();  // Uncomment when ready
                // wpm_event_initialized = true;
            }
            break;
            
        case WIDGET_BATTERY:
            widget_battery_draw(canvas, v);
            if (!battery_event_initialized) {
                // event_battery_init();  // Uncomment when ready
                // battery_event_initialized = true;
            }
            break;
            
        case WIDGET_SIGNAL:
            widget_signal_draw(canvas, v);
            if (!signal_event_initialized) {
                // event_signal_init();  // Uncomment when ready
                // signal_event_initialized = true;
            }
            break;
            
        default:
            break;
    }
}

void screen_draw_left(lv_obj_t *canvas) {
    for (uint8_t i = 0; i < DISPLAY_CONFIG.left_screen.widget_count; i++) {
        draw_widget(canvas, (widget_config_t *)&DISPLAY_CONFIG.left_screen.widgets[i]);
    }
}

void screen_draw_right(lv_obj_t *canvas) {
    for (uint8_t i = 0; i < DISPLAY_CONFIG.right_screen.widget_count; i++) {
        draw_widget(canvas, (widget_config_t *)&DISPLAY_CONFIG.right_screen.widgets[i]);
    }
}