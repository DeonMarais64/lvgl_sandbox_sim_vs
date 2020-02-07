/**
 * @file sndbx_pge_lv_app_benchmark.c
 *
 */

 /*********************
  *      INCLUDES
  *********************/
#include "sndbx_pge_lv_app_benchmark.h"
#if USE_SNDBX_PGE_LV_APP_BENCHMARK

#include <stdio.h>

/*********************
 *      DEFINES
 *********************/
#define PAGE_NAME "lv App #ff0000 Benchmark# - Managed"

#define TEST_CYCLE_NUM  10              /*How many times run the test (will calculate the average)*/
#define SHADOW_WIDTH    (LV_DPI / 8)
#define IMG_RECOLOR     LV_OPA_20
#define OPACITY         LV_OPA_60

/*********************
 * EXTERNAL REFERENCES
 *********************/
LV_IMG_DECLARE(benchmark_bg)

/**********************
 *      TYPEDEFS
 **********************/
typedef struct {
	lv_obj_t * parent;
	lv_obj_t* holder_page;
	lv_obj_t* wp;
	lv_obj_t* result_label;

	lv_style_t style_wp;
	lv_style_t style_btn_rel;
	lv_style_t style_btn_pr;
	lv_style_t style_btn_tgl_rel;
	lv_style_t style_btn_tgl_pr;

	uint32_t time_sum;
	uint32_t refr_cnt;
} mem_t;

/**********************
 *  STATIC PROTOTYPES
 **********************/

static void create_cb( lv_obj_t * parent, void * mem, const void * prms );
static void destroy_cb( void * p_mem );

static void refr_monitor(lv_disp_drv_t* disp_drv, uint32_t time_ms, uint32_t px_num);
static void run_test_event_cb(lv_obj_t* btn, lv_event_t event);
static void wp_btn_event_cb(lv_obj_t* btn, lv_event_t event);
static void recolor_btn_event_cb(lv_obj_t* btn, lv_event_t event);
static void shadow_btn_event_cb(lv_obj_t* btn, lv_event_t event);
static void opa_btn_event_cb(lv_obj_t* btn, lv_event_t event);

static void benchmark_start(void *);

/**********************
 *  GLOBAL DESCRIPTORS
 **********************/
const sndbx_pge_dsc_t sndbx_pge_lv_app_benchmark_dsc = {
	.name = PAGE_NAME,
	.mem_size = sizeof( mem_t ),
	.create_cb = create_cb,
	.destroy_cb = destroy_cb,
	.opt = SNDBX_OPT_SCREEN,
};

/**********************
 *  STATIC VARIABLES
 **********************/

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
void sndbx_pge_lv_app_benchmark_test( void )
{
	static const sndbx_pge_t page = {
		.dsc = &sndbx_pge_lv_app_benchmark_dsc,
	};

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
	MEM_INIT( mem, p_mem );
	/* Save parent */
	mem->parent = parent;
	/* Unpack page parameters*/
	const sndbx_pge_prms_lr_t * pge_prms = prms;

	/* Create content */

	lv_coord_t hres = lv_disp_get_hor_res(NULL);
	lv_coord_t vres = lv_disp_get_ver_res(NULL);

	/*Styles of the buttons*/
	lv_style_copy(&mem->style_btn_rel, &lv_style_btn_rel);
	lv_style_copy(&mem->style_btn_pr, &lv_style_btn_pr);
	lv_style_copy(&mem->style_btn_tgl_rel, &lv_style_btn_tgl_rel);
	lv_style_copy(&mem->style_btn_tgl_pr, &lv_style_btn_tgl_pr);

	mem->style_btn_rel.body.opa = LV_OPA_COVER;
	mem->style_btn_pr.body.opa = LV_OPA_COVER;
	mem->style_btn_tgl_rel.body.opa = LV_OPA_COVER;
	mem->style_btn_tgl_pr.body.opa = LV_OPA_COVER;

	mem->style_btn_rel.body.shadow.width = 0;
	mem->style_btn_pr.body.shadow.width = 0;
	mem->style_btn_tgl_rel.body.shadow.width = 0;
	mem->style_btn_tgl_pr.body.shadow.width = 0;

	/*Style of the wallpaper*/
	lv_style_copy(&mem->style_wp, &lv_style_plain);
	mem->style_wp.image.color = LV_COLOR_RED;

	/*Create a holder page (the page become scrollable on small displays )*/
	mem->holder_page = lv_page_create(lv_disp_get_scr_act(NULL), NULL);
	lv_obj_set_size(mem->holder_page, hres, vres);
	lv_page_set_style(mem->holder_page, LV_PAGE_STYLE_BG, &lv_style_transp_fit);
	lv_page_set_style(mem->holder_page, LV_PAGE_STYLE_SCRL, &lv_style_transp);
	lv_page_set_scrl_layout(mem->holder_page, LV_LAYOUT_PRETTY);

	/*Create a wallpaper on the page*/
	mem->wp = lv_img_create(mem->holder_page, NULL);
	lv_obj_set_protect(mem->wp, LV_PROTECT_PARENT);          /*Don't let to move the wallpaper by the layout */
	lv_obj_set_parent(mem->wp, mem->holder_page);
	lv_obj_set_parent(lv_page_get_scrl(mem->holder_page), mem->holder_page);
	lv_img_set_src(mem->wp, &benchmark_bg);
	lv_obj_set_size(mem->wp, hres, vres);
	lv_obj_set_pos(mem->wp, 0, 0);
	lv_obj_set_hidden(mem->wp, true);
	lv_img_set_style(mem->wp, LV_IMG_STYLE_MAIN, &mem->style_wp);
	lv_img_set_auto_size(mem->wp, false);

	/*Create a label to show the test result*/
	mem->result_label = lv_label_create(mem->holder_page, NULL);
	lv_label_set_text(mem->result_label, "Run the test");
	lv_label_set_body_draw(mem->result_label, true);
	lv_label_set_style(mem->result_label, LV_LABEL_STYLE_MAIN, &lv_style_pretty);

	/*Create a "Run test" button*/
	lv_obj_t* btn;
	btn = lv_btn_create(mem->holder_page, NULL);
	lv_obj_set_user_data(btn, p_mem);
	lv_page_glue_obj(btn, true);
	lv_btn_set_fit(btn, LV_FIT_TIGHT);
	lv_btn_set_style(btn, LV_BTN_STYLE_REL, &mem->style_btn_rel);
	lv_btn_set_style(btn, LV_BTN_STYLE_PR, &mem->style_btn_pr);
	lv_btn_set_style(btn, LV_BTN_STYLE_TGL_REL, &mem->style_btn_tgl_rel);
	lv_btn_set_style(btn, LV_BTN_STYLE_TGL_PR, &mem->style_btn_tgl_pr);
	lv_obj_set_event_cb(btn, run_test_event_cb);

	lv_obj_t* btn_l;
	btn_l = lv_label_create(btn, NULL);
	lv_label_set_text(btn_l, "Run\ntest!");
	lv_obj_set_protect(btn, LV_PROTECT_FOLLOW);     /*Line break in layout*/


	/*Create a "Wallpaper show" button*/
	btn = lv_btn_create(mem->holder_page, btn);
	lv_obj_set_user_data(btn, p_mem);
	lv_btn_set_toggle(btn, true);
	lv_obj_clear_protect(btn, LV_PROTECT_FOLLOW);
	lv_obj_set_event_cb(btn, wp_btn_event_cb);
	btn_l = lv_label_create(btn, btn_l);
	lv_label_set_text(btn_l, "Wallpaper");


	/*Create a "Wallpaper re-color" button*/
	btn = lv_btn_create(mem->holder_page, btn);
	lv_obj_set_user_data(btn, p_mem);
	lv_obj_set_event_cb(btn, recolor_btn_event_cb);
	btn_l = lv_label_create(btn, btn_l);
	lv_label_set_text(btn_l, "Wp. recolor!");

	/*Create a "Shadow draw" button*/
	btn = lv_btn_create(mem->holder_page, btn);
	lv_obj_set_user_data(btn, p_mem);
	lv_obj_set_event_cb(btn, shadow_btn_event_cb);
	btn_l = lv_label_create(btn, btn_l);
	lv_label_set_text(btn_l, "Shadow");

	/*Create an "Opacity enable" button*/
	btn = lv_btn_create(mem->holder_page, btn);
	lv_obj_set_user_data(btn, p_mem);
	lv_obj_set_event_cb(btn, opa_btn_event_cb);
	btn_l = lv_label_create(btn, btn_l);
	lv_label_set_text(btn_l, "Opacity");

	btn = sndbx_link_btn_create(parent, LV_SYMBOL_CLOSE, sndbx_pge_get_prev());
	lv_obj_align(btn, NULL, LV_ALIGN_IN_TOP_RIGHT, 0, 0);

	/* */
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

	/* Nothing else to do, parent has already been cleaned */
	/* Memory pointed to by p_mem will be deallocated ...*/
	/* ... by the sandbox handler */
}

/*===================== Callbacks and Events================== */

static void benchmark_start(void * p_mem)
{
	MEM_INIT(mem, p_mem);

	lv_disp_t* disp = lv_obj_get_disp(mem->holder_page);

	disp->driver.monitor_cb = refr_monitor;
	disp->driver.user_data = p_mem;

	lv_obj_invalidate(lv_disp_get_scr_act(disp));

	mem->time_sum = 0;
	mem->refr_cnt = 0;
}

/*--------------------
 * OTHER FUNCTIONS
 ---------------------*/

 /**
  * Called when a the library finished rendering to monitor its performance
  * @param disp_drv pointer to the caller display driver
  * @param time_ms time of rendering in milliseconds
  * @param px_num Number of pixels drawn
  */
static void refr_monitor(lv_disp_drv_t* disp_drv, uint32_t time_ms, uint32_t px_num)
{
	(void)px_num; /*Unused*/
	void * p_mem = disp_drv->user_data;
	MEM_INIT(mem, p_mem);

	lv_disp_t* disp = lv_obj_get_disp(mem->holder_page);
	mem->time_sum += time_ms;
	mem->refr_cnt++;
	lv_obj_invalidate(lv_disp_get_scr_act(disp));

	if (mem->refr_cnt >= TEST_CYCLE_NUM) {
		int time_avg = (int)mem->time_sum / (int)TEST_CYCLE_NUM;
		char buf[256];
		sprintf(buf, "Screen load: %d ms\nAverage of %d", time_avg, TEST_CYCLE_NUM);
		lv_label_set_text(mem->result_label, buf);
		disp_drv->monitor_cb = NULL;
	}
	else {
		char buf[256];
		sprintf(buf, "Running %d/%d", mem->refr_cnt, TEST_CYCLE_NUM);
		lv_label_set_text(mem->result_label, buf);

	}
}

/**
 * Called when the "Run test" button is clicked
 * @param btn pointer to the button
 * @param event the current event
 */
static void run_test_event_cb(lv_obj_t* btn, lv_event_t event)
{
	if (event != LV_EVENT_CLICKED) return;
	void* p_mem = lv_obj_get_user_data(btn);
	MEM_INIT(mem, p_mem);

	benchmark_start(p_mem);
}

/**
 * Called when the "Wallpaper" button is clicked
 * @param btn pointer to the button
 * @param event the current event
 */
static void wp_btn_event_cb(lv_obj_t* btn, lv_event_t event)
{
	if (event != LV_EVENT_CLICKED) return;

	void* p_mem = lv_obj_get_user_data(btn);
	MEM_INIT(mem, p_mem);

	if (lv_btn_get_state(btn) == LV_BTN_STATE_TGL_REL) 
		lv_obj_set_hidden(mem->wp, false);
	else 
		lv_obj_set_hidden(mem->wp, true);
}

/**
 * Called when the "Wp. recolor" button is clicked
 * @param btn pointer to the button
 * @param event the current event
 */
static void recolor_btn_event_cb(lv_obj_t* btn, lv_event_t event)
{
	if (event != LV_EVENT_CLICKED) return;

	void* p_mem = lv_obj_get_user_data(btn);
	MEM_INIT(mem, p_mem);

	if (lv_btn_get_state(btn) == LV_BTN_STATE_TGL_REL) 
		mem->style_wp.image.intense = IMG_RECOLOR;
	else 
		mem->style_wp.image.intense = LV_OPA_TRANSP;

	lv_obj_refresh_style(mem->wp);
}

/**
 * Called when the "Shadow" button is clicked
 * @param btn pointer to the button
 * @param event the current event
 */
static void shadow_btn_event_cb(lv_obj_t* btn, lv_event_t event)
{
	if (event != LV_EVENT_CLICKED) return;

	void* p_mem = lv_obj_get_user_data(btn);
	MEM_INIT(mem, p_mem);

	if (lv_btn_get_state(btn) == LV_BTN_STATE_TGL_REL) {
		mem->style_btn_rel.body.shadow.width = SHADOW_WIDTH;
		mem->style_btn_pr.body.shadow.width = SHADOW_WIDTH;
		mem->style_btn_tgl_rel.body.shadow.width = SHADOW_WIDTH;
		mem->style_btn_tgl_pr.body.shadow.width = SHADOW_WIDTH;
	}
	else {
		mem->style_btn_rel.body.shadow.width = 0;
		mem->style_btn_pr.body.shadow.width = 0;
		mem->style_btn_tgl_rel.body.shadow.width = 0;
		mem->style_btn_tgl_pr.body.shadow.width = 0;
	}

	lv_obj_report_style_mod(&mem->style_btn_rel);
	lv_obj_report_style_mod(&mem->style_btn_pr);
	lv_obj_report_style_mod(&mem->style_btn_tgl_rel);
	lv_obj_report_style_mod(&mem->style_btn_tgl_pr);
}

/**
 * Called when the "Opacity" button is clicked
 * @param btn pointer to the button
 * @param event the current event
 */
static void opa_btn_event_cb(lv_obj_t* btn, lv_event_t event)
{
	if (event != LV_EVENT_CLICKED) return;

	void* p_mem = lv_obj_get_user_data(btn);
	MEM_INIT(mem, p_mem);

	if (lv_btn_get_state(btn) == LV_BTN_STATE_TGL_REL) {
		mem->style_btn_rel.body.opa = OPACITY;
		mem->style_btn_pr.body.opa = OPACITY;
		mem->style_btn_tgl_rel.body.opa = OPACITY;
		mem->style_btn_tgl_pr.body.opa = OPACITY;
	}
	else {
		mem->style_btn_rel.body.opa = LV_OPA_COVER;
		mem->style_btn_pr.body.opa = LV_OPA_COVER;
		mem->style_btn_tgl_rel.body.opa = LV_OPA_COVER;
		mem->style_btn_tgl_pr.body.opa = LV_OPA_COVER;
	}

	lv_obj_report_style_mod(&mem->style_btn_rel);
	lv_obj_report_style_mod(&mem->style_btn_pr);
	lv_obj_report_style_mod(&mem->style_btn_tgl_rel);
	lv_obj_report_style_mod(&mem->style_btn_tgl_pr);
}

#endif  /*USE_SNDBX_PGE_LV_APP_BENCHMARK*/
