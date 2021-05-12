/**
 * @file gui.h
 *
 */
#ifndef GUI_H
#define GUI_H


#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/

#include "UI/glUtils/gui_btn.h"
#include "UI/glUtils/gui_label.h"
#include "UI/glUtils/gui_table.h"
//#include "UI/glUtils/gui_table_dynamic.h"
//#include "UI/glUtils/gui_control_motor.h"
//#include "UI/glUtils/gui_edit.h"
#include "UI/glUtils/symbol_ext_def.h"

/*********************
 *      DEFINES
 *********************/

#define GUI_RECOLOR(txt,color)  LV_TXT_COLOR_CMD color " " txt LV_TXT_COLOR_CMD

#define GUI_FONT_SZ_TINY		LV_THEME_DEFAULT_FONT_SMALL
#define GUI_FONT_SZ_SMALL		LV_THEME_DEFAULT_FONT_SUBTITLE
#define GUI_FONT_SZ_MEDIUM		LV_THEME_DEFAULT_FONT_TITLE

#if (GUI_FONTS_USE == GUI_FONTS_USE_LVGL_DEFAULTS)
	#define GUI_FONT_SZ_LARGE		&lv_font_montserrat_30
#elif (GUI_FONTS_USE == GUI_FONTS_USE_MONTSERRAT)
	#define GUI_FONT_SZ_LARGE		&lv_font_montserrat_34
#elif (GUI_FONTS_USE == GUI_FONTS_USE_ROBOTO)
	#define GUI_FONT_SZ_LARGE		&font_roboto_36
#endif

#define GUI_FONT_SZ_HUGE	&font_roboto_nb_80


/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/

extern void gui_msgbox( const char * msg, void(*callback)(bool) );

#include "IoDrivers/Ddi.h"

extern void gui_lbl_limits_update( lv_obj_t * lbl, eDdi_Fault_t fault );


/**********************
 *      MACROS
 **********************/


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*GUI_H*/
