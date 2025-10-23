#ifndef DISPLAY_CONFIG_H
#define DISPLAY_CONFIG_H

#include <stdbool.h>
#include <stdint.h>
#include "display/common.h"

// widget ids
typedef enum {
    WIDGET_MAHA_LOGO,
    WIDGET_MIRYOKU_LOGO,
    WIDGET_LAYER_INDICATOR,
    WIDGET_WPM,
    WIDGET_BATTERY,
    WIDGET_SIGNAL,
    WIDGET_COUNT
} widget_type_t;

// widget config
typedef struct {
    widget_type_t type;
    bool enabled;
    int16_t v_position;
} widget_config_t;

// screen config
typedef struct {
    widget_config_t widgets[WIDGET_COUNT];
    uint8_t widget_count;
} screen_config_t;

// display config
typedef struct {
    screen_config_t left_screen;
    screen_config_t right_screen;
} display_config_t;

// USER CONFIGURATION - Edit this section
#define LEFT_SCREEN_CONFIG { \
    .widgets = { \
        {WIDGET_BATTERY,          .enabled = true,  .v_position = PADDING+2}, \
        {WIDGET_SIGNAL,           .enabled = true,  .v_position = PADDING+2+15}, \
        {WIDGET_LAYER_INDICATOR,  .enabled = true,  .v_position = 80}, \
        {WIDGET_WPM,              .enabled = true,  .v_position = SCREEN_VER-15}, \
    }, \
    .widget_count = 4 \
}

#define RIGHT_SCREEN_CONFIG { \
    .widgets = { \
        {WIDGET_MIRYOKU_LOGO,     .enabled = true,  .v_position = 4}, \
        {WIDGET_MAHA_LOGO,        .enabled = true,  .v_position = 95}, \
        {WIDGET_BATTERY,          .enabled = true,  .v_position = SCREEN_VER-15}, \
    }, \
    .widget_count = 3 \
}

// init global config
static const display_config_t DISPLAY_CONFIG = {
    .left_screen = LEFT_SCREEN_CONFIG,
    .right_screen = RIGHT_SCREEN_CONFIG
};

#endif