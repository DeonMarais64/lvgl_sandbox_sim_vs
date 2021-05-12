/**
 * @file sndbx_pge_anim_see.c
 *
 */

 /*********************
  *      INCLUDES
  *********************/
#include "sndbx_pge_anim_see.h"
#if USE_SNDBX_PGE_ANIM_SEE

#include <stdio.h>

/*********************
 *      DEFINES
 *********************/

#define PAGE_NAME "Animation visualise"

#define PERIOD 2000

/**********************
 *      TYPEDEFS
 **********************/

typedef struct {
	uint32_t val;
	lv_obj_t* lbl;
	char txt[8];
	lv_obj_t* slider;
} bezier_t;

typedef struct {
	lv_obj_t * parent;
	lv_obj_t * lbl_anim_path;
	lv_obj_t * lbl_val;
	char txt_val[16];
	lv_obj_t * bar;
	lv_obj_t* chart;
	char chart_x_tick_txts[64];
	lv_style_t st_chart;
	lv_chart_series_t * anim_ser;
	uint16_t idx;
	bezier_t bez3_u1;
	bezier_t bez3_u2;
} mem_t;

typedef struct {
	const char* name;
	lv_anim_path_cb_t path_cb;
} anim_path_dsc_t;

/**********************
 *  STATIC PROTOTYPES
 **********************/

static void create_cb( lv_obj_t * parent, void * mem, const void * prms );
static void task_cb( void * p_mem );
static void destroy_cb( void * p_mem );

static void chart_set_next(lv_obj_t* chart, lv_anim_value_t value);
static void bar_set_value(lv_obj_t* bar, lv_anim_value_t value);
static void ddlist_event_handler(lv_obj_t* obj, lv_event_t event);
static void slider_event_handler(lv_obj_t* obj, lv_event_t event);
static lv_anim_value_t lv_anim_path_custom(const lv_anim_t* a);
static void anim_ready(lv_anim_t* pa);

/**********************
 *  GLOBAL DESCRIPTORS
 **********************/

const sndbx_pge_dsc_t sndbx_pge_anim_see_dsc = {
	.name = PAGE_NAME,
	.mem_size = sizeof( mem_t ),
	.create_cb = create_cb,
};

/**********************
 *  STATIC VARIABLES
 **********************/

static const char* const ddlist_options =
	"Linear\n"
	"Ease in\n"
	"Ease out\n"
	"Ease in out\n"
	"Overshoot\n"
	"Bounce\n"
	"Custom"
;
static const anim_path_dsc_t anim_path_dscs[] = {
	{.name = "Linear",.path_cb = lv_anim_path_linear},
	{.name = "Ease in",.path_cb = lv_anim_path_ease_in},
	{.name = "Ease out",.path_cb = lv_anim_path_ease_out},
	{.name = "Ease in out",.path_cb = lv_anim_path_ease_in_out},
	{.name = "Overshoot",.path_cb = lv_anim_path_overshoot},
	{.name = "Bounce",.path_cb = lv_anim_path_bounce},
//	{.name = "Custom",.path_cb = lv_anim_path_custom},
};

/**********************
 *      MACROS
 **********************/
#define MEM_INIT(to,from) mem_t*(to) = (from)
#define NB_ANIM_PATHS sizeof(anim_path_dscs)/sizeof(anim_path_dscs[0])

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

/**
 * Create a sandbox test application
 */
void sndbx_pge_anim_see_test( void )
{
	static const sndbx_pge_t page = {
		.dsc = &sndbx_pge_anim_see_dsc,
	};

	sndbx_app_create( &page );
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

static void create_cb( lv_obj_t * parent, void * p_mem, const void * prms )
{
	MEM_INIT( mem, p_mem );
	mem->parent = parent;

	lv_coord_t w_par = lv_obj_get_width(parent);
	lv_coord_t h_par = lv_obj_get_height(parent);

#if 0
	lv_obj_t *pge;
	pge = lv_page_create(parent, NULL);
	lv_obj_set_size(pge, w_par, h_par);

	parent = pge;
#endif

	/*chart*/
//	lv_style_copy(&mem->st_chart, &lv_style_plain);
//	mem->st_chart.body.main_color = LV_COLOR_BLACK;
//	mem->st_chart.body.grad_color = LV_COLOR_BLACK;

	mem->chart = lv_chart_create(parent, NULL);
//	lv_obj_set_style(mem->chart, &mem->st_chart);
	lv_obj_set_user_data(mem->chart, p_mem);
	lv_obj_set_size(mem->chart, w_par-LV_DPI*3/2, h_par-LV_DPI);
	lv_chart_set_point_count(mem->chart, PERIOD/LV_DISP_DEF_REFR_PERIOD);
	lv_chart_set_range(mem->chart, -1000, 11000);
	lv_chart_set_type(mem->chart, LV_CHART_TYPE_LINE);
//	lv_chart_set_series_width(mem->chart, 1);
	lv_obj_align(mem->chart, NULL, LV_ALIGN_CENTER, 0, -LV_DPI/6);
	mem->anim_ser = lv_chart_add_series(mem->chart, LV_COLOR_RED);

	lv_chart_set_div_line_count(mem->chart, 5, 7);
//	lv_chart_set_margin(mem->chart, 50);
	lv_chart_set_y_tick_length(mem->chart, 12, 6);
	lv_chart_set_y_tick_texts(mem->chart, "110\n90\n70\n50\n30\n10\n[%]", 2, LV_CHART_AXIS_SKIP_LAST_TICK);

	snprintf(mem->chart_x_tick_txts, sizeof(mem->chart_x_tick_txts), 
		"%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\nt[ms]" 
		,-PERIOD*8/8,-PERIOD*7/8,-PERIOD*6/8,-PERIOD*5/8,-PERIOD*4/8,-PERIOD*3/8,-PERIOD*2/8,-PERIOD*1/8
	);
	lv_chart_set_x_tick_length(mem->chart, 8, 2);
	lv_chart_set_x_tick_texts(mem->chart, mem->chart_x_tick_txts, 2, LV_CHART_AXIS_SKIP_LAST_TICK);
	
	/*bar*/
	mem->bar = lv_bar_create(parent, NULL);
	lv_bar_set_range(mem->bar, -1000, 11000);
	lv_obj_align(mem->bar, mem->chart, LV_ALIGN_OUT_RIGHT_TOP, LV_DPI/8, 0);
	lv_obj_set_size(mem->bar, LV_DPI/4, h_par - LV_DPI);

	/*labels*/
	mem->lbl_val = lv_label_create(parent, NULL);
	lv_obj_align(mem->lbl_val, mem->bar, LV_ALIGN_OUT_TOP_MID, 0, 0);
	lv_label_set_align(mem->lbl_val, LV_LABEL_ALIGN_CENTER);
	lv_obj_set_auto_realign(mem->lbl_val, true);
	lv_label_set_static_text(mem->lbl_val, mem->txt_val);

	mem->lbl_anim_path = lv_label_create(parent, NULL);
	lv_obj_align(mem->lbl_anim_path, mem->chart, LV_ALIGN_OUT_TOP_RIGHT, -LV_DPI/10, 0);
	lv_label_set_align(mem->lbl_anim_path, LV_LABEL_ALIGN_LEFT);
	lv_obj_set_auto_realign(mem->lbl_anim_path, true);

	lv_anim_t a;
	lv_anim_set_exec_cb(&a, mem->chart, chart_set_next);
	lv_anim_set_ready_cb(&a, anim_ready);
	lv_anim_set_time(&a, PERIOD/2, 1);
	lv_anim_set_playback(&a, 500);
	lv_anim_clear_repeat(&a);
	a.user_data = p_mem;

	mem->idx = 5;
	anim_ready(&a);

	/*drop down list*/
	lv_obj_t* ddlist = lv_ddlist_create(parent, NULL);
	lv_obj_set_user_data(ddlist, p_mem);
	lv_ddlist_set_options(ddlist, ddlist_options );

	lv_ddlist_set_align(ddlist, LV_LABEL_ALIGN_LEFT);
	lv_ddlist_set_fix_width(ddlist, 120);
	lv_ddlist_set_draw_arrow(ddlist, true);
	lv_obj_set_auto_realign(ddlist, true);
	lv_obj_align(ddlist, NULL, LV_ALIGN_IN_TOP_MID, 0, LV_DPI/20);
	lv_obj_set_event_cb(ddlist, ddlist_event_handler);

	lv_ddlist_set_selected(ddlist, mem->idx);

	mem->bez3_u1.val = mem->bez3_u2.val = LV_BEZIER_VAL_MAX / 2;
	/*bez3 labels*/
	mem->bez3_u1.lbl = lv_label_create(parent, NULL);
	lv_obj_set_auto_realign(mem->bez3_u1.lbl, true);
	mem->bez3_u2.lbl = lv_label_create(parent, mem->bez3_u1.lbl);

	snprintf(mem->bez3_u1.txt, sizeof(mem->bez3_u1.txt), "%u", mem->bez3_u1.val);
	lv_label_set_static_text(mem->bez3_u1.lbl, mem->bez3_u1.txt);
	snprintf(mem->bez3_u2.txt, sizeof(mem->bez3_u2.txt), "%u", mem->bez3_u2.val);
	lv_label_set_static_text(mem->bez3_u2.lbl, mem->bez3_u2.txt);

	/*bez3 sliders*/
	mem->bez3_u1.slider = lv_slider_create(parent, NULL);
	lv_slider_set_range(mem->bez3_u1.slider, 0, LV_BEZIER_VAL_MAX*12/10);
	lv_obj_set_width(mem->bez3_u1.slider, LV_DPI*7/4);
	lv_obj_set_event_cb(mem->bez3_u1.slider, slider_event_handler);

	lv_obj_set_user_data(mem->bez3_u1.slider, &mem->bez3_u1);
	lv_slider_set_value(mem->bez3_u1.slider, mem->bez3_u1.val, LV_ANIM_OFF );

	mem->bez3_u2.slider = lv_slider_create(parent, mem->bez3_u1.slider);
	lv_obj_set_user_data(mem->bez3_u2.slider, &mem->bez3_u2);
	lv_slider_set_value(mem->bez3_u2.slider, mem->bez3_u2.val, LV_ANIM_OFF);

	lv_coord_t h_offset = lv_obj_get_width(mem->bez3_u1.slider)/2 + LV_DPI/8;
	lv_coord_t v_offset = LV_DPI / 10;

	lv_obj_align(mem->bez3_u1.slider, NULL, LV_ALIGN_IN_BOTTOM_MID, -h_offset, -v_offset);
	lv_obj_align(mem->bez3_u1.lbl, mem->bez3_u1.slider, LV_ALIGN_OUT_LEFT_MID, -LV_DPI/8, 0);
	lv_label_set_align(mem->bez3_u1.lbl, LV_LABEL_ALIGN_RIGHT);
	lv_obj_align(mem->bez3_u2.slider, NULL, LV_ALIGN_IN_BOTTOM_MID, h_offset, -v_offset);
	lv_obj_align(mem->bez3_u2.lbl, mem->bez3_u2.slider, LV_ALIGN_OUT_RIGHT_MID, LV_DPI/8, 0);

	if( mem->idx != NB_ANIM_PATHS-1)
	{
		lv_obj_set_hidden(mem->bez3_u1.lbl, true);
		lv_obj_set_hidden(mem->bez3_u1.slider, true);
		lv_obj_set_hidden(mem->bez3_u2.lbl, true);
		lv_obj_set_hidden(mem->bez3_u2.slider, true);
	}

	const sndbx_pge_prms_lr_t* pge_prms = prms;
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

static lv_anim_value_t lv_anim_path_custom(const lv_anim_t* a)
{
	/*Calculate the current step*/
	uint32_t t;
	if (a->time == a->act_time)
		t = LV_BEZIER_VAL_MAX;
	else
		t = (uint32_t)((uint32_t)a->act_time * LV_BEZIER_VAL_MAX) / a->time;
	void* p_mem = a->user_data;
	MEM_INIT(mem, p_mem);

	int32_t step = lv_bezier3(t, 0, mem->bez3_u1.val, mem->bez3_u2.val, LV_BEZIER_VAL_MAX);

	int32_t new_value;
	new_value = (int32_t)step * (a->end - a->start);
	new_value = new_value >> LV_BEZIER_VAL_SHIFT;
	new_value += a->start;

	return (lv_anim_value_t)new_value;
}

static void anim_ready(lv_anim_t* pa)
{
	lv_obj_t* chart = pa->var;
	void* p_mem = lv_obj_get_user_data(chart);
	MEM_INIT(mem, p_mem);

	const anim_path_dsc_t* dsc = &anim_path_dscs[mem->idx];
	pa->path_cb = dsc->path_cb;
	lv_label_set_static_text(mem->lbl_anim_path, dsc->name);

	lv_anim_set_values(pa, 0, 10000);
	if( pa->act_time > 0)
		pa->act_time = -1000;

	lv_anim_create(pa);

	lv_anim_set_exec_cb(pa, mem->bar, bar_set_value);
	lv_anim_set_ready_cb(pa, NULL);

	lv_anim_create(pa);

	//	mem->idx = mem->idx < NB_ANIM_PATHS-1 ? mem->idx+1 : 0;
}

static void chart_set_next(lv_obj_t* chart, lv_anim_value_t value)
{
	void* p_mem = lv_obj_get_user_data(chart);
	MEM_INIT(mem, p_mem);
	lv_chart_set_next(chart, mem->anim_ser, value);
	snprintf(mem->txt_val, sizeof(mem->txt_val), "%d.%.2u %%", value/100, LV_MATH_ABS(value)%100);
	lv_label_set_static_text(mem->lbl_val, NULL);
}

static void bar_set_value(lv_obj_t* bar, lv_anim_value_t value)
{
	lv_bar_set_value(bar, value, LV_ANIM_OFF);
}

void ddlist_event_handler(lv_obj_t* obj, lv_event_t event)
{
	if (event != LV_EVENT_VALUE_CHANGED)
		return;
	
	uint16_t idx = lv_ddlist_get_selected(obj);
	if (idx >= NB_ANIM_PATHS)
		return;

	void* p_mem;
	p_mem = lv_obj_get_user_data(obj);
	MEM_INIT(mem, p_mem);
	mem->idx = idx;

	lv_anim_del(mem->chart, chart_set_next);
	lv_anim_del(mem->bar, bar_set_value);

	lv_chart_clear_serie(mem->chart, mem->anim_ser);

	lv_anim_t a;
	lv_anim_set_exec_cb(&a, mem->chart, chart_set_next);
	lv_anim_set_ready_cb(&a, anim_ready);
	lv_anim_set_time(&a, PERIOD/2, 1);
	lv_anim_set_playback(&a, 500);
	lv_anim_clear_repeat(&a);
	a.user_data = p_mem;

	anim_ready(&a);

	bool hide = mem->idx != NB_ANIM_PATHS-1;

	lv_obj_set_hidden(mem->bez3_u1.lbl, hide);
	lv_obj_set_hidden(mem->bez3_u1.slider, hide);
	lv_obj_set_hidden(mem->bez3_u2.lbl, hide);
	lv_obj_set_hidden(mem->bez3_u2.slider, hide);
}

void slider_event_handler(lv_obj_t* obj, lv_event_t event)
{
	if (event != LV_EVENT_VALUE_CHANGED)
		return;
	bezier_t * bez3 = (bezier_t*)lv_obj_get_user_data(obj);

	bez3->val = lv_slider_get_value(obj);
	snprintf(bez3->txt, sizeof(bez3->txt), "%u", bez3->val );
	lv_label_set_static_text(bez3->lbl, NULL);
}

#endif  /*USE_SNDBX_PGE_ANIM_SEE*/
