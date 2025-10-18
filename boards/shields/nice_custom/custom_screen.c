#include <lvgl.h>
#include <zephyr/logging/log.h>

#include "display/common.h"
#include "display/screens/screen_layouts.h"


LOG_MODULE_DECLARE(zmk, CONFIG_ZMK_LOG_LEVEL);


static lv_color_t canvas_buf[SCREEN_VER * SCREEN_HOR];

lv_obj_t *zmk_display_status_screen() {
    lv_obj_t *screen = lv_obj_create(NULL);

    // create canvas
    lv_obj_t *canvas = lv_canvas_create(screen);
    lv_canvas_set_buffer(canvas, canvas_buf, SCREEN_VER, SCREEN_HOR, LV_IMG_CF_TRUE_COLOR);
    lv_canvas_fill_bg(canvas, COLOR_BG, LV_OPA_COVER);

#if LEFT_DISPLAY
    screen_draw_left(canvas);
#else
    screen_draw_right(canvas);
#endif

    return screen;
}

void zmk_display_status_screen_init(void) {
    lv_obj_t *screen = zmk_display_status_screen();
    lv_scr_load(screen);
}
