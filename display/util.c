#include "display/util.h"
#include "display/common.h"

pos_t coordinates_from_vh(int16_t v, int16_t h) {
    int16_t x = SCREEN_VER-v-1;
    int16_t y = h;
    pos_t pos = {x, y, v, h};
    return pos;
}

pos_t coordinates_from_xy(int16_t x, int16_t y) {
    int16_t v = SCREEN_VER-x-1;
    int16_t h = y;
    pos_t pos = {x, y, v, h};
    return pos;
}

pos_t coordinates_shift(pos_t pos, int16_t vshift, int16_t hshift) {
    return coordinates_from_vh(pos.v+vshift, pos.h+hshift);
}

LV_IMG_DECLARE(digit_0);
LV_IMG_DECLARE(digit_1);
LV_IMG_DECLARE(digit_2);
LV_IMG_DECLARE(digit_3);
LV_IMG_DECLARE(digit_4);
LV_IMG_DECLARE(digit_5);
LV_IMG_DECLARE(digit_6);
LV_IMG_DECLARE(digit_7);
LV_IMG_DECLARE(digit_8);
LV_IMG_DECLARE(digit_9);

const void *digits[10] = {
    &digit_0, 
    &digit_1, 
    &digit_2, 
    &digit_3, 
    &digit_4, 
    &digit_5,
    &digit_6,
    &digit_7,
    &digit_8,
    &digit_9
};

void draw_number(lv_obj_t *canvas, uint8_t number, pos_t pos) {
    lv_draw_img_dsc_t img_dsc;
    lv_draw_img_dsc_init(&img_dsc);

    uint8_t d0 = number % 10;
    uint8_t d1 = (number % 100) / 10;
    uint8_t d2 = number / 100;

    // span is always 18 = 5*3+2, digits shifted by 12, 6, 0
    lv_canvas_draw_img(canvas, pos.x, pos.y+12, digits[d0], &img_dsc);
    if ((d2 != 0 && d1 == 0) || d1 != 0) lv_canvas_draw_img(canvas, pos.x, pos.y+6, digits[d1], &img_dsc);
    if (d2 != 0) lv_canvas_draw_img(canvas, pos.x, pos.y, digits[d2], &img_dsc);
}
