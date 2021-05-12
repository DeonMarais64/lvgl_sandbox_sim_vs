/**
 * @file sndbx_pge_lv_ex_widgets.c
 *
 */

 /*********************
  *      INCLUDES
  *********************/
#include "sndbx_pge_lv_ex_widgets.h"
#if USE_SNDBX_PGE_LV_EX_WIDGETS

#include "lv_examples/src/lv_ex_widgets/lv_ex_widgets.h"

/*********************
 * EXTERNAL PROTOTYPES
 *********************/

extern void main_dispatch_post_lvgl_tskh(void(*)(void));

/*********************
 *      DEFINES
 *********************/
#if LV_HOR_RES_MAX < 800
#define PAGE_NAME "lv Widgets"
#else
#define PAGE_NAME "LVGL Widgets"
#endif

#define USE_EX_LABEL_3	0	/*Starts a task*/

#define NB_APP_PAGES (sizeof(app_pages)/sizeof(app_pages[0]))

/**********************
 *      TYPEDEFS
 **********************/
typedef struct {
	lv_obj_t * parent;
	lv_obj_t * obj_modal;
	bool setings_active;
} mem_t;

/**********************
 *  STATIC PROTOTYPES
 **********************/

static void create_cb( lv_obj_t * parent, void * mem, const void * prms );

static bool settings_cb( void * p_mem, lv_event_t evt );

static void btnm_event_handler(lv_obj_t * obj, lv_event_t evt);

static void dispatch_lv_ex_cont_1(void)
{
	main_dispatch_post_lvgl_tskh(lv_ex_cont_1);
}

static void dispatch_lv_ex_objmask_1(void)
{
	main_dispatch_post_lvgl_tskh(lv_ex_objmask_1);
}

/**********************
 *  STATIC VARIABLES
 **********************/

/*Unmanaged page descriptors*/
static const sndbx_pge_dsc_unmngd_t pge_dscs_unmngd[] = {
	{
		.app = lv_ex_arc_1,
		.ret_btn_opa_scale = LV_OPA_100,
		.ret_btn_align = LV_ALIGN_IN_TOP_RIGHT,
	},
	{
		.app = lv_ex_arc_2,
		.ret_btn_opa_scale = LV_OPA_100,
		.ret_btn_align = LV_ALIGN_IN_TOP_RIGHT,
	},
	{
		.app = lv_ex_bar_1,
		.ret_btn_opa_scale = LV_OPA_100,
		.ret_btn_align = LV_ALIGN_IN_TOP_RIGHT,
	},
	{
		.app = lv_ex_btn_1,
		.ret_btn_opa_scale = LV_OPA_100,
		.ret_btn_align = LV_ALIGN_IN_TOP_RIGHT,
	},
	{
		.app = lv_ex_btn_2,
		.ret_btn_opa_scale = LV_OPA_100,
		.ret_btn_align = LV_ALIGN_IN_TOP_RIGHT,
	},
	{
		.app = lv_ex_btnmatrix_1,
		.ret_btn_opa_scale = LV_OPA_100,
		.ret_btn_align = LV_ALIGN_IN_TOP_RIGHT,
	},
	{
		.app = lv_ex_calendar_1,
		.ret_btn_opa_scale = LV_OPA_100,
		.ret_btn_align = LV_ALIGN_IN_TOP_RIGHT,
	},
	{
		.app = lv_ex_canvas_1,
		.ret_btn_opa_scale = LV_OPA_100,
		.ret_btn_align = LV_ALIGN_IN_TOP_RIGHT,
	},
	{
		.app = lv_ex_canvas_2,
		.ret_btn_opa_scale = LV_OPA_100,
		.ret_btn_align = LV_ALIGN_IN_TOP_RIGHT,
	},
	{
		.app = lv_ex_checkbox_1,
		.ret_btn_opa_scale = LV_OPA_100,
		.ret_btn_align = LV_ALIGN_IN_TOP_RIGHT,
	},
	{
		.app = lv_ex_chart_1,
		.ret_btn_opa_scale = LV_OPA_100,
		.ret_btn_align = LV_ALIGN_IN_TOP_RIGHT,
	},
	{
		.app = lv_ex_chart_2,
		.ret_btn_opa_scale = LV_OPA_100,
		.ret_btn_align = LV_ALIGN_IN_TOP_RIGHT,
	},
	{
		.app = dispatch_lv_ex_cont_1,
		.ret_btn_opa_scale = LV_OPA_100,
		.ret_btn_align = LV_ALIGN_IN_TOP_RIGHT,
	},
	{
		.app = lv_ex_cpicker_1,
		.ret_btn_opa_scale = LV_OPA_100,
		.ret_btn_align = LV_ALIGN_IN_TOP_RIGHT,
	},
	{
		.app = lv_ex_cpicker_2,
		.ret_btn_opa_scale = LV_OPA_100,
		.ret_btn_align = LV_ALIGN_IN_TOP_RIGHT,
	},
	{
		.app = lv_ex_dropdown_1,
		.ret_btn_opa_scale = LV_OPA_100,
		.ret_btn_align = LV_ALIGN_IN_TOP_RIGHT,
	},
	{
		.app = lv_ex_dropdown_2,
		.ret_btn_opa_scale = LV_OPA_100,
		.ret_btn_align = LV_ALIGN_IN_TOP_RIGHT,
	},
	{
		.app = lv_ex_gauge_1,
		.ret_btn_opa_scale = LV_OPA_100,
		.ret_btn_align = LV_ALIGN_IN_TOP_RIGHT,
	},
	{
		.app = lv_ex_gauge_2,
		.ret_btn_opa_scale = LV_OPA_100,
		.ret_btn_align = LV_ALIGN_IN_TOP_RIGHT,
	},
	{
		.app = lv_ex_img_1,
		.ret_btn_opa_scale = LV_OPA_100,
		.ret_btn_align = LV_ALIGN_IN_TOP_RIGHT,
	},
	{
		.app = lv_ex_img_2,
		.ret_btn_opa_scale = LV_OPA_100,
		.ret_btn_align = LV_ALIGN_IN_TOP_RIGHT,
	},

	{
		.app = lv_ex_img_3,
		.ret_btn_opa_scale = LV_OPA_100,
		.ret_btn_align = LV_ALIGN_IN_TOP_RIGHT,
	},
	{
		.app = lv_ex_imgbtn_1,
		.ret_btn_opa_scale = LV_OPA_100,
		.ret_btn_align = LV_ALIGN_IN_TOP_RIGHT,
	},
	{
		.app = lv_ex_keyboard_1,
		.ret_btn_opa_scale = LV_OPA_100,
		.ret_btn_align = LV_ALIGN_IN_TOP_RIGHT,
	},
	{
		.app = lv_ex_label_1,
		.ret_btn_opa_scale = LV_OPA_100,
		.ret_btn_align = LV_ALIGN_IN_TOP_RIGHT,
	},
	{
		.app = lv_ex_label_2,
		.ret_btn_opa_scale = LV_OPA_100,
		.ret_btn_align = LV_ALIGN_IN_TOP_RIGHT,
	},
	{
#if USE_EX_LABEL_3
		.app = lv_ex_label_3,
#endif
		.ret_btn_opa_scale = LV_OPA_100,
		.ret_btn_align = LV_ALIGN_IN_TOP_RIGHT,
	},
	{
		.app = lv_ex_led_1,
		.ret_btn_opa_scale = LV_OPA_100,
		.ret_btn_align = LV_ALIGN_IN_TOP_RIGHT,
	},
	{
		.app = lv_ex_line_1,
		.ret_btn_opa_scale = LV_OPA_100,
		.ret_btn_align = LV_ALIGN_IN_TOP_RIGHT,
	},
	{
		.app = lv_ex_list_1,
		.ret_btn_opa_scale = LV_OPA_100,
		.ret_btn_align = LV_ALIGN_IN_TOP_RIGHT,
	},
	{
		.app = lv_ex_linemeter_1,
		.ret_btn_opa_scale = LV_OPA_100,
		.ret_btn_align = LV_ALIGN_IN_TOP_RIGHT,
	},
	{
		.app = lv_ex_msgbox_1,
		.ret_btn_opa_scale = LV_OPA_100,
		.ret_btn_align = LV_ALIGN_IN_TOP_RIGHT,
	},
	{
		.app = lv_ex_msgbox_2,
		.ret_btn_opa_scale = LV_OPA_100,
		.ret_btn_align = LV_ALIGN_IN_TOP_RIGHT,
	},
	{
		.app = lv_ex_obj_1,
		.ret_btn_opa_scale = LV_OPA_100,
		.ret_btn_align = LV_ALIGN_IN_TOP_RIGHT,
	},
	{
		.app = lv_ex_page_1,
		.ret_btn_opa_scale = LV_OPA_100,
		.ret_btn_align = LV_ALIGN_IN_TOP_RIGHT,
	},
	{
		.app = lv_ex_spinner_1,
		.ret_btn_opa_scale = LV_OPA_100,
		.ret_btn_align = LV_ALIGN_IN_TOP_RIGHT,
	},
	{
		.app = lv_ex_roller_1,
		.ret_btn_opa_scale = LV_OPA_100,
		.ret_btn_align = LV_ALIGN_IN_TOP_RIGHT,
	},
	{
		.app = lv_ex_slider_1,
		.ret_btn_opa_scale = LV_OPA_100,
		.ret_btn_align = LV_ALIGN_IN_TOP_RIGHT,
	},
	{
		.app = lv_ex_slider_2,
		.ret_btn_opa_scale = LV_OPA_100,
		.ret_btn_align = LV_ALIGN_IN_TOP_RIGHT,
	},
	{
		.app = lv_ex_spinbox_1,
		.ret_btn_opa_scale = LV_OPA_100,
		.ret_btn_align = LV_ALIGN_IN_TOP_RIGHT,
	},
	{
		.app = lv_ex_switch_1,
		.ret_btn_opa_scale = LV_OPA_100,
		.ret_btn_align = LV_ALIGN_IN_TOP_RIGHT,
	},

	{
		.app = lv_ex_textarea_1,
		.ret_btn_opa_scale = LV_OPA_100,
		.ret_btn_align = LV_ALIGN_IN_TOP_RIGHT,
	},
	{
		.app = lv_ex_textarea_2,
		.ret_btn_opa_scale = LV_OPA_100,
		.ret_btn_align = LV_ALIGN_IN_TOP_RIGHT,
	},
	{
		.app = lv_ex_textarea_3,
		.ret_btn_opa_scale = LV_OPA_100,
		.ret_btn_align = LV_ALIGN_IN_TOP_RIGHT,
	},
	{
		.app = dispatch_lv_ex_objmask_1,
		.ret_btn_opa_scale = LV_OPA_100,
		.ret_btn_align = LV_ALIGN_IN_TOP_RIGHT,
	},
	{
		.app = lv_ex_objmask_2,
		.ret_btn_opa_scale = LV_OPA_100,
		.ret_btn_align = LV_ALIGN_IN_TOP_RIGHT,
	},
	{
		.app = lv_ex_table_1,
		.ret_btn_opa_scale = LV_OPA_100,
		.ret_btn_align = LV_ALIGN_IN_TOP_RIGHT,
	},
	{
		.app = lv_ex_tabview_1,
		.ret_btn_opa_scale = LV_OPA_100,
		.ret_btn_align = LV_ALIGN_IN_TOP_RIGHT,
	},
	{
		.app = lv_ex_tileview_1,
		.ret_btn_opa_scale = LV_OPA_100,
		.ret_btn_align = LV_ALIGN_IN_TOP_RIGHT,
	},
	{
		.app = lv_ex_win_1,
		.ret_btn_opa_scale = LV_OPA_100,
		.ret_btn_align = LV_ALIGN_IN_TOP_MID,
	},
};
#define NB_PGE_DSCS (sizeof(pge_dscs_unmngd)/sizeof(pge_dscs_unmngd[0]))

static sndbx_pge_t app_pages[NB_PGE_DSCS] = {
	{ .dsc_u = &pge_dscs_unmngd[0], },
	{ .dsc_u = &pge_dscs_unmngd[1], },
	{ .dsc_u = &pge_dscs_unmngd[2], },
	{ .dsc_u = &pge_dscs_unmngd[3], },
	{ .dsc_u = &pge_dscs_unmngd[4], },
	{ .dsc_u = &pge_dscs_unmngd[5], },
	{ .dsc_u = &pge_dscs_unmngd[6], },
	{ .dsc_u = &pge_dscs_unmngd[7], },
	{ .dsc_u = &pge_dscs_unmngd[8], },
	{ .dsc_u = &pge_dscs_unmngd[9], },
	{ .dsc_u = &pge_dscs_unmngd[10], },
	{ .dsc_u = &pge_dscs_unmngd[11], },
	{ .dsc_u = &pge_dscs_unmngd[12], },
	{ .dsc_u = &pge_dscs_unmngd[13], },
	{ .dsc_u = &pge_dscs_unmngd[14], },
	{ .dsc_u = &pge_dscs_unmngd[15], },
	{ .dsc_u = &pge_dscs_unmngd[16], },
	{ .dsc_u = &pge_dscs_unmngd[17], },
	{ .dsc_u = &pge_dscs_unmngd[18], },
	{ .dsc_u = &pge_dscs_unmngd[19], },
	{ .dsc_u = &pge_dscs_unmngd[20], },
	{ .dsc_u = &pge_dscs_unmngd[21], },
	{ .dsc_u = &pge_dscs_unmngd[22], },
	{ .dsc_u = &pge_dscs_unmngd[23], },
	{ .dsc_u = &pge_dscs_unmngd[24], },
	{ .dsc_u = &pge_dscs_unmngd[25], },
	{ .dsc_u = &pge_dscs_unmngd[26], },
	{ .dsc_u = &pge_dscs_unmngd[27], },
	{ .dsc_u = &pge_dscs_unmngd[28], },
	{ .dsc_u = &pge_dscs_unmngd[29], },
	{ .dsc_u = &pge_dscs_unmngd[30], },
	{ .dsc_u = &pge_dscs_unmngd[31], },
	{ .dsc_u = &pge_dscs_unmngd[32], },
	{ .dsc_u = &pge_dscs_unmngd[33], },
	{ .dsc_u = &pge_dscs_unmngd[34], },
	{ .dsc_u = &pge_dscs_unmngd[35], },
	{ .dsc_u = &pge_dscs_unmngd[36], },
	{ .dsc_u = &pge_dscs_unmngd[37], },
	{ .dsc_u = &pge_dscs_unmngd[38], },
	{ .dsc_u = &pge_dscs_unmngd[39], },
	{ .dsc_u = &pge_dscs_unmngd[40], },
	{ .dsc_u = &pge_dscs_unmngd[41], },
	{ .dsc_u = &pge_dscs_unmngd[42], },
	{ .dsc_u = &pge_dscs_unmngd[43], },
	{ .dsc_u = &pge_dscs_unmngd[44], },
	{ .dsc_u = &pge_dscs_unmngd[45], },
	{ .dsc_u = &pge_dscs_unmngd[46], },
	{ .dsc_u = &pge_dscs_unmngd[47], },
	{ .dsc_u = &pge_dscs_unmngd[48], },
	{ .dsc_u = &pge_dscs_unmngd[49], },
};

static const char * const btnm_map1[] = {
	"arc 1", "arc 2", "bar", "button 1", "button 2", "\n",
	"btnmatrix", "calendar", "canvas 1", "canvas 2", "checkbox", "\n",
	"chart 1", "chart 2", "cont", "cpicker 1", "cpicker 2", "\n",
	"dropdown 1", "dropdown 2", "gauge 1", "gauge 2", "img 1",
	"",
};
static const char * const btnm_map2[] = {
	"img 2", "img 3", "imgbtn", "keyboard", "label 1", "\n",
	"label 2", "label 3", "led","line", "list", "\n",
	"linemeter", "mbox 1", "mbox 2", "obj", "page", "\n",
	"spinner", "roller", "slider 1", "slider 2", "spinbox",
	"",
};
static const char* const btnm_map3[] = {
	"sw", "ta 1", "ta 2", "ta 3 ", "objmask1","\n",
	"objmask2",  "table", "tabview", "tileview", "win",
	"",
};

static const struct sndbx_pge_lv_ex_widgets_prms pge_prms[3];
static const sndbx_pge_t pages[3] = {
	{.dsc = &sndbx_pge_lv_ex_widgets_dsc, &pge_prms[0]},
	{.dsc = &sndbx_pge_lv_ex_widgets_dsc, &pge_prms[1]},
	{.dsc = &sndbx_pge_lv_ex_widgets_dsc, &pge_prms[2]},
};
static const sndbx_pge_lv_ex_widgets_prms_t pge_prms[3] = {
	{.links.left = NULL         , .links.right = &pages[1], .index = 0},
	{.links.left = &pages[0]    , .links.right = &pages[2], .index = 1},
	{.links.left = &pages[1],                         NULL, .index = 2},
};

static lv_theme_t * theme;

/**********************
 *      MACROS
 **********************/
#define MEM_INIT(to,from)	mem_t*(to) = (from)

/**********************
 *   GLOBAL DESCRIPTORS
 **********************/

const sndbx_pge_dsc_t sndbx_pge_lv_ex_widgets_dsc = {
	.name = PAGE_NAME,
	.mem_size = sizeof(mem_t),
	.create_cb = create_cb,
	.settings_cb = settings_cb,
};

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

/**
 * Create a sandbox application
 */
void sndbx_pge_lv_ex_widgets_test( void )
{
	sndbx_app_create(&pages[0]);
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
	const sndbx_pge_lv_ex_widgets_prms_t * pge_prms = prms;
	MEM_INIT(mem, p_mem);
	mem->parent = parent;
	 
	/* Create content */
	lv_coord_t w_par = lv_obj_get_width(parent);
	lv_coord_t h_par = lv_obj_get_height(parent);

	lv_obj_t * lbl = lv_label_create(parent, NULL);
	lv_label_set_text_static(lbl, "Please select an example to run");
	lv_obj_align(lbl, NULL, LV_ALIGN_IN_TOP_MID, 0, LV_DPI/4 );

	lv_obj_t * btnm = lv_btnmatrix_create(parent, NULL);

	const char ** bntm_maps[3] = { (const char**)btnm_map1, (const char**)btnm_map2 , (const char**)btnm_map3 };
	const char ** bntm_map = bntm_maps[pge_prms->index];

	lv_btnmatrix_set_map( btnm, bntm_map );
	lv_obj_set_size( btnm, w_par * 3 / 4, h_par * 3 / 4 );
	lv_obj_align( btnm, lbl, LV_ALIGN_OUT_BOTTOM_MID, 0, LV_DPI / 6 );
	lv_obj_set_event_cb( btnm, btnm_event_handler );
	lv_obj_set_user_data( btnm, &app_pages[pge_prms->index*20] );

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
	uint16_t idx = lv_btnmatrix_get_active_btn(obj);
	if (idx >= NB_APP_PAGES)
		return;
	const sndbx_pge_t *pages = lv_obj_get_user_data(obj);
	sndbx_pge_change(&pages[idx]);
}

/*===================== Callbacks and Events================== */

/*Help*/
/**
 * Called on help message box close button events
 * @param obj pointer to button
 * @param evt event that occurred
 */
static void settings_event_handler( lv_obj_t * obj, lv_event_t evt )
{
	mem_t* mem = sndbx_pge_get_mem();
	if (evt == LV_EVENT_DELETE)
	{
		sndbx_settings_btn_restore_parent();
		if( mem->obj_modal )
			lv_obj_del_async(mem->obj_modal);
		return;	
	}

	if (evt != LV_EVENT_CLICKED)
		return;
	mem->setings_active = false;

	lv_msgbox_start_auto_close(obj, 0);
	sndbx_help_btn_enable_set(true);
}

/**
 * Called on sandbox toolbar help button events
 * @param obj pointer to help button
 * @param evt event that occurred
 */
static bool settings_cb( void * p_mem, lv_event_t evt )
{	
	LV_LOG_INFO("Settings event %d", evt);
	if( evt != LV_EVENT_CLICKED )
		return false;
	MEM_INIT(mem, p_mem);

	if (mem->setings_active)
		return false;

	mem->setings_active = true;
	mem->obj_modal = sndbx_obj_modal_settings_create();
	lv_obj_t * mbox = lv_msgbox_create(mem->obj_modal, NULL);

	lv_obj_set_drag( mbox, true );
	lv_msgbox_set_text( mbox,
		PAGE_NAME" Settings message box\n"
		"Some settings here\n"
	);
	static const char* btns[] = { "Ok", "" };
	lv_msgbox_add_btns( mbox, btns );
	lv_obj_align( mbox, NULL, LV_ALIGN_CENTER, 0, 0 );

	lv_obj_set_event_cb( mbox, settings_event_handler );

	return false;
}

#endif  /*USE_SNDBX_PGE_LV_EX_WIDGETS*/
