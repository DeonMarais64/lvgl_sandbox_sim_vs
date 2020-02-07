/**
 * @file sndbx_pge_sndbx_demo.h
 *
 */

#ifndef SNDBX_PGE_SNDBX_DEMO_H
#define SNDBX_PGE_SNDBX_DEMO_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#ifndef USE_SNDBX_PGE_SNDBX_DEMO
#define USE_SNDBX_PGE_SNDBX_DEMO 1
#endif
#if USE_SNDBX_PGE_SNDBX_DEMO

#include "../src/sndbx.h"

/*********************
 *      DEFINES
 *********************/

 /**********************
  * GLOBAL DESCRIPTORS
  **********************/

extern const sndbx_pge_dsc_t sndbx_pge_sndbx_demo_dsc;

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/

extern void sndbx_pge_sndbx_demo_test( void );

/**********************
 *      MACROS
 **********************/

#endif /*USE_SNDBX_PGE_SNDBX_DEMO*/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* SNDBX_PGE_SNDBX_DEMO_H */
