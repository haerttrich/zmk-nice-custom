#include "display/widgets/widget_maha.h"
#include "display/common.h"
#include "display/util.h"

// logo has vh dims v: 48, h: 19
LV_IMG_DECLARE(maha);

// the widget has dims v: SCREEN_HEIGHT, h: 19, the logo gets centered

// draw maha logo widget
void widget_maha_logo_draw(lv_obj_t *canvas, int16_t v) {
    pos_t pos_maha = coordinates_from_vh(v+19, (SCREEN_HOR-48) / 2);

    lv_draw_img_dsc_t img_dsc;
    lv_draw_img_dsc_init(&img_dsc);
    lv_canvas_draw_img(canvas, pos_maha.x, pos_maha.y, &maha, &img_dsc);
}