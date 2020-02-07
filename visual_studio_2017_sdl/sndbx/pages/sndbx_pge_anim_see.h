/**
 * @file sndbx_pge_anim_see.h
 *
 */

#ifndef SNDBX_PGE_ANIM_SEE_H
#define SNDBX_PGE_ANIM_SEE_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#ifndef USE_SNDBX_PGE_ANIM_SEE
#define USE_SNDBX_PGE_ANIM_SEE 1
#endif
#if USE_SNDBX_PGE_ANIM_SEE

#include "../src/sndbx.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 * GLOBAL DESCRIPTORS
 **********************/
extern const sndbx_pge_dsc_t sndbx_pge_anim_see_dsc;

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/**
 * Create a sandbox test application
 */
extern void sndbx_pge_anim_see_test( void );

/**********************
 *      MACROS
 **********************/

#endif /*USE_SNDBX_PGE_ANIM_SEE*/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* SNDBX_PGE_ANIM_SEE_H */
