#include "display/common.h"
#include "display/display_config.h"
#include "display/screens/screen_layout.h"
#include "display/screens/screen_draw.h"

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

static bool layer_event_initialized = false;
static bool battery_event_initialized = false;
static bool wpm_event_initialized = false;
static bool signal_event_initialized = false;

// Phase 1: Initialize events for widgets (get data, NO drawing)
static void init_widget_event(widget_type_t type) {
    switch (type) {
        case WIDGET_LAYER_INDICATOR:
            if (!layer_event_initialized) {
                event_layer_init();
                layer_event_initialized = true;
            }
            break;
            
        case WIDGET_WPM:
            if (!wpm_event_initialized) {
                event_wpm_init();
                wpm_event_initialized = true;
            }
            break;
            
        case WIDGET_BATTERY:
            if (!battery_event_initialized) {
                event_battery_init();
                battery_event_initialized = true;
            }
            break;
            
        case WIDGET_SIGNAL:
            if (!signal_event_initialized) {
                event_signal_init();
                signal_event_initialized = true;
            }
            break;
            
        default:
            break;
    }
}

// Phase 2: Draw widget (data already initialized)
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
            widget_layer_draw(canvas, v);
            break;
            
        case WIDGET_WPM:
            widget_wpm_draw(canvas, v);
            break;
            
        case WIDGET_BATTERY:
            widget_battery_draw(canvas, v);
            break;
            
        case WIDGET_SIGNAL:
            widget_signal_draw(canvas, v);
            break;
            
        default:
            break;
    }
}

// Initialize all events for left screen (before any drawing)
void screen_init_events_left(void) {
    for (uint8_t i = 0; i < DISPLAY_CONFIG.left_screen.widget_count; i++) {
        init_widget_event(DISPLAY_CONFIG.left_screen.widgets[i].type);
    }
}

// Initialize all events for right screen (before any drawing)
void screen_init_events_right(void) {
    for (uint8_t i = 0; i < DISPLAY_CONFIG.right_screen.widget_count; i++) {
        init_widget_event(DISPLAY_CONFIG.right_screen.widgets[i].type);
    }
}

// Draw left screen (data already initialized)
void screen_draw_left(lv_obj_t *canvas) {
    for (uint8_t i = 0; i < DISPLAY_CONFIG.left_screen.widget_count; i++) {
        widget_config_t *config = (widget_config_t *)&DISPLAY_CONFIG.left_screen.widgets[i];
        draw_widget(canvas, config);
    }
    // Don't call screen_set_needs_redraw() here!
}

// Draw right screen (data already initialized)
void screen_draw_right(lv_obj_t *canvas) {
    for (uint8_t i = 0; i < DISPLAY_CONFIG.right_screen.widget_count; i++) {
        draw_widget(canvas, (widget_config_t *)&DISPLAY_CONFIG.right_screen.widgets[i]);
    }
    // Don't call screen_set_needs_redraw() here!
}