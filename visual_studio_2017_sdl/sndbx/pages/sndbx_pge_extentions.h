/**
 * @file sndbx_pge_extentions.h
 *
 */

#ifndef SNDBX_PGE_EXTENTIONS_H
#define SNDBX_PGE__H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#ifndef USE_SNDBX_PGE_EXTENTIONS
#define USE_SNDBX_PGE_EXTENTIONS 1
#endif
#if USE_SNDBX_PGE_EXTENTIONS

#include "../src/sndbx.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 * GLOBAL DESCRIPTORS
 **********************/
extern const sndbx_pge_dsc_t sndbx_pge_extentions_dsc;

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/**
 * Create a sandbox test application
 */
extern void sndbx_pge_extentions_test( void );

/**********************
 *      MACROS
 **********************/

#endif /*USE_SNDBX_PGE_EXTENTIONS*/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* SNDBX_PGE_EXTENTIONS_H */
