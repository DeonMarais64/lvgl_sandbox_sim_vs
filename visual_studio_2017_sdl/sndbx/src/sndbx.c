/**
 * @file sndbx.c
 *
 */
#if 1
 /*********************
  *      INCLUDES
  *********************/
#include "sndbx.h"
#if SNDBX_USE_SNDBX

#include "sndbx_nav.h"
#include "../fonts/symbol_ext_def.h"

#if SNDBX_USE_MEM_TRACE
#include <stdio.h>
#endif

/*********************
 *      DEFINES
 *********************/ 

/**********************
 *      TYPEDEFS
 **********************/
typedef enum
{
	NAV_PREV,
	NAV_NEXT,
	NAV_HOME,
	NAV_SETTINGS,
	NAV_INFO,
	NAV_HELP,
} nav_t;

/**********************
 *  STATIC PROTOTYPES
 **********************/

static lv_obj_t * btn_create( lv_obj_t * par, const char * txt, nav_t id );
static void btn_disable ( lv_obj_t * btn );
static void btn_enable ( lv_obj_t * btn );
static lv_obj_t * label_create( lv_obj_t * par, const char * txt );

static void header_create ( lv_obj_t * par );
static void body_create ( lv_obj_t * par );

static void buttons_set_correct_state( void );
static void page_set( const sndbx_pge_t * page );
static void page_set_unmanaged(const sndbx_pge_t * page);
static void link_btn_event_handler(lv_obj_t * obj, lv_event_t evt);

#if SNDBX_USE_MEM_TRACE
static void mem_dump(void);
#endif

/**********************
 *  STATIC VARIABLES
 **********************/
static lv_obj_t * header;
static lv_obj_t * body;
static lv_obj_t * lbl_title;

static lv_obj_t * btn_prev;
static lv_obj_t * btn_next;
static lv_obj_t * btn_home;

#if SNDBX_USE_SNDBX
#if SNDBX_USE_BTN_SETTINGS
static lv_obj_t * btn_settings;
#endif
#if SNDBX_USE_BTN_INFO
static lv_obj_t * btn_info;
#endif
#if SNDBX_USE_BTN_HELP
static lv_obj_t * btn_help;
#endif
#endif

static lv_obj_t * btn_return;

static lv_obj_t * scr_sndbx_root;
static lv_obj_t * scr_sndbx;

static const sndbx_pge_t *page_active;

static const sndbx_pge_t *page_home;

static void * page_mem;

static lv_task_t * page_task;

/**********************
 *      MACROS
 **********************/
#if SNDBX_USE_MEM_TRACE
#define MEM_TRACE mem_dump()
#else
#define MEM_TRACE
#endif
#if SNDBX_USE_NAV_TRACE
#define NAV_TRACE sndbx_nav_dump_list()
#else
#define NAV_TRACE
#endif

#define PAGE_IS_MANAGED(pge) (pge->dsc->name!=NULL)

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

/**
 * Create a sandbox application
 * @param home application home page
 */
void sndbx_app_create ( const sndbx_pge_t * home )
{
	if( !home )
		return;
	scr_sndbx_root = lv_disp_get_scr_act(NULL);
	lv_obj_clean( scr_sndbx_root );
	scr_sndbx = lv_obj_create(NULL, NULL);

	MEM_TRACE;	/*See lvgl heap memory usage*/

	sndbx_nav_init();
	page_home = home;

	header_create( scr_sndbx_root );
	body_create( scr_sndbx_root );

	sndbx_nav_page_push(page_home);
	page_set( page_home );
}

/**
 * change to another sandbox page
 * @param page new page to change to
 */
void sndbx_pge_change ( const sndbx_pge_t * page )
{
	if(!page_home )	/*sndbx_app_create has not been called successfully*/
		return;

	if( !page )
		page = page_home;

	if( page == page_active )
		return;

	sndbx_nav_page_branch( page_active, page );
	page_set( page );

	NAV_TRACE;	/*See the navigation list*/
}

/**
 * get the active page
 * @return act pointer to current active page
 */
extern const sndbx_pge_t *sndbx_pge_get_act(void)
{
	return page_active;
}

/**
 * get the active page memory pointer
 * @return memory pointer allocated to the active page
 */
void *sndbx_pge_get_mem(void)
{
	return page_mem;
}

/**
 * get the previous active page
 * @return prev pointer to previous active page
 */
extern const sndbx_pge_t *sndbx_pge_get_prev(void)
{
	return sndbx_nav_page_get_prev(page_active);
}

/**
 * get the task for the active sandbox page, applies to managed pages
 * @return page_task active page task or NULL if not running
 */
lv_task_t * sndbx_task_get( void )
{
	return page_task;
}

/**
 * enable/disable sandbox help button
 * @param en true: enable the help button
 */
void sndbx_help_btn_enable_set( bool en )
{
#if SNDBX_USE_BTN_HELP
	if (!btn_help)
		return;
	if( en )
		btn_enable( btn_help );
	else
		btn_disable( btn_help );
#else
	(void)en;
#endif
}

/**
 * enable/disable sandbox info button
 * @param en true: enable the info button
 */
void sndbx_info_btn_enable_set( bool en )
{
#if SNDBX_USE_BTN_INFO
	if( !btn_info )
		return;
	if( en )
		btn_enable( btn_info );
	else
		btn_disable( btn_info );
#else
	(void)en;
#endif
}

/**
 * enable/disable sandbox settings button
 * @param en true: enable the settings button
 */
void sndbx_settings_btn_enable_set( bool en )
{
#if SNDBX_USE_BTN_SETTINGS
	if (!btn_settings)
		return;
	if( en )
		btn_enable( btn_settings );
	else
		btn_disable( btn_settings );
#else
	(void)en;
#endif
}

/**
 * get return button for the active screen, applies only to unmanaged pages
 * @return btn_return pointer to active screen return button or NULL if none
 */
extern lv_obj_t * sndbx_return_btn_get(void)
{
	return btn_return;
}

/**
  * Helper function. called to create a link button.
  * @param par parent object,
  * @param text for the button
  * @param pge to link to when button is clicked.
  */
lv_obj_t *sndbx_link_btn_create(lv_obj_t *par, const char *txt, const sndbx_pge_t *pge)
{
	if( par == NULL )
		par = lv_disp_get_scr_act(NULL);
	lv_obj_t *btn = lv_btn_create(par, NULL);
	lv_obj_set_user_data(btn, (lv_obj_user_data_t)pge);
	lv_obj_set_event_cb(btn, link_btn_event_handler);
#if LV_USE_ANIMATION && LV_BTN_INK_EFFECT
	lv_btn_set_ink_in_time(btn, 200);
	lv_btn_set_ink_wait_time(btn, 100);
	lv_btn_set_ink_out_time(btn, 500);
#endif
	lv_obj_t * lbl = label_create(btn, txt);
	lv_btn_set_fit(btn, LV_FIT_TIGHT);

	return btn;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

/**
 * lv_task, calls task created in descriptor if not NULL
 */
static void task_cb( lv_task_t * prms )
{
	if( page_active->dsc->task_cb )
		page_active->dsc->task_cb( prms->user_data );
}

/**
 * Instantiate a page
 * @param page page to create
 */
static void page_set ( const sndbx_pge_t * page )
{
	if( !page )
		return;

	lv_obj_t * scr_current = lv_disp_get_scr_act(NULL);
	if( scr_current != scr_sndbx_root )
		if( scr_current != scr_sndbx )
			lv_obj_del(scr_current);

	if (page_active)
	{
		if (PAGE_IS_MANAGED(page_active))
		{
			if (page_active->dsc->opt == SNDBX_OPT_SCREEN)
				lv_obj_clean(scr_sndbx);
			else
				lv_obj_clean(body);

			if (page_task)
				lv_task_del(page_task);
			if (page_active->dsc->destroy_cb)
				page_active->dsc->destroy_cb(page_mem);
			if (page_mem)
				lv_mem_free(page_mem);
		}
		else
		{
			if (page_active->dsc_u->epilogue)
				page_active->dsc_u->epilogue();

			if (scr_current == scr_sndbx)
				lv_obj_clean(scr_sndbx);
		}
	}

	MEM_TRACE;	/*See lvgl heap memory usage*/

	if( !PAGE_IS_MANAGED(page) )
	{
		if( scr_current != scr_sndbx )
			lv_scr_load(scr_sndbx);
		page_set_unmanaged(page);

		return;
	}
	/*else page_set_managed*/
	lv_obj_t * scr_target = page->dsc->opt == SNDBX_OPT_DEFAULT ? scr_sndbx_root : scr_sndbx;
	if (scr_current != scr_target)
		lv_scr_load(scr_target);

	page_active = page;
	btn_return = NULL;	/* No return button, new page is managed and should create its own links */
	if( page_active->dsc->mem_size )
	{
		page_mem = lv_mem_alloc( page_active->dsc->mem_size );
		memset( page_mem, 0, page_active->dsc->mem_size );
	}
	else
		page_mem = NULL;
	if( page->dsc->opt != SNDBX_OPT_SCREEN) /* Pointless setting a name if it is not going to be seen */
		lv_label_set_static_text(lbl_title, page_active->dsc->name);

	buttons_set_correct_state();

	if (page_active->dsc->create_cb)
	{
		lv_obj_t *parent = page->dsc->opt != SNDBX_OPT_SCREEN ? body : scr_sndbx;
		page_active->dsc->create_cb(parent, page_mem, page_active->prms);
	}

	if( page_active->dsc->task_cb )
		page_task = lv_task_create( task_cb,
			page_active->dsc->task_period,
			page_active->dsc->task_prio,
			page_mem
		);
	else
		page_task = NULL;
}

/**
 * Instantiate an unmanaged page
 * @param page page to create
 */
static void page_set_unmanaged(const sndbx_pge_t * page)
{
	if (page->dsc_u->prologue)
		page->dsc_u->prologue();

	const void *prev = page_active;
	page_active = page;

//	void * p = NULL;
	if (page_active->dsc_u->app)
//		p = page_active->dsc_u->app(page_active->prms);
//		p = page_active->dsc_u->app();
		page_active->dsc_u->app();

#if 1
	/* Pointless creating a button if it is not going to be seen */
	if (page_active->dsc_u->ret_btn_opa_scale > LV_OPA_TRANSP)
	{
		btn_return = sndbx_link_btn_create(NULL, LV_SYMBOL_CLOSE, prev);	/*Create a return link */
		lv_obj_align(btn_return, NULL, page_active->dsc_u->ret_btn_align, 0, 0);
		lv_obj_set_top(btn_return, true);
		if (page_active->dsc_u->ret_btn_opa_scale < LV_OPA_COVER)
		{
			lv_obj_set_opa_scale_enable(btn_return, true);
			lv_obj_set_opa_scale(btn_return, page_active->dsc_u->ret_btn_opa_scale);
		}
	}
	else
#endif		
		btn_return = NULL;

	if( page_active->dsc_u->post_app )
//		page_active->dsc_u->post_app(p);
		page_active->dsc_u->post_app(NULL);
}

static void buttons_set_correct_state ( void )
{
	const void *prev, *next;
	if( !sndbx_nav_page_get_prev_next(page_active, &prev, &next) )
	{ /* Error, previous page_active must be in the list  */
		return;
	}

	lv_btn_state_t prev_state = lv_btn_get_state( btn_prev );
	if( !prev )
	{
		if( prev_state != LV_BTN_STATE_INA )
			btn_disable( btn_prev );
	}
	else if( prev_state == LV_BTN_STATE_INA )
		btn_enable( btn_prev );

	lv_btn_state_t next_state = lv_btn_get_state( btn_next );
	if( !next )
	{
		if( next_state != LV_BTN_STATE_INA )
			btn_disable( btn_next );
	}
	else if( next_state == LV_BTN_STATE_INA )
		btn_enable( btn_next );

#if	SNDBX_USE_BTNS
	if( !PAGE_IS_MANAGED(page_active) )
		return;

#if SNDBX_USE_BTN_HELP
	if (btn_help)
	{
		if( page_active->dsc->help_cb )
		{
			if( lv_btn_get_state(btn_help) == LV_BTN_STATE_INA )
				btn_enable(btn_help);
		}
		else if (lv_btn_get_state(btn_help) != LV_BTN_STATE_INA )
				btn_disable(btn_help);
	}
#endif
#if SNDBX_USE_BTN_INFO
	if (btn_info)
	{
		if (page_active->dsc->info_cb)
		{
			if (lv_btn_get_state(btn_info) == LV_BTN_STATE_INA)
				btn_enable(btn_info);
		}
		else if (lv_btn_get_state(btn_info) != LV_BTN_STATE_INA)
			btn_disable(btn_info);
	}
#endif
#if SNDBX_USE_BTN_SETTINGS
	if( btn_settings )
	{
		if (page_active->dsc->settings_cb)
		{
			if (lv_btn_get_state(btn_settings) == LV_BTN_STATE_INA)
				btn_enable(btn_settings);
		}
		else if (lv_btn_get_state(btn_settings) != LV_BTN_STATE_INA)
			btn_disable(btn_settings);
	}
#endif
#endif /*SNDBX_USE_BTNS*/
}

/**
 * Toolbar button event handler
 * @param btn pointer to button
 * @param evt event 
 */
static void btn_event_handler( lv_obj_t *btn, lv_event_t evt )
{
	nav_t id = (nav_t)lv_obj_get_user_data( btn );

#if SNDBX_USE_BTNS
	switch( id ) {
#if SNDBX_USE_BTN_SETTINGS
	case NAV_SETTINGS:
			if( page_active->dsc->settings_cb )
				if( page_active->dsc->settings_cb( page_mem, evt ) )
					btn_disable( btn_settings );
		return;
#endif
#if SNDBX_USE_BTN_INFO
		case NAV_INFO:
			if( page_active->dsc->info_cb )
				if( page_active->dsc->info_cb( page_mem, evt ) )
					btn_disable( btn_info );
		return;
#endif
#if SNDBX_USE_BTN_HELP
		case NAV_HELP:
			if( page_active->dsc->help_cb )
				if( page_active->dsc->help_cb( page_mem, evt ) )
					btn_disable( btn_help );
		return;
#endif
		default:
		break;
	}
#endif /*SNDBX_USE_BTNS*/

	if( evt != LV_EVENT_CLICKED )
		return;

	const void *prev, *next;
	switch( id ) {
		case NAV_PREV:
			if( (prev = sndbx_nav_page_get_prev(page_active)) )
				page_set( prev );
		break;
		case NAV_NEXT:
			if( (next = sndbx_nav_page_get_next(page_active)) )
				page_set( next );
		break;
		case NAV_HOME:
			if( page_active != page_home )
			{
				sndbx_nav_page_branch( page_active, page_home );
				page_set( page_home );
//				sndbx_nav_clean();
			}
		break;
		default:
		break;
	}

	NAV_TRACE;
}

/**
 * Creates the toolbar and adds navigation and settings/info/help buttons if enabled
 * @param par parent for the header container
 */
static void header_create ( lv_obj_t *par )
{
//	header = lv_obj_create( par, NULL );
//	lv_obj_set_style( header, &lv_style_plain );
	header = lv_cont_create( par, NULL );
	lv_obj_set_width( header, lv_obj_get_width(par) );
	lv_obj_set_height( header, lv_obj_get_height(par)/10 );
//	lv_cont_set_layout( header, LV_LAYOUT_ROW_M );	/* Tighter without this */

	btn_prev = btn_create( header, LV_SYMBOL_PREV, NAV_PREV );
	lv_obj_align( btn_prev, NULL, LV_ALIGN_IN_LEFT_MID, 0, 0 );

	btn_next = btn_create( header, LV_SYMBOL_NEXT, NAV_NEXT );
	lv_obj_align( btn_next, btn_prev, LV_ALIGN_OUT_RIGHT_MID, 0, 0 );

	btn_home = btn_create( header, LV_SYMBOL_HOME, NAV_HOME );
	lv_obj_align( btn_home, btn_next, LV_ALIGN_OUT_RIGHT_MID, 0, 0 );
	lbl_title = label_create( header, "" );
	lv_label_set_recolor(lbl_title, true);
	lv_obj_align( lbl_title, btn_home, LV_ALIGN_OUT_RIGHT_MID, 5, 0 );
	lv_obj_set_auto_realign( lbl_title, true );

#if	SNDBX_USE_BTNS
	lv_obj_t * base = NULL;
	lv_align_t align = LV_ALIGN_IN_RIGHT_MID;
#if	SNDBX_USE_BTN_HELP
	btn_help = btn_create(header, SYMBOL_EXT_QUESTION, NAV_HELP);
	lv_obj_align( btn_help, NULL, align, 0, 0 );
	base = btn_help;
	align = LV_ALIGN_OUT_LEFT_MID;
#endif
#if	SNDBX_USE_BTN_INFO
	btn_info = btn_create( header, SYMBOL_EXT_INFO, NAV_INFO );
	lv_obj_align( btn_info, base, align, 0, 0 );
	base = btn_info;
	align = LV_ALIGN_OUT_LEFT_MID;
#endif
#if	SNDBX_USE_BTN_SETTINGS
	btn_settings = btn_create( header, LV_SYMBOL_SETTINGS, NAV_SETTINGS );
	lv_obj_align( btn_settings, base, align, 0, 0 );
#endif
#endif
}

static void body_create ( lv_obj_t *par )
{
//	body = lv_obj_create( par, NULL );
//	lv_obj_set_style( body, &lv_style_plain );
	body = lv_cont_create( par, NULL );
	lv_obj_set_width( body, lv_obj_get_width(par) );
	lv_obj_set_height( body, lv_obj_get_height(par)-lv_obj_get_height(header) );
	lv_obj_align( body, NULL, LV_ALIGN_IN_BOTTOM_MID, 0, 0 );
}

/**
 * create a label
 * @param par parent for the label
 * @param txt text to assign to the label
 */
static lv_obj_t *label_create( lv_obj_t *par, const char *txt )
{
	lv_obj_t * lbl = lv_label_create( par, NULL );
	lv_label_set_static_text( lbl, txt );

	return lbl;
}

/**
 * Disable toolbar button
 */
static void btn_disable ( lv_obj_t *btn )
{
	lv_btn_set_state( btn, LV_BTN_STATE_INA );
	lv_obj_set_click( btn, false );
}

/**
 * Enable toolbar button
 */
static void btn_enable ( lv_obj_t *btn )
{
	lv_btn_set_state( btn, LV_BTN_STATE_REL );
	lv_obj_set_click( btn, true ); 
}

/**
 * Toolbar buttons
 */
static lv_obj_t *btn_create ( lv_obj_t *par, const char *txt, nav_t id )
{
	lv_obj_t *btn = lv_btn_create( par, NULL );
	lv_obj_set_user_data( btn, (lv_obj_user_data_t)id );
	lv_obj_set_event_cb( btn, btn_event_handler );
#if LV_USE_ANIMATION && LV_BTN_INK_EFFECT
	lv_btn_set_ink_in_time( btn, 200 );
	lv_btn_set_ink_wait_time( btn, 100 );
	lv_btn_set_ink_out_time( btn, 500 );
#endif
#if 1
//	lv_coord_t w_par = lv_obj_get_width( par );
	lv_coord_t h_par = lv_obj_get_height( par );
//	lv_obj_set_size( btn, h_par*3/2, h_par );
	lv_obj_set_width( btn, h_par*3/2 );
	lv_obj_set_height( btn, h_par );
#else
	lv_btn_set_fit( btn, LV_FIT_TIGHT );
#endif

	label_create( btn, txt );

	return btn;
}

/**
  * Called when the page is being changed from a link button
  * @param obj button. button creating the event
  * @param obj evt event
  */
static void link_btn_event_handler( lv_obj_t * obj, lv_event_t evt )
{
	if( evt != LV_EVENT_CLICKED )
		return;
	const sndbx_pge_t *page;
	page = lv_obj_get_user_data( obj );
	sndbx_pge_change( page );
}

static void mem_dump(void)
{
	lv_mem_monitor_t mem;
	lv_mem_monitor(&mem);
	printf(
		"LVGL_Heap,\n"
		"            used : %6d, %3d %%\n"
		"            frag : %3d %%\n"
		"    Biggest free : %6d\n"
		, (int)mem.total_size - mem.free_size, mem.used_pct
		, mem.frag_pct
		, (int)mem.free_biggest_size
	);
}

#endif  /*SNDBX_USE_SNDBX*/
#endif