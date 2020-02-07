/**
 * @file sndbx_pge_demo.c
 *
 */

 /*********************
  *      INCLUDES
  *********************/
#include "sndbx_pge_demo.h"
#if USE_SNDBX_PGE_DEMO

#include <stdio.h>

/*********************
 *      DEFINES
 *********************/
#define PAGE_NAME "Sandbox Demo"

#define TASK_PERIOD_MAX			1000
#define TASK_SLIDER_VAL_MAX		TASK_PERIOD_MAX
#define REFR_SLIDER_VAL_MAX		(LV_DISP_DEF_REFR_PERIOD*40)
#define REFR_PERIOD_MIN			(LV_DISP_DEF_REFR_PERIOD/2)
#define INFO_REDUCE_CPU_LOADING	0

/**********************
 *      TYPEDEFS
 **********************/
typedef struct {
	lv_obj_t * parent;
	struct {
		lv_obj_t * lbl;
		char * txt;
		uint8_t txt_size;
		uint32_t counter;
		uint32_t time_stamp;
	} task;
	struct {
		bool active;
		lv_obj_t * lbl;
		char * txt;
		uint8_t txt_size;
	} settings;
	struct {
		bool active;
		lv_task_t * task;
		lv_obj_t * lbl;
		char * txt;
		uint16_t txt_size;
		lv_obj_t * chart;
		lv_chart_series_t * cpu_ser;
		lv_chart_series_t * mem_ser;
	} info;
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

static lv_obj_t * label_create( lv_obj_t * par, const char * txt );

/**********************
 *  GLOBAL DESCRIPTORS
 **********************/

const sndbx_pge_dsc_t sndbx_pge_demo_dscs[] = {
	{
		.name = PAGE_NAME" 1",
		.mem_size = sizeof( mem_t ),
		.create_cb = create_cb,
		.task_cb = task_cb,
		.destroy_cb = destroy_cb,
		.task_prio = LV_TASK_PRIO_OFF,
		.task_period = TASK_PERIOD_MAX,
		.settings_cb = settings_cb,
		.info_cb = info_cb,
		.help_cb = help_cb,
	},
	{
		.name = PAGE_NAME" 2",
		.mem_size = sizeof( mem_t ),
		.create_cb = create_cb,
		.task_cb = task_cb,
		.destroy_cb = destroy_cb,
		.task_prio = LV_TASK_PRIO_LOWEST,
		.task_period = TASK_PERIOD_MAX/2,
		.settings_cb = settings_cb,
		.info_cb = info_cb,
		.help_cb = help_cb,
	},
	{
		.name = PAGE_NAME" 3",
		.mem_size = sizeof( mem_t ),
		.create_cb = create_cb,
		.task_cb = task_cb,
		.destroy_cb = destroy_cb,
		.task_prio = LV_TASK_PRIO_LOW,
		.task_period = TASK_PERIOD_MAX/4,
		.settings_cb = settings_cb,
		.info_cb = info_cb,
		.help_cb = help_cb,
	},
	{
		.name = PAGE_NAME" 4",
		.mem_size = sizeof( mem_t ),
		.create_cb = create_cb,
		.task_cb = task_cb,
		.destroy_cb = destroy_cb,
		.task_prio = LV_TASK_PRIO_MID,
		.task_period = TASK_PERIOD_MAX/4,
		.settings_cb = settings_cb,
		.info_cb = info_cb,
		.help_cb = help_cb,
	},
	{
		.name = PAGE_NAME" 5",
		.mem_size = sizeof( mem_t ),
		.create_cb = create_cb,
		.task_cb = task_cb,
		.destroy_cb = destroy_cb,
		.task_prio = LV_TASK_PRIO_HIGH,
		.task_period = TASK_PERIOD_MAX/8,
		.settings_cb = settings_cb,
		.info_cb = info_cb,
		.help_cb = help_cb,
	},
	{
		.name = PAGE_NAME" 6",
		.mem_size = sizeof( mem_t ),
		.create_cb = create_cb,
		.task_cb = task_cb,
		.destroy_cb = destroy_cb,
		.task_prio = LV_TASK_PRIO_HIGHEST,
		.task_period = TASK_PERIOD_MAX/16,
		.settings_cb = settings_cb,
		.info_cb = info_cb,
		.help_cb = help_cb,
	},
};
#define NB_DSCS (sizeof(sndbx_pge_demo_dscs)/sizeof(sndbx_pge_demo_dscs[0]))

/**********************
 *  STATIC VARIABLES
 **********************/

/* Forward declaration of parameters */
static const struct sndbx_pge_demo_prms _prms[NB_DSCS];

/* Different flavours of the same app */
static const sndbx_pge_t pages[NB_DSCS] = {
	{.dsc = &sndbx_pge_demo_dscs[0],.prms = &_prms[0] },
	{.dsc = &sndbx_pge_demo_dscs[1],.prms = &_prms[1] },
	{.dsc = &sndbx_pge_demo_dscs[2],.prms = &_prms[2] },
	{.dsc = &sndbx_pge_demo_dscs[3],.prms = &_prms[3] },
	{.dsc = &sndbx_pge_demo_dscs[4],.prms = &_prms[4] },
	{.dsc = &sndbx_pge_demo_dscs[5],.prms = &_prms[5] },
};

/* Links between pages, if required */
static const sndbx_pge_demo_prms_t _prms[NB_DSCS] = {
	{.self = &sndbx_pge_demo_dscs[0],.links.left = NULL,.links.right = &pages[1], },
	{.self = &sndbx_pge_demo_dscs[1],.links.left = &pages[0],.links.right = &pages[2], },
	{.self = &sndbx_pge_demo_dscs[2],.links.left = &pages[1],.links.right = &pages[3], },
	{.self = &sndbx_pge_demo_dscs[3],.links.left = &pages[2],.links.right = &pages[4], },
	{.self = &sndbx_pge_demo_dscs[4],.links.left = &pages[3],.links.right = &pages[5], },
	{.self = &sndbx_pge_demo_dscs[5],.links.left = &pages[4],.links.right = NULL, },
};

static const char * const priorities[_LV_TASK_PRIO_NUM] = {
	"Off", "Lowest", "Low", "Mid", "High", "Highest",
};

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
void sndbx_pge_demo_test( void )
{
	lv_theme_t * th;
//	th = lv_theme_default_init( 0, NULL );
//	th = lv_theme_alien_init( 180, NULL );
//	th = lv_theme_material_init( 180, NULL );
//	th = lv_theme_mono_init( 0, NULL );
	th = lv_theme_night_init( 210, NULL );
//	th = lv_theme_nemo_init( 180, NULL );
//	th = lv_theme_zen_init( 180, NULL );
	lv_theme_set_current( th );
	sndbx_app_create( &pages[3] );
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
	/* Unpack parameters */
	const sndbx_pge_demo_prms_t * pge_prms = prms;

	/* Create content */
	/* Allocate resources needed to set the page up */
	uint8_t txt_size = 128;
	char * txt = lv_mem_alloc( txt_size );
	lv_obj_t * lbl = lv_label_create( parent, NULL );
	lv_task_t * disp_refr_task = lv_disp_get_refr_task( NULL );

	if( pge_prms->self->task_prio == LV_TASK_PRIO_OFF )
	{
		snprintf( txt, txt_size,
			"Create:\n"
			"    Sandbox created but task not running,\n"
			"    Display refresh task period %u ms."
			, disp_refr_task->period
		);
	}
	else
	{
		snprintf( txt, txt_size,
			"Create:\n"
			"    Sandbox task started with period %u ms at %s priority,\n"
			"    Display refresh task period %u ms."
			, pge_prms->self->task_period, priorities[pge_prms->self->task_prio]
			, disp_refr_task->period
		);
	}
	lv_label_set_text( lbl, txt );
	lv_label_set_align( lbl, LV_LABEL_ALIGN_CENTER );
	lv_obj_align( lbl, NULL, LV_ALIGN_IN_TOP_MID, 0, LV_DPI/8 );

	/* Free allocated resources needed to set the page up */
	lv_mem_free( txt );

	/* 1. Create object and add content */
	mem->task.lbl = label_create( parent, "" );
	/* 2. Set Kind of alignment if so required */
	lv_label_set_align( mem->task.lbl, LV_LABEL_ALIGN_LEFT );
	/* 3. Set Behaviour if so required */
	lv_obj_set_auto_realign( mem->task.lbl, true );
	/* 4. Set Placement if so required */
	lv_obj_align( mem->task.lbl, lbl, LV_ALIGN_OUT_BOTTOM_MID, 0, LV_DPI/8 );

	mem->settings.lbl = label_create( parent, "" );
	lv_label_set_align( mem->settings.lbl, LV_LABEL_ALIGN_LEFT );
	lv_obj_set_auto_realign( mem->settings.lbl, true );
	lv_obj_align( mem->settings.lbl, mem->task.lbl, LV_ALIGN_OUT_BOTTOM_MID, 0, LV_DPI/8 );

	/* Add links to other pages */	
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

	help_cb(p_mem, LV_EVENT_CLICKED);
	sndbx_help_btn_enable_set(false);

	/* Initialise all other memory variables that will be used by the task */
	mem->task.time_stamp = lv_tick_get();
}

/**
 * Called periodically, specified by task_period in sndbx_pge_dsc_t
 * @param p_mem memory pointer, points to memory allocated by the sandbox
 */
static void task_cb( void * p_mem )
{
	MEM_INIT( mem, p_mem );

	if( !mem->task.txt )
	{
		mem->task.txt_size = 128;
		mem->task.txt = lv_mem_alloc( mem->task.txt_size );
		mem->task.txt[0] = '\0';
		lv_label_set_static_text( mem->task.lbl, mem->task.txt );
	}

	lv_task_t * sndbx_task = sndbx_task_get();

	snprintf( mem->task.txt, mem->task.txt_size,
		"Task:\n"
		"    Run count %u,\n"
		"    Elapsed time since last run %u ms."
		, ++mem->task.counter
		, lv_tick_elaps(mem->task.time_stamp)
	);

	lv_label_set_static_text( mem->task.lbl, NULL );

	mem->task.time_stamp = lv_tick_get();
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
	if( mem->info.active && mem->info.task )
		lv_task_del( mem->info.task );
	if( mem->info.txt )
		lv_mem_free( mem->info.txt );
	if( mem->settings.txt )
		lv_mem_free( mem->settings.txt );
	if( mem->task.txt )
		lv_mem_free( mem->task.txt );
	/* Nothing else to do, parent has already been cleaned */
	/* Memory pointed to by p_mem will be deallocated ...*/
	/* ... by the sandbox hander */
}

/*===================== Callbacks and Events================== */

/*Settings*/
static void settings_txt_update( mem_t * mem )
{
	lv_task_t * sndbx_task = sndbx_task_get();
	lv_task_t * disp_refr_task = lv_disp_get_refr_task( NULL );

	snprintf( mem->settings.txt, mem->settings.txt_size, 
		"Settings:\n"
		"    Sandbox task period %u ms at %s priority,\n"
		"    Display refresh task period %u ms."
		, sndbx_task->period, priorities[sndbx_task->prio]
		, disp_refr_task->period
	);
	lv_label_set_text( mem->settings.lbl, NULL );
}
/**
 * Called when a new value on the roller is set
 * @param slider pointer to the slider
 * @param event
 */
static void settings_roller_event_handler( lv_obj_t * roller, lv_event_t event )
{
	if( event != LV_EVENT_VALUE_CHANGED )
		return;

	void * p_mem = lv_obj_get_user_data( roller );
	MEM_INIT( mem, p_mem );

	lv_task_prio_t prio = (lv_task_prio_t)lv_roller_get_selected( roller );
	lv_task_t * sndbx_task = sndbx_task_get();
	lv_task_set_prio( sndbx_task, prio );

	settings_txt_update( mem );
}
/**
 * Called on button events
 * @param obj pointer to button
 * @param event 
 */
static void settings_btn_event_handler( lv_obj_t * btn, lv_event_t event )
{
	if( event != LV_EVENT_CLICKED )
		return;

	void * p_mem = lv_obj_get_user_data( btn );
	MEM_INIT( mem, p_mem );

	lv_task_t * sndbx_task = sndbx_task_get();
	lv_task_ready( sndbx_task );
}

#include <math.h>
/**
 * inverse exponential decay response from slider, 
 * 1-e^(slider_val/exponential_constant) 
 * Todo: Re-impliment without using logf/expf/roundf, 
 *    perhaps by somehow using lv_bezier3 instead ???
 */
static float exponential_constant( uint32_t per_min, uint32_t per_max, uint32_t sv_max )
{
	float per_span = (float)(per_max - per_min);
	float tau = -(float)sv_max / logf( (float)1 - per_span/(float)sv_max );
	return tau;
}
static uint32_t task_period_from_slider_val( int16_t slider_val )
{
	lv_task_t * refr_task = lv_disp_get_refr_task( NULL );
	uint32_t refr_task_period = refr_task->period;

	float tau = exponential_constant( refr_task_period, TASK_PERIOD_MAX, TASK_SLIDER_VAL_MAX );

	float val = (float)TASK_SLIDER_VAL_MAX * ((float)1-expf( -(float)slider_val/tau ));

	return TASK_PERIOD_MAX - (uint32_t)roundf( val );
}
static int16_t task_slider_val_from_period( uint32_t period )
{ 
	lv_task_t * refr_task = lv_disp_get_refr_task( NULL );
	uint32_t refr_task_period = refr_task->period;
	float tau = exponential_constant( refr_task_period, TASK_PERIOD_MAX, TASK_SLIDER_VAL_MAX );

	float val = -tau * logf( (float)1 - 
		(float)(TASK_PERIOD_MAX-period) / 
		(float)TASK_SLIDER_VAL_MAX );

	return (int16_t)roundf( val );
}
/**
 * Called when a new value on the slider is set
 * @param slider pointer to the slider
 * @param event slider event
 */
static void settings_slider_event_handler( lv_obj_t * slider, lv_event_t event )
{
	if( event != LV_EVENT_VALUE_CHANGED )
		return;

	lv_task_t * sndbx_task = sndbx_task_get();
	int16_t v = lv_slider_get_value( slider );
	uint32_t period = task_period_from_slider_val( v );
	lv_task_set_period( sndbx_task, period );

	void * p_mem = lv_obj_get_user_data( slider );
	MEM_INIT( mem, p_mem );

	settings_txt_update( mem );
}
static uint32_t refr_period_from_slider_val( int16_t slider_val )
{	
	float sv = (float)slider_val / (float)10;
	uint32_t period_min = REFR_PERIOD_MIN;
	uint32_t period_max = REFR_SLIDER_VAL_MAX/10;
	float tau = exponential_constant( period_min, period_max, period_max );

	float val = (float)period_max * ((float)1-expf(-sv/tau));

	return period_max - (uint32_t)roundf(val);
}
static int16_t refr_slider_val_from_period( uint32_t period )
{ 
	uint32_t period_min = REFR_PERIOD_MIN;
	uint32_t period_max = REFR_SLIDER_VAL_MAX/10;
	float tau = exponential_constant( period_min, period_max, period_max );

	float val = -tau * logf( (float)1 - 
		(float)(period_max-period)/(float)period_max );

	return (int16_t)(roundf(val*(float)10));
}
/**
 * Called when a new value on the slider is set
 * @param slider pointer to the slider
 * @param event slider event
 */
static void settings_refr_slider_event_handler( lv_obj_t * slider, lv_event_t event )
{
	if( event != LV_EVENT_VALUE_CHANGED )
		return;

	lv_task_t * refr_task = lv_disp_get_refr_task( NULL );
	int16_t slider_val = lv_slider_get_value( slider );

	uint32_t refr_period = refr_period_from_slider_val( slider_val );

	lv_task_set_period( refr_task, refr_period );

	void * p_mem = lv_obj_get_user_data( slider );
	MEM_INIT( mem, p_mem );

	settings_txt_update( mem );
}
/**
 * Called on settings window events.
 * @param obj pointer to settings window
 * @param evt event
 */
static void settings_win_event_handler( lv_obj_t * obj, lv_event_t evt )
{
	if( evt == LV_EVENT_CLICKED )
	{
		void * p_mem = lv_obj_get_user_data( obj );
		MEM_INIT( mem, p_mem );
		mem->settings.active = false;
		sndbx_settings_btn_enable_set( true );
	}

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
	if( mem->settings.active )
		return false;
	mem->settings.active = true;

	if( !mem->settings.txt )
	{
		mem->settings.txt_size = 128;
		mem->settings.txt = lv_mem_alloc( mem->settings.txt_size );
		mem->settings.txt[0] = '\0';
		lv_label_set_static_text( mem->settings.lbl, mem->settings.txt );
	}

	/*Create a window*/
	lv_obj_t * win = lv_win_create( mem->parent, NULL );
	lv_win_set_drag( win, true );
	lv_obj_set_top( win, true );

	/*Set the title*/
	lv_win_set_title( win, "Context related settings window" );

	/*Add control button to the header*/
	lv_obj_t * btn_close = lv_win_add_btn( win, LV_SYMBOL_CLOSE );  
	lv_obj_set_user_data( btn_close, p_mem );
	lv_obj_set_event_cb( btn_close, settings_win_event_handler );

	lv_coord_t h = lv_obj_get_height( mem->parent ) * 1 / 2;
	lv_coord_t w = lv_obj_get_width( mem->parent ) * 3 / 4;
	lv_obj_set_size( win, w, h );

#if 1
	/*!!!Fix the rest by properly setting the correct styles */
	lv_coord_t hh = LV_VER_RES_MAX / 10;
	lv_win_ext_t * ext = lv_obj_get_ext_attr( win );
	lv_obj_set_height( ext->header, hh );
//	lv_btn_set_fit( btn_close, LV_FIT_TIGHT );
	lv_obj_set_size( btn_close, LV_VER_RES_MAX * 3 / 20, LV_VER_RES_MAX / 10 );
	/* The rest is done so that the page in the window uses the remaining height */
	/* And so that the title and close button are properly aligned */
	lv_obj_set_height( ext->page, h - hh );
	const lv_style_t * st = lv_win_get_style( win, LV_WIN_STYLE_HEADER );
	lv_obj_align( ext->page, ext->header, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 0 );
	lv_obj_align( ext->title, ext->header, LV_ALIGN_IN_LEFT_MID, st->body.padding.left, 0 );
	lv_obj_align( btn_close, ext->header, LV_ALIGN_IN_RIGHT_MID, -st->body.padding.right, 0 );

	/* Then if the size changes, it goes back to defaults */
//	lv_obj_set_size( win, w*10/9, h*10/9 );
#endif

	/*Add Content*/
	lv_win_set_layout( win, LV_LAYOUT_PRETTY );

	lv_task_t * sndbx_task = sndbx_task_get();

	/* Roller */
	lv_obj_t * roller = lv_roller_create( win, NULL );
	lv_roller_set_options( roller,
		"Off\n"
		"Lowest\n"
		"Low\n"
		"Mid\n"
		"High\n"
		"Highest"
		,LV_ROLLER_MODE_NORMAL
	);
	lv_roller_set_selected( roller, sndbx_task->prio, true );
	lv_obj_set_user_data( roller, p_mem );
	lv_obj_set_event_cb( roller, settings_roller_event_handler );

	/* Button */
	lv_obj_t *btn = lv_btn_create( win, NULL );
	lv_obj_t *btn_txt = label_create( btn, "Run Now" );
	lv_btn_set_fit( btn, LV_FIT_TIGHT );
	lv_obj_set_user_data( btn, p_mem );
	lv_obj_set_event_cb( btn, settings_btn_event_handler );

	/* Sliders */
	lv_obj_t * slider;

	slider = lv_slider_create( win, NULL );
	lv_obj_set_event_cb( slider, settings_slider_event_handler );
	lv_slider_set_range( slider, 0, TASK_SLIDER_VAL_MAX );
	int16_t slider_val = task_slider_val_from_period( sndbx_task->period );
	lv_slider_set_value( slider, slider_val, true );
	lv_obj_set_user_data( slider, p_mem );

	slider = lv_slider_create( win, NULL );
	lv_obj_set_event_cb( slider, settings_refr_slider_event_handler );
	lv_slider_set_range( slider, 0, REFR_SLIDER_VAL_MAX );
	lv_task_t * refr_task = lv_disp_get_refr_task( NULL );
	slider_val = refr_slider_val_from_period( refr_task->period );
	lv_slider_set_value( slider, slider_val, true );
	lv_obj_set_user_data( slider, p_mem );

	/*Finally, align window to the bottom of the page*/
	lv_obj_align( win, NULL, LV_ALIGN_IN_BOTTOM_MID, 0, 0 );

	return true;
}

/*Info*/
/**
 * Called on info window events.
 * @param obj pointer to info window
 * @param evt event
 */
static void info_win_event_handler( lv_obj_t * obj, lv_event_t evt )
{
	if( evt == LV_EVENT_CLICKED )
	{
		void * p_mem = lv_obj_get_user_data( obj );
		MEM_INIT( mem, p_mem );
		mem->info.active = false;

	    lv_task_del(mem->info.task);
	    mem->info.task = NULL;
		sndbx_info_btn_enable_set( true );
	}

	/*Use built-in close action*/
	lv_win_close_event_cb( obj, evt );
}
/**
 * Called periodically, specified by task_period in lv_task_t
 * @param task lv_task_t
 */
static void info_task_cb( lv_task_t * task )
{
	mem_t * mem = task->user_data;

    /*Get CPU and memory information */
    uint8_t cpu_busy;
    cpu_busy = 100 - lv_task_get_idle();

    uint8_t mem_used_pct = 0;
#if  LV_MEM_CUSTOM == 0
    lv_mem_monitor_t mem_mon;
    lv_mem_monitor(&mem_mon);
    mem_used_pct = mem_mon.used_pct;
#endif

    /*Add the CPU and memory data to the chart*/
    lv_chart_set_next(mem->info.chart, mem->info.cpu_ser, cpu_busy);
    lv_chart_set_next(mem->info.chart, mem->info.mem_ser, mem_used_pct);

#if INFO_REDUCE_CPU_LOADING
	uint16_t nxtp, pnts = lv_chart_get_point_cnt(mem->info.chart);
	nxtp = mem->info.cpu_ser->start_point % pnts;
	mem->info.cpu_ser->points[nxtp] = LV_CHART_POINT_DEF;
	mem->info.mem_ser->points[nxtp] = LV_CHART_POINT_DEF;
#endif

    /*Refresh the and windows*/
    snprintf(mem->info.txt, mem->info.txt_size, "%s%s CPU: %d %%%s, ",
		LV_TXT_COLOR_CMD,
		"FF0000",
		cpu_busy,
		LV_TXT_COLOR_CMD);

#if LV_MEM_CUSTOM == 0
    snprintf(mem->info.txt, mem->info.txt_size, 
#if LV_HOR_RES_MAX > 480
		"%s"LV_TXT_COLOR_CMD"%s MEMORY: %d %%"LV_TXT_COLOR_CMD", "
		"Used: %d B, Free: %d B, Frag: %d %%",
#else
		"%s"LV_TXT_COLOR_CMD"%s Mem:%d%%"LV_TXT_COLOR_CMD", "
		"Usd:%dB, Fre:%dB, Frg:%d%%",
#endif
		mem->info.txt,
		"0000FF",
		mem_used_pct,
		(int)mem_mon.total_size - mem_mon.free_size, mem_mon.free_size, mem_mon.frag_pct);
#else
    snprintf(mem->info.txt, mem->info.txt_size,
		"%s"LV_TXT_COLOR_CMD"%s MEMORY: N/A"LV_TXT_COLOR_CMD,
		mem->info.txt,
        "0000FF");
#endif
    lv_label_set_static_text(mem->info.lbl, NULL);
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

	if( !mem->info.txt )
	{
		mem->info.txt_size = 256;
		mem->info.txt = lv_mem_alloc( mem->info.txt_size );
		mem->info.txt[0] = '\0';
	}

	/*Create a window*/
	lv_obj_t * win = lv_win_create( mem->parent, NULL );
	lv_win_set_drag( win, true );
	lv_obj_set_top( win, true );

	/*Set the title*/
	lv_win_set_title( win, "Context related info window" );

	/*Add control button to the header*/
	lv_obj_t * btn_close = lv_win_add_btn( win, LV_SYMBOL_CLOSE );  
	lv_obj_set_user_data( btn_close, p_mem );
	lv_obj_set_event_cb( btn_close, info_win_event_handler );

	lv_coord_t h = lv_obj_get_height( mem->parent ) * 3 / 4;
	lv_coord_t w = lv_obj_get_width( mem->parent ) * 4 / 5;
	lv_obj_set_size( win, w, h );

#if 1
	/*!!!Fix the rest by properly setting the correct styles */
	lv_coord_t hh = LV_VER_RES_MAX / 10;
	lv_win_ext_t * ext = lv_obj_get_ext_attr( win );
	lv_obj_set_height( ext->header, hh );
//	lv_btn_set_fit( btn_close, LV_FIT_TIGHT );
	lv_obj_set_size( btn_close, LV_VER_RES_MAX * 3 / 20, LV_VER_RES_MAX / 10 );
	/* The rest is done so that the page in the window uses the remaining height */
	/* And so that the title and close button are properly aligned */
	lv_obj_set_height( ext->page, h - hh );
	const lv_style_t * st = lv_win_get_style( win, LV_WIN_STYLE_HEADER );
	lv_obj_align( ext->page, ext->header, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 0 );
	lv_obj_align( ext->title, ext->header, LV_ALIGN_IN_LEFT_MID, st->body.padding.left, 0 );
	lv_obj_align( btn_close, ext->header, LV_ALIGN_IN_RIGHT_MID, -st->body.padding.right, 0 );

	/* Then if the size changes, it goes back to defaults */
//	lv_obj_set_size( win, w*10/9, h*10/9 );
#endif

	/*Add Content*/
	lv_win_set_layout( win, LV_LAYOUT_PRETTY );

    /*Create a label for the details of Memory and CPU usage*/
    mem->info.lbl = lv_label_create(win, NULL);
	lv_label_set_static_text( mem->info.lbl, mem->info.txt );
    lv_label_set_recolor(mem->info.lbl, true);
	lv_label_set_align( mem->info.lbl, LV_LABEL_ALIGN_CENTER );
	lv_obj_set_auto_realign( mem->info.lbl, true );
    lv_obj_align(mem->info.lbl, NULL, LV_ALIGN_IN_TOP_MID, 0, 0);

	/*Create a chart with two data lines*/
    mem->info.chart = lv_chart_create(win, NULL);
//    lv_obj_set_size(mem->info.chart, w-LV_DPI/8, h-LV_DPI);
	lv_coord_t h_w_p = lv_obj_get_height( ext->page );
	lv_coord_t h_lbl = lv_obj_get_height( mem->info.lbl );
    lv_obj_set_size(mem->info.chart, w-LV_DPI/8, h_w_p-h_lbl*2);
    lv_chart_set_point_count(mem->info.chart, 100);
    lv_chart_set_range(mem->info.chart, 0, 100);
    lv_chart_set_type(mem->info.chart, LV_CHART_TYPE_LINE);
    lv_chart_set_series_width(mem->info.chart, 2);
    mem->info.cpu_ser = lv_chart_add_series(mem->info.chart, LV_COLOR_RED);
    mem->info.mem_ser = lv_chart_add_series(mem->info.chart, LV_COLOR_BLUE);

#if INFO_REDUCE_CPU_LOADING
	/* Reduce CPU Loading for embedded systems */
	lv_chart_set_update_mode( mem->info.chart, LV_CHART_UPDATE_MODE_CIRCULAR );
#else
    /*Set the data series to zero*/
    uint16_t i;
    for(i = 0; i < 100; i++) {
        lv_chart_set_next(mem->info.chart, mem->info.cpu_ser, 0);
        lv_chart_set_next(mem->info.chart, mem->info.mem_ser, 0);
    }
#endif

    mem->info.task = lv_task_create(info_task_cb, 500, LV_TASK_PRIO_LOW, p_mem);

	/*Finally, align window to the bottom of the page*/
	lv_obj_align( win, NULL, LV_ALIGN_CENTER, 0, 0 );

	/*Refresh the chart and label manually at first*/
	info_task_cb( mem->info.task );

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

	static const char * const btns[] = { "Ok", "" };

	lv_obj_t * mbox = lv_mbox_create( mem->parent, NULL );
	lv_obj_set_drag( mbox, true );
	lv_mbox_set_text( mbox,
		PAGE_NAME" help message box\n"
		"Click on settings and info buttons\n"
		"On the toolbar above.\n"
		"Make changes and observe behaviour"
	);
	lv_mbox_add_btns( mbox, (const char**)btns );
	lv_obj_align( mbox, NULL, LV_ALIGN_CENTER, 0, 0 );
	lv_obj_set_top( mbox, true );

	lv_obj_set_event_cb( mbox, help_event_handler );
	lv_obj_set_user_data( mbox, p_mem );

	return true;
}

/* Helpers from here */
static lv_obj_t *label_create( lv_obj_t *par, const char *txt )
{
	lv_obj_t * lbl = lv_label_create( par, NULL );
	lv_label_set_static_text( lbl, txt );

	return lbl;
}


#endif  /*USE_SNDBX_PGE_DEMO*/
