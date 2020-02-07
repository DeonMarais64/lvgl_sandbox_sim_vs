/**
 * @file sndbx_pge_table.c
 *
 */

 /*********************
  *      INCLUDES
  *********************/
#include "sndbx_pge_table.h"
#if USE_SNDBX_PGE_TABLE

#include <stdio.h>
#include <stdlib.h>
//#include <string.h>
#include <time.h>
#include "../gui/gui_table.h"
#include "../utils/Variant-Lib.h"
#include "../utils/utils.h"
#include "../fonts/symbol_ext_def.h"

/*********************
 *      DEFINES
 *********************/
#define PAGE_NAME "LittlevGL Table test"

#define TASK_PRIO      LV_TASK_PRIO_LOW
#define TASK_PERIOD    250

/**********************
 *      TYPEDEFS
 **********************/

typedef struct {
	PCC				name;
	PCC				value;
	PCC				units;
	PCC				pFmt;
	_VarXT_PFN_V_	pfValueGet;
	eVar_t			vt;
} val_dsc_t;

typedef struct {
	lv_obj_t *table;
	uint8_t row;
	Var64 value;
	const val_dsc_t *val_dsc;
} disp_val_obj_t;

typedef struct {
	uint32_t    crc32;
	const char  compileDate[21];
	const char  name[21];
	const char  application[22];
} product_dsc_t;

/**********************
 *  STATIC PROTOTYPES
 **********************/

static void create_cb( lv_obj_t * parent, void * mem, const void * prms );
static void task_cb( void * p_mem );
static void destroy_cb( void * p_mem );

static PCC DiState(V);
static FP AiValue(V);
static PCC DoState(V);
static FP AoValue(V);
static const char *TimeOpen(V);
static const char *DateTime(V);

/**********************
 *  STATIC VARIABLES
 **********************/

static const val_dsc_t val_di_dscs[] = {
	{
		.name = "Limit, upper",
		.value = "",
		.pFmt = "%.8s",
		.pfValueGet = (_VarXT_PFN_V_)DiState,
		.vt = V_CSTRING,
	},
	{
		.name = "Limit, lower",
		.value = "",
		.pFmt = "%.8s",
		.pfValueGet = (_VarXT_PFN_V_)DiState,
		.vt = V_CSTRING,
	},
	{
		.name = "Prox input",
		.value = "",
		.pFmt = "%.8s",
		.pfValueGet = (_VarXT_PFN_V_)DiState,
		.vt = V_CSTRING,
	},
	{
		.name = "Proximity",
		.units = "mm",
		.pFmt = "%.1f",
		.pfValueGet = (_VarXT_PFN_V_)AiValue,
		.vt = V_FP,
	},
};
#define NB_DISP_DSCS_DI NB_ARRAY_ITEMS(val_di_dscs)

static const val_dsc_t val_ai_dscs[] = {
	{
		.name = "Load Cell - Control",
		.units = "V",
		.pFmt = "%.3f",
		.pfValueGet = (_VarXT_PFN_V_)AiValue,
		.vt = V_FP,
	},
	{
		.name = "Load Cell - UI",
		.units = "V",
		.pFmt = "%.2f",
		.pfValueGet = (_VarXT_PFN_V_)AiValue,
		.vt = V_FP,
	},
	{
		.name = "Load Cell - Temp",
		.units = SYMBOL_EXT_DEGREE_SIGN"C",
		.pFmt = "%.2f",
		.pfValueGet = (_VarXT_PFN_V_)AiValue,
		.vt = V_FP,
	},
};
#define NB_DISP_DSCS_AI NB_ARRAY_ITEMS(val_ai_dscs)

static const val_dsc_t val_do_dscs[] = {
	{
		.name = "Solenoid Valve",
		.value = "",
		.pFmt = "%.3s",
		.pfValueGet = (_VarXT_PFN_V_)DoState,
		.vt = V_CSTRING,
	},
	{
		.name = "Motor On",
		.value = "",
		.pFmt = "%.3s",
		.pfValueGet = (_VarXT_PFN_V_)DoState,
		.vt = V_CSTRING,
	},
	{
		.name = "Buzzer",
		.value = "",
		.pFmt = "%.3s",
		.pfValueGet = (_VarXT_PFN_V_)DoState,
		.vt = V_CSTRING,
	},
};
#define NB_DISP_DSCS_DO NB_ARRAY_ITEMS(val_do_dscs)

static const val_dsc_t val_ao_dscs[] = {
	{
		.name = "VOS DAC O/P",
		.units = "V",
		.pFmt = "%.3f",
		.pfValueGet = (_VarXT_PFN_V_)AoValue,
		.vt = V_FP,
	},
	{
		.name = "VOS Sensors",
		.units = "V",
		.pFmt = "%.2f",
		.pfValueGet = (_VarXT_PFN_V_)AoValue,
		.vt = V_FP,
	},
	{
		.name = "Control Out",
		.units = "V",
		.pFmt = "%.2f",
		.pfValueGet = (_VarXT_PFN_V_)AoValue,
		.vt = V_FP,
	},
	{
		.name = "Control Out",
		.units = "mA",
		.pFmt = "%.2f",
		.pfValueGet = (_VarXT_PFN_V_)AoValue,
		.vt = V_FP,
	},
};
#define NB_DISP_DSCS_AO NB_ARRAY_ITEMS(val_ao_dscs)

static const val_dsc_t val_si_dscs[] = {
	{
		.name = "Uptime",
		.value = "",
		.pFmt = "%s",
		.pfValueGet = (_VarXT_PFN_V_)TimeOpen,
		.vt = V_CSTRING,
	},
	{
		.name = "Date & Time",
		.value = "",
		.pFmt = "%s",
		.pfValueGet = (_VarXT_PFN_V_)DateTime,
		.vt = V_CSTRING,
	},
	{
		.name = "Board - Temp",
		.units = SYMBOL_EXT_DEGREE_SIGN"C",
		.pFmt = "%.2f",
		.pfValueGet = (_VarXT_PFN_V_)AiValue,
		.vt = V_FP,
	},
};
#define NB_DISP_DSCS_SI NB_ARRAY_ITEMS(val_si_dscs)

#define NB_DISP_DSCS (NB_DISP_DSCS_DI+NB_DISP_DSCS_AI+NB_DISP_DSCS_DO+NB_DISP_DSCS_AO+NB_DISP_DSCS_SI)

static const product_dsc_t product = {
	.crc32 = 0x12345678,
	.compileDate = __DATE__,
	.name = "LittlevGL Simulator",
	.application = "TFT Simulator",
};

/**********************
 *      TYPEDEFS
 **********************/
typedef struct {
	lv_obj_t* parent;
	lv_style_t st_row0;
	lv_style_t st_rows;
	union {
		struct {
			disp_val_obj_t dvo_di[NB_DISP_DSCS_DI];
			disp_val_obj_t dvo_ai[NB_DISP_DSCS_AI];
			disp_val_obj_t dvo_do[NB_DISP_DSCS_DO];
			disp_val_obj_t dvo_ao[NB_DISP_DSCS_AO];
			disp_val_obj_t dvo_si[NB_DISP_DSCS_SI];
		};
		disp_val_obj_t disp_val_objs[NB_DISP_DSCS];
	};
	struct timespec ts;
	time_t time_start;
	char time_act_buf[32];
} mem_t;

/**********************
 *      MACROS
 **********************/
#define MEM_INIT(to,from)	mem_t*(to) = (from)

 /**********************
  *  GLOBAL DESCRIPTORS
  **********************/

const sndbx_pge_dsc_t sndbx_pge_table_dsc = {
	.name = PAGE_NAME,
	.mem_size = sizeof(mem_t),
	.create_cb = create_cb,
	.task_cb = task_cb,
	.destroy_cb = destroy_cb,
	.task_prio = TASK_PRIO,
	.task_period = TASK_PERIOD,
};

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

/**
 * Create a sandbox test application
 */
void sndbx_pge_table_test( void )
{
	static const sndbx_pge_t page = {
		.dsc = &sndbx_pge_table_dsc,
	};

	sndbx_app_create( &page );
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

static void table_set(const val_dsc_t* vd, disp_val_obj_t* dvo, lv_obj_t* table, int8_t nb)
{
	int i;
	for( i = 0; i < nb; ++i, ++vd, ++dvo )
	{
		dvo->val_dsc = vd;
		dvo->table = table;
		dvo->row = i + 1;
		gui_table_nsvu_set_row(dvo->table, dvo->row, dvo->val_dsc->name, ":", dvo->val_dsc->value, dvo->val_dsc->units);
		gui_table_nsvu_set_row_align(dvo->table, dvo->row, LV_LABEL_ALIGN_RIGHT, LV_LABEL_ALIGN_CENTER, LV_LABEL_ALIGN_LEFT, LV_LABEL_ALIGN_CENTER);
		if (!dvo->val_dsc->pfValueGet)
			dvo->value.pcc = dvo->val_dsc->value;
		else if(dvo->val_dsc->vt == V_CSTRING)
			dvo->value.pcc = dvo->val_dsc->value;
		else
			dvo->value.u64 = -1;
	}
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

	lv_style_t * pst;
    lv_theme_t * th = lv_theme_get_current();
    if(th)
        pst = th->style.cont;
    else
        pst = &lv_style_pretty_color;

	lv_style_copy(&mem->st_row0, &lv_style_transp_tight);
	mem->st_row0.text.font = &font_roboto_22;
	mem->st_row0.text.color = pst->text.color;
	lv_style_copy(&mem->st_rows, &lv_style_transp_tight);
	mem->st_rows.text.color = pst->text.color;
	lv_style_t* bg = &lv_style_transp_tight,
		* c1 = &mem->st_rows,
		* c2 = &mem->st_row0;

	gui_table_nsvu_row_t heading = {
		.name = "Digital Inputs",
		.value = "Value",
		.units = "Units",
	};
	lv_obj_t* table1 = gui_table_nsvu_create(parent, &heading, NB_DISP_DSCS_DI+1);
	lv_table_set_cell_align(table1, 0, 3, LV_LABEL_ALIGN_CENTER);
	gui_table_set_cell_styles(table1, bg, c1, c2, NULL, NULL);
	gui_table_nsvu_set_row_types(table1,0,2,0,2,2);

	table_set(&val_di_dscs[0], &mem->dvo_di[0], table1, NB_DISP_DSCS_DI);

	gui_table_nsvu_set_col_widths(table1, LV_DPI*5/4, LV_DPI*1/6, LV_DPI*5/8, LV_DPI*1/2);
	lv_obj_align(table1, NULL, LV_ALIGN_IN_TOP_LEFT, LV_DPI/12, LV_DPI/12);

	heading.name = "Analogue Inputs";
	lv_obj_t* table2 = gui_table_nsvu_create(parent, &heading, NB_DISP_DSCS_AI+1);
	lv_table_set_cell_align(table2, 0, 3, LV_LABEL_ALIGN_CENTER);
	gui_table_set_cell_styles(table2, bg, c1, c2, NULL, NULL);
	gui_table_nsvu_set_row_types(table2,0,2,0,2,2);

	table_set(&val_ai_dscs[0], &mem->dvo_ai[0], table2, NB_DISP_DSCS_AI);

	gui_table_nsvu_set_col_widths(table2, LV_DPI*5/4, LV_DPI*1/6, LV_DPI*5/8, LV_DPI*1/2);
	lv_coord_t w_t2 = lv_obj_get_width(table2);

	lv_obj_align(table2, NULL, LV_ALIGN_IN_TOP_MID, w_t2/2+LV_DPI/12, LV_DPI/12);

	int i;

	heading.name = "Digital Outputs";
	heading.value = NULL;
	heading.units = NULL;
	lv_obj_t* table3 = gui_table_nsvu_create(parent, &heading, NB_DISP_DSCS_DO+1);
	for( i=0; i<NB_DISP_DSCS_DO; ++i )
		lv_table_set_cell_merge_right(table3, 0, i, true);
	gui_table_set_cell_styles(table3, bg, c1, c2, NULL, NULL);
	gui_table_nsvu_set_row_types(table3, 0, 2, 0, 2, 2);

	table_set(&val_do_dscs[0], &mem->dvo_do[0], table3, NB_DISP_DSCS_DO);

	gui_table_nsvu_set_col_widths(table3, LV_DPI*5/4, LV_DPI*1/6, LV_DPI*5/8, LV_DPI*1/2);

	lv_obj_align(table3, table1, LV_ALIGN_OUT_BOTTOM_LEFT, 0, LV_DPI/12);

	heading.name = "Analogue Derived O/P's";
	lv_obj_t* table4 = gui_table_nsvu_create(parent, &heading, NB_DISP_DSCS_AO+1);
	for( i=0; i<NB_DISP_DSCS_AO; ++i )
		lv_table_set_cell_merge_right(table4, 0, i, true);
	gui_table_set_cell_styles(table4, bg, c1, c2, NULL, NULL);
	gui_table_nsvu_set_row_types(table4, 0, 2, 0, 2, 2);

	table_set(&val_ao_dscs[0], &mem->dvo_ao[0], table4, NB_DISP_DSCS_AO);

	gui_table_nsvu_set_col_widths(table4, LV_DPI*5/4, LV_DPI*1/6, LV_DPI*5/8, LV_DPI*1/2);

	lv_obj_align(table4, table2, LV_ALIGN_OUT_BOTTOM_LEFT, 0, LV_DPI/12);

	heading.name = "Version Information";
	lv_obj_t* table5 = gui_table_nsv_create(parent, (gui_table_nsv_row_t*)&heading, 5);
	for(i = 0; i < 3; ++i)
		lv_table_set_cell_merge_right(table5, 0, i, true);
	gui_table_set_cell_styles(table5, bg, c1, c2, NULL, NULL);
	gui_table_nsv_set_row_types(table5, 0, 2, 0, 2);

	gui_table_nsv_set_row_align(table5, 0, LV_LABEL_ALIGN_LEFT, LV_LABEL_ALIGN_LEFT, LV_LABEL_ALIGN_LEFT);

	gui_table_nsv_set_row(table5, 1, "Product", ":", product.name );
	gui_table_nsv_set_row_align(table5, 1, LV_LABEL_ALIGN_RIGHT, LV_LABEL_ALIGN_CENTER, LV_LABEL_ALIGN_LEFT);
	gui_table_nsv_set_row(table5, 2, "Application", ":", product.application);
	gui_table_nsv_set_row_align(table5, 2, LV_LABEL_ALIGN_RIGHT, LV_LABEL_ALIGN_CENTER, LV_LABEL_ALIGN_LEFT);
	char crc[12];
	snprintf( crc, sizeof(crc), "0x%.8x", product.crc32 );
	gui_table_nsv_set_row(table5, 3, "CRC", ":", crc);
	gui_table_nsv_set_row_align(table5, 3, LV_LABEL_ALIGN_RIGHT, LV_LABEL_ALIGN_CENTER, LV_LABEL_ALIGN_LEFT);
	gui_table_nsv_set_row(table5, 4, "Compiled", ":", product.compileDate);
	gui_table_nsv_set_row_align(table5, 4, LV_LABEL_ALIGN_RIGHT, LV_LABEL_ALIGN_CENTER, LV_LABEL_ALIGN_LEFT);

	gui_table_nsv_set_col_widths(table5, LV_DPI*3/4, LV_DPI*1/6, LV_DPI*10/8);

	lv_obj_align(table5, table3, LV_ALIGN_OUT_BOTTOM_LEFT, 0, LV_DPI/12);

	heading.name = "System Information";
	lv_obj_t* table6 = gui_table_nsvu_create(parent, &heading, NB_DISP_DSCS_SI+1);
	for(i = 0; i < NB_DISP_DSCS_SI; ++i)
		lv_table_set_cell_merge_right(table6, 0, i, true);
	for(i = 2; i < NB_DISP_DSCS_SI; ++i)
		lv_table_set_cell_merge_right(table6, 2, i, true);
	gui_table_set_cell_styles(table6, bg, c1, c2, NULL, NULL);
	gui_table_nsvu_set_row_types(table6, 0, 2, 0, 2, 2);

	table_set(&val_si_dscs[0], &mem->dvo_si[0], table6, NB_DISP_DSCS_SI);

	gui_table_nsvu_set_col_widths(table6, LV_DPI*8/10, LV_DPI*1/6, LV_DPI*1/1, LV_DPI*1/2);

	lv_obj_align(table6, table4, LV_ALIGN_OUT_BOTTOM_LEFT, 0, LV_DPI/12);

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

    (V)timespec_get(&mem->ts, TIME_UTC);

	mem->time_start = time(NULL);
	task_cb(p_mem);
}

/**
 * Called periodically, specified by sndbx_pge_dsc_t
 * @param p_mem memory pointer, points to memory allocated by the sandbox
 */
static void task_cb( void * p_mem )
{
	MEM_INIT( mem, p_mem );

	Var64 val;
	disp_val_obj_t* dvo = &mem->disp_val_objs[0];
	char txt[32];
	int i;
	for (i = 0; i < NB_DISP_DSCS; ++i, ++dvo)
	{
		val.u64 = 0;
		Var_AssignVarFrFun(&val, dvo->val_dsc->pfValueGet, dvo->val_dsc->vt );
		if( dvo->val_dsc->vt == V_CSTRING  )
			dvo->value.pcc = gui_table_nsvu_get_value(dvo->table, dvo->row);
		if( Var_VarCmp(&val, &dvo->value, dvo->val_dsc->vt) )
		{
			txt[0] = '\0';
			Var_AssignVar(&dvo->value, &val, dvo->val_dsc->vt);
			Var_VarToStrn(txt, dvo->val_dsc->pFmt, &dvo->value, sizeof(txt), dvo->val_dsc->vt);
			gui_table_nsvu_set_value(dvo->table, dvo->row, txt);
		}
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
	/* ... by the sandbox handler */
}

/*===================== Callbacks and Events================== */


/*===================== Other functions ====================== */

static PCC DiState(V)
{
	return rand()&1 ? "Active" : "Inactive";
}

static FP AiValue(V)
{
	FP val = FpRandomMinMax((FP)1, (FP)1999);

	return FpRound(val)/(FP)1000;
}

static PCC DoState(V)
{
	return rand()&1 ? "On" : "Off";
}

static FP AoValue(V)
{
	FP val = FpRandomMinMax((FP)1, (FP)1999);

	return FpRound(val)/(FP)1000;
}

const char *TimeOpen(V)
{
	void * p_mem = sndbx_pge_get_mem();
	MEM_INIT( mem, p_mem );

	struct timespec ts;
	(V)timespec_get(&ts, TIME_UTC);

	U32 act_time = (U32)(ts.tv_sec - mem->ts.tv_sec);
	U32 act_ms;
	if( ts.tv_nsec >= mem->ts.tv_nsec)
		act_ms = (U32)(ts.tv_nsec - mem->ts.tv_nsec)/1000000u;
	else
	{
		act_ms = (U32)(mem->ts.tv_nsec - ts.tv_nsec)/1000000u;
		--act_time;
	}
//	U32 act_time = clock()/CLOCKS_PER_SEC;
	snprintf(mem->time_act_buf, sizeof(mem->time_act_buf), 
		"%u:%.2u:%.2u:%.2u.%.3u"
		,act_time/86400
		,(act_time%86400)/3600
		,(act_time%3600)/60
		,act_time%60
		,act_ms
	);
	return mem->time_act_buf;
}

static const char *DateTime(V)
{
	time_t _time = time(NULL);
	char * ret;
#if 0
	struct tm * _tm;
	_tm = localtime(&_time);
	ret = asctime(_tm);
#else
	ret = ctime(&_time);
#endif 
	if(ret)
	{
		char *nl = strchr(ret, '\n');
		if(nl)
			*nl = '\0';
	}

	return ret;
}

#endif  /*USE_SNDBX_PGE_TABLE*/
