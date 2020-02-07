/**
 * @file sndbx_pge_tests.h
 *
 */

#ifndef SNDBX_PGE_LV_TESTS_H
#define SNDBX_PGE_LV_TESTS_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#ifndef USE_SNDBX_PGE_LV_TESTS
#define USE_SNDBX_PGE_LV_TESTS 1
#endif
#if USE_SNDBX_PGE_LV_TESTS

#include "../src/sndbx.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 * GLOBAL DESCRIPTORS
 **********************/

extern const sndbx_pge_dsc_t sndbx_pge_lv_tests_dsc;

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/

extern void sndbx_pge_lv_tests_test( void );

/**********************
 *      MACROS
 **********************/

#endif /*USE_SNDBX_PGE_LV_TESTS*/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* SNDBX_PGE_LV_TESTS_H */
