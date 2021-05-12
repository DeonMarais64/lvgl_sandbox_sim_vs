/**
 * @file cbe_prv_test.h
 *
 */

#ifndef CBE_PRV_TEST_H
#define CBE_PRV_TEST_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#ifndef USE_CBE_PRV_TEST
#define USE_CBE_PRV_TEST 1
#endif
#if USE_CBE_PRV_TEST

#include "sndbx/src/sndbx.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 * GLOBAL DESCRIPTORS
 **********************/
extern const sndbx_pge_dsc_t cbe_prv_test_dsc;

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/**
 * Create a sandbox test application
 */
extern void cbe_prv_test_test( void );

/**********************
 *      MACROS
 **********************/

#endif /*USE_CBE_PRV_TEST*/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* CBE_PRV_TEST_H */
