#ifndef COMMON_H
#define COMMON_H

#ifdef CONFIG_ZMK_DISPLAY
    // ZMK environment
    #define IS_ZMK 1
    // keyboard side
    #if !IS_ENABLED(CONFIG_ZMK_SPLIT) || IS_ENABLED(CONFIG_ZMK_SPLIT_ROLE_CENTRAL)
        #define LEFT_DISPLAY 1
    #else
        #define LEFT_DISPLAY 0
    #endif
    #include <zephyr/kernel.h>
    #include <lvgl.h>
#else
    // Simulator environment
    #define IS_ZMK 0
    #include "lvgl/lvgl.h"
#endif

// Layout constants
#define SCREEN_VER 160
#define SCREEN_HOR 68
#define PADDING 4

// color constants
#define COLOR_BG lv_color_black()
#define COLOR_FG lv_color_white()

#endif 