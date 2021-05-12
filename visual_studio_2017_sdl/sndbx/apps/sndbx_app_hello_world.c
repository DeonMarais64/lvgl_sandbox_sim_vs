/**
 * @file sndbx_app_hello_world.c
 *
 */

 /*********************
  *      INCLUDES
  *********************/
#include "sndbx_app_hello_world.h"
#if USE_SNDBX_APP_HELLO_WORLD

#include "../src/sndbx.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/
static void hello_world(lv_obj_t * parent, void * mem, const void * prms);

/**********************
 *  STATIC VARIABLES
 **********************/

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

/**
 * Create a sandbox application, 
 * The simplist possible example
 */
void sndbx_app_hello_world( void )
{
	static const sndbx_pge_dsc_t dsc = {
		.name = "Hello World",
		.create_cb = hello_world,
	};
	static const sndbx_pge_t app = {
		.dsc = &dsc,
	};
	sndbx_app_create( &app );
}

/**********************
 *   STATIC FUNCTIONS
 **********************/
void hello_world( lv_obj_t * parent, void * mem, const void * prms )
{
	(void)mem;    /* Not used */
	(void)prms;   /* Not used */

	/* Create content */
	lv_obj_t * lbl =  lv_label_create(parent, NULL);

	lv_label_set_text(lbl, "Hello world!");

	lv_obj_align(lbl, NULL, LV_ALIGN_CENTER, 0, 0);
}

#endif  /*USE_SNDBX_APP_HELLO_WORLD*/
