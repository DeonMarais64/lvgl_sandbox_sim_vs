/**
 * @file sndbx_app_.h
 *
 */

#ifndef SNDBX_APP__H
#define SNDBX_APP__H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#ifndef USE_SNDBX_APP_
#define USE_SNDBX_APP_ 1
#endif
#if USE_SNDBX_APP_

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

extern void sndbx_app_( void );

/**********************
 *      MACROS
 **********************/

#endif /*USE_SNDBX_APP_*/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* SNDBX_APP__H */
