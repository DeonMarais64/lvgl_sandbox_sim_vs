/**
 * @file gui_control_motor.h
 *
 */
#ifndef GUI_CONTROL_MOTOR_H
#define GUI_CONTROL_MOTOR_H

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

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/

lv_obj_t* gui_ctrlmotor_rs_create(lv_obj_t* par, lv_event_cb_t event_cb);
lv_obj_t* gui_ctrlmotor_uds_create(lv_obj_t* par, lv_event_cb_t event_cb);

/**********************
 *      MACROS
 **********************/


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*GUI_CONTROL_MOTOR_H*/
