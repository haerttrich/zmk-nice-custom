#ifndef WIDGET_BATTERY_H
#define WIDGET_BATTERY_H

#include <lvgl.h>
#include <stdint.h>
#include <stdbool.h>

void widget_battery_init(uint8_t initial_percentage, bool initial_charging);
void widget_battery_update(uint8_t percentage, bool charging);
void widget_battery_draw(lv_obj_t *canvas, int16_t v);

#endif