#include <stdio.h>
#include "display/widgets/widget_battery.h"
#include "display/common.h"
#include "display/util.h"

LV_IMG_DECLARE(bat);
LV_IMG_DECLARE(charging);

static struct {
    uint8_t percentage;
    bool charging;
} battery_data = {
    .percentage = 100,
    .charging = false
};

// Initialize battery widget
void widget_battery_init(uint8_t initial_percentage, bool initial_charging) {
    battery_data.percentage = initial_percentage;
    battery_data.charging = initial_charging;
}

// Update battery data (called by events)
void widget_battery_update(uint8_t percentage, bool charging) {
    battery_data.percentage = percentage;
    battery_data.charging = charging;
}

// Draw battery widget on canvas
void widget_battery_draw(lv_obj_t *canvas, int16_t v) {
    lv_draw_img_dsc_t img_dsc;
    lv_draw_img_dsc_init(&img_dsc);

    // Draw "BAT" label on left
    pos_t pos_bat = coordinates_from_vh(v+9, PADDING);
    lv_canvas_draw_img(canvas, pos_bat.x, pos_bat.y, &bat, &img_dsc);
    
    // Draw charge icon if charging (positioned after "BAT")
    if (battery_data.charging) {
        pos_t pos_charging = coordinates_from_vh(v+11, PADDING+16+2);
        lv_canvas_draw_img(canvas, pos_charging.x, pos_charging.y, &charging, &img_dsc);
    }
    
    // Draw percentage value on right
    pos_t pos_perc = coordinates_from_vh(v+9, SCREEN_HOR-PADDING-18);
    draw_number(canvas, battery_data.percentage, pos_perc);

}