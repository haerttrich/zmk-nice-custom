#include <stdio.h>
#include "display/widgets/widget_wpm.h"
#include "display/common.h"
#include "display/util.h"

LV_IMG_DECLARE(wpm);

static struct {
    uint8_t value;
} wpm_data = {
    .value = 0,
};


// init battery widget
void widget_wpm_init(uint8_t initial_wpm) {
    wpm_data.value = initial_wpm;
}

// update remaining battery
void widget_wpm_update(uint8_t wpm) {
    wpm_data.value = wpm;
}

// draw battery widget
void widget_wpm_draw(lv_obj_t *canvas, int16_t v) {
    lv_draw_img_dsc_t img_dsc;
    lv_draw_img_dsc_init(&img_dsc);

    // Draw "WPM" label on left
    pos_t pos_wpm = coordinates_from_vh(v+9, PADDING);
    lv_canvas_draw_img(canvas, pos_wpm.x, pos_wpm.y, &wpm, &img_dsc);

    // Draw wpm value on right
    pos_t pos_perc = coordinates_from_vh(v+9, SCREEN_HOR-PADDING-18);
    draw_number(canvas, wpm_data.value, pos_perc);
}