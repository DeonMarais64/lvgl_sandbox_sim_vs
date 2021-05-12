/**
 * @file sndbx_pge_lv_apps.c
 *
 */

 /*********************
  *      INCLUDES
  *********************/
#include "sndbx_pge_lv_apps.h"
#if USE_SNDBX_PGE_LV_APPS

#include "lv_apps/src/lv_benchmark/lv_benchmark.h"
#include "lv_apps/src/lv_demo/lv_demo.h"
#include "lv_apps/src/lv_menu/lv_menu.h"
//#include "lv_apps/src/lv_settings/lv_settings.h"
#include "lv_apps/src/lv_sysmon/lv_sysmon.h"
#include "lv_apps/src/lv_terminal/lv_terminal.h"
#include "lv_apps/src/lv_tpcal/lv_tpcal.h"
#include "lv_apps/src/lv_wifi/lv_wifi.h"
#include "lv_apps/src/lv_benchmark/lv_benchmark.h"

#include "sndbx_pge_lv_app_demo.h"
#include "sndbx_pge_lv_app_sysmon.h"

/*********************
 * EXTERNAL PROTOTYPES
 *********************/
extern void lv_ex_settings_1(void);
extern void lv_ex_settings_2(void);

/*********************
 *      DEFINES
 *********************/
#define PAGE_NAME "LittlevGL Apps"

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

static lv_obj_t * label_create( lv_obj_t * par, const char * txt );

static void btnmatrix_event_handler(lv_obj_t * obj, lv_event_t evt);

static void save_theme(void);
static void recover_theme(void);

static void post_terminal_create(void *);
static void term_create(void)
{
	terminal_create();
}
static void pre_tpcal_create(void);

/**********************
 *  STATIC VARIABLES
 **********************/

/*Unmanaged page descriptors*/
static const sndbx_pge_dsc_unmngd_t pge_dscs_unmngd[] = {
	{
		.app = (sndbx_pge_unmngd_cb_t)demo_create,
		.ret_btn_opa_scale = LV_OPA_100,
		.ret_btn_align = LV_ALIGN_IN_TOP_RIGHT,
	},
	{
		.app = (sndbx_pge_unmngd_cb_t)benchmark_create,
		.ret_btn_opa_scale = LV_OPA_100,
		.ret_btn_align = LV_ALIGN_IN_TOP_RIGHT,
	},
	{
		.prologue = save_theme,				/* Remember theme */
		.app = (sndbx_pge_unmngd_cb_t)lv_ex_settings_1,
		.epilogue = recover_theme,			/* Recover the theme set by lv_ex_settings_1 */
		.ret_btn_opa_scale = LV_OPA_100,
		.ret_btn_align = LV_ALIGN_IN_TOP_MID,
	},
	{
		.prologue = save_theme,				/* Remember theme */
		.app = (sndbx_pge_unmngd_cb_t)lv_ex_settings_2,
		.epilogue = recover_theme,			/* Recover the theme set by lv_ex_settings_2 */
		.ret_btn_opa_scale = LV_OPA_100,
		.ret_btn_align = LV_ALIGN_IN_TOP_MID,
	},
	{
		.app = (sndbx_pge_unmngd_cb_t)sysmon_create,
		.ret_btn_opa_scale = LV_OPA_100,
		.ret_btn_align = LV_ALIGN_IN_TOP_MID,
	},
	{
		.app = (sndbx_pge_unmngd_cb_t)term_create,
		.post_app = post_terminal_create,	/* Add some text to the terminal */
		.ret_btn_opa_scale = LV_OPA_100,
		.ret_btn_align = LV_ALIGN_IN_TOP_MID,
	},
	{
		.prologue = pre_tpcal_create,		/* Create close button underneath tpcal */
		.app = (sndbx_pge_unmngd_cb_t)tpcal_create,
	},
};
#define NB_PGE_DSCS (sizeof(pge_dscs_unmngd)/sizeof(pge_dscs_unmngd[0]))

static sndbx_pge_t app_pages[NB_PGE_DSCS] = {
#if 0&&!LV_DEMO_SLIDE_SHOW
	{.dsc_u = &pge_dscs_unmngd[0],.prms = NULL },
#else /*Using converted managed version because of task created by original */
	{.dsc = &sndbx_pge_lv_app_demo_dsc, },
#endif
	{.dsc_u = &pge_dscs_unmngd[1], },
	{.dsc_u = &pge_dscs_unmngd[2], },
	{.dsc_u = &pge_dscs_unmngd[3], },
#if 0
	{.dsc_u = &pge_dscs_unmngd[4],.prms = NULL },
#else /*Using converted managed version because of task created by original */
	{.dsc = &sndbx_pge_lv_app_sysmon_dsc, },
#endif
	{.dsc_u = &pge_dscs_unmngd[5], },
	{.dsc_u = &pge_dscs_unmngd[6], },
};

static lv_theme_t * volatile theme;

/**********************
 *      MACROS
 **********************/
#define MEM_INIT(to,from)	mem_t*(to) = (from)

/**********************
 *   GLOBAL DESCRIPTORS
 **********************/

const sndbx_pge_dsc_t sndbx_pge_lv_apps_dsc = {
	.name = PAGE_NAME,
	.mem_size = sizeof(mem_t),
	.create_cb = create_cb,
	.help_cb = help_cb,
};

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

/**
 * Create a demo application
 */
void sndbx_pge_lv_apps_test( void ) 
{
	static const sndbx_pge_t page = {
		.dsc = &sndbx_pge_lv_apps_dsc, 
	};

//	theme = lv_theme_default_init(0, NULL);
//	lv_theme_set_current( theme );
	sndbx_app_create(&page);
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

	lv_obj_t * lbl = label_create(parent, "Please select an app to run");
	lv_obj_align(lbl, NULL, LV_ALIGN_IN_TOP_MID, 0, LV_DPI/4 );

	static const char * btnmatrix_map[] = {
		"Demo",	"Benchmark", "\n",
		"Settings 1", "Settings 2", "\n",
		"Sysmon", "Terminal", "\n",
		"TP Cal", 
		"",
	};

	lv_obj_t * btnmatrix = lv_btnmatrix_create(parent, NULL);
	lv_btnmatrix_set_map(btnmatrix, btnmatrix_map);
	lv_obj_set_size(btnmatrix, w_par * 3 / 4, h_par * 3 / 4);
	lv_obj_align(btnmatrix, lbl, LV_ALIGN_OUT_BOTTOM_MID, 0, LV_DPI / 6);
	lv_obj_set_event_cb(btnmatrix, btnmatrix_event_handler);

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
}

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

void save_theme(void)
{
//	if( !theme )
//		theme = lv_theme_get_current();
}

void recover_theme(void)
{
//	if (theme)
//		lv_theme_set_current(theme);
	extern void app_init_theme( void );
	app_init_theme();
}

static void post_terminal_create(void * obj)
{
	(void)obj;
	terminal_add("This text is added during run time to the terminal\n\n");
	terminal_add("Info: System Started\n");
	terminal_add("Debug: Initialising file system\n");
	terminal_add("Debug: File system initialised, checking for new firmware\n");
	terminal_add("Warning: Directory FIRMWARE does not exist, creating directory FIRMWARE\n");
	terminal_add("Error: Could not create directory FIRMWARE, File system error -2\n");
}

static void pre_tpcal_create(void)
{
	const void * prev = sndbx_pge_get_act();
	lv_obj_t *btn_ret = sndbx_link_btn_create(NULL, LV_SYMBOL_CLOSE, prev);
	lv_obj_align(btn_ret, NULL, LV_ALIGN_IN_TOP_RIGHT, 0, 0);
}


/*===================== Callbacks and Events================== */


/*Help*/
/**
 * Called on help message box close button events
 * @param obj pointer to button
 * @param evt event that occurred
 */
static void help_event_handler( lv_obj_t * obj, lv_event_t evt )
{
	if( evt != LV_EVENT_CLICKED )
		return;
	lv_msgbox_start_auto_close( obj, 0 );

	sndbx_help_btn_enable_set( true );
}

/**
 * Called on sandbox toolbar help button events
 * @param obj pointer to help button
 * @param evt event that occurred
 */
static bool help_cb( void * p_mem, lv_event_t evt )
{
	if( evt != LV_EVENT_CLICKED )
		return false;
	MEM_INIT(mem, p_mem);

	static const char * btns[] = { "Ok", "" };

	lv_obj_t * msgbox = lv_msgbox_create( mem->parent, NULL );
	lv_obj_set_drag( msgbox, true );
	lv_msgbox_set_text( msgbox,
		PAGE_NAME" help message box\n"
		"Some help here\n"
	);
	lv_msgbox_add_btns( msgbox, btns );
	lv_obj_align( msgbox, NULL, LV_ALIGN_CENTER, 0, 0 );

	lv_obj_set_event_cb( msgbox, help_event_handler );

	return true;
}

/* Helpers from here */
static lv_obj_t *label_create( lv_obj_t *par, const char *txt )
{
	lv_obj_t * lbl = lv_label_create( par, NULL );
	lv_label_set_static_text( lbl, txt );

	return lbl;
}

#endif  /*USE_SNDBX_PGE_LV_APPS*/
