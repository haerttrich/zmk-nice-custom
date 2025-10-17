#ifndef SCREEN_LAYOUTS_H
#define SCREEN_LAYOUTS_H

#include <lvgl.h>
#include <stdbool.h>

void screen_draw_left(lv_obj_t *canvas);
void screen_draw_right(lv_obj_t *canvas);

void screen_set_needs_redraw(void);
bool screen_needs_redraw(void);
void screen_clear_redraw_flag(void);

#endif