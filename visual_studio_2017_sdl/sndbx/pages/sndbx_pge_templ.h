/**
 * @file sndbx_pge_templ.h
 *
 */

#ifndef SNDBX_PGE_TEMPL_H
#define SNDBX_PGE_TEMPL_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#ifndef USE_SNDBX_PGE_TEMPL
#define USE_SNDBX_PGE_TEMPL 1
#endif
#if USE_SNDBX_PGE_TEMPL

#include "../src/sndbx.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 * GLOBAL DESCRIPTORS
 **********************/
extern const sndbx_pge_dsc_t sndbx_pge_templ_dsc;

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/**
 * Create a sandbox test application
 */
extern void sndbx_pge_templ_test( void );

/**********************
 *      MACROS
 **********************/

#endif /*USE_SNDBX_PGE_TEMPL*/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* SNDBX_PGE_TEMPL_H */
