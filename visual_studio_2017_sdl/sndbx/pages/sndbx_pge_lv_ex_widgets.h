/**
 * @file sndbx_pge_ex_widgets.h
 *
 */

#ifndef SNDBX_PGE_LV_EX_WIDGETS_H
#define SNDBX_PGE_LV_EX_WIDGETS_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#ifndef USE_SNDBX_PGE_LV_EX_WIDGETS
#define USE_SNDBX_PGE_LV_EX_WIDGETS 1
#endif
#if USE_SNDBX_PGE_LV_EX_WIDGETS

#include "../src/sndbx.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 * GLOBAL DESCRIPTORS
 **********************/

extern const sndbx_pge_dsc_t sndbx_pge_lv_ex_widgets_dsc;

/**********************
 *      TYPEDEFS
 **********************/
typedef struct sndbx_pge_lv_ex_widgets_prms {
	struct {
		const sndbx_pge_t * left;
		const sndbx_pge_t * right;
	} links;
	uint8_t index;
} sndbx_pge_lv_ex_widgets_prms_t;

/**********************
 * GLOBAL PROTOTYPES
 **********************/

extern void sndbx_pge_lv_ex_widgets_test( void );

/**********************
 *      MACROS
 **********************/

#endif /*USE_SNDBX_PGE_LV_EX_WIDGETS*/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* SNDBX_PGE_LV_EX_WIDGETS_H */
