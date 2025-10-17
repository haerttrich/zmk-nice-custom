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

#ifndef LV_ATTRIBUTE_IMG_DIGIT_5
#define LV_ATTRIBUTE_IMG_DIGIT_5
#endif

const LV_ATTRIBUTE_MEM_ALIGN LV_ATTRIBUTE_LARGE_CONST LV_ATTRIBUTE_IMG_DIGIT_5 uint8_t digit_5_map[] = {
  0xfe, 0xfe, 0xfe, 0xff, 	/*Color of index 0*/
  0x00, 0x00, 0x00, 0xff, 	/*Color of index 1*/

  0xff, 
  0xb1, 
  0x76, 
  0x76, 
  0x8e, 
};

const lv_img_dsc_t digit_5 = {
  .header.cf = LV_IMG_CF_INDEXED_1BIT,
  .header.always_zero = 0,
  .header.reserved = 0,
  .header.w = 8,
  .header.h = 5,
  .data_size = 13,
  .data = digit_5_map,
};
