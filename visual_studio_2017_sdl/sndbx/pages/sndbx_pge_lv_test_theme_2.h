/**
 * @file sndbx_pge_lv_test_theme_2.h
 *
 */

#ifndef SNDBX_PGE_LV_TEST_THEME_2_H
#define SNDBX_PGE_LV_TEST_THEME_2_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#ifndef USE_SNDBX_PGE_LV_TEST_THEME_2
#define USE_SNDBX_PGE_LV_TEST_THEME_2 1
#endif
#if USE_SNDBX_PGE_LV_TEST_THEME_2

#include "../src/sndbx.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 * GLOBAL DESCRIPTORS
 **********************/
extern const sndbx_pge_dsc_t sndbx_pge_lv_test_theme_2_dsc;

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/**
 * Create a sandbox test application
 */
extern void sndbx_pge_lv_test_theme_2_test( void );

/**********************
 *      MACROS
 **********************/

#endif /*USE_SNDBX_PGE_LV_TEST_THEME_2*/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* SNDBX_PGE_LV_TEST_THEME_2_H */
