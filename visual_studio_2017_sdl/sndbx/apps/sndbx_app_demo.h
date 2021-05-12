/**
 * @file sndbx_app_demo.h
 *
 */

#ifndef SNDBX_APP_DEMO_H
#define SNDBX_APP_DEMO_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#ifndef USE_SNDBX_APP_DEMO
#define USE_SNDBX_APP_DEMO 1
#endif
#if USE_SNDBX_APP_DEMO

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

extern void sndbx_app_demo( void );

/**********************
 *      MACROS
 **********************/

#endif /*USE_SNDBX_APP_DEMO*/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* SNDBX_APP_DEMO_H */
