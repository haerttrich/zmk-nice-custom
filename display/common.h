#ifndef COMMON_H
#define COMMON_H

#ifdef CONFIG_ZMK_DISPLAY
    // ZMK environment - include Zephyr first
    #include <zephyr/kernel.h>
    #include <lvgl.h>
    #define IS_ZMK 1
    
    // NOW we can use IS_ENABLED after including zephyr/kernel.h
    #if !IS_ENABLED(CONFIG_ZMK_SPLIT) || IS_ENABLED(CONFIG_ZMK_SPLIT_ROLE_CENTRAL)
        #define LEFT_DISPLAY 1
    #else
        #define LEFT_DISPLAY 0
    #endif
#else
    // Simulator environment
    #define IS_ZMK 0
    #define LEFT_DISPLAY 1  // Default to left for simulator
    #include "lvgl/lvgl.h"
#endif

// Layout constants
#define SCREEN_VER 160
#define SCREEN_HOR 68
#define PADDING 4

// Color constants
#define COLOR_BG lv_color_white()
#define COLOR_FG lv_color_black()

#endif