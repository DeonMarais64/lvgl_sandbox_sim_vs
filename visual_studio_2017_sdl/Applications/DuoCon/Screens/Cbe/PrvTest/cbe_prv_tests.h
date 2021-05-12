/**
 * @file cbe_prv_tests_.h
 *
 */

#ifndef CBE_PRV_TESTS_H
#define CBE_PRV_TESTS_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#ifndef USE_CBE_PRV_TESTS
#define USE_CBE_PRV_TESTS 1
#endif
#if USE_CBE_PRV_TESTS

#include "sndbx/src/sndbx.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 * GLOBAL DESCRIPTORS
 **********************/
extern const sndbx_pge_dsc_t cbe_prv_tests_dsc;

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/**
 * Create a sandbox test application
 */
extern void cbe_prv_tests_test( void );

/**********************
 *      MACROS
 **********************/

#endif /*USE_CBE_PRV_TESTS*/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* CBE_PRV_TESTS_H */
