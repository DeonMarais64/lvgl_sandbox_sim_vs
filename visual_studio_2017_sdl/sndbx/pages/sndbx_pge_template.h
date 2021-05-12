/**
 * @file sndbx_pge_template.h
 *
 */

#ifndef SNDBX_PGE_TEMPLATE_H
#define SNDBX_PGE_TEMPLATE_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#ifndef USE_SNDBX_PGE_TEMPLATE
#define USE_SNDBX_PGE_TEMPLATE 1
#endif
#if USE_SNDBX_PGE_TEMPLATE

#include "../src/sndbx.h"

/*********************
 *      DEFINES
 *********************/
#define SNDBX_PGE_TEMPLATE_NB_DSCS 3

/**********************
 * GLOBAL DESCRIPTORS
 **********************/
extern const sndbx_pge_dsc_t sndbx_pge_template_dscs[SNDBX_PGE_TEMPLATE_NB_DSCS];

/**********************
 *      TYPEDEFS
 **********************/
typedef struct sndbx_pge_template_prms {
	struct {
		const sndbx_pge_t * left;
		const sndbx_pge_t * right;
	} links;
} sndbx_pge_template_prms_t;

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/**
 * Create a sandbox test application
 */
extern void sndbx_pge_template_test( void );

/**********************
 *      MACROS
 **********************/

#endif /*USE_SNDBX_PGE_TEMPLATE*/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* SNDBX_PGE_TEMPLATE_H */
