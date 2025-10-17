#ifdef __has_include
    #if __has_include("lvgl.h")
        #ifndef LV_LVGL_H_INCLUDE_SIMPLE
            #define LV_LVGL_H_INCLUDE_SIMPLE
        #endif
    #endif
#endif

#if defined(LV_LVGL_H_INCLUDE_SIMPLE)
    #include "lvgl.h"
#else
    #include "lvgl/lvgl.h"
#endif


#ifndef LV_ATTRIBUTE_MEM_ALIGN
#define LV_ATTRIBUTE_MEM_ALIGN
#endif

#ifndef LV_ATTRIBUTE_IMG_CHARGING
#define LV_ATTRIBUTE_IMG_CHARGING
#endif

const LV_ATTRIBUTE_MEM_ALIGN LV_ATTRIBUTE_LARGE_CONST LV_ATTRIBUTE_IMG_CHARGING uint8_t charging_map[] = {
  0xff, 0xff, 0xff, 0xff, 	/*Color of index 0*/
  0x00, 0x00, 0x00, 0xff, 	/*Color of index 1*/

  0xf9, 0xe0, 
  0x78, 0xe0, 
  0x9a, 0x60, 
  0xcb, 0x20, 
  0xe3, 0xc0, 
  0xf3, 0xe0, 
};

const lv_img_dsc_t charging = {
  .header.cf = LV_IMG_CF_INDEXED_1BIT,
  .header.always_zero = 0,
  .header.reserved = 0,
  .header.w = 11,
  .header.h = 6,
  .data_size = 20,
  .data = charging_map,
};
