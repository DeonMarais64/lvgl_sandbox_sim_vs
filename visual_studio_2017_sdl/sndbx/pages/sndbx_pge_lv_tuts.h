/**
 * @file sndbx_pge_tuts.h
 *
 */

#ifndef SNDBX_PGE_LV_TUTS_H
#define SNDBX_PGE_LV_TUTS_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#ifndef USE_SNDBX_PGE_LV_TUTS
#define USE_SNDBX_PGE_LV_TUTS 1
#endif
#if USE_SNDBX_PGE_LV_TUTS

#include "../src/sndbx.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 * GLOBAL DESCRIPTORS
 **********************/

extern const sndbx_pge_dsc_t sndbx_pge_lv_tuts_dsc;

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/

extern void sndbx_pge_lv_tuts_test( void );

/**********************
 *      MACROS
 **********************/

#endif /*USE_SNDBX_PGE_LV_TUTS*/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* SNDBX_PGE_LV_TUTS_H */
