/**
 * @file sndbx_pge_templ.c
 *
 */

 /*********************
  *      INCLUDES
  *********************/
#include "sndbx_pge_templ.h"
#if USE_SNDBX_PGE_TEMPL

#include <stdio.h>

/*********************
 *      DEFINES
 *********************/
#define PAGE_NAME "Sandbox Templ"

#define TASK_PRIO      LV_TASK_PRIO_LOW
#define TASK_PERIOD    400

/**********************
 *      TYPEDEFS
 **********************/
typedef struct {          /* Memory spec, if required */
	lv_obj_t * parent;
	struct {              /* Task data, if required */
		uint32_t counter;	
		lv_obj_t * lbl;
	} task;
	struct {              /* Settings data, if required */
		bool active;
	} settings;
	struct {              /* Info data, if required */
		bool active;
	} info;
	struct {              /* Help data if required */
		bool active;
	} help;
} mem_t;

/**********************
 *  STATIC PROTOTYPES
 **********************/

static void create_cb( lv_obj_t * parent, void * mem, const void * prms );
static void task_cb( void * p_mem );
static void destroy_cb( void * p_mem );
static bool help_cb( void * p_mem, lv_event_t evt );
static bool settings_cb( void * p_mem, lv_event_t evt );
static bool info_cb( void * p_mem, lv_event_t evt );

/**********************
 *  GLOBAL DESCRIPTORS
 **********************/
const sndbx_pge_dsc_t sndbx_pge_templ_dsc = {
	.name = PAGE_NAME,
	.mem_size = sizeof( mem_t ),
	.create_cb = create_cb,
	.task_cb = task_cb,
	.destroy_cb = destroy_cb,
	.task_prio = TASK_PRIO,
	.task_period = TASK_PERIOD,
	.settings_cb = settings_cb,
	.info_cb = info_cb,
	.help_cb = help_cb,
};

/**********************
 *  STATIC VARIABLES
 **********************/

/**********************
 *      MACROS
 **********************/
#define MEM_INIT(to,from)	mem_t*(to) = (from)

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

/**
 * Create a sandbox test application
 */
void sndbx_pge_templ_test( void )
{
	static const sndbx_pge_t page = {
		.dsc = &sndbx_pge_templ_dsc,
	};

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
	MEM_INIT( mem, p_mem );
	/* Save parent */
	mem->parent = parent;
	/* Unpack page parameters*/
	const sndbx_pge_prms_lr_t * pge_prms = prms;

	/* Create content */
	/* Allocate resources needed to set the page up */
	uint8_t txt_size = 128;
	char * txt = lv_mem_alloc( txt_size );
	lv_obj_t * lbl = lv_label_create( parent, NULL );
	snprintf( txt, txt_size, "Create: Created." );

	lv_label_set_text( lbl, txt );
	lv_label_set_align( lbl, LV_LABEL_ALIGN_CENTER );
	lv_obj_align( lbl, NULL, LV_ALIGN_IN_TOP_MID, 0, LV_DPI/6 );

	/* Free allocated resources needed to set the page up */
	lv_mem_free( txt );

	mem->task.lbl = lv_label_create( parent, NULL );
	lv_label_set_text( mem->task.lbl, "Task: " );
	lv_label_set_align( mem->task.lbl, LV_LABEL_ALIGN_LEFT );
	lv_obj_set_auto_realign( mem->task.lbl, true );
	lv_obj_align( mem->task.lbl, lbl, LV_ALIGN_OUT_BOTTOM_MID, 0, LV_DPI / 6 );

	if( pge_prms )
	{	/* Add links to other pages */
		if( pge_prms->links.left )
		{
			lv_obj_t * btn = sndbx_link_btn_create( parent, LV_SYMBOL_LEFT, pge_prms->links.left );
			lv_obj_align( btn, NULL, LV_ALIGN_IN_BOTTOM_LEFT, 0, 0 );
		}
		if( pge_prms->links.right )
		{
			lv_obj_t * btn = sndbx_link_btn_create( parent, LV_SYMBOL_RIGHT, pge_prms->links.right );
			lv_obj_align( btn, NULL, LV_ALIGN_IN_BOTTOM_RIGHT, 0, 0 );
		}
	}

	/* Initialise all other memory variables that will be used by the task */
}

/**
 * Called periodically, specified by sndbx_pge_dsc_t
 * @param p_mem memory pointer, points to memory allocated by the sandbox
 */
static void task_cb( void * p_mem )
{
	MEM_INIT( mem, p_mem );

	char buf[64];
	snprintf( buf, 64,
		"Task:\n"
		"    Run count %u\n"
		, ++mem->task.counter
	);

	lv_label_set_text( mem->task.lbl, buf );
}

/**
 * Called when the page is being destoyed.
 * @param p_mem memory pointer, points to memory allocated by the sandbox
 */
static void destroy_cb( void * p_mem )
{
	MEM_INIT( mem, p_mem );
	/* Deallocate additional resources allocaed by the page ..*/
	/* .. that would be in create_cb and/or, task_cb. */
	/* .. and/or those created in the settings/info/help callbacks. */

	/* Nothing else to do, parent has already been cleaned */
	/* Memory pointed to by p_mem will be deallocated ...*/
	/* ... by the sandbox handler */
}

/*===================== Callbacks and Events================== */

/*Settings*/
/**
 * settings message box event handler
 * @param obj pointer to settings message box
 * @param evt event
 */
static void settings_event_handler( lv_obj_t * obj, lv_event_t evt )
{
	if( evt != LV_EVENT_CLICKED )
		return;
	lv_mbox_start_auto_close( obj, 0 );

	void * p_mem = lv_obj_get_user_data( obj );
	MEM_INIT( mem, p_mem );
	mem->settings.active = false;
	sndbx_settings_btn_enable_set( true );
}
/**
 * Called on settings button events.
 * @param p_mem memory pointer, points to memory allocated by the sandbox
 * @param evt event
 * @return disable settings button if true
 */
static bool settings_cb( void * p_mem, lv_event_t evt )
{
	if( evt != LV_EVENT_CLICKED )
		return false;

	MEM_INIT( mem, p_mem );
	if( mem->settings.active )
		return false;
	mem->settings.active = true;

	static const char * btns[] = { "Ok", "" };

	lv_obj_t * mbox = lv_mbox_create( mem->parent, NULL );
	lv_obj_set_drag( mbox, true );
	lv_mbox_set_text( mbox,
		"Template page settings message box\n" 
		"Some settings here\n"
	);
	lv_mbox_add_btns( mbox, btns );
	lv_obj_align( mbox, NULL, LV_ALIGN_IN_BOTTOM_MID, 0, 0 );

	lv_obj_set_event_cb( mbox, settings_event_handler );
	lv_obj_set_user_data( mbox, p_mem );

	return true;
}

/*Info*/
/**
 * info message box event handler
 * @param obj pointer to info message box
 * @param evt event
 */
static void info_event_handler( lv_obj_t * obj, lv_event_t evt )
{
	if( evt != LV_EVENT_CLICKED )
		return;
	lv_mbox_start_auto_close( obj, 0 );

	void * p_mem = lv_obj_get_user_data( obj );
	MEM_INIT( mem, p_mem );
	mem->info.active = false;
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
	if( mem->info.active )
		return false;
	mem->info.active = true;

	static const char * btns[] = { "Ok", "" };

	lv_obj_t * mbox = lv_mbox_create( mem->parent, NULL );
	lv_obj_set_drag( mbox, true );
	lv_mbox_set_text( mbox,
		"Template page info message box\n"
		"Some information here\n"
	);
	lv_mbox_add_btns( mbox, btns );
	lv_obj_align( mbox, NULL, LV_ALIGN_IN_TOP_LEFT, 0, 0 );
	lv_obj_set_event_cb( mbox, info_event_handler );
	lv_obj_set_user_data( mbox, p_mem );

	return true;
}

/*Help*/
/**
 * help message box event handler
 * @param obj pointer to help message box
 * @param evt event
 */
static void help_event_handler( lv_obj_t * obj, lv_event_t evt )
{
	if( evt != LV_EVENT_CLICKED )
		return;
	lv_mbox_start_auto_close( obj, 0 );

	void * p_mem = lv_obj_get_user_data( obj );
	MEM_INIT( mem, p_mem );
	mem->help.active = false;
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
	if( mem->help.active )
		return false;
	mem->help.active = true;

	static const char * btns[] = { "Ok", "" };

	lv_obj_t * mbox = lv_mbox_create( mem->parent, NULL );
	lv_obj_set_drag( mbox, true );
	lv_mbox_set_text( mbox,
		"Template page help message box\n" 
		"Some help here\n"
	);
	lv_mbox_add_btns( mbox, btns );
	lv_obj_align( mbox, NULL, LV_ALIGN_IN_TOP_RIGHT, 0, 0 );

	lv_obj_set_event_cb( mbox, help_event_handler );
	lv_obj_set_user_data( mbox, p_mem );

	return true;
}

#endif  /*USE_SNDBX_PGE_TEMPL*/
