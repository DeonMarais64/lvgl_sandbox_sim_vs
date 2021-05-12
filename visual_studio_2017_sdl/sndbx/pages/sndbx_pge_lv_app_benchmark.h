/**
 * @file sndbx_pge_lv_app_benchmark.h
 *
 */

#ifndef SNDBX_PGE_LV_APP_BENCHMARK_H
#define SNDBX_PGE_LV_APP_BENCHMARK_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#ifndef USE_SNDBX_PGE_LV_APP_BENCHMARK
#define USE_SNDBX_PGE_LV_APP_BENCHMARK 1
#endif
#if USE_SNDBX_PGE_LV_APP_BENCHMARK

#include "../src/sndbx.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 * GLOBAL DESCRIPTORS
 **********************/
extern const sndbx_pge_dsc_t sndbx_pge_lv_app_benchmark_dsc;

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/**
 * Create a sandbox test application
 */
extern void sndbx_pge_lv_app_benchmark_test( void );

/**********************
 *      MACROS
 **********************/

#endif /*USE_SNDBX_PGE_LV_APP_BENCHMARK*/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* SNDBX_PGE_LV_APP_BENCHMARK_H */
