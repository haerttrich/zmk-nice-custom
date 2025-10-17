#ifndef UTIL_H
#define UTIL_H

#include "display/common.h"


// the screens pixel coordinates
typedef struct {
    int16_t x;
    int16_t y;
    int16_t v;
    int16_t h;
} pos_t;

pos_t coordinates_from_vh(int16_t v, int16_t h);
pos_t coordinates_from_xy(int16_t x, int16_t y);
pos_t coordinates_shift(pos_t pos, int16_t vshift, int16_t hshift);

void draw_number(lv_obj_t *canvas, uint8_t number, pos_t pos);

#endif