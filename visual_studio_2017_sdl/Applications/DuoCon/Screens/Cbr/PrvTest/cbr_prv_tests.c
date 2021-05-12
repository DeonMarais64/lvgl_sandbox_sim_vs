/**
 * @file cbr_prv_tests.c
 *
 */

 /*********************
  *      INCLUDES
  *********************/
#include "cbr_prv_tests.h"
//#include "../NewTest/cbr_tests.h"

#if USE_CBR_PRV_TESTS

#include "Controller/Cbr/controllerCbr.h"
#include "UI/glUtils/glUtils.h"
#include "UI/glUtils/gui.h"
#include "RTC.h"
#include "utils.h"
#include "utilsStr.h"
//#include "File.h"
//#include "FileUtility.h"

#include <stdlib.h>
#include <stdio.h>

/*********************
 *      DEFINES
 *********************/
#define PAGE_NAME "CBR press Previous Tests"

/**********************
 *      TYPEDEFS
 **********************/
typedef struct{
	C tme[12];
	C sampleNb[20];
	C pressure[12];
	C displacement[12];
	C other[12];
} TestStrings_t;

typedef struct {
	lv_obj_t * parent;
	eCbrCtrlrId_t testId;
	PCC logDir;
	//finddata_t fd;
	union {
		C path[80];
		C buf[80];
	};
	FILE * pf;
	L fpos;
	I 	lines;
	I nbDispResults;
	TestStrings_t tDta;
	lv_obj_t *table_results;
} mem_t;

/**********************
 *  STATIC PROTOTYPES
 **********************/

static void create_cb( lv_obj_t * parent, void * mem, const void * prms );
static void destroy_cb( void * p_mem );

/**********************
 *  GLOBAL DESCRIPTORS
 **********************/
const sndbx_pge_dsc_t cbr_prv_tests_dsc = {
	.name = PAGE_NAME,
	.mem_size = sizeof( mem_t ),
	.create_cb = create_cb,
	.destroy_cb = destroy_cb,
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
void cbr_prv_tests_test( void )
{
	static const sndbx_pge_t page = {
		.dsc = &cbr_prv_tests_dsc,
	};

	sndbx_app_create( &page );
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

static V PageTitleSet( eCbrCtrlrId_t id )
{
	PCC title = NULL;
	switch( id ) {
		case CTRLR_CBR_TSTCBR: title = "CBR Results"; break;
		case CTRLR_CBR_TSTUCS: title = "UCS Results"; break;
		case CTRLR_CBR_TSTITS: title = "ITS Results"; break;
		case CTRLR_CBR_TSTMARSHALL: title = "Marshall Results"; break;
		default: return;
	}

	sndbx_pge_set_title( title );
}

static void up_btn_event_cb(lv_obj_t* btn, lv_event_t e)
{
	if (e != LV_EVENT_CLICKED)
		return;
	mem_t* mem = sndbx_pge_get_mem();
	(V)mem;
}

static void dn_btn_event_cb(lv_obj_t* btn, lv_event_t e)
{
	if (e != LV_EVENT_CLICKED)
		return;
	mem_t* mem = sndbx_pge_get_mem();
	(V)mem;
}

/**
 * Called when the page is created,
 * @param parent object pointer, lv_container or lv_scr
 * @param p_mem memory pointer, points to memory allocated by the sandbox  
 * @param prms create_cb parameters
 */
static void create_cb( lv_obj_t * parent, void * p_mem, const void * prms )
{
	MEM_INIT( mem, p_mem );

	mem->parent = parent;
	const eCbrCtrlrId_t *pTestId = (eCbrCtrlrId_t*)prms;
	mem->testId = *pTestId;
	PageTitleSet( mem->testId );

#if 0
	mem->logDir = cbr_LogDirectoryGet( mem->testId );

	H hff = FileFindFirst( mem->logDir, 0, &mem->fd );
	do {
	} while( FileFindNext(hff, &mem->fd) == 0 );

	FileFindClose( hff );
	if( !mem->fd.name[0] )
		return;

	ST len = strlen( mem->logDir );
	sprintf( mem->path, "%s/%s", mem->logDir, mem->fd.name );
	mem->lines = FileCountChar( mem->path, '\n' );
	if( !mem->lines )
		return;
#else
	mem->lines = 36;
	strcpy(mem->path, "cbr.txt");
#endif;

	mem->pf = fopen( mem->path, "r" );
	mem->fpos = ftell( mem->pf );
	fseek( mem->pf, mem->fpos, SEEK_SET );

	I k, lines = mem->lines;
	mem->nbDispResults = lines <= 20 ? lines : 20;
	for( ; lines > mem->nbDispResults; --lines )
		k = fscanf( mem->pf, "%s\r\n", mem->buf	);

	mem->table_results = gui_table_create( parent, mem->nbDispResults, 5 );
	gui_table_c5_set_types( mem->table_results, mem->nbDispResults, 1, 1, 1, 1, 1 );

	B hasAnalogue = 0
		| (mem->testId == CTRLR_CBR_TSTUCS)
		| (mem->testId == CTRLR_CBR_TSTITS)
		| (mem->testId == CTRLR_CBR_TSTMARSHALL)
	;
	gui_table_c5_set_aligns( mem->table_results, mem->nbDispResults,
		LV_LABEL_ALIGN_CENTER,
		LV_LABEL_ALIGN_LEFT,
		LV_LABEL_ALIGN_RIGHT,
		LV_LABEL_ALIGN_RIGHT,
		hasAnalogue ? LV_LABEL_ALIGN_RIGHT : LV_LABEL_ALIGN_CENTER
	);

	for( I i = 0; i< mem->nbDispResults; ++i )
		lv_table_set_cell_crop( mem->table_results, i, 1, true );
	gui_table_c5_set_col_widths( mem->table_results, LV_DPI*5/6, LV_DPI*9/6, LV_DPI*5/6, LV_DPI*3/6, LV_DPI*5/6 );

	lv_obj_align( mem->table_results, NULL, LV_ALIGN_CENTER, 0, 0 );

	for( I i = 0; lines; --lines, ++i )
	{
		k = fscanf( mem->pf, "%s\r\n", mem->buf	);
		StrReplaceChar( mem->buf, ',' , ' ' );

		TestStrings_t * td = &mem->tDta;
		memset( td, 0, sizeof(*td) );
		k = sscanf( mem->buf, "%s %s %s %s %s",
			td->tme, td->sampleNb, td->pressure, td->displacement, td->other );
		gui_table_c5_set_row( mem->table_results, i,
			td->tme, td->sampleNb, td->pressure, td->displacement, td->other
		);
	}
	fclose( mem->pf );
	mem->pf = NULL;
	
	lv_obj_t* btn;
	btn = gui_btn_create( parent, LV_SYMBOL_UP, up_btn_event_cb, 1, NULL);
	lv_btn_set_fit( btn, LV_FIT_TIGHT );
	//lv_obj_set_height( btn, lv_obj_get_width(btn)*3/4 );
	lv_obj_align( btn, NULL, LV_ALIGN_IN_TOP_RIGHT, 0, 0 );

	btn = gui_btn_create( parent, LV_SYMBOL_DOWN, dn_btn_event_cb, 1, NULL);
	lv_btn_set_fit( btn, LV_FIT_TIGHT );
	lv_obj_set_height( btn, lv_obj_get_width(btn)*3/4);
	lv_obj_align( btn, NULL, LV_ALIGN_IN_BOTTOM_RIGHT, 0, 0 );
}

/**
 * Called when the page is being destroyed.
 * @param p_mem memory pointer, points to memory allocated by the sandbox
 */
static void destroy_cb( void * p_mem )
{
	MEM_INIT( mem, p_mem );
	if( mem->pf )
		fclose( mem->pf );
}

/*===================== Callbacks and Events================== */

/*+Settings*/
/*-Settings*/

#endif  /*USE_CBR_PRV_TESTS*/
