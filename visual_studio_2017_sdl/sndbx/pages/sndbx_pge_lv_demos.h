/**
 * @file sndbx_pge_exs_rework.h
 *
 */

#ifndef SNDBX_PGE_LV_DEMOS_H
#define SNDBX_PGE_LV_DEMOS_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#ifndef USE_SNDBX_PGE_LV_DEMOS
#define USE_SNDBX_PGE_LV_DEMOS 1
#endif
#if USE_SNDBX_PGE_LV_DEMOS

#include "../src/sndbx.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 * GLOBAL DESCRIPTORS
 **********************/

extern const sndbx_pge_dsc_t sndbx_pge_lv_demos_dsc;

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/

extern void sndbx_pge_lv_demos_test( void );

/**********************
 *      MACROS
 **********************/

#endif /*USE_SNDBX_PGE_LV_DEMOS*/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* SNDBX_PGE_LV_DEMOS_H */
