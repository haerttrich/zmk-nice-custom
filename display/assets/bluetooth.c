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

#ifndef LV_ATTRIBUTE_IMG_BLUETOOTH
#define LV_ATTRIBUTE_IMG_BLUETOOTH
#endif

const LV_ATTRIBUTE_MEM_ALIGN LV_ATTRIBUTE_LARGE_CONST LV_ATTRIBUTE_IMG_BLUETOOTH uint8_t bluetooth_map[] = {
  0xfe, 0xfe, 0xfe, 0xff, 	/*Color of index 0*/
  0x00, 0x00, 0x00, 0xff, 	/*Color of index 1*/

  0xce, 0x60, 
  0xe4, 0xe0, 
  0x00, 0x00, 
  0x91, 0x20, 
  0xc4, 0x60, 
  0xee, 0xe0, 
};

const lv_img_dsc_t bluetooth = {
  .header.cf = LV_IMG_CF_INDEXED_1BIT,
  .header.always_zero = 0,
  .header.reserved = 0,
  .header.w = 11,
  .header.h = 6,
  .data_size = 20,
  .data = bluetooth_map,
};
