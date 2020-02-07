/**
 * @file sndbx_app_monolith.h
 *
 */

#ifndef SNDBX_APP_MONOLITH_H
#define SNDBX_APP_MONOLITH_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#ifndef USE_SNDBX_APP_MONOLITH
#define USE_SNDBX_APP_MONOLITH 1
#endif
#if USE_SNDBX_APP_MONOLITH

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/**
 * Create a sandbox application
 */
extern void sndbx_app_monolith_test( void );

/**********************
 *      MACROS
 **********************/

#endif /*USE_SNDBX_APP_MONOLITH*/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* SNDBX_APP_MONOLITH_H */
