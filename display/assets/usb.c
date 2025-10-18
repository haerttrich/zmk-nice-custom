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

  0x0c, 0x00, 
  0x1f, 0x00, 
  0x1f, 0x00, 
  0x0e, 0x00, 
  0x04, 0x00, 
  0x06, 0x00, 
  0x0f, 0x00, 
  0x1d, 0x80, 
  0x34, 0xc0, 
  0x64, 0x40, 
  0x44, 0xe0, 
  0xe4, 0xe0, 
  0xe4, 0x40, 
  0xe4, 0x00, 
  0x04, 0x00, 
  0x1f, 0x00, 
  0x0e, 0x00, 
  0x04, 0x00, 
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
