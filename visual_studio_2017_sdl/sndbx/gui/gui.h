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

#include "gui_btn.h"
#include "gui_table.h"
#include "gui_control_motor.h"

/*********************
 *      DEFINES
 *********************/
#define GUI_RECOLOR(txt,color)  LV_TXT_COLOR_CMD color " " txt LV_TXT_COLOR_CMD

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/**********************
 *      MACROS
 **********************/


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*GUI_H*/
