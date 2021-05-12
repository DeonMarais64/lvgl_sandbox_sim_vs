/**
 * @file gui_label.h
 *
 */
#ifndef GUI_LABEL_H
#define GUI_LABEL_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#if 0 && defined LV_CONF_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif


/*********************
 *      DEFINES
 *********************/
#define lv_label_set_font	gui_label_set_font
#define lv_label_set_color	gui_label_set_color

#ifndef GUI_LABEL_USE_MACROS
#define GUI_LABEL_USE_MACROS 1
#endif

#if GUI_LABEL_USE_MACROS
#define gui_label_set_font(lbl, font)\
	lv_obj_set_style_local_text_font(lbl, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, font )

#define gui_label_set_color(lbl, color)\
	lv_obj_set_style_local_text_color(lbl, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, color)
#endif

#if LV_COLOR_DEPTH == 16
#define GUI_LABEL_NO_COLOR	LV_COLOR_MAKE(0,8,0)
#endif

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/

#if !GUI_LABEL_USE_MACROS
void gui_label_set_font(lv_obj_t* lbl, const lv_font_t * font);
void gui_label_set_color(lv_obj_t* lbl, lv_color_t color);
#endif

lv_obj_t * gui_label_create(lv_obj_t* parent, const char * txt, const lv_font_t * font );

/**********************
 *      MACROS
 **********************/


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*GUI_LABEL_H*/
