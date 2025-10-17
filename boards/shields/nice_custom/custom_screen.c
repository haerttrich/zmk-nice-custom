#include <lvgl.h>
#include <zephyr/logging/log.h>

#include "display/common.h"
#include "display/screens/screen_layouts.h"


LOG_MODULE_DECLARE(zmk, CONFIG_ZMK_LOG_LEVEL);


static lv_color_t canvas_buf[SCREEN_VER * SCREEN_HOR];

void canvas_invert(lv_obj_t *canvas) {
    lv_canvas_set_buffer(canvas, canvas_buf, SCREEN_VER, SCREEN_HOR, LV_IMG_CF_TRUE_COLOR); // existing buffer

    lv_color_t *buf = (lv_color_t *)lv_canvas_get_buffer(canvas);
    for (int i = 0; i < SCREEN_VER * SCREEN_HOR; i++) {
        buf[i].full = ~buf[i].full;  // invert all bits
    }
}

lv_obj_t *zmk_display_status_screen() {
    lv_obj_t *screen = lv_obj_create(NULL);

    // create canvas
    lv_obj_t *canvas = lv_canvas_create(screen);
    lv_canvas_set_buffer(canvas, canvas_buf, SCREEN_VER, SCREEN_HOR, LV_IMG_CF_TRUE_COLOR);

#if LEFT_DISPLAY
    screen_draw_left(canvas);
#else
    screen_draw_right(canvas);
#endif

    // invert canvas
    canvas_invert(canvas);
    lv_obj_invalidate(canvas);

    return screen;
}

void zmk_display_status_screen_init(void) {
    lv_obj_t *screen = zmk_display_status_screen();
    lv_scr_load(screen);
}
