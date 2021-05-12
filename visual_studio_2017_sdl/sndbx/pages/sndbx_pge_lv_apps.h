/**
 * @file sndbx_pge_lv_apps.h
 *
 */

#ifndef SNDBX_PGE_LV_APPS_H
#define SNDBX_PGE_LV_APPS_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#ifndef USE_SNDBX_PGE_LV_APPS
#define USE_SNDBX_PGE_LV_APPS 1
#endif
#if USE_SNDBX_PGE_LV_APPS

#include "../src/sndbx.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 * GLOBAL DESCRIPTORS
 **********************/

extern const sndbx_pge_dsc_t sndbx_pge_lv_apps_dsc;

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/
extern void sndbx_pge_lv_apps_test( void );

/**********************
 *      MACROS
 **********************/

#endif /*USE_SNDBX_PGE_LV_APPS*/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* SNDBX_PGE_LV_APPS_H */
