/**
 * @file sndbx_pge_lv_app_demo.h
 *
 */

#ifndef SNDBX_PGE_LV_APP_DEMO_H
#define SNDBX_PGE_LV_APP_DEMO_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#ifndef USE_SNDBX_PGE_LV_APP_DEMO
#define USE_SNDBX_PGE_LV_APP_DEMO 1
#endif
#if USE_SNDBX_PGE_LV_APP_DEMO

#include "../src/sndbx.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL DESCRIPTORS
 **********************/

extern const sndbx_pge_dsc_t sndbx_pge_lv_app_demo_dsc;

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/**
 * Create a sandbox test application
 */
extern void sndbx_pge_lv_app_demo_test( void );

/**********************
 *      MACROS
 **********************/

#endif /*USE_SNDBX_PGE_LV_APP_DEMO*/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*SNDBX_PGE_LV_APP_DEMO_H*/
