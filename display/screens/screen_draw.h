#ifndef SCREEN_DRAW_H
#define SCREEN_DRAW_H

#include <lvgl.h>
#include <stdbool.h>

void screen_set_needs_redraw(void);
bool screen_needs_redraw(void);
void screen_clear_redraw_flag(void);

lv_obj_t *screen_display(void);
void screen_update(void);
void screen_init(void);


#endif