#include "display/widgets/widget_signal.h"
#include "display/common.h"
#include "display/util.h"

LV_IMG_DECLARE(sig);
LV_IMG_DECLARE(usb);
LV_IMG_DECLARE(bluetooth);

static struct {
    bool usb;
    bool connected;
    uint8_t device;
} signal_data = {
    .usb = false,
    .connected = false,
    .device = 0
};


// init signal widget
void widget_signal_init(bool initial_usb, bool initial_connected, uint8_t initial_device) {
    signal_data.usb = initial_usb;
    signal_data.connected = initial_connected;
    signal_data.device = initial_device;
}

// update signal battery
void widget_signal_update_usb(bool usb) {
    signal_data.usb = usb;
}

void widget_signal_update_conn(bool connected) {
    signal_data.connected = connected;
}

void widget_signal_update_device(uint8_t device) {
    signal_data.device = device;
}

// draw signal widget
void widget_signal_draw(lv_obj_t *canvas, int16_t v) {
    lv_draw_img_dsc_t img_dsc;
    lv_draw_img_dsc_init(&img_dsc);

    // Draw "SIG" label on left
    pos_t pos_sig = coordinates_from_vh(v+9, PADDING);
    lv_canvas_draw_img(canvas, pos_sig.x, pos_sig.y, &sig, &img_dsc);

    if (signal_data.usb) {
        pos_t pos_usb = coordinates_from_vh(v+11, SCREEN_HOR-PADDING-18);
        lv_canvas_draw_img(canvas, pos_usb.x, pos_usb.y, &usb, &img_dsc);
    } else if (signal_data.connected) {
        pos_t pos_dev = coordinates_from_vh(v+9, SCREEN_HOR-PADDING-6-18-2);
        draw_number(canvas, signal_data.device, pos_dev);

        pos_t pos_bt = coordinates_from_vh(v+11, SCREEN_HOR-PADDING-6);
        lv_canvas_draw_img(canvas, pos_bt.x, pos_bt.y, &bluetooth, &img_dsc);
    } else {
        pos_t pos_dev = coordinates_from_vh(v+9, SCREEN_HOR-PADDING-6-18-2);
        draw_number(canvas, signal_data.device, pos_dev);

        pos_t pos_bt = coordinates_from_vh(v+11, SCREEN_HOR-PADDING-6);
        lv_canvas_draw_img(canvas, pos_bt.x, pos_bt.y, &bluetooth, &img_dsc);
    }
}