/**
 * @file sndbx_pge_sndbx_demo.c
 *
 */

 /*********************
  *      INCLUDES
  *********************/
#include "sndbx_pge_sndbx_demo.h"
#if USE_SNDBX_PGE_SNDBX_DEMO

#include "sndbx_pge_demo.h"
#include "sndbx_pge_template.h"
#include "sndbx_pge_anim_see.h"
#include "sndbx_pge_lv_app_benchmark.h"
#include "sndbx_pge_lv_test_theme_2.h"
#include "sndbx_pge_table.h"

/*********************
 * EXTERNAL PROTOTYPES
 *********************/

/*********************
 *      DEFINES
 *********************/
#define PAGE_NAME "Sandbox demos"

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

/**********************
 *  STATIC VARIABLES
 **********************/

static const struct sndbx_pge_demo_prms prms[6];

static sndbx_pge_t app_pages[] = {
	{ .dsc = &sndbx_pge_demo_dscs[1]		, &prms[0] },
	{ .dsc = &sndbx_pge_template_dscs[0]	, &prms[1] },
//	{ .dsc = &sndbx_pge_demo_dscs[2]		, &prms[2] },
	{ .dsc = &sndbx_pge_anim_see_dsc		, &prms[2] },
//	{ .dsc = &sndbx_pge_template_dscs[1]	, &prms[3] },
	{ .dsc = &sndbx_pge_lv_app_benchmark_dsc, &prms[3] },
	{ .dsc = &sndbx_pge_lv_test_theme_2_dsc , &prms[4] },
//	{ .dsc = &sndbx_pge_template_dscs[2]	, &prms[5] },
	{ .dsc = &sndbx_pge_table_dsc			, &prms[5] },
};

static const sndbx_pge_demo_prms_t prms[6] = {
	{.links.left =          NULL,.links.right = &app_pages[1],.self = &sndbx_pge_demo_dscs[1]},
	{.links.left = &app_pages[0],.links.right = &app_pages[2], },
//	{.links.left = &app_pages[1],.links.right = &app_pages[3],.self = &sndbx_pge_demo_dscs[2]},
	{.links.left = &app_pages[1],.links.right = &app_pages[3], },
	{.links.left = &app_pages[2],.links.right = &app_pages[4], },
	{.links.left = &app_pages[3],.links.right = &app_pages[5],.self = &sndbx_pge_demo_dscs[3]},
	{.links.left = &app_pages[4],.links.right = NULL, },
};

static const char * const btnm_map[] = {
	"Demo 2", "Template 1", "\n",
	"Animation Chart", "LittlevGL Benchmark\nSandbox Managed", "\n",
	"lv_test_theme_2\nSandbox Managed", "Table Dynamic",
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

const sndbx_pge_dsc_t sndbx_pge_sndbx_demo_dsc = {
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
void sndbx_pge_sndbx_demo_test( void )
{
	static const sndbx_pge_t page = {
		.dsc = &sndbx_pge_sndbx_demo_dsc,
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
 */
static void create_cb( lv_obj_t * parent, void * p_mem, const void * prms )
{
	const sndbx_pge_prms_lr_t * pge_prms = prms;
	MEM_INIT(mem, p_mem);
	mem->parent = parent;

	/* Create content */
	lv_coord_t w_par = lv_obj_get_width(parent);
	lv_coord_t h_par = lv_obj_get_height(parent);

	lv_obj_t * lbl = label_create(parent, "Please select a demo to run");
	lv_obj_align(lbl, NULL, LV_ALIGN_IN_TOP_MID, 0, LV_DPI/4 );


	lv_obj_t * btnm = lv_btnm_create(parent, NULL);
	lv_btnm_set_map(btnm, (const char**)btnm_map);
	lv_obj_set_size(btnm, w_par * 3 / 4, h_par * 3 / 4);
	lv_obj_align(btnm, lbl, LV_ALIGN_OUT_BOTTOM_MID, 0, LV_DPI / 6);
	lv_obj_set_event_cb(btnm, btnm_event_handler);

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
	const sndbx_pge_t *page = &app_pages[idx];
	sndbx_pge_change(page);
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

#endif  /*USE_SNDBX_PGE_SNDBX_DEMO*/
