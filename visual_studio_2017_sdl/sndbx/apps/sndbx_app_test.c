/**
 * @file sndbx_app_test.c
 *
 */

 /*********************
  *      INCLUDES
  *********************/
#include "sndbx_app_test.h"
#if USE_SNDBX_APP_TEST
#include "../pages/sndbx_pge_demo.h"
#include "../pages/sndbx_pge_templ.h"
#include "../pages/sndbx_pge_anim_see.h"
#include "../pages/sndbx_pge_template.h"
#include "../pages/sndbx_pge_table.h"
#include "../pages/sndbx_pge_lv_app_demo.h"
#include "../pages/sndbx_pge_lv_app_sysmon.h"
#include "../pages/sndbx_pge_lv_app_benchmark.h"

#include <stdio.h>

/*********************
 *      DEFINES
 *********************/
#define PAGE_NAME "Sandbox App Test"

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

static void btnmatrix_event_handler(lv_obj_t * obj, lv_event_t evt);

static lv_obj_t * label_create( lv_obj_t * par, const char * txt );

/**********************
 *  STATIC VARIABLES
 **********************/
/* Descriptors for this page, IE home page */
static const sndbx_pge_dsc_t dsc = {
	.name = PAGE_NAME,
	.mem_size = sizeof( mem_t ),
	.create_cb = create_cb,
};

typedef struct prms_app_pges {
	struct {
		const sndbx_pge_t* left;
		const sndbx_pge_t* right;
	} links;
	union {
		const sndbx_pge_dsc_t* self;
	};
} prms_app_pges_t;
static const struct prms_app_pges pge_prms[8];

static const sndbx_pge_t app_pages[] = {
	{.dsc = &sndbx_pge_lv_app_demo_dsc, &pge_prms[0],},
	{.dsc = &sndbx_pge_lv_app_sysmon_dsc,&pge_prms[1], },
	{.dsc = &sndbx_pge_lv_app_benchmark_dsc,&pge_prms[2], },
	{.dsc = &sndbx_pge_templ_dsc,&pge_prms[3], },
	{.dsc = &sndbx_pge_template_dscs[0],.prms = &pge_prms[4] },
	{.dsc = &sndbx_pge_demo_dscs[3],.prms = &pge_prms[5] },
	{.dsc = &sndbx_pge_anim_see_dsc,&pge_prms[6], },
	{.dsc = &sndbx_pge_table_dsc,&pge_prms[7], },
};

static const prms_app_pges_t pge_prms[8] = {
	{.links.left =          NULL,.links.right = &app_pages[1],},
	{.links.left = &app_pages[0],.links.right = &app_pages[2],},
	{.links.left = &app_pages[1],.links.right = &app_pages[3],},
	{.links.left = &app_pages[2],.links.right = &app_pages[4],},
	{.links.left = &app_pages[3],.links.right = &app_pages[5],},
	{.links.left = &app_pages[4],.links.right = &app_pages[6],.self = &sndbx_pge_demo_dscs[3]},
	{.links.left = &app_pages[5],.links.right = &app_pages[7],},
	{.links.left = &app_pages[6],.links.right = &app_pages[0],},
};


/**********************
 *      MACROS
 **********************/
#define MEM_INIT(to,from)	mem_t*(to) = (from)

/**********************
 *   GLOBAL FUNCTIONS
 **********************/
/**
 * Create a demo application
 */
void sndbx_app_test_test( void )
{
	static const sndbx_pge_t page = {
		.dsc = &dsc,
	};

//	lv_theme_t* th;
//	th = lv_theme_default_init(0, NULL);
//	lv_theme_set_current(th);
	sndbx_app_create(&page);
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

static void btnmatrix_event_handler( lv_obj_t * obj, lv_event_t evt )
{
	if( evt != LV_EVENT_CLICKED )
		return;
	uint16_t idx = lv_btnmatrix_get_active_btn( obj );
	if (idx >= NB_APP_PAGES)
		return;
	const sndbx_pge_t *page = &app_pages[idx];
	sndbx_pge_change( page );
}

/**
 * Called when the page is created,
 * @param parent object pointer, normally just an lv_container
 * @param p_mem memory pointer, points to memory allocated by the sandbox  
 */
static void create_cb( lv_obj_t * parent, void * p_mem, const void * prms )
{
	MEM_INIT( mem, p_mem );
	/* Save parent, if required */
	mem->parent = parent;

	uint8_t txt_size = 128;
	char * txt = lv_mem_alloc( txt_size );
	lv_obj_t * lbl;
	lv_obj_t * btnmatrix;

	lv_coord_t w_par = lv_obj_get_width( parent );
	lv_coord_t h_par = lv_obj_get_height( parent );
	/* Create content */
	/* Sandbox Apps */
	lbl = lv_label_create( parent, NULL );
	snprintf( txt, txt_size,
		"Sandbox Template Applications" );
	lv_label_set_text( lbl, txt );
	lv_label_set_align( lbl, LV_LABEL_ALIGN_CENTER );
	lv_obj_align( lbl, NULL, LV_ALIGN_IN_TOP_MID, 0, LV_DPI/10);

	lv_mem_free(txt);

	static const char * const btnmatrix_map[] = {
		"LV Demo", "LV Sysmon", "LV Benchmark","\n",
		"Templ", "Template", "Demo", "\n",
		"Animation", "Table",
		"",
	};

	btnmatrix = lv_btnmatrix_create(parent, NULL);
    lv_btnmatrix_set_map(btnmatrix, (const char**)btnmatrix_map);
	lv_obj_set_size( btnmatrix, w_par*3/4, h_par/2 );
    lv_obj_align(btnmatrix, lbl, LV_ALIGN_OUT_BOTTOM_MID, 0, 0);
	lv_obj_set_event_cb(btnmatrix, btnmatrix_event_handler);
}

/*===================== Callbacks and Events================== */

/* Helpers from here */
static lv_obj_t *label_create( lv_obj_t *par, const char *txt )
{
	lv_obj_t * lbl = lv_label_create( par, NULL );
	lv_label_set_static_text( lbl, txt );

	return lbl;
}

#endif  /*USE_SNDBX_APP_TEST*/
