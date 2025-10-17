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

#ifndef LV_ATTRIBUTE_IMG_WPM
#define LV_ATTRIBUTE_IMG_WPM
#endif

const LV_ATTRIBUTE_MEM_ALIGN LV_ATTRIBUTE_LARGE_CONST LV_ATTRIBUTE_IMG_WPM uint8_t wpm_map[] = {
  0xfe, 0xfe, 0xfe, 0xff, 	/*Color of index 0*/
  0x00, 0x00, 0x00, 0xff, 	/*Color of index 1*/

  0xe0, 
  0x1f, 
  0xe3, 
  0x1f, 
  0xe0, 
  0xff, 
  0x00, 
  0xde, 
  0xde, 
  0xe1, 
  0xff, 
  0x00, 
  0xf9, 
  0xe7, 
  0xf9, 
  0x00, 
};

const lv_img_dsc_t wpm = {
  .header.cf = LV_IMG_CF_INDEXED_1BIT,
  .header.always_zero = 0,
  .header.reserved = 0,
  .header.w = 8,
  .header.h = 16,
  .data_size = 24,
  .data = wpm_map,
};
