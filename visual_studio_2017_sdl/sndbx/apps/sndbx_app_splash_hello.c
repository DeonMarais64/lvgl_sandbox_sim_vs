/**
 * @file sndbx_app_splash_hello.c
 *
 */

 /*********************
  *      INCLUDES
  *********************/
#include "sndbx_app_splash_hello.h"
#if USE_SNDBX_APP_SPLASH_HELLO

#include "../src/sndbx.h"
#include <stdio.h>

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/
typedef struct {          /* Memory spec, if required */
    lv_obj_t* lbl;
    uint32_t ctr;
} hello_people_mem_t;

/**********************
 *  STATIC PROTOTYPES
 **********************/
static void splash_create(lv_obj_t* parent, void* mem, const void* prms);
static void splash_task(void* p_mem);

static void hello_world_create(lv_obj_t * parent, void * mem, const void * prms);
static void hello_people_create(lv_obj_t* parent, void* mem, const void* prms);
static void hello_people_task(void* p_mem);

/**********************
 *  STATIC VARIABLES
 **********************/
static const sndbx_pge_dsc_t dsc_splash = {
    .name = "",
    .create_cb = splash_create,
    .task_cb = splash_task,
    .task_prio = LV_TASK_PRIO_LOW,
    .task_period = 1500,    /*1.5 second splash duration*/
    .opt = SNDBX_OPT_SCREEN,
};

static const sndbx_pge_dsc_t dsc_hello_world = {
    .name = "Hello World",
    .create_cb = hello_world_create,
};

static const sndbx_pge_dsc_t dsc_hello_people = {
    .name = "Hello People",
    .mem_size = sizeof(hello_people_mem_t),
    .create_cb = hello_people_create,
    .task_cb = hello_people_task,
    .task_prio = LV_TASK_PRIO_MID,
    .task_period = 500,
};

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

/**
 * Create a sandbox application, 
 * The simplist possible example
 */
void sndbx_app_splash_hello( void )
{
	static const sndbx_pge_t pge = {
		.dsc = &dsc_splash,
	};
	sndbx_app_create( &pge );
}

/**********************
 *   STATIC FUNCTIONS
 **********************/
void splash_create(lv_obj_t* parent, void* p_mem, const void* prms)
{
    (void)p_mem;  /* Not used */
    (void)prms;   /* Not used */

    /* Create content */
    lv_obj_t* lbl = lv_label_create(parent, NULL);

    lv_label_set_text(lbl, "**** Splash content ****");

    lv_obj_align(lbl, NULL, LV_ALIGN_CENTER, 0, 0);
}

void splash_task(void* p_mem)
{
    (void)p_mem;  /* Not used */

    static const sndbx_pge_t pge = {
        .dsc = &dsc_hello_world,
    };

    sndbx_app_create(&pge);
}

void hello_world_create( lv_obj_t * parent, void * p_mem, const void * prms )
{
	(void)p_mem;  /* Not used */
	(void)prms;   /* Not used */

	/* Create content */
	lv_obj_t * lbl =  lv_label_create(parent, NULL);

	lv_label_set_text(lbl, "Hello World !");
	lv_obj_align(lbl, NULL, LV_ALIGN_CENTER, 0, 0);

    static const sndbx_pge_t link_right = {
        .dsc = &dsc_hello_people,
    };

    lv_obj_t* btn = sndbx_link_btn_create(parent, LV_SYMBOL_RIGHT, &link_right);
    lv_obj_align(btn, NULL, LV_ALIGN_IN_BOTTOM_RIGHT, 0, 0);
}

void hello_people_create(lv_obj_t* parent, void* p_mem, const void* prms)
{
    hello_people_mem_t* mem = p_mem;
    (void)prms;   /* Not used */

    /* Create content */
    mem->lbl = lv_label_create(parent, NULL);
    lv_label_set_text(mem->lbl, "");

    static const sndbx_pge_t link_left = {
        .dsc = &dsc_hello_world,
    };

    lv_obj_t* btn = sndbx_link_btn_create(parent, LV_SYMBOL_LEFT, &link_left);
    lv_obj_align(btn, NULL, LV_ALIGN_IN_BOTTOM_LEFT, 0, 0);
}

void hello_people_task(void* p_mem)
{
    const char* people[] = {
        "Mathew", "Mark",
        "Luke", "John",
    };
    hello_people_mem_t* mem = p_mem;

    char str[128];
    if (mem->ctr >= sizeof(people) / sizeof(people[0]))
        mem->ctr = 0;
    sprintf(str, "Hello %s !", people[mem->ctr++]);    
    lv_label_set_text(mem->lbl, str);
    lv_obj_align(mem->lbl, NULL, LV_ALIGN_CENTER, 0, 0);
}

#endif  /*USE_SNDBX_APP_SPLASH_HELLO*/
