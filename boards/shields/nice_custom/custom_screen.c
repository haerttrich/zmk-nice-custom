#include <zmk/display.h>
#include "display/screens/screen_draw.h"


lv_obj_t *zmk_display_status_screen() {
    return screen_display();
}

void zmk_display_status_screen_init(void) {
    screen_init();
}
