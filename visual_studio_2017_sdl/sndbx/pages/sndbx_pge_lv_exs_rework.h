/**
 * @file sndbx_pge_exs_rework.h
 *
 */

#ifndef SNDBX_PGE_LV_EXS_REWORK_H
#define SNDBX_PGE_LV_EXS_REWORK_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#ifndef USE_SNDBX_PGE_LV_EXS_REWORK
#define USE_SNDBX_PGE_LV_EXS_REWORK 1
#endif
#if USE_SNDBX_PGE_LV_EXS_REWORK

#include "../src/sndbx.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 * GLOBAL DESCRIPTORS
 **********************/

extern const sndbx_pge_dsc_t sndbx_pge_lv_exs_rework_dsc;

/**********************
 *      TYPEDEFS
 **********************/
typedef struct sndbx_pge_lv_exs_rework_prms {
	struct {
		const sndbx_pge_t * left;
		const sndbx_pge_t * right;
	} links;
	uint8_t index;
} sndbx_pge_lv_exs_rework_prms_t;

/**********************
 * GLOBAL PROTOTYPES
 **********************/

extern void sndbx_pge_lv_exs_rework_test( void );

/**********************
 *      MACROS
 **********************/

#endif /*USE_SNDBX_PGE_LV_EXS_REWORK*/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* SNDBX_PGE_LV_EXS_REWORK_H */
