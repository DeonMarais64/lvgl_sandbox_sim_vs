/**
 * @file sndbx_pge_lv_tests.c
 *
 */

 /*********************
  *      INCLUDES
  *********************/
#include "sndbx_pge_lv_tests.h"
#if USE_SNDBX_PGE_LV_TESTS

#include "lv_examples/lv_tests/lv_test_group/lv_test_group.h"
#include "lv_examples/lv_tests/lv_test_misc/lv_test_task.h"
#include "lv_examples/lv_tests/lv_test_obj/lv_test_obj.h"
#include "lv_examples/lv_tests/lv_test_theme/lv_test_theme_1.h"
#include "lv_examples/lv_tests/lv_test_theme/lv_test_theme_2.h"

/*********************
 * EXTERNAL PROTOTYPES
 *********************/

/*********************
 *      DEFINES
 *********************/
#define PAGE_NAME "LittlevGL Tests"

/*Cannot run as lv_test_group.c currently is written...
 *..Probably need to add a epilogue function that ..
 *..deletes all of the added input devices.*/
#define TEST_GROUP 0

/*Cannot run these as lv_test_task.c currently is written...
 *..Probably need to add epilogue function that ..
 *..deletes all of the added tasks.*/
#define TEST_TASKS 0

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
/*Unmanaged page descriptors*/
static const sndbx_pge_dsc_unmngd_t pge_dscs_unmngd[] = {
#if TEST_GROUP
	{
		.app = (sndbx_pge_unmngd_cb_t)lv_test_group_1,
		.ret_btn_opa_scale = LV_OPA_100,
		.ret_btn_align = LV_ALIGN_IN_TOP_RIGHT,
	},
#endif
	{
		.app = (sndbx_pge_unmngd_cb_t)lv_test_object_1,
		.ret_btn_opa_scale = LV_OPA_100,
		.ret_btn_align = LV_ALIGN_IN_TOP_RIGHT,
	},
#if TEST_TASKS
	{
		.app = (sndbx_pge_unmngd_cb_t)lv_test_task_1,
		.ret_btn_opa_scale = LV_OPA_100,
		.ret_btn_align = LV_ALIGN_IN_TOP_RIGHT,
	},
	{
		.app = (sndbx_pge_unmngd_cb_t)lv_test_task_2,
		.ret_btn_opa_scale = LV_OPA_100,
		.ret_btn_align = LV_ALIGN_IN_TOP_RIGHT,
	},
	{
		.app = (sndbx_pge_unmngd_cb_t)lv_test_task_3,
		.ret_btn_opa_scale = LV_OPA_100,
		.ret_btn_align = LV_ALIGN_IN_TOP_RIGHT,
	},
#endif
	{
		.app = (sndbx_pge_unmngd_cb_t)lv_test_theme_2,
		.ret_btn_opa_scale = LV_OPA_80,
		.ret_btn_align = LV_ALIGN_IN_BOTTOM_LEFT,
	},
};
#define NB_PGE_DSCS (sizeof(pge_dscs_unmngd)/sizeof(pge_dscs_unmngd[0]))

static sndbx_pge_t app_pages[NB_PGE_DSCS] = {
	{.dsc_u = &pge_dscs_unmngd[0], },
	{.dsc_u = &pge_dscs_unmngd[1], },
#if TEST_GROUP
	{.dsc_u = &pge_dscs_unmngd[2], },
#endif
#if TEST_TASKS
	{.dsc_u = &pge_dscs_unmngd[3], },
	{.dsc_u = &pge_dscs_unmngd[4], },
	{.dsc_u = &pge_dscs_unmngd[5], },
#endif
};

static const char * const btnm_map[] = {
#if TEST_GROUP
	"Group",
#endif
#if TEST_TASKS
	"Objects", "Tasks 1", "\n",
	"Tasks 2", "Tasks 3", "Theme 2",
#else
	"Objects", "Theme 2",
#endif
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

const sndbx_pge_dsc_t sndbx_pge_lv_tests_dsc = {
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
void sndbx_pge_lv_tests_test( void ) 
{
	static const sndbx_pge_t page = {
		.dsc = &sndbx_pge_lv_tests_dsc, 
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
	const sndbx_pge_prms_lr_t * pge_prms = prms;
	MEM_INIT(mem, p_mem);
	mem->parent = parent;

	/* Create content */
	lv_coord_t w_par = lv_obj_get_width(parent);
	lv_coord_t h_par = lv_obj_get_height(parent);

	lv_obj_t * lbl = label_create(parent, "Please select a test to run");
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

static void save_theme(void)
{
	if( !theme )
		theme = lv_theme_get_current();
}

static void recover_theme(void)
{
//	if (theme)
//		lv_theme_set_current(theme);
	extern void app_init_theme( void );
	app_init_theme();
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

#endif  /*USE_SNDBX_PGE_LV_TESTS*/
