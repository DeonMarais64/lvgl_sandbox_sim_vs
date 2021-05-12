/**
 * @file sndbx_pge_demo.h
 *
 */

#ifndef SNDBX_PGE_DEMO_H
#define SNDBX_PGE_DEMO_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#ifndef USE_SNDBX_PGE_DEMO
#define USE_SNDBX_PGE_DEMO 1
#endif
#if USE_SNDBX_PGE_DEMO

#include "../src/sndbx.h"

/*********************
 *      DEFINES
 *********************/
#define SNDBX_PGE_DEMO_NB_DSCS 6

/**********************
 * GLOBAL DESCRIPTORS
 **********************/
extern const sndbx_pge_dsc_t sndbx_pge_demo_dscs[SNDBX_PGE_DEMO_NB_DSCS];

/**********************
 *      TYPEDEFS
 **********************/

typedef struct sndbx_pge_demo_prms {
	struct {
		const sndbx_pge_t * left;
		const sndbx_pge_t * right;
	} links;
	const sndbx_pge_dsc_t * self;
} sndbx_pge_demo_prms_t;

/**********************
 * GLOBAL PROTOTYPES
 **********************/

extern void sndbx_pge_demo_test( void );

/**********************
 *      MACROS
 **********************/

#endif /*USE_SNDBX_PGE_DEMO*/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* SNDBX_PGE_DEMO_H */
