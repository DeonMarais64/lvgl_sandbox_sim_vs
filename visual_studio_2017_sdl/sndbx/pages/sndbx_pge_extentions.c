/**
 * @file sndbx_pge_extentions.c
 *
 */

 /*********************
  *      INCLUDES
  *********************/
#include "sndbx_pge_extentions.h"
#if USE_SNDBX_PGE_EXTENTIONS

#include <stdio.h>
#include "../gui/gui.h"

/*********************
 *      DEFINES
 *********************/
#define PAGE_NAME "Obj Extentions"

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

static void btn_rs_cb(lv_obj_t *btn, lv_event_t e);
static void btn_uds_cb(lv_obj_t* btn, lv_event_t e);

//LV_EVENT_CB_DECLARE(btn_cb);

/**********************
 *  GLOBAL DESCRIPTORS
 **********************/
const sndbx_pge_dsc_t sndbx_pge_extentions_dsc = {
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
void sndbx_pge_extentions_test( void )
{
	static const sndbx_pge_t page = {
		.dsc = &sndbx_pge_extentions_dsc,
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

	/*+ Create content */

	lv_obj_t* ctrl_lhs = gui_ctrlmotor_uds_create(parent, btn_uds_cb);
	lv_obj_align(ctrl_lhs, NULL, LV_ALIGN_IN_LEFT_MID, 0, 0);


	lv_obj_t* ctrl_rhs = gui_ctrlmotor_rs_create(parent, btn_rs_cb);
	lv_obj_align(ctrl_rhs, NULL, LV_ALIGN_IN_RIGHT_MID, 0, 0 );

	lv_coord_t w_par = lv_obj_get_width(parent);
	lv_coord_t h_par = lv_obj_get_height(parent);

	lv_coord_t w_lhs = lv_obj_get_width(ctrl_lhs);

	lv_coord_t w_tv = w_par - lv_obj_get_width(ctrl_lhs) - lv_obj_get_width(ctrl_rhs);
	lv_coord_t h_tv = h_par;

	/*+ Tileview */
	static const lv_point_t valid_pos[] = { 
		{0, 0}, 
		{0, 1}, 
		{0, 2},
	};
	lv_obj_t* tileview;
	tileview = lv_tileview_create(parent, NULL);
	lv_tileview_set_valid_positions(tileview, valid_pos, 3);
	lv_obj_set_size(tileview, w_tv, h_tv);
	//lv_obj_set_width(tileview, w_tv);
	lv_tileview_set_edge_flash(tileview, true);
	lv_obj_align(tileview, NULL, LV_ALIGN_CENTER, 0, 0);
	//lv_tileview_set_anim_time(tileview, 0);

	lv_obj_t* lbl;

	/*Tile 1 */
	lv_obj_t *tile1 = lv_obj_create(tileview, NULL);
	lv_obj_set_size(tile1, w_tv, h_tv);
	lv_tileview_add_element(tileview, tile1);

	lbl = lv_label_create(tile1, NULL);
	lv_label_set_text_static(lbl, "\nTile 1");
	lv_obj_align(lbl, NULL, LV_ALIGN_CENTER, 0, 0);

	/*Tile 2 */
	lv_obj_t* tile2 = lv_obj_create(tileview, tile1);
	lv_obj_align(tile2, tile1, LV_ALIGN_OUT_BOTTOM_MID, 0, 0);
	lv_tileview_add_element(tileview, tile2);

	lbl = lv_label_create(tile2, NULL);
	lv_label_set_text_static(lbl, "\n\nTile 2");
	lv_obj_align(lbl, NULL, LV_ALIGN_CENTER, 0, 0);

	lbl = lv_label_create(tile2, NULL);

	int i;

	i = lv_obj_count_children(tile2);

	char str[32];
	sprintf(str, "Tile 2\nChildren : %i", i);
	lv_label_set_text(lbl, str);
	lv_obj_align(lbl, NULL, LV_ALIGN_IN_BOTTOM_MID, 0, 0);

	/*Tile 3 */
	lv_obj_t* tile3 = lv_obj_create(tileview, tile2);
	lv_obj_set_size(tile3, w_tv, h_tv);
	lv_obj_align(tile3, tile2, LV_ALIGN_OUT_BOTTOM_MID, 0, 0);
	lv_tileview_add_element(tileview, tile3);

	lbl = lv_label_create(tile3, NULL);
	lv_label_set_text_static(lbl, "\n\n\nTile 3");
	lv_obj_align(lbl, NULL, LV_ALIGN_CENTER, 0, 0);
	/*- Tileview */

	/*+ Task*/
	mem->task.lbl = lv_label_create( parent, NULL );
	lv_label_set_text_static( mem->task.lbl, "" );
	lv_obj_set_auto_realign( mem->task.lbl, true );
	//lv_label_set_align( mem->task.lbl, LV_LABEL_ALIGN_LEFT );
	//lv_obj_align( mem->task.lbl, lbl, LV_ALIGN_OUT_BOTTOM_MID, 0, LV_DPI / 6 );
	/*- Task*/

	/*- Create content */

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

	if (!mem->task.lbl)
		return;

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
	lv_msgbox_start_auto_close( obj, 0 );

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

	lv_obj_t * mbox = lv_msgbox_create( mem->parent, NULL );
	lv_obj_set_drag( mbox, true );
	lv_msgbox_set_text( mbox,
		"Template page settings message box\n" 
		"Some settings here\n"
	);
	lv_msgbox_add_btns( mbox, btns );
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
	lv_msgbox_start_auto_close( obj, 0 );

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

	lv_obj_t * mbox = lv_msgbox_create( mem->parent, NULL );
	lv_obj_set_drag( mbox, true );
	lv_msgbox_set_text( mbox,
		"Template page info message box\n"
		"Some information here\n"
	);
	lv_msgbox_add_btns( mbox, btns );
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
	lv_msgbox_start_auto_close( obj, 0 );

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

	lv_obj_t * mbox = lv_msgbox_create( mem->parent, NULL );
	lv_obj_set_drag( mbox, true );
	lv_msgbox_set_text( mbox,
		"Template page help message box\n" 
		"Some help here\n"
	);
	lv_msgbox_add_btns( mbox, btns );
	lv_obj_align( mbox, NULL, LV_ALIGN_IN_TOP_RIGHT, 0, 0 );

	lv_obj_set_event_cb( mbox, help_event_handler );
	lv_obj_set_user_data( mbox, p_mem );

	return true;
}

static void btn_rs_cb(lv_obj_t *btn, lv_event_t e)
{
	if (e != LV_EVENT_CLICKED)
		return;
	uint8_t id = gui_btn_get_id(btn);

	mem_t * mem = (mem_t*)sndbx_pge_get_mem();
	
	switch (id) {
	case 1: lv_label_set_text_static(mem->task.lbl, "Run pressed"); break;
	case 2: lv_label_set_text_static(mem->task.lbl, "Stop pressed"); break;
	default: lv_label_set_text_static(mem->task.lbl, "Unknown Event Id"); break;
	}
}

static void btn_uds_cb(lv_obj_t* btn, lv_event_t e)
{
	if (e != LV_EVENT_CLICKED)
		return;
	uint8_t id = gui_btn_get_id(btn);

	mem_t* mem = (mem_t*)sndbx_pge_get_mem();

	switch (id) {
	case 1: lv_label_set_text_static(mem->task.lbl, "Up pressed"); break;
	case 2: lv_label_set_text_static(mem->task.lbl, "Down pressed"); break;
	case 3: lv_label_set_text_static(mem->task.lbl, "Stop pressed"); break;
	default: lv_label_set_text_static(mem->task.lbl, "Unknown Event Id"); break;
	}
}

#endif  /*USE_SNDBX_PGE_EXTENTIONS*/
