/**
 * @file sndbx.h
 *
 */

#ifndef SNDBX_H
#define SNDBX_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include "sndbx_conf.h"
#ifndef SNDBX_USE_SNDBX
#define SNDBX_USE_SNDBX 1
#endif
#if SNDBX_USE_SNDBX

#ifdef LV_CONF_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif

/*
 * !!! NB !!!,
 * Please note that a page in the sandbox context is NOT a LittlevGL page object
 * It is a page in the sense that is more akin to a web page as viewed in a web browser
 */


/* 
 *	To Do, need to add conditional compilation to ...
 *		sndbx_pge_dsc_t and all app and pge files
 *	#if SNDBX_USE_BTNS ...
 *	#if SNDBX_USE_BTN_SETTINGS	...
 *	#if SNDBX_USE_BTN_INFO	...
 *	#if SNDBX_USE_BTN_INFO	...
 */

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/*Managed page types*/
enum {
	SNDBX_OPT_DEFAULT = false,
	SNDBX_OPT_SCREEN = true,
};
typedef bool sndbx_opt_t;

typedef void (*sndbx_pge_create_cb_t)(lv_obj_t *, void *, const void *);
typedef void (*sndbx_pge_task_cb_t)(void *);
typedef void (*sndbx_pge_destroy_cb_t)(void *);

typedef bool (*sndbx_pge_help_cb_t)(void *, lv_event_t);
typedef bool (*sndbx_pge_settings_cb_t)(void *, lv_event_t);
typedef bool (*sndbx_pge_info_cb_t)(void *, lv_event_t);

typedef struct {
	const char *			name;			/**< Name of page, displayed in the toolbar */	
	uint32_t				mem_size;		/**< How much memory the page needs */
	sndbx_pge_create_cb_t	create_cb;		/**< Called when the page is created */
	sndbx_pge_task_cb_t		task_cb;		/**< Called periodically, set by task_period */
	sndbx_pge_destroy_cb_t	destroy_cb;		/**< Called when the page is destroyed */
	lv_task_prio_t			task_prio;		/**< Task Priority */
	uint32_t				task_period;	/**< How often the task should run */
	sndbx_pge_settings_cb_t	settings_cb;	/**< Called on settings button events */
	sndbx_pge_info_cb_t		info_cb;		/**< Called on info button events */
	sndbx_pge_help_cb_t		help_cb;		/**< Called on help button events */
	sndbx_opt_t				opt;			/**< parent is screen or body container */
} sndbx_pge_dsc_t;

/*Unmanaged page types*/
typedef void (*sndbx_pge_unmngd_prologue_cb_t)(void);
//typedef void *(*sndbx_pge_unmngd_cb_t)(const void*);
//typedef void *(*sndbx_pge_unmngd_cb_t)(void);
typedef void (*sndbx_pge_unmngd_cb_t)(void);
typedef void (*sndbx_pge_unmngd_post_cb_t)(void*);
typedef void (*sndbx_pge_unmngd_epilogue_cb_t)(void);
typedef struct {
	const char *					name;			/**< Name of page, must be NULL */
	sndbx_pge_unmngd_prologue_cb_t	prologue;		/**< Called before call to app */
	sndbx_pge_unmngd_cb_t			app;			/**< Function to create an unmanaged app */
	sndbx_pge_unmngd_post_cb_t		post_app;		/**< Called after call to app */
	sndbx_pge_unmngd_epilogue_cb_t	epilogue;		/**< Function called after page is terminated */
	lv_opa_t						ret_btn_opa_scale; /**< return button button opacity, if 0 then do not create */
	lv_align_t						ret_btn_align;	/**< Where to put the the return button */
} sndbx_pge_dsc_unmngd_t;

/*Unified page type*/
typedef struct {
	union {
		const sndbx_pge_dsc_t * dsc;			/**< Decscriptor for a sandbox page, implies managed */
		const sndbx_pge_dsc_unmngd_t *dsc_u;	/**< Decscriptor for an unmanaged page */
	};
	const void * prms;							/**< Parameters given to create function if any */
} sndbx_pge_t;

/*Types for common create_cb parameters*/
/*These can be used to create commonly used links*/
typedef struct sndbx_pge_prms_lr {
	struct {
		const sndbx_pge_t * left;
		const sndbx_pge_t * right;
	} links;
} sndbx_pge_prms_lr_t;
typedef struct sndbx_pge_prms_lrud {
	struct {
		const sndbx_pge_t * left;
		const sndbx_pge_t * right;
		const sndbx_pge_t * up;
		const sndbx_pge_t * down;
	} links;
} sndbx_pge_prms_lrud_t;

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/**
 * create a sandbox application
 * @param home application home page
 */
extern void sndbx_app_create( const sndbx_pge_t * home );

/**
 * change to another sandbox page, managed or not
 * @param page new page to change to
 */
extern void sndbx_pge_change( const sndbx_pge_t * page );

/**
 * get the active page
 * @return act pointer to current active page
 */
extern const sndbx_pge_t *sndbx_pge_get_act(void);

/**
 * get the active page memory pointer
 * @return memory pointer allocated to the active page
 */
extern void *sndbx_pge_get_mem(void);

/**
 * get the previous active page
 * @return prev pointer to previous active page
 */
extern const sndbx_pge_t *sndbx_pge_get_prev(void);


/**
 * get the task for the active sandbox page, applies to managed pages
 * @return page_task active page task or NULL if not running
 */
extern lv_task_t * sndbx_task_get( void );

/**
 * enable/disable sandbox help button
 * @param en true: enable the help button
 */
extern void sndbx_help_btn_enable_set( bool en );

/**
 * enable/disable sandbox info button
 * @param en true: enable the info button
 */
extern void sndbx_info_btn_enable_set( bool en );

/**
 * enable/disable sandbox settings button
 * @param en true: enable the settings button
 */
extern void sndbx_settings_btn_enable_set( bool en );

/**
 * get return button for the active screen, applies only to unmanaged pages
 * @return btn_return pointer to active screen return button or NULL if none
 */
extern lv_obj_t * sndbx_return_btn_get(void);

/* Helpers */
/**
  * Helper function. Called to create a link button.
  * @param par parent object, 
  * @param txt text for the button
  * @param pge to link to when button is clicked.
  * @return pointer to created button.
  */
extern lv_obj_t *sndbx_link_btn_create( lv_obj_t *par, const char *txt, const sndbx_pge_t *pge );

/**********************
 *      MACROS
 **********************/

#endif /*SNDBX_USE_SNDBX*/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* SNDBX_H */
