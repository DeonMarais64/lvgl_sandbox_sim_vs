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
#include "lv_examples/lv_apps/demo/demo.h"
#include "lv_examples/lv_apps/benchmark/benchmark.h"
#include "lv_examples/lv_tests/lv_test.h"
//#include "lv_examples/lv_tests/lv_test_theme/lv_test_theme_1.h"
#include "lv_examples/lv_tutorial/10_keyboard/lv_tutorial_keyboard.h"

#include <stdio.h>
#include "sndbx/apps/sndbx_apps.h"

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
static void app_lv_log (lv_log_level_t lev, const char* fn, uint32_t ln, const char* msg);

/**********************
*  STATIC VARIABLES
**********************/
static lv_indev_t * kb_indev;

/**********************
*      MACROS
**********************/

/**********************
*   GLOBAL FUNCTIONS
**********************/

int main(int argc, char** argv)
{
    lv_log_register_print_cb(app_lv_log);

    /*Initialize LittlevGL*/
    lv_init();

    /*Initialize the HAL for LittlevGL*/
    hal_init();

    /*
     * Demo, benchmark, tests and tutorial.
     *
     * Uncomment any one (and only one) of the functions below to run that
     * particular demo, test or tutorial.
     */

	//sndbx_pge_lv_test_theme_2_test();
    //sndbx_app_hello_world();
    //sndbx_app_monolith_test();
	//sndbx_app_test_test();
    sndbx_app_splash_hello();

	//lv_ex_table_1();

	//lv_test_chart_1();
	//lv_test_chart_2(3);
	//lv_test_chart_3();


	//demo_create();
    //benchmark_create();
    //lv_test_theme_1(lv_theme_night_init(210, NULL));
    //lv_test_theme_1(lv_theme_night_init(100, NULL));
    //lv_test_theme_1(lv_theme_material_init(210, NULL));
    //lv_test_theme_1(lv_theme_alien_init(210, NULL));
    //lv_test_theme_1(lv_theme_zen_init(210, NULL));
    //lv_test_theme_1(lv_theme_nemo_init(210, NULL));
    //lv_test_theme_1(lv_theme_mono_init(210, NULL));
    //lv_test_theme_1(lv_theme_default_init(210, NULL));
    //lv_tutorial_keyboard(kb_indev);

    while (1) {
        /* Periodically call the lv_task handler.
        * It could be done in a timer interrupt or an OS task too.*/
        lv_task_handler();
        Sleep(10);       /*Just to let the system breathe */
    }

    return 0;
}

void app_init_theme( void )
{
	lv_theme_t * th;
	th = lv_theme_default_init( 0, NULL );
	lv_theme_set_current( th );
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
        lv_tick_inc(5);
        SDL_Delay(5);   /*Sleep for 1 millisecond*/
    }

    return 0;
}

static void app_lv_log (lv_log_level_t lev, const char* fn, uint32_t ln, const char* msg)
{
    static const char* lvl_prefix[] = { "Trace", "Info", "Warn", "Error", "Lev??" };
    lev = lev <= LV_LOG_LEVEL_ERROR ? lev : 4;
    const char* slash = strrchr(fn, '\\');
    fn = slash ? slash + 1 : fn;
    printf("%5s: %15s %4d, %s\n", lvl_prefix[lev], fn, ln, msg);
}
