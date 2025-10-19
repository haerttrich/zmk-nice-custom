#include <stdbool.h>
#include <zephyr/kernel.h>  
#include <zmk/display.h>
#include "display/screens/screen_draw.h"

#if IS_ENABLED(CONFIG_ZMK_SPLIT)
#include "display/relay/widget_relay.h"
#endif

lv_obj_t *zmk_display_status_screen() {
    return screen_display();
}

void zmk_display_status_screen_init(void) {
    screen_init();
}
