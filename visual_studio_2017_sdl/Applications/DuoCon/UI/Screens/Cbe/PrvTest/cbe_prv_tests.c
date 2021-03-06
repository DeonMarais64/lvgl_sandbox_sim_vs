/**
 * @file cbe_prv_tests.c
 *
 */

 /*********************
  *      INCLUDES
  *********************/
#include "cbe_prv_tests.h"
//#include "../NewTest/cbe_tests.h"

#if USE_CBE_PRV_TESTS

#include "Controller/Cbe/controllerCbe.h"
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
#define PAGE_NAME "Cube press Previous Tests"

/**********************
 *      TYPEDEFS
 **********************/
typedef struct{
	C tme[12];
	C sampleNb[20];
	C pressure[12];
	C sampleMass[12];
	C other[12];
} TestStrings_t;

typedef struct {
	I	index;
	I	count;
	PL	pPos;
} FilePos_t;

typedef struct {
	lv_obj_t * parent;
	C title[32];
	eCbeCtrlrId_t testId;
	PCC logDir;
	//finddata_t fd;
	union {
		C path[80];
		C buf[80];
	};
	FILE * pf;
	FilePos_t fpos;
	TestStrings_t tDta;
	lv_obj_t *table_results;
	lv_obj_t* btn_up;
	lv_obj_t* btn_dn;
} mem_t;

/**********************
 *  STATIC PROTOTYPES
 **********************/

static void create_cb( lv_obj_t * parent, void * mem, const void * prms );
static void destroy_cb( void * p_mem );

/**********************
 *  GLOBAL DESCRIPTORS
 **********************/
const sndbx_pge_dsc_t cbe_prv_tests_dsc = {
	.name = PAGE_NAME,
	.mem_size = sizeof( mem_t ),
	.create_cb = create_cb,
	.destroy_cb = destroy_cb,
};

/**********************
 *  STATIC VARIABLES
 **********************/

static const TestStrings_t testStrEmpty = {
	"","","",""
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
void cbe_prv_tests_test( void )
{
	static const sndbx_pge_t page = {
		.dsc = &cbe_prv_tests_dsc,
	};

	sndbx_app_create( &page );
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

static V PageTitleSet ( eCbeCtrlrId_t id )
{
	PCC title = NULL;
	switch( id ) {
		case CTRLR_CBE_TSTCS: title = "Cubes Results"; break;
		case CTRLR_CBE_TSTACV: title = "ACV Results"; break;
		case CTRLR_CBE_TSTFACT: title = "10% Fact Results"; break;
		case CTRLR_CBE_TSTBRKS: title = "Bricks Results"; break;
		case CTRLR_CBE_TSTCLNDS: title = "Cylinders Results"; break;
		default: return;
	}

	PCC date = "20201207";
	U32 v = atol( date );
	UI yyyy = v / 10000;
	UI mm = (v % 10000)/100;
	UI dd = v % 100;

	mem_t* mem = sndbx_pge_get_mem();

	sprintf(mem->title, "%s %.4u-%.2u-%.2u", title, yyyy, mm, dd);

	sndbx_pge_set_title( mem->title );
}

static void table_results_show( bool up )
{
	mem_t* mem = sndbx_pge_get_mem();
	FilePos_t* pos = &mem->fpos;
	if( up )
	{
		pos->index = pos->index >= 1 ? pos->index-1 : 0;
		fseek( mem->pf, pos->pPos[pos->index], SEEK_SET );
		if( mem->btn_up )
			if( pos->pPos[pos->index] == 0 )
				gui_btn_disable( mem->btn_up );
	}
	else
	{
		++pos->index;
		if( pos->index >= pos->count )
		{
			pos->count = pos->index+1;
			PL p = (PL)lv_mem_realloc(pos->pPos, pos->count * sizeof(L));
			pos->pPos = p ? p : --pos->index, pos->pPos;
			pos->pPos[pos->index] = ftell(mem->pf);
		}
	}

	I rows = lv_table_get_row_cnt(mem->table_results);	
	for( I i = 0; i<rows; ++i )
	{
		TestStrings_t* td = &mem->tDta;
		if( feof(mem->pf) )
			*td = testStrEmpty;
		else
		{
			I k = fscanf(mem->pf, "%s\r\n", mem->buf);
			if( k < 1 )
				*td = testStrEmpty;
			else
			{
				StrReplaceChar( mem->buf, ',', ' ' );
				k = sscanf( mem->buf, "%s %s %s %s %s",
					td->tme, td->sampleNb, td->sampleMass, td->pressure, td->other
				);
			}
		}
		gui_table_c5_set_row( mem->table_results, i,
			td->tme, td->sampleNb, td->sampleMass, td->pressure, td->other
		);
	}
}

static void up_btn_event_cb( lv_obj_t* btn, lv_event_t e )
{
	if( e != LV_EVENT_CLICKED )
		return;
	table_results_show( true );
	mem_t* mem = sndbx_pge_get_mem();
	gui_btn_enable( mem->btn_dn );
}

static void dn_btn_event_cb( lv_obj_t* btn, lv_event_t e )
{
	if( e != LV_EVENT_CLICKED )
		return;
	table_results_show( false );
	mem_t* mem = sndbx_pge_get_mem();
	gui_btn_enable(mem->btn_up);
	if( feof(mem->pf) )
		gui_btn_disable( btn );
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
	const eCbeCtrlrId_t *pTestId = (eCbeCtrlrId_t*)prms;
	mem->testId = *pTestId;
	PageTitleSet( mem->testId );

#if 0
	mem->logDir = cbe_LogDirectoryGet( mem->testId );

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
	strcpy(mem->path, "test.txt" );
#endif;
	mem->pf = fopen( mem->path, "r" );
	mem->fpos.pPos = lv_mem_alloc( sizeof(L) );
	if( !mem->fpos.pPos )
		return;

	I rows = 20;
	mem->table_results = gui_table_create( parent, rows, 5 );

	gui_table_c5_set_types( mem->table_results, rows, 1, 1, 1, 1, 1 );
	B hasStress = 0
		| (mem->testId == CTRLR_CBE_TSTCS)
		| (mem->testId == CTRLR_CBE_TSTBRKS)
		| (mem->testId == CTRLR_CBE_TSTCLNDS)
	;
	gui_table_c5_set_aligns( mem->table_results, rows,
		LV_LABEL_ALIGN_CENTER,
		LV_LABEL_ALIGN_LEFT,
		LV_LABEL_ALIGN_RIGHT,
		LV_LABEL_ALIGN_RIGHT,
		hasStress ? LV_LABEL_ALIGN_RIGHT : LV_LABEL_ALIGN_CENTER
	);

	for( I i = 0; i < rows; ++i )
		lv_table_set_cell_crop( mem->table_results, i, 1, true );
	gui_table_c5_set_col_widths( mem->table_results, LV_DPI*5/6, LV_DPI*7/6, LV_DPI*3/6, LV_DPI*5/6, LV_DPI*5/6 );
	lv_obj_align( mem->table_results, NULL, LV_ALIGN_CENTER, 0, 0 );

	mem->fpos.index = -1;
	mem->fpos.count = 1;
	mem->fpos.pPos[0] = ftell( mem->pf );
	table_results_show( false );

	if( !feof(mem->pf) )
	{
		mem->btn_up = gui_btn_create( parent, LV_SYMBOL_UP, up_btn_event_cb, 1, NULL );
		lv_btn_set_fit( mem->btn_up, LV_FIT_TIGHT );
		lv_obj_align( mem->btn_up, NULL, LV_ALIGN_IN_TOP_RIGHT, 0, 0 );
		gui_btn_disable( mem->btn_up );
		mem->btn_dn = gui_btn_create( parent, LV_SYMBOL_DOWN, dn_btn_event_cb, 1, NULL );
		lv_btn_set_fit( mem->btn_dn, LV_FIT_TIGHT );
		lv_obj_align( mem->btn_dn, NULL, LV_ALIGN_IN_BOTTOM_RIGHT, 0, 0 );
	}
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
	if( mem->fpos.pPos )
		lv_mem_free( mem->fpos.pPos );
}

/*===================== Callbacks and Events================== */

/*+Settings*/
/*-Settings*/

#endif  /*USE_CBE_PRV_TESTS*/
