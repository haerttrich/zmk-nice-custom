#include <lvgl.h>

#include "display/common.h"
#include "display/screens/screen_draw.h"
#include "display/screens/screen_layout.h"


static lv_color_t canvas_buf[SCREEN_VER * SCREEN_HOR];
static lv_obj_t *status_canvas = NULL; 

static bool needs_redraw = false;


void screen_set_needs_redraw(void) {
    needs_redraw = true;
}

bool screen_needs_redraw(void) {
    return needs_redraw;
}

void screen_clear_redraw_flag(void) {
    needs_redraw = false;
}

lv_obj_t *screen_display(void) {
    lv_obj_t *screen = lv_obj_create(NULL);
    lv_obj_t *canvas = lv_canvas_create(screen);
    lv_canvas_set_buffer(canvas, canvas_buf, SCREEN_VER, SCREEN_HOR, LV_IMG_CF_TRUE_COLOR);
    lv_canvas_fill_bg(canvas, COLOR_BG, LV_OPA_COVER);
    status_canvas = canvas;

#if LEFT_DISPLAY
    screen_draw_left(canvas);
#else
    screen_draw_right(canvas);
#endif

    return screen;
}

void screen_update(void) {
    if (status_canvas == NULL) return;
    
    if (screen_needs_redraw()) {
        lv_canvas_fill_bg(status_canvas, COLOR_BG, LV_OPA_COVER);

#if LEFT_DISPLAY
        screen_draw_left(status_canvas);
#else
        screen_draw_right(status_canvas);
#endif
        screen_clear_redraw_flag();
    }
}

void screen_init(void) {
    lv_obj_t *screen = screen_display();
    lv_scr_load(screen);
}

