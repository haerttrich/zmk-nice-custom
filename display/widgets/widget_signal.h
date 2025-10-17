#ifndef WIDGET_SIGNAL_H
#define WIDGET_SIGNAL_H

#include <lvgl.h>
#include <stdbool.h>

void widget_signal_init(bool initial_usb, bool initial_connected, uint8_t initial_device) ;
void widget_signal_update_usb(bool usb);
void widget_signal_update_conn(bool connected);
void widget_signal_update_device(uint8_t device);
void widget_signal_draw(lv_obj_t *canvas, int16_t v);

#endif