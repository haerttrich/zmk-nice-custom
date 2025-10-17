#include <stdio.h>
#include "display/widgets/widget_battery.h"
#include "display/common.h"
#include "display/util.h"

LV_IMG_DECLARE(bat);

static struct {
    uint8_t percentage;
} battery_data = {
    .percentage = 100,
};

// Initialize battery widget
void widget_battery_init(uint8_t initial_percentage) {
    battery_data.percentage = initial_percentage;
}

// Update battery data (called by events)
void widget_battery_update(uint8_t percentage) {
    battery_data.percentage = percentage;
}

// Draw battery widget on canvas
void widget_battery_draw(lv_obj_t *canvas, int16_t v) {
    lv_draw_img_dsc_t img_dsc;
    lv_draw_img_dsc_init(&img_dsc);

    // Draw "BAT" label on left
    pos_t pos_bat = coordinates_from_vh(v+9, PADDING);
    lv_canvas_draw_img(canvas, pos_bat.x, pos_bat.y, &bat, &img_dsc);
    
    // Draw percentage value on right
    pos_t pos_perc = coordinates_from_vh(v+9, SCREEN_HOR-PADDING-18);
    draw_number(canvas, battery_data.percentage, pos_perc);

}