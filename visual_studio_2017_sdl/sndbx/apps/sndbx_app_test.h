/**
 * @file sndbx_app_test.h
 *
 */

#ifndef SNDBX_APP_TEST_H
#define SNDBX_APP_TEST_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#ifndef USE_SNDBX_APP_TEST
#define USE_SNDBX_APP_TEST 1
#endif
#if USE_SNDBX_APP_TEST

#include "../src/sndbx.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/

extern void sndbx_app_test_test( void );

/**********************
 *      MACROS
 **********************/

#endif /*USE_SNDBX_APP_TEST*/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* SNDBX_APP_TEST_H */
