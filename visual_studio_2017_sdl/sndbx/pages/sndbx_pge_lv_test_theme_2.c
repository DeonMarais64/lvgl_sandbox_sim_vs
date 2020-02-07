/**
 * @file sndbx_pge_lv_test_theme_2.c
 *
 */

 /*********************
  *      INCLUDES
  *********************/
#include "sndbx_pge_lv_test_theme_2.h"
#if USE_SNDBX_PGE_LV_TEST_THEME_2

#include <stdio.h>

/*********************
 *      DEFINES
 *********************/
//#define PAGE_NAME "LittlevGL Test Theme 1"
#if LV_HOR_RES_MAX < 800
#define PAGE_NAME "lv Test #ff0000 Theme 2# - Managed"
#else
#define PAGE_NAME "LittlevGL Test #ff0000 Theme 2# - Managed version"
#endif

/**********************
 *      TYPEDEFS
 **********************/
typedef struct {          /* Memory spec, if required */
	lv_obj_t * parent;
	lv_obj_t * scr;
	lv_obj_t * header;
	lv_obj_t * sb;
	lv_obj_t * content;
	lv_theme_t * th_act;
	lv_theme_t * themes[8];
} mem_t;

/**********************
 *  STATIC PROTOTYPES
 **********************/

static void create_cb( lv_obj_t * parent, void * mem, const void * prms );
static void destroy_cb( void * mem );

static void test_theme_2(void * p_mem);

static void header_create(void * p_mem);
static void sb_create(void * p_mem);
static void content_create(void * p_mem);

static void theme_select_event_handler(lv_obj_t * roller, lv_event_t event);
static void hue_select_event_cb(lv_obj_t * roller, lv_event_t event);
static void init_all_themes(void * p_mem, uint16_t hue);
static void bar_set_value(lv_obj_t * bar, int16_t value);

/**********************
 *  GLOBAL DESCRIPTORS
 **********************/
const sndbx_pge_dsc_t sndbx_pge_lv_test_theme_2_dsc = {
	.name = PAGE_NAME,
	.mem_size = sizeof( mem_t ),
	.create_cb = create_cb,
	.destroy_cb = destroy_cb,
	.opt = SNDBX_OPT_SCREEN,
};

/**********************
 *  STATIC VARIABLES
 **********************/

static const char * th_options =
{
#if LV_USE_THEME_NIGHT
        "Night"
#endif
#if LV_USE_THEME_MATERIAL
        "\nMaterial"
#endif
#if LV_USE_THEME_ALIEN
        "\nAlien"
#endif
#if LV_USE_THEME_ZEN
        "\nZen"
#endif
#if LV_USE_THEME_NEMO
        "\nNemo"
#endif
#if LV_USE_THEME_MONO
        "\nMono"
#endif
#if LV_USE_THEME_DEFAULT
        "\nDefault"
#endif
        ""
};

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
void sndbx_pge_lv_test_theme_2_test( void )
{
	static const sndbx_pge_t page = {
		.dsc = &sndbx_pge_lv_test_theme_2_dsc,
	};

	sndbx_app_create( &page );
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
	test_theme_2(p_mem);
	if( pge_prms )
	{
		const sndbx_pge_t * ret = sndbx_pge_get_prev();
		lv_obj_t * btn = sndbx_link_btn_create( mem->scr, LV_SYMBOL_CLOSE, ret );
		lv_obj_align( btn, NULL, LV_ALIGN_IN_BOTTOM_LEFT, 0, 0 );
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
	/* ... by the sandbox hander */
}

/**
 * Test run time theme change
 */
static void test_theme_2(void * p_mem)
{
	MEM_INIT( mem, p_mem );

    /* By doing this, we hide the first (empty) option. */
    if(th_options[0] == '\n')
	    th_options++;

    init_all_themes(p_mem, 0);
    mem->th_act = mem->themes[0];
    if(mem->th_act == NULL) {
    	LV_LOG_WARN("lv_test_theme_2: no theme is enabled. Check lv_conf.h");
    	return;
    }

    lv_theme_set_current(mem->th_act);

    mem->scr = lv_obj_create(NULL, NULL);
    lv_disp_load_scr(mem->scr);

    header_create(p_mem);
    sb_create(p_mem);
    content_create(p_mem);
}

static void header_create(void * p_mem)
{
	MEM_INIT( mem, p_mem );

    mem->header = lv_cont_create(lv_disp_get_scr_act(NULL), NULL);
    lv_obj_set_width(mem->header, lv_disp_get_hor_res(NULL));

    lv_obj_t * sym = lv_label_create(mem->header, NULL);
    lv_label_set_text(sym, LV_SYMBOL_GPS LV_SYMBOL_WIFI LV_SYMBOL_BLUETOOTH LV_SYMBOL_VOLUME_MAX);
    lv_obj_align(sym, NULL, LV_ALIGN_IN_RIGHT_MID, -LV_DPI/10, 0);

    lv_obj_t * clock = lv_label_create(mem->header, NULL);
    lv_label_set_text(clock, "14:21");
    lv_obj_align(clock, NULL, LV_ALIGN_IN_LEFT_MID, LV_DPI/10, 0);

    lv_cont_set_fit2(mem->header, LV_FIT_NONE, LV_FIT_TIGHT);   /*Let the height set automatically*/
    lv_obj_set_pos(mem->header, 0, 0);
}

static void sb_create(void * p_mem)
{
	MEM_INIT( mem, p_mem );

    lv_coord_t hres = lv_disp_get_hor_res(NULL);
    lv_coord_t vres = lv_disp_get_ver_res(NULL);

    mem->sb = lv_page_create(lv_disp_get_scr_act(NULL), NULL);
    lv_page_set_scrl_layout(mem->sb, LV_LAYOUT_COL_M);
    lv_page_set_style(mem->sb, LV_PAGE_STYLE_BG, &lv_style_transp_tight);
    lv_page_set_style(mem->sb, LV_PAGE_STYLE_SCRL, &lv_style_transp);

    lv_obj_t * th_label = lv_label_create(mem->sb, NULL);
    lv_label_set_text(th_label, "Theme");

    lv_obj_t * th_roller = lv_roller_create(mem->sb, NULL);
    lv_roller_set_options(th_roller, th_options, true);
    lv_obj_set_event_cb(th_roller, theme_select_event_handler);
	lv_obj_set_user_data(th_roller, p_mem);

    lv_obj_t * hue_label = lv_label_create(mem->sb, NULL);
    lv_label_set_text(hue_label, "\nColor");

    lv_obj_t * hue_roller = lv_roller_create(mem->sb, NULL);
    lv_roller_set_options(hue_roller, "0\n30\n60\n90\n120\n150\n180\n210\n240\n270\n300\n330", true);
    lv_obj_set_event_cb(hue_roller, hue_select_event_cb);
	lv_obj_set_user_data(hue_roller, p_mem);

    if(hres > vres) {
        lv_obj_set_height(mem->sb, vres - lv_obj_get_height(mem->header));
        lv_cont_set_fit2(mem->sb, LV_FIT_TIGHT, LV_FIT_NONE);
        lv_obj_align(mem->sb, mem->header, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 0);
        lv_page_set_sb_mode(mem->sb, LV_SB_MODE_DRAG);
    } else {
        lv_obj_set_size(mem->sb, hres, vres / 2 - lv_obj_get_height(mem->header));
        lv_obj_align(mem->sb, mem->header, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 0);
        lv_page_set_sb_mode(mem->sb, LV_SB_MODE_AUTO);
    }
}

static void content_create(void * p_mem)
{
	MEM_INIT( mem, p_mem );

    lv_coord_t hres = lv_disp_get_hor_res(NULL);
    lv_coord_t vres = lv_disp_get_ver_res(NULL);

    mem->content = lv_page_create(lv_disp_get_scr_act(NULL), NULL);

    if(hres > vres) {
        lv_obj_set_size(mem->content, hres - lv_obj_get_width(mem->sb), vres - lv_obj_get_height(mem->header));
        lv_obj_set_pos(mem->content,  lv_obj_get_width(mem->sb), lv_obj_get_height(mem->header));
    } else {
        lv_obj_set_size(mem->content, hres , vres / 2);
        lv_obj_set_pos(mem->content,  0, vres / 2);
    }

    lv_page_set_scrl_layout(mem->content, LV_LAYOUT_PRETTY);
    lv_page_set_scrl_fit2(mem->content, LV_FIT_FLOOD, LV_FIT_TIGHT);

    lv_coord_t max_w = lv_page_get_fit_width(mem->content);


    /*Button*/
    lv_obj_t * btn = lv_btn_create(mem->content, NULL);
    lv_btn_set_ink_in_time(btn, 200);
    lv_btn_set_ink_wait_time(btn, 100);
    lv_btn_set_ink_out_time(btn, 500);
    lv_obj_t * label = lv_label_create(btn, NULL);
    lv_label_set_text(label, "Button");

    /*Switch*/
    lv_obj_t * sw = lv_sw_create(mem->content, NULL);
    lv_sw_set_anim_time(sw, 250);

    /*Check box*/
    lv_cb_create(mem->content, NULL);

    /*Bar*/
    lv_obj_t * bar = lv_bar_create(mem->content, NULL);
    lv_obj_set_width(bar, LV_MATH_MIN(max_w, 3 * LV_DPI / 2));
#if LV_USE_ANIMATION
    lv_anim_t a;
    a.var = bar;
    a.start = 0;
    a.end = 100;
    a.exec_cb = (lv_anim_exec_xcb_t)bar_set_value;
    a.path_cb = lv_anim_path_linear;
    a.ready_cb = NULL;
    a.act_time = 0;
    a.time = 1000;
    a.playback = 1;
    a.playback_pause = 100;
    a.repeat = 1;
    a.repeat_pause = 100;
    lv_anim_create(&a);
#endif

    /*Slider*/
    lv_obj_t * slider = lv_slider_create(mem->content, NULL);
    lv_obj_set_width(slider, LV_MATH_MIN(max_w, 3 * LV_DPI / 2));
    lv_slider_set_value(slider, 30, false);

    /*Roller*/
    static const char * days = "Monday\nTuesday\nWednesday\nThursday\nFriday\nSaturday\nSunday";
    lv_obj_t * roller = lv_roller_create(mem->content, NULL);
    lv_roller_set_options(roller, days, false);

    /*Drop down list*/
    static const char * nums = "One\nTwo\nThree\nFour";
    lv_obj_t * ddlist = lv_ddlist_create(mem->content, NULL);
    lv_ddlist_set_options(ddlist, nums);

    /*Line meter*/
    lv_obj_t * lmeter = lv_lmeter_create(mem->content, NULL);
    lv_obj_set_click(lmeter, false);
#if LV_USE_ANIMATION
    a.var = lmeter;
    a.start = 0;
    a.end = 100;
    a.exec_cb = (lv_anim_exec_xcb_t)lv_lmeter_set_value;
    a.path_cb = lv_anim_path_linear;
    a.ready_cb = NULL;
    a.act_time = 0;
    a.time = 1000;
    a.playback = 1;
    a.playback_pause = 100;
    a.repeat = 1;
    a.repeat_pause = 100;
    lv_anim_create(&a);
#endif

    /*Gauge*/
    lv_obj_t * gauge = lv_gauge_create(mem->content, NULL);
    lv_gauge_set_value(gauge, 0, 47);
    lv_obj_set_size(gauge, LV_MATH_MIN(max_w, LV_DPI * 3 / 2), LV_MATH_MIN(max_w, LV_DPI * 3 / 2));
    lv_obj_set_click(gauge, false);

    /*Text area*/
    lv_obj_t * ta = lv_ta_create(mem->content, NULL);
    lv_obj_set_width(ta, LV_MATH_MIN(max_w, LV_DPI * 3 / 2));
    lv_ta_set_one_line(ta, true);
    lv_ta_set_text(ta, "Type...");

    /*Keyboard*/
    lv_obj_t * kb = lv_kb_create(mem->content, NULL);
    lv_obj_set_width(kb, max_w - LV_DPI / 4);
    lv_kb_set_ta(kb, ta);

    lv_obj_t * mbox = lv_mbox_create(lv_disp_get_scr_act(NULL), NULL);
    lv_obj_set_drag(mbox, true);
    lv_mbox_set_text(mbox, "Choose a theme and a color on the left!");

    static const char * mbox_btns[] = {"Ok", ""};
    lv_mbox_add_btns(mbox, mbox_btns);

    lv_obj_align(mbox, NULL, LV_ALIGN_CENTER, 0, 0);
}

static void init_all_themes(void * p_mem, uint16_t hue)
{
	MEM_INIT( mem, p_mem );
    /* NOTE: This must be adjusted if more themes are added. */
    int i = 0;
#if LV_USE_THEME_NIGHT
    mem->themes[i++] = lv_theme_night_init(hue, NULL);
#endif

#if LV_USE_THEME_MATERIAL
    mem->themes[i++] = lv_theme_material_init(hue, NULL);
#endif

#if LV_USE_THEME_ALIEN
    mem->themes[i++] = lv_theme_alien_init(hue, NULL);
#endif

#if LV_USE_THEME_ZEN
    mem->themes[i++] = lv_theme_zen_init(hue, NULL);
#endif

#if LV_USE_THEME_NEMO
    mem->themes[i++] = lv_theme_nemo_init(hue, NULL);
#endif

#if LV_USE_THEME_MONO
    mem->themes[i++] = lv_theme_mono_init(hue, NULL);
#endif

#if LV_USE_THEME_DEFAULT
    mem->themes[i++] = lv_theme_default_init(hue, NULL);
#endif
}

static void theme_select_event_handler(lv_obj_t * roller, lv_event_t event)
{
    if(event == LV_EVENT_VALUE_CHANGED) {
        lv_coord_t hres = lv_disp_get_hor_res(NULL);
        lv_coord_t vres = lv_disp_get_ver_res(NULL);

		void * p_mem = lv_obj_get_user_data(roller);
		MEM_INIT( mem, p_mem );

		uint16_t opt = lv_roller_get_selected(roller);
        mem->th_act = mem->themes[opt];
        lv_theme_set_current(mem->th_act);

        lv_obj_align(mem->header, NULL, LV_ALIGN_IN_TOP_MID, 0, 0);
        lv_obj_align(mem->sb, mem->header, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 0);

		if(hres > vres) {
			lv_obj_set_size(mem->content, hres - lv_obj_get_width(mem->sb), vres - lv_obj_get_height(mem->header));
			lv_obj_set_pos(mem->content,  lv_obj_get_width(mem->sb), lv_obj_get_height(mem->header));
		} else {
			lv_obj_set_size(mem->content, hres , vres / 2);
			lv_obj_set_pos(mem->content,  0, vres / 2);
		}

        lv_page_focus(mem->sb, roller, LV_ANIM_ON);
    }
}

static void hue_select_event_cb(lv_obj_t * roller, lv_event_t event)
{
    if(event == LV_EVENT_VALUE_CHANGED) {
        uint16_t hue = lv_roller_get_selected(roller) * 30;

		void * p_mem = lv_obj_get_user_data(roller);
		MEM_INIT( mem, p_mem );

		init_all_themes(p_mem, hue);

        lv_theme_set_current(mem->th_act);

        lv_page_focus(mem->sb, roller, LV_ANIM_ON);
    }
}

static void bar_set_value(lv_obj_t * bar, int16_t value)
{
    lv_bar_set_value(bar, value, LV_ANIM_OFF);
}

/*===================== Callbacks and Events================== */

/*Settings*/
/*Info*/
/*Help*/

#endif  /*USE_SNDBX_PGE_LV_TEST_THEME_2*/
