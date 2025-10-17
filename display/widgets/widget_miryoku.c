#include "display/widgets/widget_miryoku.h"
#include "display/common.h"
#include "display/util.h"

// logo has vh dims v: 60, h: 60
LV_IMG_DECLARE(miryoku);

// the widget has dims v: SCREEN_HEIGHT, h: 60, the logo gets centered

// draw maha logo widget
void widget_miryoku_logo_draw(lv_obj_t *canvas, int16_t v) {
    pos_t pos = coordinates_from_vh(v+60, (SCREEN_HOR -60) / 2);

    lv_draw_img_dsc_t img_dsc;
    lv_draw_img_dsc_init(&img_dsc);
    lv_canvas_draw_img(canvas, pos.x, pos.y, &miryoku, &img_dsc);
}