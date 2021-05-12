/**
 * @file sndbx_pge_.h
 *
 */

#ifndef SNDBX_PGE__H
#define SNDBX_PGE__H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#ifndef USE_SNDBX_PGE_
#define USE_SNDBX_PGE_ 1
#endif
#if USE_SNDBX_PGE_

#include "../src/sndbx.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 * GLOBAL DESCRIPTORS
 **********************/
extern const sndbx_pge_dsc_t sndbx_pge__dsc;

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/**
 * Create a sandbox test application
 */
extern void sndbx_pge__test( void );

/**********************
 *      MACROS
 **********************/

#endif /*USE_SNDBX_PGE_*/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* SNDBX_PGE__H */
