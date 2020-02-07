/**
 * @file sndbx_pge_lv_app_sysmon.h
 *
 */

#ifndef SNDBX_PGE_LV_APP_SYSMON_H
#define SNDBX_PGE_LV_APP_SYSMON_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#ifndef USE_SNDBX_PGE_LV_APP_SYSMON
#define USE_SNDBX_PGE_LV_APP_SYSMON 1
#endif
#if USE_SNDBX_PGE_LV_APP_SYSMON

#include "../src/sndbx.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL DESCRIPTORS
 **********************/

extern const sndbx_pge_dsc_t sndbx_pge_lv_app_sysmon_dsc;

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/**
 * Create a sandbox test application
 */
extern void sndbx_pge_lv_app_sysmon_test( void );


/**********************
 *      MACROS
 **********************/

#endif /*USE_SNDBX_PGE_LV_APP_SYSMON*/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* USE_SNDBX_PGE_LV_APP_SYSMON_H */
