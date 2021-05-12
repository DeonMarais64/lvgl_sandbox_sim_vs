/**
 * @file gui_table_dynamic.h
 *
 */
#ifndef GUI_TABLE_DYNAMIC_H
#define GUI_TABLE_DYNAMIC_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include "gui_table.h"
#include "Variant-Lib.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

typedef struct {
	eVar_t			vt;
	uint16_t		value_col;
	PCC				pFmt;
	VarAssignDsc_t	va_dsc;
	PCC				cols[4];
} gui_table4_val_dsc_t;
typedef struct {
	lv_obj_t *			table;
	uint8_t				row;
	Var		 			value;
	const gui_table4_val_dsc_t 	*val_dsc;
} gui_disp_val_obj_t;

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/**********************
 *      MACROS
 **********************/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*GUI_TABLE_DYNAMIC_H*/
