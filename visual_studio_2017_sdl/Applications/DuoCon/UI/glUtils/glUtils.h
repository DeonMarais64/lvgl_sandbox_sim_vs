#ifndef	GLUTILS_H
#define GLUTILS_H

#include "button.h"
#include "bar.h"
#include "txtNV.h"
#include "txtNVU.h"
#include "kb.h"

#ifndef COLOR_HEX
#define COLOR_HEX(c)	LV_COLOR_MAKE(((U32)((U32)c >> 16) & 0xff), \
                                ((U32)((U32)c >> 8) & 0xff), \
                                ((U32) c & 0xff))
#endif

#define DISP_HOR_SZMM		154
#define DISP_VER_SZMM		86
/* WRT Dots */
#define DISP_DPMM			((LV_HOR_RES_MAX/LV_HOR_SZMM+5)/10)
#define DISP_D2I(dots)		(((dots*10+5)/LV_DPI)/10)
#define DISP_D2MM(dots)		(((dots)*10*LV_HOR_RES_MAX/LV_HOR_SZMM+5)/10)
#define DISP_MM2D(mm)		(((mm)*10*LV_HOR_RES_MAX/154+5)/10)

/* WRT Pixels */
#define DISP_PPMM	DISP_DPMM
#define DISP_P2I	DISP_D2I
#define DISP_P2MM	DISP_D2MM
#define DISP_MM2P	DISP_MM2D

#include "UI/glUtils/symbol_ext_def.h"

#define FONT_SZ_TINY		LV_THEME_DEFAULT_FONT_SMALL
#define FONT_SZ_SMALL		LV_THEME_DEFAULT_FONT_SUBTITLE
#define FONT_SZ_MEDIUM		LV_THEME_DEFAULT_FONT_TITLE

#if (GUI_FONTS_USE == GUI_FONTS_USE_LVGL_DEFAULTS)
	#define FONT_SZ_LARGE		&lv_font_montserrat_28
#elif (GUI_FONTS_USE == GUI_FONTS_USE_MONTSERRAT)
	#define FONT_SZ_LARGE		&lv_font_montserrat_30
#elif (GUI_FONTS_USE == GUI_FONTS_USE_ROBOTO)
	#define FONT_SZ_LARGE		&font_roboto_36
#endif

#define FONT_SZ_HUGE	&font_roboto_nb_80

#if 0
extern lv_style_t stLblTinyBlack;

extern lv_style_t stLblSmallWhite;
extern lv_style_t stLblSmallBlack;

extern lv_style_t stLblMediumBlack;
extern lv_style_t stLblMediumWhite;
extern lv_style_t stLblMediumOrange;

extern lv_style_t stLblLargeWhite;
extern lv_style_t stLblLargeBlack;

extern lv_style_t stLblIcon;

extern lv_style_t stBtnGrey;

extern lv_style_t stLblDispVals;
#endif

extern const char * const lv_btnm_ok[];

#endif
