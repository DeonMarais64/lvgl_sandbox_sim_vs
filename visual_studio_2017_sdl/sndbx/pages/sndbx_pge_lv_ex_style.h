/**
 * @file sndbx_pge_ex_style.h
 *
 */

#ifndef SNDBX_PGE_LV_EX_STYLE_H
#define SNDBX_PGE_LV_EX_STYLE_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#ifndef USE_SNDBX_PGE_LV_EX_STYLE
#define USE_SNDBX_PGE_LV_EX_STYLE 1
#endif
#if USE_SNDBX_PGE_LV_EX_STYLE

#include "../src/sndbx.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 * GLOBAL DESCRIPTORS
 **********************/

extern const sndbx_pge_dsc_t sndbx_pge_lv_ex_style_dsc;

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/

extern void sndbx_pge_lv_ex_style_test( void );

/**********************
 *      MACROS
 **********************/

#endif /*USE_SNDBX_PGE_LV_EX_STYLE*/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* SNDBX_PGE_LV_EX_STYLE_H */
