/**
 * @file cbr_prv_tests.h
 *
 *
 */

#ifndef CBR_PRV_TESTS_H
#define CBR_PRV_TESTS_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#ifndef USE_CBR_PRV_TESTS
#define USE_CBR_PRV_TESTS 1
#endif
#if USE_CBR_PRV_TESTS

#include "sndbx/src/sndbx.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 * GLOBAL DESCRIPTORS
 **********************/
extern const sndbx_pge_dsc_t cbr_prv_tests_dsc;

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/**
 * Create a sandbox test application
 */
extern void cbr_prv_tests_test( void );

/**********************
 *      MACROS
 **********************/

#endif /*USE_CBR_PRV_TESTS*/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* CBR_PRV_TESTS_H */
