/**
 * @file sndbx_pge_table.h
 *
 */

#ifndef SNDBX_PGE_TABLE_H
#define SNDBX_PGE_TABLE_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#ifndef USE_SNDBX_PGE_TABLE
#define USE_SNDBX_PGE_TABLE 1
#endif
#if USE_SNDBX_PGE_TABLE

#include "../src/sndbx.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 * GLOBAL DESCRIPTORS
 **********************/
extern const sndbx_pge_dsc_t sndbx_pge_table_dsc;

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/**
 * Create a sandbox test application
 */
extern void sndbx_pge_table_test( void );

/**********************
 *      MACROS
 **********************/

#endif /*USE_SNDBX_PGE_TABLE*/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* SNDBX_PGE_TABLE_H */
