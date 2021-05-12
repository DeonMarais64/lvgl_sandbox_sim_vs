/**
 * @file sndbx_app_monolith.c
 *
 */

 /*********************
  *      INCLUDES
  *********************/
#include "sndbx_app_monolith.h"
#if USE_SNDBX_APP_MONOLITH

#include "../src/sndbx.h"

#include "../pages/sndbx_pge_lv_apps.h"
#include "../pages/sndbx_pge_lv_tuts.h"
#include "../pages/sndbx_pge_lv_tests.h"
#include "../pages/sndbx_pge_lv_exs_rework.h"
#include "../pages/sndbx_pge_sndbx_demo.h"

#include <stdio.h>

/*********************
 *      DEFINES
 *********************/
#define PAGE_NAME "Sandbox Page Selector"

#define NB_APP_PAGES (sizeof(app_pages)/sizeof(app_pages[0]))

/**********************
 *      TYPEDEFS
 **********************/
typedef struct {
	lv_obj_t * parent;
} mem_t;

/**********************
 *  STATIC PROTOTYPES
 **********************/
static void create_cb( lv_obj_t * parent, void * mem, const void * prms );
static bool help_cb( void * p_mem, lv_event_t evt );
static bool settings_cb( void * p_mem, lv_event_t evt );
static bool info_cb( void * p_mem, lv_event_t evt );

static lv_obj_t * label_create( lv_obj_t * par, const char * txt );

static void btnmatrix_event_handler(lv_obj_t * obj, lv_event_t evt);

/**********************
 *  STATIC VARIABLES
 **********************/
/*This page*/
static const sndbx_pge_dsc_t dsc = {
	.name = PAGE_NAME,
	.mem_size = sizeof( mem_t ),
	.create_cb = create_cb,
	.settings_cb = settings_cb,
	.info_cb = info_cb,
	.help_cb = help_cb,
};

/*External pages*/
/* The app should know about the parameters needed by all
 * the disperate pages it is going to use.
 * So create a structure that suites all of them.
 */
typedef struct prms_app_pges {
	struct {
		const sndbx_pge_t * left;
		const sndbx_pge_t * right;
	} links;
	union {
		uint8_t index;
		const sndbx_pge_dsc_t *self;
	};
} prms_app_pges_t;
static const struct prms_app_pges pge_prms[6];

static const sndbx_pge_t app_pages[6] = {
	{.dsc = &sndbx_pge_lv_apps_dsc,.prms = &pge_prms[0] },
	{.dsc = &sndbx_pge_lv_tuts_dsc,.prms = &pge_prms[1] },
	{.dsc = &sndbx_pge_lv_tests_dsc,.prms = &pge_prms[2] },
	{.dsc = &sndbx_pge_lv_exs_rework_dsc,.prms = &pge_prms[3] },
	{.dsc = &sndbx_pge_lv_exs_rework_dsc,.prms = &pge_prms[4] },
	{.dsc = &sndbx_pge_sndbx_demo_dsc,.prms = &pge_prms[5] },
};

static const prms_app_pges_t pge_prms[6] = {
	{.links.left =          NULL, .links.right = &app_pages[1]},
	{.links.left = &app_pages[0], .links.right = &app_pages[2]},
	{.links.left = &app_pages[1], .links.right = &app_pages[3]},
	{.links.left = &app_pages[2], .links.right = &app_pages[4], .index=0},
	{.links.left = &app_pages[3], .links.right = &app_pages[5], .index=1},
	{.links.left = &app_pages[4], .links.right =          NULL, },
};

static const char * const btnmatrix_map[] = {
#if LV_HOR_RES_MAX < 800
	"lv Apps",
	"lv Tutorials", 
	"lv Tests", "\n",
	"lv Examples 1",
	"lv Examples 2",
	"Sandbox Demo",
#else
	"LittlevGL Apps",
	"LittlevGL Tutorials",
	"LittlevGL Tests", "\n",
	"LittlevGL Examples 1", "\n",
	"LittlevGL Examples 2", "\n",
	"Sandbox Demo",
#endif
	"",
};

static const char * const btn_map_ok[] = { "Ok", "" };

/**********************
 *      MACROS
 **********************/
#define MEM_INIT(to,from)	mem_t*(to) = (from)

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

/**
 * Create a sandbox application
 */
void sndbx_app_monolith_test( void )
{
	static const sndbx_pge_t page = {
		.dsc = &dsc,
	};

//	lv_theme_t * th;
//	th = lv_theme_default_init( 0, NULL );
//	lv_theme_set_current( th );
	sndbx_app_create( &page );
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

/**
 * Called when the page is created,
 * @param parent object pointer, lv_container or lv_scr
 * @param p_mem memory pointer, points to memory allocated by the sandbox
 * @param prms create_cb parameters
 */
static void create_cb( lv_obj_t * parent, void * p_mem, const void * prms )
{
	const sndbx_pge_prms_lr_t * pge_prms = prms;
	MEM_INIT(mem, p_mem);
	mem->parent = parent;

	/* Create content */
	lv_coord_t w_par = lv_obj_get_width(parent);
	lv_coord_t h_par = lv_obj_get_height(parent);

	lv_obj_t * lbl = label_create(parent, "Please select a page to open");
	lv_obj_align(lbl, NULL, LV_ALIGN_IN_TOP_MID, 0, LV_DPI / 4);

	lv_obj_t * btnmatrix = lv_btnmatrix_create(parent, NULL);
	lv_btnmatrix_set_map(btnmatrix, (const char **)btnmatrix_map);
	lv_obj_set_size(btnmatrix, w_par * 3 / 4, h_par * 3 / 4);
	lv_obj_align(btnmatrix, lbl, LV_ALIGN_OUT_BOTTOM_MID, 0, LV_DPI / 6);
	lv_obj_set_event_cb(btnmatrix, btnmatrix_event_handler);

	if (pge_prms)
	{	/* Add links to other pages */
		if (pge_prms->links.left)
		{
			lv_obj_t * btn = sndbx_link_btn_create(parent, LV_SYMBOL_LEFT, pge_prms->links.left);
			lv_obj_align(btn, NULL, LV_ALIGN_IN_BOTTOM_LEFT, 0, 0);
		}
		if (pge_prms->links.right)
		{
			lv_obj_t * btn = sndbx_link_btn_create(parent, LV_SYMBOL_RIGHT, pge_prms->links.right);
			lv_obj_align(btn, NULL, LV_ALIGN_IN_BOTTOM_RIGHT, 0, 0);
		}
	}
}

/*===================== Callbacks and Events================== */

/**
 * button matrix event handler, dispatches another sandbox page.
 * @param obj pointer button matrix
 * @param evt event that occurred
 */
static void btnmatrix_event_handler(lv_obj_t * obj, lv_event_t evt)
{
	if (evt != LV_EVENT_CLICKED)
		return;
	uint16_t idx = lv_btnmatrix_get_active_btn(obj);
	if (idx >= NB_APP_PAGES)
		return;
	const sndbx_pge_t *page = &app_pages[idx];
	sndbx_pge_change(page);
}

/*Settings*/
/**
 * settings window event handler
 * @param obj pointer to settings window
 * @param evt event that occurred
 */
static void settings_win_event_handler( lv_obj_t * obj, lv_event_t evt )
{
	if( evt == LV_EVENT_CLICKED )
		sndbx_settings_btn_enable_set( true );

	/*Use built-in close action*/
	lv_win_close_event_cb( obj, evt );
}
/**
 * Called on sandbox settings button events
 * @param p_mem memory pointer, points to memory allocated by the sandbox
 * @return disable settings button if true
 */
static bool settings_cb( void * p_mem, lv_event_t evt )
{
	if( evt != LV_EVENT_CLICKED )
		return false;

	MEM_INIT( mem, p_mem );

	/*Create a window*/
	lv_obj_t * win = lv_win_create( mem->parent, NULL );
	lv_win_set_drag( win, true );

	/*Set the title*/
	lv_win_set_title( win, "Context related settings window" );

	/*Add control button to the header*/
	lv_obj_t * btn_close = lv_win_add_btn( win, LV_SYMBOL_CLOSE );  
	lv_obj_set_user_data( btn_close, p_mem ); /*Not really needed in this case ...*/
											/*..but recomended in case used ... */
											/*.. by the window event */
	lv_obj_set_event_cb( btn_close, settings_win_event_handler );

	lv_coord_t h = lv_obj_get_height( mem->parent ) * 1 / 2;
	lv_coord_t w = lv_obj_get_width( mem->parent ) * 3 / 4;
	lv_obj_set_size( win, w, h );

	/*Add Content*/
//	lv_win_set_layout( win, LV_LAYOUT_PRETTY );

	/*Finally, align window to the bottom of the page*/
	lv_obj_align( win, NULL, LV_ALIGN_IN_BOTTOM_MID, 0, 0 );

	return true;
}

/*Info*/
/**
 * info message box event handler
 * @param obj pointer to info message box
 */
static void info_event_handler( lv_obj_t * obj, lv_event_t evt )
{
	if( evt != LV_EVENT_CLICKED )
		return;
	lv_msgbox_start_auto_close( obj, 0 );

	sndbx_info_btn_enable_set( true );
}
/**
 * Called on sandbox info button events
 * @param p_mem memory pointer, points to memory allocated by the sandbox
 * @return disable info button if true
 */
static bool info_cb( void * p_mem, lv_event_t evt )
{
	if( evt != LV_EVENT_CLICKED )
		return false;

	MEM_INIT( mem, p_mem );

	lv_obj_t * msgbox = lv_msgbox_create( mem->parent, NULL );
	lv_obj_set_drag( msgbox, true );
	char txt[128]; 
	snprintf(txt, 128, 
		"LittlevGL Version : %d.%d.%d %s\n",
		LVGL_VERSION_MAJOR,LVGL_VERSION_MINOR,LVGL_VERSION_PATCH,LVGL_VERSION_INFO
	);

	lv_msgbox_set_text( msgbox, 
//		"Template page info message box\n"
//		"Some information here\n"
		txt
	);
	lv_msgbox_add_btns( msgbox, (const char **)btn_map_ok);
	lv_obj_align( msgbox, NULL, LV_ALIGN_IN_TOP_LEFT, 0, 0 );
	lv_obj_set_event_cb( msgbox, info_event_handler );
	lv_obj_set_user_data( msgbox, p_mem );	/*Not really needed in this case ...*/
											/*..but recomended in case used ... */
											/*.. by the message box event */
	return true;
}

/*Help*/
/**
 * info message box event handler
 * @param obj pointer to help message box
 * @param evt event
 */
static void help_event_handler( lv_obj_t * obj, lv_event_t evt )
{
	if( evt != LV_EVENT_CLICKED )
		return;
	lv_msgbox_start_auto_close( obj, 0 );

	sndbx_help_btn_enable_set( true );
}
/**
 * Called on sandbox help button events
 * @param p_mem memory pointer, points to memory allocated by the sandbox
 * @return disable help button if true
 */
static bool help_cb( void * p_mem, lv_event_t evt )
{
	if( evt != LV_EVENT_CLICKED )
		return false;

	MEM_INIT( mem, p_mem );

	lv_obj_t * msgbox = lv_msgbox_create( mem->parent, NULL );
	lv_obj_set_drag( msgbox, true );
	lv_msgbox_set_text( msgbox,
		"Template page help message box\n" 
		"Some help here\n"
	);
	lv_msgbox_add_btns( msgbox, (const char **)btn_map_ok );
	lv_obj_align( msgbox, NULL, LV_ALIGN_IN_TOP_RIGHT, 0, 0 );

	lv_obj_set_event_cb( msgbox, help_event_handler );
	
	lv_obj_set_user_data(msgbox, p_mem);		/*Not really needed in this case ...*/
											/*..but recomended in case used ... */
											/*.. by the message box event */
	return true;
}

/* Helpers from here */
static lv_obj_t *label_create( lv_obj_t *par, const char *txt )
{
	lv_obj_t * lbl = lv_label_create( par, NULL );
	lv_label_set_static_text( lbl, txt );

	return lbl;
}

#endif  /*USE_SNDBX_APP_MONOLITH*/
