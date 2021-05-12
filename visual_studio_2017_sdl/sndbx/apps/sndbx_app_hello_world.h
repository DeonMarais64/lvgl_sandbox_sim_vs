/**
 * @file sndbx_app_hello_world.h
 *
 */

#ifndef SNDBX_APP_HELLO_WORLD_H
#define SNDBX_APP_HELLO_WORLD_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#ifndef USE_SNDBX_APP_HELLO_WORLD
#define USE_SNDBX_APP_HELLO_WORLD 1
#endif
#if USE_SNDBX_APP_HELLO_WORLD

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/
extern void sndbx_app_hello_world( void );

/**********************
 *      MACROS
 **********************/

#endif /*USE_SNDBX_APP_HELLO_WORLD*/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*SNDBX_APP_HELLO_WORLD_H*/
