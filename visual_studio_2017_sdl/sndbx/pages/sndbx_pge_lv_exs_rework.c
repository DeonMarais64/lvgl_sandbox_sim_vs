/**
 * @file sndbx_pge_lv_exs_rework.c
 *
 */

 /*********************
  *      INCLUDES
  *********************/
#include "sndbx_pge_lv_exs_rework.h"
#if USE_SNDBX_PGE_LV_EXS_REWORK

#include "lv_examples-rework/lv_examples.h"

/*********************
 * EXTERNAL PROTOTYPES
 *********************/

/*********************
 *      DEFINES
 *********************/
#if LV_HOR_RES_MAX < 800
#define PAGE_NAME "lv Examples Rework"
#else
#define PAGE_NAME "LittlevGL Examples Rework"
#endif

#define USE_EX_GAUGE_1	1	/*Compiler error C2099: initializer is not a constant*/
#define USE_EX_LABEL_3	0	/*Starts a task*/
#define USE_EX_MISC_1	0	/*Does not exist*/

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

static void btnm_event_handler(lv_obj_t * obj, lv_event_t evt);

static void save_theme(void);
static void recover_theme(void);

/**********************
 *  STATIC VARIABLES
 **********************/
/*Unmanaged page descriptors*/
static const sndbx_pge_dsc_unmngd_t pge_dscs_unmngd[] = {
	{
		.app = (sndbx_pge_unmngd_cb_t)lv_ex_arc_1,
		.ret_btn_opa_scale = LV_OPA_100,
		.ret_btn_align = LV_ALIGN_IN_TOP_RIGHT,
	},
	{
		.app = (sndbx_pge_unmngd_cb_t)lv_ex_arc_2,
		.ret_btn_opa_scale = LV_OPA_100,
		.ret_btn_align = LV_ALIGN_IN_TOP_RIGHT,
	},
	{
		.app = (sndbx_pge_unmngd_cb_t)lv_ex_bar_1,
		.ret_btn_opa_scale = LV_OPA_100,
		.ret_btn_align = LV_ALIGN_IN_TOP_RIGHT,
	},
	{
		.prologue = save_theme,
		.app = (sndbx_pge_unmngd_cb_t)lv_ex_btn_1,
		.epilogue = recover_theme,
		.ret_btn_opa_scale = LV_OPA_100,
		.ret_btn_align = LV_ALIGN_IN_TOP_RIGHT,
	},
	{
		.app = (sndbx_pge_unmngd_cb_t)lv_ex_btnm_1,
		.ret_btn_opa_scale = LV_OPA_100,
		.ret_btn_align = LV_ALIGN_IN_TOP_RIGHT,
	},
	{
		.app = (sndbx_pge_unmngd_cb_t)lv_ex_calendar_1,
		.ret_btn_opa_scale = LV_OPA_100,
		.ret_btn_align = LV_ALIGN_IN_TOP_RIGHT,
	},
	{
		.app = (sndbx_pge_unmngd_cb_t)lv_ex_canvas_1,
		.ret_btn_opa_scale = LV_OPA_100,
		.ret_btn_align = LV_ALIGN_IN_TOP_RIGHT,
	},
	{
		.app = (sndbx_pge_unmngd_cb_t)lv_ex_cb_1,
		.ret_btn_opa_scale = LV_OPA_100,
		.ret_btn_align = LV_ALIGN_IN_TOP_RIGHT,
	},
	{
		.app = (sndbx_pge_unmngd_cb_t)lv_ex_chart_1,
		.ret_btn_opa_scale = LV_OPA_100,
		.ret_btn_align = LV_ALIGN_IN_TOP_RIGHT,
	},
	{
		.app = (sndbx_pge_unmngd_cb_t)lv_ex_cont_1,
		.ret_btn_opa_scale = LV_OPA_100,
		.ret_btn_align = LV_ALIGN_IN_TOP_RIGHT,
	},
	{
		.app = (sndbx_pge_unmngd_cb_t)lv_ex_ddlist_1,
		.ret_btn_opa_scale = LV_OPA_100,
		.ret_btn_align = LV_ALIGN_IN_TOP_RIGHT,
	},
	{
#if USE_EX_GAUGE_1
		.app = (sndbx_pge_unmngd_cb_t)lv_ex_gauge_1,
#endif
		.ret_btn_opa_scale = LV_OPA_100,
		.ret_btn_align = LV_ALIGN_IN_TOP_RIGHT,
	},
	{
		.app = (sndbx_pge_unmngd_cb_t)lv_ex_img_1,
		.ret_btn_opa_scale = LV_OPA_100,
		.ret_btn_align = LV_ALIGN_IN_TOP_RIGHT,
	},
	{
		.app = (sndbx_pge_unmngd_cb_t)lv_ex_img_2,
		.ret_btn_opa_scale = LV_OPA_100,
		.ret_btn_align = LV_ALIGN_IN_TOP_RIGHT,
	},
	{
		.app = (sndbx_pge_unmngd_cb_t)lv_ex_imgbtn_1,
		.ret_btn_opa_scale = LV_OPA_100,
		.ret_btn_align = LV_ALIGN_IN_TOP_RIGHT,
	},
	{
		.app = (sndbx_pge_unmngd_cb_t)lv_ex_kb_1,
		.ret_btn_opa_scale = LV_OPA_100,
		.ret_btn_align = LV_ALIGN_IN_TOP_RIGHT,
	},
	{
		.app = (sndbx_pge_unmngd_cb_t)lv_ex_label_1,
		.ret_btn_opa_scale = LV_OPA_100,
		.ret_btn_align = LV_ALIGN_IN_TOP_RIGHT,
	},
	{
		.app = (sndbx_pge_unmngd_cb_t)lv_ex_label_2,
		.ret_btn_opa_scale = LV_OPA_100,
		.ret_btn_align = LV_ALIGN_IN_TOP_RIGHT,
	},
	{
#if USE_EX_LABEL_3
		.app = (sndbx_pge_unmngd_cb_t)lv_ex_label_3,
#endif
		.ret_btn_opa_scale = LV_OPA_100,
		.ret_btn_align = LV_ALIGN_IN_TOP_RIGHT,
	},
	{
		.app = (sndbx_pge_unmngd_cb_t)lv_ex_led_1,
		.ret_btn_opa_scale = LV_OPA_100,
		.ret_btn_align = LV_ALIGN_IN_TOP_RIGHT,
	},
	{
		.app = (sndbx_pge_unmngd_cb_t)lv_ex_line_1,
		.ret_btn_opa_scale = LV_OPA_100,
		.ret_btn_align = LV_ALIGN_IN_TOP_RIGHT,
	},
	{
		.app = (sndbx_pge_unmngd_cb_t)lv_ex_list_1,
		.ret_btn_opa_scale = LV_OPA_100,
		.ret_btn_align = LV_ALIGN_IN_TOP_RIGHT,
	},
	{
		.app = (sndbx_pge_unmngd_cb_t)lv_ex_lmeter_1,
		.ret_btn_opa_scale = LV_OPA_100,
		.ret_btn_align = LV_ALIGN_IN_TOP_RIGHT,
	},
	{
		.app = (sndbx_pge_unmngd_cb_t)lv_ex_mbox_1,
		.ret_btn_opa_scale = LV_OPA_100,
		.ret_btn_align = LV_ALIGN_IN_TOP_RIGHT,
	},
	{
		.app = (sndbx_pge_unmngd_cb_t)lv_ex_mbox_2,
		.ret_btn_opa_scale = LV_OPA_100,
		.ret_btn_align = LV_ALIGN_IN_TOP_RIGHT,
	},
	{
#if USE_EX_MISC_1
		.app = (sndbx_pge_unmngd_cb_t)lv_ex_misc_1,
#endif
		.ret_btn_opa_scale = LV_OPA_100,
		.ret_btn_align = LV_ALIGN_IN_TOP_RIGHT,
	},
	{
		.app = (sndbx_pge_unmngd_cb_t)lv_ex_obj_1,
		.ret_btn_opa_scale = LV_OPA_100,
		.ret_btn_align = LV_ALIGN_IN_TOP_RIGHT,
	},
	{
		.app = (sndbx_pge_unmngd_cb_t)lv_ex_page_1,
		.ret_btn_opa_scale = LV_OPA_100,
		.ret_btn_align = LV_ALIGN_IN_TOP_RIGHT,
	},
	{
		.app = (sndbx_pge_unmngd_cb_t)lv_ex_preload_1,
		.ret_btn_opa_scale = LV_OPA_100,
		.ret_btn_align = LV_ALIGN_IN_TOP_RIGHT,
	},
	{
		.app = (sndbx_pge_unmngd_cb_t)lv_ex_roller_1,
		.ret_btn_opa_scale = LV_OPA_100,
		.ret_btn_align = LV_ALIGN_IN_TOP_RIGHT,
	},
	{
		.app = (sndbx_pge_unmngd_cb_t)lv_ex_slider_1,
		.ret_btn_opa_scale = LV_OPA_100,
		.ret_btn_align = LV_ALIGN_IN_TOP_RIGHT,
	},
	{
		.app = (sndbx_pge_unmngd_cb_t)lv_ex_slider_2,
		.ret_btn_opa_scale = LV_OPA_100,
		.ret_btn_align = LV_ALIGN_IN_TOP_RIGHT,
	},
	{
		.app = (sndbx_pge_unmngd_cb_t)lv_ex_spinbox_1,
		.ret_btn_opa_scale = LV_OPA_100,
		.ret_btn_align = LV_ALIGN_IN_TOP_RIGHT,
	},
	{
		.app = (sndbx_pge_unmngd_cb_t)lv_ex_sw_1,
		.ret_btn_opa_scale = LV_OPA_100,
		.ret_btn_align = LV_ALIGN_IN_TOP_RIGHT,
	},
	{
		.app = (sndbx_pge_unmngd_cb_t)lv_ex_ta_1,
		.ret_btn_opa_scale = LV_OPA_100,
		.ret_btn_align = LV_ALIGN_IN_TOP_RIGHT,
	},
	{
		.app = (sndbx_pge_unmngd_cb_t)lv_ex_ta_2,
		.ret_btn_opa_scale = LV_OPA_100,
		.ret_btn_align = LV_ALIGN_IN_TOP_RIGHT,
	},
	{
		.app = (sndbx_pge_unmngd_cb_t)lv_ex_table_1,
		.ret_btn_opa_scale = LV_OPA_100,
		.ret_btn_align = LV_ALIGN_IN_TOP_RIGHT,
	},
	{
		.app = (sndbx_pge_unmngd_cb_t)lv_ex_tabview_1,
		.ret_btn_opa_scale = LV_OPA_100,
		.ret_btn_align = LV_ALIGN_IN_TOP_RIGHT,
	},
	{
		.app = (sndbx_pge_unmngd_cb_t)lv_ex_tileview_1,
		.ret_btn_opa_scale = LV_OPA_100,
		.ret_btn_align = LV_ALIGN_IN_TOP_RIGHT,
	},
	{
		.app = (sndbx_pge_unmngd_cb_t)lv_ex_win_1,
		.ret_btn_opa_scale = LV_OPA_100,
		.ret_btn_align = LV_ALIGN_IN_TOP_MID,
	},
};
#define NB_PGE_DSCS (sizeof(pge_dscs_unmngd)/sizeof(pge_dscs_unmngd[0]))

static sndbx_pge_t app_pages[NB_PGE_DSCS] = {
	{.dsc_u = &pge_dscs_unmngd[0], },
	{.dsc_u = &pge_dscs_unmngd[1], },
	{.dsc_u = &pge_dscs_unmngd[2], },
	{.dsc_u = &pge_dscs_unmngd[3], },
	{.dsc_u = &pge_dscs_unmngd[4], },
	{.dsc_u = &pge_dscs_unmngd[5], },
	{.dsc_u = &pge_dscs_unmngd[6], },
	{.dsc_u = &pge_dscs_unmngd[7], },
	{.dsc_u = &pge_dscs_unmngd[8], },
	{.dsc_u = &pge_dscs_unmngd[9], },
	{.dsc_u = &pge_dscs_unmngd[10], },
	{.dsc_u = &pge_dscs_unmngd[11], },
	{.dsc_u = &pge_dscs_unmngd[12], },
	{.dsc_u = &pge_dscs_unmngd[13], },
	{.dsc_u = &pge_dscs_unmngd[14], },
	{.dsc_u = &pge_dscs_unmngd[15], },
	{.dsc_u = &pge_dscs_unmngd[16], },
	{.dsc_u = &pge_dscs_unmngd[17], },
	{.dsc_u = &pge_dscs_unmngd[18], },
	{.dsc_u = &pge_dscs_unmngd[19], },
	{.dsc_u = &pge_dscs_unmngd[20], },
	{.dsc_u = &pge_dscs_unmngd[21], },
	{.dsc_u = &pge_dscs_unmngd[22], },
	{.dsc_u = &pge_dscs_unmngd[23], },
	{.dsc_u = &pge_dscs_unmngd[24], },
	{.dsc_u = &pge_dscs_unmngd[25], },
	{.dsc_u = &pge_dscs_unmngd[26], },
	{.dsc_u = &pge_dscs_unmngd[27], },
	{.dsc_u = &pge_dscs_unmngd[28], },
	{.dsc_u = &pge_dscs_unmngd[29], },
	{.dsc_u = &pge_dscs_unmngd[30], },
	{.dsc_u = &pge_dscs_unmngd[31], },
	{.dsc_u = &pge_dscs_unmngd[32], },
	{.dsc_u = &pge_dscs_unmngd[33], },
	{.dsc_u = &pge_dscs_unmngd[34], },
	{.dsc_u = &pge_dscs_unmngd[35], },
	{.dsc_u = &pge_dscs_unmngd[36], },
	{.dsc_u = &pge_dscs_unmngd[37], },
	{.dsc_u = &pge_dscs_unmngd[38], },
	{.dsc_u = &pge_dscs_unmngd[39], },
};

static const char * const btnm_map1[] = {
	"arc 1", "arc 2", "bar", "btn", "btnm 1", "\n",
	"calendar", "canvas","cb", "chart", "cont", "\n",
	"ddlist", "gauge", "img 1", "img 2", "imgbtn", "\n",
	"kb", "label 1", "label 2", "label 3", "led", 
	"",
};
static const char * const btnm_map2[] = {
	"line", "list", "lmeter", "mbox 1", "mbox 2", "\n",
	"misc", "obj", "page", "preload", "roller", "\n",
	"slider 1",	"slider 2", "spinbox", "sw", "ta 1", "\n",
	"ta 2", "table",	"tabview", "tileview", "win",
	"",
};

static lv_theme_t * theme;

/**********************
 *      MACROS
 **********************/
#define MEM_INIT(to,from)	mem_t*(to) = (from)

/**********************
 *   GLOBAL DESCRIPTORS
 **********************/

const sndbx_pge_dsc_t sndbx_pge_lv_exs_rework_dsc = {
	.name = PAGE_NAME,
	.mem_size = sizeof(mem_t),
	.create_cb = create_cb,
	.help_cb = help_cb,
};

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

/**
 * Create a sandbox application
 */
void sndbx_pge_lv_exs_rework_test( void ) 
{
	static const sndbx_pge_t page = {
		.dsc = &sndbx_pge_lv_exs_rework_dsc,
	};

	theme = lv_theme_default_init(0, NULL);
	lv_theme_set_current( theme );
	sndbx_app_create(&page);
}

/**********************
 *   STATIC FUNCTIONS
 **********************/
 
/**
 * Called when the page is created,
 * @param parent pointer to parent object
 * @param p_mem pointer to memory allocated by the sandbox  
 * @param prms pointer to page parameters
 */
static void create_cb( lv_obj_t * parent, void * p_mem, const void * prms )
{
	const sndbx_pge_lv_exs_rework_prms_t * pge_prms = prms;
	MEM_INIT(mem, p_mem);
	mem->parent = parent;
	 
	/* Create content */
	lv_coord_t w_par = lv_obj_get_width(parent);
	lv_coord_t h_par = lv_obj_get_height(parent);

	lv_obj_t * lbl = label_create(parent, "Please select an example to run");
	lv_obj_align(lbl, NULL, LV_ALIGN_IN_TOP_MID, 0, LV_DPI/4 );


	lv_obj_t * btnm = lv_btnm_create(parent, NULL);
	const char ** bntm_map = (const char **)(pge_prms->index ? btnm_map2 : btnm_map1);

	lv_btnm_set_map(btnm, bntm_map );
	lv_obj_set_size(btnm, w_par * 3 / 4, h_par * 3 / 4);
	lv_obj_align(btnm, lbl, LV_ALIGN_OUT_BOTTOM_MID, 0, LV_DPI / 6);
	lv_obj_set_event_cb(btnm, btnm_event_handler);
	lv_obj_set_user_data(btnm, &app_pages[pge_prms->index*20]);

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

static void btnm_event_handler(lv_obj_t * obj, lv_event_t evt)
{
	if (evt != LV_EVENT_CLICKED)
		return;
	uint16_t idx = lv_btnm_get_active_btn(obj);
	if (idx >= NB_APP_PAGES)
		return;
	const sndbx_pge_t *pages = lv_obj_get_user_data(obj);
	sndbx_pge_change(&pages[idx]);
}

static void save_theme(void)
{
	if( !theme )
		theme = lv_theme_get_current();
}

static void recover_theme(void)
{
	if (theme)
		lv_theme_set_current(theme);
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
	lv_mbox_start_auto_close( obj, 0 );

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

	lv_obj_t * mbox = lv_mbox_create( mem->parent, NULL );
	lv_obj_set_drag( mbox, true );
	lv_mbox_set_text( mbox,
		PAGE_NAME" help message box\n"
		"Some help here\n"
	);
	lv_mbox_add_btns( mbox, btns );
	lv_obj_align( mbox, NULL, LV_ALIGN_CENTER, 0, 0 );

	lv_obj_set_event_cb( mbox, help_event_handler );

	return true;
}

/* Helpers from here */
static lv_obj_t *label_create( lv_obj_t *par, const char *txt )
{
	lv_obj_t * lbl = lv_label_create( par, NULL );
	lv_label_set_static_text( lbl, txt );

	return lbl;
}

#endif  /*USE_SNDBX_PGE_LV_EXS_REWORK*/
