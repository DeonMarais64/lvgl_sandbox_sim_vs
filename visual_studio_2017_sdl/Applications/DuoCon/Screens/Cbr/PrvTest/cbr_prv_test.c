/**
 * @file cbr_prv_test.c
 *
 */

 /*********************
  *      INCLUDES
  *********************/
#include "cbr_prv_test.h"
#if USE_CBR_PRV_TEST

#include "cbr_prv_tests.h"
#include "Controller/Cbr/controllerCbr.h"

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
const sndbx_pge_dsc_t cbr_prv_test_dsc = {
	.name = PAGE_NAME,
	.create_cb = create_cb,
};

/**********************
 *  STATIC VARIABLES
 **********************/

static const eCbrCtrlrId_t prms_pages[] = {
	CTRLR_CBR_TSTCBR,
	CTRLR_CBR_TSTUCS,
	CTRLR_CBR_TSTITS,
	CTRLR_CBR_TSTMARSHALL,
};

static const sndbx_pge_t pages[] = {
    { .dsc = &cbr_prv_tests_dsc, .prms = &prms_pages[0] },
    { .dsc = &cbr_prv_tests_dsc, .prms = &prms_pages[1] },
    { .dsc = &cbr_prv_tests_dsc, .prms = &prms_pages[2] },
    { .dsc = &cbr_prv_tests_dsc, .prms = &prms_pages[3] },
    { .dsc = NULL			},
};

static const char * const btnm_map[] = {
	"CBR", "UCS", "ITS", "\n",
	"Marshall",  "Custom",
    "",
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
void cbr_prv_test_test( void )
{
	static const sndbx_pge_t page = {
		.dsc = &cbr_prv_test_dsc,
	};

	sndbx_app_create( &page );
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

static void create_cb( lv_obj_t * parent, void * p_mem, const void * prms )
{
	/* Create content */
	lv_obj_t * btnm;
    btnm = lv_btnmatrix_create(parent, NULL);
    lv_btnmatrix_set_align(btnm, LV_LABEL_ALIGN_CENTER);
    lv_coord_t w_par = lv_obj_get_width(parent);
    lv_coord_t h_par = lv_obj_get_height(parent);
    lv_btnmatrix_set_map(btnm, (const char **)btnm_map);
    lv_obj_set_width( btnm, w_par*4/5 );
    lv_obj_set_height( btnm, h_par*4/5 );
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

#endif  /*USE_CBR_PRV_TEST*/
