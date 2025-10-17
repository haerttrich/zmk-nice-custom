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

#ifndef LV_ATTRIBUTE_IMG_USB
#define LV_ATTRIBUTE_IMG_USB
#endif

const LV_ATTRIBUTE_MEM_ALIGN LV_ATTRIBUTE_LARGE_CONST LV_ATTRIBUTE_IMG_USB uint8_t usb_map[] = {
  0xfe, 0xfe, 0xfe, 0xff, 	/*Color of index 0*/
  0x00, 0x00, 0x00, 0xff, 	/*Color of index 1*/

  0xf3, 0xe0, 
  0xe0, 0xe0, 
  0xe0, 0xe0, 
  0xf1, 0xe0, 
  0xfb, 0xe0, 
  0xf9, 0xe0, 
  0xf0, 0xe0, 
  0xe2, 0x60, 
  0xcb, 0x20, 
  0x9b, 0xa0, 
  0xbb, 0x00, 
  0x1b, 0x00, 
  0x1b, 0xa0, 
  0x1b, 0xe0, 
  0xfb, 0xe0, 
  0xe0, 0xe0, 
  0xf1, 0xe0, 
  0xfb, 0xe0, 
};

const lv_img_dsc_t usb = {
  .header.cf = LV_IMG_CF_INDEXED_1BIT,
  .header.always_zero = 0,
  .header.reserved = 0,
  .header.w = 11,
  .header.h = 18,
  .data_size = 44,
  .data = usb_map,
};
