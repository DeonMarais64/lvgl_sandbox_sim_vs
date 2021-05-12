/**
 * @file cbr_prv_test.h
 *
 */

#ifndef CBR_PRV_TEST_H
#define CBR_PRV_TEST_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#ifndef USE_CBR_PRV_TEST
#define USE_CBR_PRV_TEST 1
#endif
#if USE_CBR_PRV_TEST

#include "sndbx/src/sndbx.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 * GLOBAL DESCRIPTORS
 **********************/
extern const sndbx_pge_dsc_t cbr_prv_test_dsc;

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/**
 * Create a sandbox test application
 */
extern void cbr_prv_test_test( void );

/**********************
 *      MACROS
 **********************/

#endif /*USE_CBR_PRV_TEST*/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* CBR_PRV_TEST_H */
