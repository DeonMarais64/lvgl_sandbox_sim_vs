/**
 * @file cbe_prv_test.c
 *
 */

 /*********************
  *      INCLUDES
  *********************/
#include "cbe_prv_test.h"
#if USE_CBE_PRV_TEST

#include "cbe_prv_tests.h"
#include "Controller/Cbe/controllerCbe.h"

/*********************
 *      DEFINES
 *********************/
#define PAGE_NAME "Previous Test"

#define NB_APP_PAGES (sizeof(pages)/sizeof(pages[0]))

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/

static void create_cb( lv_obj_t * parent, void * mem, const void * prms );
static void btnm_event_handler( lv_obj_t * btnm, lv_event_t evt );


/**********************
 *  GLOBAL DESCRIPTORS
 **********************/
const sndbx_pge_dsc_t cbe_prv_test_dsc = {
	.name = PAGE_NAME,
	.create_cb = create_cb,
};

/**********************
 *  STATIC VARIABLES
 **********************/

static const eCbeCtrlrId_t prms_pages[] = {
	CTRLR_CBE_TSTCS,
	CTRLR_CBE_TSTCLNDS,
	CTRLR_CBE_TSTACV,
	CTRLR_CBE_TSTFACT,
	CTRLR_CBE_TSTBRKS,
};

static const sndbx_pge_t pages[] = {
    { .dsc = &cbe_prv_tests_dsc, .prms = &prms_pages[0] },
    { .dsc = &cbe_prv_tests_dsc, .prms = &prms_pages[1] },
    { .dsc = &cbe_prv_tests_dsc, .prms = &prms_pages[2] },
    { .dsc = &cbe_prv_tests_dsc, .prms = &prms_pages[3] },
    { .dsc = &cbe_prv_tests_dsc, .prms = &prms_pages[4] },
    { .dsc = NULL			},
};

static const char * const btnm_map[] = {
	"Cubes", "Cyliners", "ACV", "\n",
	"10% Fact",  "Bricks", "Custom",
    "",
};

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

void cbe_prv_test_test( void )
{
	static const sndbx_pge_t page = {
		.dsc = &cbe_prv_test_dsc,
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
	(void)prms;

	lv_obj_t * btnm;
    btnm = lv_btnmatrix_create(parent, NULL);
    lv_btnmatrix_set_align(btnm, LV_LABEL_ALIGN_CENTER);
    lv_coord_t w_par = lv_obj_get_width(parent);
    lv_coord_t h_par = lv_obj_get_height(parent);
    lv_btnmatrix_set_map(btnm, (const char **)btnm_map);
    lv_obj_set_width(btnm, w_par*4/5 );
    lv_obj_set_height(btnm, h_par*4/5 );
    lv_obj_align(btnm, NULL, LV_ALIGN_CENTER, 0, 0);

	for( int i = 0; i < NB_APP_PAGES; ++i)
		if( !pages[i].dsc )
			lv_btnmatrix_set_btn_ctrl(btnm, i, LV_BTNMATRIX_CTRL_DISABLED);

    lv_obj_set_event_cb(btnm, btnm_event_handler);
}


static void btnm_event_handler( lv_obj_t * btnm, lv_event_t evt )
{
    if( evt != LV_EVENT_CLICKED )
        return;
    uint16_t idx = lv_btnmatrix_get_active_btn( btnm );
    if (idx >= NB_APP_PAGES)
        return;
    if( lv_btnmatrix_get_btn_ctrl(btnm, idx, LV_BTNMATRIX_CTRL_DISABLED) )
    	return;
	const sndbx_pge_t *page = &pages[idx];
	sndbx_pge_change( page );
}

#endif  /*USE_CBE_PRV_TEST*/
