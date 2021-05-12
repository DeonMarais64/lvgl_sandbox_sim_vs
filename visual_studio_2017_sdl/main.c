/**
* @file main
*
*/

/*********************
*      INCLUDES
*********************/
#include <stdlib.h>
#include <Windows.h>
#include <SDL.h>
#include "lvgl/lvgl.h"
#include "lv_drivers/display/monitor.h"
#include "lv_drivers/indev/mouse.h"
#include "lv_drivers/indev/keyboard.h"

#include "lv_examples/lv_examples.h"

#include <stdio.h>

#if 0
#include "lv_examples/lv_apps/demo/demo.h"
#include "lv_examples/lv_apps/benchmark/benchmark.h"
#include "lv_examples/lv_tests/lv_test.h"
//#include "lv_examples/lv_tests/lv_test_theme/lv_test_theme_1.h"
#include "lv_examples/lv_tutorial/10_keyboard/lv_tutorial_keyboard.h"

#endif
#include "sndbx/apps/sndbx_apps.h"
#include "sndbx/pages/sndbx_pges.h"

#include "Applications/DuoCon/UI/Screens/Cbe/PrvTest/cbe_prv_test.h"
#include "Applications/DuoCon/UI/Screens/Cbr/PrvTest/cbr_prv_test.h"


/*********************
*      DEFINES
*********************/

/**********************
*      TYPEDEFS
**********************/

/**********************
*  STATIC PROTOTYPES
**********************/
static void hal_init(void);
static int tick_thread(void *data);
static void app_lv_log (lv_log_level_t lev, const char* fn, uint32_t ln, const char* msg, const char* buf);

/**********************
*  STATIC VARIABLES
**********************/
static lv_indev_t * kb_indev;

#if 0
static bool lv_task_handler_in_tick = true;
#else
static bool lv_task_handler_in_tick;
#endif

static void (*main_lv_taskh_dispatch)(void);

/**********************
*      MACROS
**********************/

/**********************
*   GLOBAL FUNCTIONS
**********************/

void main_dispatch_post_lvgl_tskh(void (*fun)(void))
{
    main_lv_taskh_dispatch = fun;
}

int main(int argc, char** argv)
{
    lv_log_register_print_cb(app_lv_log);

    /*Initialize LVGL*/
    lv_init();

    /*Initialize the HAL for LVGL*/
    hal_init();

    SDL_Delay(LV_DISP_DEF_REFR_PERIOD+1);
    lv_task_handler();
    lv_task_handler_in_tick = true;


/*+ V7 */
#if 1
    //lv_demo_benchmark();
    //lv_demo_keypad_encoder();
    //lv_demo_music();
    //lv_demo_printer();
    //lv_demo_stress();
    //lv_demo_widgets();
    //lv_demo_music();

    //lv_ex_get_started_1();
    //lv_ex_get_started_2();
    //lv_ex_get_started_3();

    //lv_ex_style_1();
    //lv_ex_style_2();
    //lv_ex_style_3();
    //lv_ex_style_4();
    //lv_ex_style_5();
    //lv_ex_style_6();
    //lv_ex_style_7();
    //lv_ex_style_8();
    //lv_ex_style_9();
    //lv_ex_style_10();
    //lv_ex_style_11();

    //lv_ex_arc_1();
    //lv_ex_arc_2();

    //lv_ex_bar_1();
    //lv_ex_cont_1();
    //lv_ex_objmask_1();
    //lv_ex_calendar_1();
#endif
/*- V7 */

#if 1
    //main_test_chart();

/*+ Sandbox Apps*/
    //sndbx_app_hello_world();
    //sndbx_app_splash_hello();
    sndbx_app_demo();
    //sndbx_app_monolith_test();    /* Not yet working */
	//sndbx_app_test_test();        /* Not yet working */

    //sndbx_app_();
 /*- Sandbox Apps*/

/*+ Sandbox Pages*/
    //sndbx_pge__test();
    //sndbx_pge_templ_test();
    //sndbx_pge_template_test();
    //sndbx_pge_lv_app_sysmon_test();
    //sndbx_pge_table_test();
    //sndbx_pge_lv_demos_test();
    //sndbx_pge_lv_ex_style_test();
    //sndbx_pge_lv_ex_widgets_test();

    //sndbx_pge_demo_test();
/*- Sandbox Pages*/

/*+ Application Development */
    //cbe_prv_test_test();
    //cbr_prv_test_test();
    //sndbx_pge_extentions_test();
/*- Applications Development */
#endif


    lv_task_handler_in_tick = false;
    while (1) {
        /* Periodically call the lv_task handler.
        * It could be done in a timer interrupt or an OS task too.*/
        if (!lv_task_handler_in_tick)
        {
            lv_task_handler();
            if (main_lv_taskh_dispatch)
            {
                lv_task_handler_in_tick = true;
                main_lv_taskh_dispatch();
                main_lv_taskh_dispatch = NULL;
                lv_task_handler_in_tick = false;
            }
        }
        Sleep(10);       /*Just to let the system breathe */
    }

    return 0;
}

/**********************
*   STATIC FUNCTIONS
**********************/

/**
* Initialize the Hardware Abstraction Layer (HAL) for the Littlev graphics library
*/
static void hal_init(void)
{
    /* Add a display
    * Use the 'monitor' driver which creates window on PC's monitor to simulate a display*/
    monitor_init();

    lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);            /*Basic initialization*/

    static lv_disp_buf_t disp_buf1;
    static lv_color_t buf1_1[LV_HOR_RES_MAX*LV_VER_RES_MAX];
    lv_disp_buf_init(&disp_buf1, buf1_1, NULL, LV_HOR_RES_MAX*LV_VER_RES_MAX);

    disp_drv.buffer = &disp_buf1;
    disp_drv.flush_cb = monitor_flush;
    lv_disp_drv_register(&disp_drv);

    /* Add the mouse (or touchpad) as input device
    * Use the 'mouse' driver which reads the PC's mouse*/
    mouse_init();
    lv_indev_drv_t indev_drv;
    lv_indev_drv_init(&indev_drv);          /*Basic initialization*/
    indev_drv.type = LV_INDEV_TYPE_POINTER;
    indev_drv.read_cb = mouse_read;         /*This function will be called periodically (by the library) to get the mouse position and state*/
    lv_indev_drv_register(&indev_drv);

    /* If the PC keyboard driver is enabled in`lv_drv_conf.h`
    * add this as an input device. It might be used in some examples. */
#if USE_KEYBOARD
    lv_indev_drv_t kb_drv;
    lv_indev_drv_init(&kb_drv);
    kb_drv.type = LV_INDEV_TYPE_KEYPAD;
    kb_drv.read_cb = keyboard_read;
    kb_indev = lv_indev_drv_register(&kb_drv);
#endif

    /* Tick init.
    * You have to call 'lv_tick_inc()' in every milliseconds
    * Create an SDL thread to do this*/
    SDL_CreateThread(tick_thread, "tick", NULL);
}

/**
* A task to measure the elapsed time for LittlevGL
* @param data unused
* @return never return
*/
static int tick_thread(void *data)
{
    while (1) {
        SDL_Delay(5);   /*Sleep for 5 milliseconds*/
        lv_tick_inc(5);
        if (lv_task_handler_in_tick)
        {
            static bool twice;
            twice = !twice;
            if( twice )
            {
                lv_task_handler();
            }
        }
    }

    return 0;
}

static void app_lv_log ( lv_log_level_t lev, const char* fn, uint32_t ln, const char* msg, const char * buf )
{
    static const char* lvl_prefix[] = { "Trace", "Info", "Warn", "Error", "Lev??" };
    lev = lev <= LV_LOG_LEVEL_ERROR ? lev : 4;
    const char* slash = strrchr(fn, '\\');
    slash = slash ? slash : strrchr(fn, '/');
    fn = slash ? slash + 1 : fn;
    printf("%5s: %15s %4d, %20s, %s\n", lvl_prefix[lev], fn, ln, msg, buf);
}
