/**
 * @file sndbx_pge_lv_test_theme_1.h
 *
 */

#ifndef SNDBX_PGE_LV_TEST_THEME_1_H
#define SNDBX_PGE_LV_TEST_THEME_1_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#ifndef USE_SNDBX_PGE_LV_TEST_THEME_1
#define USE_SNDBX_PGE_LV_TEST_THEME_1 1
#endif
#if USE_SNDBX_PGE_LV_TEST_THEME_1

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

extern const sndbx_pge_dsc_t sndbx_pge_lv_test_theme_1_dsc;

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/**
 * Create a sandbox test application
 */
extern void sndbx_pge_lv_test_theme_1_test( void );

/**********************
 *      MACROS
 **********************/

#endif /*USE_SNDBX_PGE_LV_TEST_THEME_1*/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*SNDBX_PGE_LV_TEST_THEME_1_H*/
