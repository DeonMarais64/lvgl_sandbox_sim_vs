/**
 * @file sndbx_pge_lv_demos.c
 *
 */

 /*********************
  *      INCLUDES
  *********************/
#include "sndbx_pge_lv_demos.h"
#if USE_SNDBX_PGE_LV_DEMOS

#include "lv_examples/src/lv_demo_benchmark/lv_demo_benchmark.h"
#include "lv_examples/src/lv_demo_keypad_encoder/lv_demo_keypad_encoder.h"
#include "lv_examples/src/lv_demo_printer/lv_demo_printer.h"
#include "lv_examples/src/lv_demo_stress/lv_demo_stress.h"
#include "lv_examples/src/lv_demo_widgets/lv_demo_widgets.h"

/*********************
 * EXTERNAL PROTOTYPES
 *********************/

/*********************
 *      DEFINES
 *********************/
#define PAGE_NAME "LVGL Demos"

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

static void btnm_event_handler(lv_obj_t * obj, lv_event_t evt);

/**********************
 *  STATIC VARIABLES
 **********************/

/*Unmanaged page descriptors*/
static const sndbx_pge_dsc_unmngd_t pge_dscs_unmngd[] = {
	{
		.app = lv_demo_benchmark,
		.ret_btn_opa_scale = LV_OPA_100,
		.ret_btn_align = LV_ALIGN_IN_TOP_RIGHT,
	},
	{
		.app = lv_demo_keypad_encoder,
		.ret_btn_opa_scale = LV_OPA_100,
		.ret_btn_align = LV_ALIGN_IN_TOP_RIGHT,
	},
	{
		.app = lv_demo_printer,
		.ret_btn_opa_scale = LV_OPA_100,
		.ret_btn_align = LV_ALIGN_IN_TOP_RIGHT,
	},
	{
		.app = lv_demo_stress,
		.ret_btn_opa_scale = LV_OPA_100,
		.ret_btn_align = LV_ALIGN_IN_TOP_RIGHT,
	},
	{
		.app = lv_demo_widgets,
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
};

static const char * const btnm_map[] = {
	"Benchmark", "\n",
	"Keypad Encoder", "\n",
	"Printer", "\n",
	"Stress", "\n",
	"Widgets",
	"",
};

/**********************
 *      MACROS
 **********************/
#define MEM_INIT(to,from)	mem_t*(to) = (from)

/**********************
 *   GLOBAL DESCRIPTORS
 **********************/

const sndbx_pge_dsc_t sndbx_pge_lv_demos_dsc = {
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
void sndbx_pge_lv_demos_test( void ) 
{
	static const sndbx_pge_t page = {
		.dsc = &sndbx_pge_lv_demos_dsc, .prms = NULL ,
	};

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
	MEM_INIT(mem, p_mem);
	mem->parent = parent;
	 
	/* Create content */
	lv_coord_t w_par = lv_obj_get_width(parent);
	lv_coord_t h_par = lv_obj_get_height(parent);

	lv_obj_t * lbl = lv_label_create(parent, NULL);
	lv_label_set_text_static(lbl, "Please select a demo to run");
	lv_obj_align(lbl, NULL, LV_ALIGN_IN_TOP_MID, 0, LV_DPI/4 );

	lv_obj_t * btnm = lv_btnmatrix_create(parent, NULL);

	lv_btnmatrix_set_map( btnm, (const char **)btnm_map );
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
	if (idx >= NB_PGE_DSCS)
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

	lv_obj_t * mbox = lv_msgbox_create( mem->parent, NULL );
	lv_obj_set_drag( mbox, true );
	lv_msgbox_set_text( mbox,
		PAGE_NAME" help message box\n"
		"Some help here\n"
	);
	lv_msgbox_add_btns( mbox, btns );
	lv_obj_align( mbox, NULL, LV_ALIGN_CENTER, 0, 0 );

	lv_obj_set_event_cb( mbox, help_event_handler );

	return true;
}

/* Helpers from here */
static lv_obj_t *label_create( lv_obj_t *par, const char *txt )
{
	lv_obj_t * lbl = lv_label_create( par, NULL );
	lv_label_set_text_static( lbl, txt );

	return lbl;
}

#endif  /*USE_SNDBX_PGE_LV_DEMOS*/
