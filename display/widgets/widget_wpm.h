#ifndef WIDGET_WPM_H
#define WIDGET_WPM_H

#include <lvgl.h>
#include <stdint.h>

void widget_wpm_init(uint8_t initial_wpm);
void widget_wpm_update(uint8_t wpm);
void widget_wpm_draw(lv_obj_t *canvas, int16_t v);

#endif