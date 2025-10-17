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

#ifndef LV_ATTRIBUTE_IMG_SIG
#define LV_ATTRIBUTE_IMG_SIG
#endif

const LV_ATTRIBUTE_MEM_ALIGN LV_ATTRIBUTE_LARGE_CONST LV_ATTRIBUTE_IMG_SIG uint8_t sig_map[] = {
  0xfe, 0xfe, 0xfe, 0xff, 	/*Color of index 0*/
  0x00, 0x00, 0x00, 0xff, 	/*Color of index 1*/

  0xb9, 
  0x76, 
  0x76, 
  0x76, 
  0x8d, 
  0xff, 
  0x7e, 
  0x00, 
  0x7e, 
  0xff, 
  0xff, 
  0x81, 
  0x7e, 
  0x7e, 
  0x6e, 
  0x0d, 
};

const lv_img_dsc_t sig = {
  .header.cf = LV_IMG_CF_INDEXED_1BIT,
  .header.always_zero = 0,
  .header.reserved = 0,
  .header.w = 8,
  .header.h = 16,
  .data_size = 24,
  .data = sig_map,
};
