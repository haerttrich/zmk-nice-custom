#include "display/common.h"
#include "display/util.h"
#include "display/widgets/widget_layer.h"

LV_IMG_DECLARE(bse_0);
LV_IMG_DECLARE(med_1);
LV_IMG_DECLARE(tap_2);
LV_IMG_DECLARE(btn_3);
LV_IMG_DECLARE(nav_4);
LV_IMG_DECLARE(mse_5);
LV_IMG_DECLARE(sym_6);
LV_IMG_DECLARE(num_7);
LV_IMG_DECLARE(fkt_8);

static struct {
    uint8_t current_layer;
    const void *layer_images[9];
    uint8_t n_layers;
} layer_data = {
    .current_layer = 0,
    .layer_images = { &bse_0, &med_1, &tap_2, &btn_3, &nav_4, &mse_5, &sym_6, &num_7, &fkt_8 },
    .n_layers = 9
};

// init layer widget
void widget_layer_indicator_init(uint8_t initial_layer) {
    layer_data.current_layer = initial_layer;
}

// update active layer
void widget_layer_indicator_update(uint8_t layer) {
    if (layer < layer_data.n_layers) layer_data.current_layer = layer;
}

// draw layer widget
void widget_layer_indicator_draw(lv_obj_t *canvas, int16_t v) {
    lv_draw_img_dsc_t img_dsc;
    lv_draw_img_dsc_init(&img_dsc);

    // Draw active layer
    pos_t pos_layer = coordinates_from_vh(v+14, (SCREEN_HOR-34)/2);
    lv_canvas_draw_img(canvas, pos_layer.x, pos_layer.y, layer_data.layer_images[layer_data.current_layer], &img_dsc);
}
