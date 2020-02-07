/**
 * @file sndbx_pge_lv_tuts.c
 *
 */

 /*********************
  *      INCLUDES
  *********************/
#include "sndbx_pge_lv_tuts.h"
#if USE_SNDBX_PGE_LV_TUTS

#include "lv_examples/lv_tutorial/1_hello_world/lv_tutorial_hello_world.h"
#include "lv_examples/lv_tutorial/2_objects/lv_tutorial_objects.h"
#include "lv_examples/lv_tutorial/3_styles/lv_tutorial_styles.h"
#include "lv_examples/lv_tutorial/4_themes/lv_tutorial_themes.h"
#include "lv_examples/lv_tutorial/5_antialiasing/lv_tutorial_antialiasing.h"
#include "lv_examples/lv_tutorial/6_images/lv_tutorial_images.h"
#include "lv_examples/lv_tutorial/7_fonts/lv_tutorial_fonts.h"
#include "lv_examples/lv_tutorial/8_animations/lv_tutorial_animations.h"
#include "lv_examples/lv_tutorial/9_responsive/lv_tutorial_responsive.h"
#include "lv_examples/lv_tutorial/10_keyboard/lv_tutorial_keyboard.h"

/*********************
 * EXTERNAL PROTOTYPES
 *********************/

/*********************
 *      DEFINES
 *********************/
#define PAGE_NAME "LittlevGL Tutorials"

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

static void tutorial_keyboard(void)
{
	lv_tutorial_keyboard(NULL);
}

/**********************
 *  STATIC VARIABLES
 **********************/
/*Unmanaged page descriptors*/
static const sndbx_pge_dsc_unmngd_t pge_dscs_unmngd[] = {
	{
//		.app = (sndbx_pge_unmngd_cb_t)lv_tutorial_hello_world,
		.app = lv_tutorial_hello_world,
		.ret_btn_opa_scale = LV_OPA_100,
		.ret_btn_align = LV_ALIGN_IN_TOP_RIGHT,
	},
	{
		.app = (sndbx_pge_unmngd_cb_t)lv_tutorial_objects,
		.ret_btn_opa_scale = LV_OPA_100,
		.ret_btn_align = LV_ALIGN_IN_TOP_RIGHT,
	},
	{
		.app = (sndbx_pge_unmngd_cb_t)lv_tutorial_styles,
		.ret_btn_opa_scale = LV_OPA_100,
		.ret_btn_align = LV_ALIGN_IN_TOP_RIGHT,
	},
	{
		.prologue = save_theme,
		.app = (sndbx_pge_unmngd_cb_t)lv_tutorial_themes,
		.epilogue = recover_theme,
		.ret_btn_opa_scale = LV_OPA_100,
		.ret_btn_align = LV_ALIGN_IN_TOP_RIGHT,
	},
	{
		.app = (sndbx_pge_unmngd_cb_t)lv_tutorial_antialiasing,
		.ret_btn_opa_scale = LV_OPA_100,
		.ret_btn_align = LV_ALIGN_IN_TOP_RIGHT,
	},
	{
		.app = (sndbx_pge_unmngd_cb_t)lv_tutorial_image,
		.ret_btn_opa_scale = LV_OPA_100,
		.ret_btn_align = LV_ALIGN_IN_TOP_RIGHT,
	},
	{
		.app = (sndbx_pge_unmngd_cb_t)lv_tutorial_fonts,
		.ret_btn_opa_scale = LV_OPA_100,
		.ret_btn_align = LV_ALIGN_IN_TOP_RIGHT,
	},
	{
		.app = (sndbx_pge_unmngd_cb_t)lv_tutorial_animations,
		.ret_btn_opa_scale = LV_OPA_100,
		.ret_btn_align = LV_ALIGN_IN_TOP_RIGHT,
	},
	{
		.app = (sndbx_pge_unmngd_cb_t)lv_tutorial_responsive,
		.ret_btn_opa_scale = LV_OPA_100,
		.ret_btn_align = LV_ALIGN_IN_TOP_RIGHT,
	},
	{
		.app = (sndbx_pge_unmngd_cb_t)tutorial_keyboard,
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
};

static const char * const btnm_map[] = {
	"Hello World",	"Objects", 	"Styles", "Themes", "\n",
	"Antialiasing", "Images", 	"Fonts", "Animations", "\n",
	"Responsive", "Keyboard",
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

const sndbx_pge_dsc_t sndbx_pge_lv_tuts_dsc = {
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
void sndbx_pge_lv_tuts_test( void ) 
{
	static const sndbx_pge_t page = {
		.dsc = &sndbx_pge_lv_tuts_dsc, 
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

	lv_obj_t * lbl = label_create(parent, "Please select a tutorial to run");
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

#endif  /*USE_SNDBX_PGE_LV_TUTS*/
