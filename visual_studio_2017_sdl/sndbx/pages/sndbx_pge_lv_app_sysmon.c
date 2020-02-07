/**
 * @file sndbx_pge_lv_app_sysmon.c
 *
 */

 /*********************
  *      INCLUDES
  *********************/
#include "sndbx_pge_lv_app_sysmon.h"
#if USE_SNDBX_PGE_LV_APP_SYSMON

#include <stdio.h>

/*********************
 *      DEFINES
 *********************/
//#define PAGE_NAME "LittlevGL App Sysmon"
#if LV_HOR_RES_MAX < 800
#define PAGE_NAME "lv App #ff0000 Sysmon# - Managed"
#else
#define PAGE_NAME "LittlevGL App #ff0000 Sysmon# - Managed version"
#endif

#define CPU_LABEL_COLOR    "FF0000"
#define MEM_LABEL_COLOR    "0000FF"
#define CHART_POINT_NUM    100
#define REFR_TIME    500

/**********************
 *      TYPEDEFS
 **********************/
typedef struct {
	lv_obj_t * chart;
	lv_chart_series_t * cpu_ser;
	lv_chart_series_t * mem_ser;
	lv_obj_t * info_label;
	lv_task_t * refr_task;
} mem_t;

/**********************
 *  STATIC PROTOTYPES
 **********************/
static void create_cb( lv_obj_t * parent, void * mem, const void * prms );
static void task_cb( void * p_mem );

/**********************
 *  STATIC VARIABLES
 **********************/

/**********************
 *      MACROS
 **********************/
#define MEM_INIT(to,from)	mem_t*(to) = (from)

/**********************
 *   GLOBAL DESCRIPTORS
 **********************/
const sndbx_pge_dsc_t sndbx_pge_lv_app_sysmon_dsc = {
	.name = PAGE_NAME,
	.mem_size = sizeof(mem_t),
	.create_cb = create_cb,
	.task_cb = task_cb,
	.task_prio = LV_TASK_PRIO_LOW,
	.task_period = REFR_TIME,
};

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

/**
 * Create a sandbox test application
 */
void sndbx_pge_lv_app_sysmon_test( void )
{
	static const sndbx_pge_t page = {
		.dsc = &sndbx_pge_lv_app_sysmon_dsc,
	};

	sndbx_app_create( &page );
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
	MEM_INIT( mem, p_mem );

	/* Create content */

    lv_coord_t hres = lv_obj_get_width(parent);
    lv_coord_t vres = lv_obj_get_height(parent);

    /*Create a chart with two data lines*/
    mem->chart = lv_chart_create(parent, NULL);
    lv_obj_set_size(mem->chart, hres / 2, vres / 2);
//	lv_obj_set_pos(mem->chart, LV_DPI / 10, LV_DPI / 10);
	lv_obj_align(mem->chart, NULL, LV_ALIGN_CENTER, -LV_DPI*2/3, 0 );
    lv_chart_set_point_count(mem->chart, CHART_POINT_NUM);
    lv_chart_set_range(mem->chart, 0, 100);
    lv_chart_set_type(mem->chart, LV_CHART_TYPE_LINE);
    lv_chart_set_series_width(mem->chart, 2);
    mem->cpu_ser =  lv_chart_add_series(mem->chart, LV_COLOR_RED);
    mem->mem_ser =  lv_chart_add_series(mem->chart, LV_COLOR_BLUE);

    /*Set the data series to zero*/
    uint16_t i;
    for(i = 0; i < CHART_POINT_NUM; i++) {
        lv_chart_set_next(mem->chart, mem->cpu_ser, 0);
        lv_chart_set_next(mem->chart, mem->mem_ser, 0);
    }

    /*Create a label for the details of Memory and CPU usage*/
    mem->info_label = lv_label_create(parent, NULL);
    lv_label_set_recolor(mem->info_label, true);
    lv_obj_align(mem->info_label, mem->chart, LV_ALIGN_OUT_RIGHT_TOP, LV_DPI / 4, 0);

    /*Refresh the chart and label manually at first*/
    task_cb( p_mem );
}

/**
 * Called periodically, specified by task_period in sndbx_pge_dsc_t
 * @param p_mem memory pointer, points to memory allocated by the sandbox
 */
static void task_cb( void * p_mem )
{
	MEM_INIT( mem, p_mem );

    /*Get CPU and memory information */
    uint8_t cpu_busy;
    cpu_busy = 100 - lv_task_get_idle();

    uint8_t mem_used_pct = 0;
#if  LV_MEM_CUSTOM == 0
    lv_mem_monitor_t mem_mon;
    lv_mem_monitor(&mem_mon);
    mem_used_pct = mem_mon.used_pct;
#endif

    /*Add the CPU and memory data to the chart*/
    lv_chart_set_next(mem->chart, mem->cpu_ser, cpu_busy);
    lv_chart_set_next(mem->chart, mem->mem_ser, mem_used_pct);

    /*Refresh the and windows*/
    char buf_long[256];
    sprintf(buf_long, "%s%s CPU: %d %%%s\n\n",
            LV_TXT_COLOR_CMD,
            CPU_LABEL_COLOR,
            cpu_busy,
            LV_TXT_COLOR_CMD);

#if LV_MEM_CUSTOM == 0
    sprintf(buf_long, "%s"LV_TXT_COLOR_CMD"%s MEMORY: %d %%"LV_TXT_COLOR_CMD"\n"
            "Total: %d bytes\n"
            "Used: %d bytes\n"
            "Free: %d bytes\n"
            "Frag: %d %%",
            buf_long,
            MEM_LABEL_COLOR,
            mem_used_pct,
            (int)mem_mon.total_size,
            (int)mem_mon.total_size - mem_mon.free_size, mem_mon.free_size, mem_mon.frag_pct);
#else
    sprintf(buf_long, "%s"LV_TXT_COLOR_CMD"%s MEMORY: N/A"LV_TXT_COLOR_CMD,
            buf_long,
            MEM_LABEL_COLOR);
#endif
    lv_label_set_text(mem->info_label, buf_long);
}

#endif  /*USE_SNDBX_PGE_LV_APP_SYSMON*/
