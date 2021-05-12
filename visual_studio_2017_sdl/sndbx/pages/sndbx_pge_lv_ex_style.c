/**
 * @file sndbx_pge_lv_ex_style.c
 *
 */

 /*********************
  *      INCLUDES
  *********************/
#include "sndbx_pge_lv_ex_style.h"
#if USE_SNDBX_PGE_LV_EX_STYLE

#include "lv_examples/src/lv_ex_style/lv_ex_style.h"

/*********************
 * EXTERNAL PROTOTYPES
 *********************/

/*********************
 *      DEFINES
 *********************/
#if LV_HOR_RES_MAX < 800
#define PAGE_NAME "lv Style"
#else
#define PAGE_NAME "LVGL Style examples"
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

/**********************
 *  STATIC VARIABLES
 **********************/

/*Unmanaged page descriptors*/
static const sndbx_pge_dsc_unmngd_t pge_dscs_unmngd[] = {
	{
		.app = lv_ex_style_1,
		.ret_btn_opa_scale = LV_OPA_100,
		.ret_btn_align = LV_ALIGN_IN_TOP_RIGHT,
	},
	{
		.app = lv_ex_style_2,
		.ret_btn_opa_scale = LV_OPA_100,
		.ret_btn_align = LV_ALIGN_IN_TOP_RIGHT,
	},
	{
		.app = lv_ex_style_3,
		.ret_btn_opa_scale = LV_OPA_100,
		.ret_btn_align = LV_ALIGN_IN_TOP_RIGHT,
	},
	{
		.app = lv_ex_style_4,
		.ret_btn_opa_scale = LV_OPA_100,
		.ret_btn_align = LV_ALIGN_IN_TOP_RIGHT,
	},
	{
		.app = lv_ex_style_5,
		.ret_btn_opa_scale = LV_OPA_100,
		.ret_btn_align = LV_ALIGN_IN_TOP_RIGHT,
	},
	{
		.app = lv_ex_style_6,
		.ret_btn_opa_scale = LV_OPA_100,
		.ret_btn_align = LV_ALIGN_IN_TOP_RIGHT,
	},
	{
		.app = lv_ex_style_7,
		.ret_btn_opa_scale = LV_OPA_100,
		.ret_btn_align = LV_ALIGN_IN_TOP_RIGHT,
	},
	{
		.app = lv_ex_style_8,
		.ret_btn_opa_scale = LV_OPA_100,
		.ret_btn_align = LV_ALIGN_IN_TOP_RIGHT,
	},
	{
		.app = lv_ex_style_9,
		.ret_btn_opa_scale = LV_OPA_100,
		.ret_btn_align = LV_ALIGN_IN_TOP_RIGHT,
	},
	{
		.app = lv_ex_style_10,
		.ret_btn_opa_scale = LV_OPA_100,
		.ret_btn_align = LV_ALIGN_IN_TOP_RIGHT,
	},
	{
		.app = lv_ex_style_11,
		.ret_btn_opa_scale = LV_OPA_100,
		.ret_btn_align = LV_ALIGN_IN_TOP_RIGHT,
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
};

static const char * const btnm_map[] = {
	"Brackgroud", "Border", "Outline", "Shadow", "\n",
	"Patern", "Value", "Text", "Line", "\n",
	"Image", "Transitions", "Scale",
	"",
};
static const sndbx_pge_t pages[1] = {
	{.dsc = &sndbx_pge_lv_ex_style_dsc, NULL},
};

static lv_theme_t * theme;

/**********************
 *      MACROS
 **********************/
#define MEM_INIT(to,from)	mem_t*(to) = (from)

/**********************
 *   GLOBAL DESCRIPTORS
 **********************/

const sndbx_pge_dsc_t sndbx_pge_lv_ex_style_dsc = {
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
void sndbx_pge_lv_ex_style_test( void )
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
	MEM_INIT(mem, p_mem);
	mem->parent = parent;
	 
	/* Create content */
	lv_coord_t w_par = lv_obj_get_width(parent);
	lv_coord_t h_par = lv_obj_get_height(parent);

	lv_obj_t * lbl = lv_label_create(parent, NULL);
	lv_label_set_text_static(lbl, "Using Style Properties");
	lv_obj_align(lbl, NULL, LV_ALIGN_IN_TOP_MID, 0, LV_DPI/4 );

	lv_obj_t * btnm = lv_btnmatrix_create(parent, NULL);

	const char ** bntm_maps[1] = { (const char**)btnm_map,};
	const char ** bntm_map = bntm_maps[0];

	lv_btnmatrix_set_map( btnm, bntm_map );
	lv_obj_set_size( btnm, w_par * 3 / 4, h_par * 3 / 4 );
	lv_obj_align( btnm, lbl, LV_ALIGN_OUT_BOTTOM_MID, 0, LV_DPI / 6 );
	lv_obj_set_event_cb( btnm, btnm_event_handler );
	lv_obj_set_user_data( btnm, &app_pages[0] );
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
