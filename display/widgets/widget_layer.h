#ifndef WIDGET_LAYER_H
#define WIDGET_LAYER_H

#include <lvgl.h>
#include <stdint.h>
#include <stdbool.h>


void widget_layer_init(uint8_t initial_layer);
void widget_layer_update(uint8_t layer);
void widget_layer_draw(lv_obj_t *canvas, int16_t y);

#endif