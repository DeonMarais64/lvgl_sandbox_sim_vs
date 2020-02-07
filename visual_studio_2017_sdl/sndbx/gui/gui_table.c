/**
 * @file gui_table.c
 *
 */

/*********************
 *      INCLUDES
 *********************/

#include "gui_table.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

typedef struct {
	const char* name;
	const char* units;
} gui_table_nvu_t;

typedef struct {
	const char* name;
} gui_table_nv_t;

/**********************
 *  STATIC PROTOTYPES
 **********************/

/**********************
 *  STATIC VARIABLES
 **********************/

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

void gui_table_set_cell_styles(lv_obj_t* table, const lv_style_t* bg, const lv_style_t* c1, const lv_style_t* c2, const lv_style_t* c3, const lv_style_t* c4)
{
	if(bg)
		lv_table_set_style(table, LV_TABLE_STYLE_BG, bg);
	if(c1)
		lv_table_set_style(table, LV_TABLE_STYLE_CELL1, c1);
	if(c2)
		lv_table_set_style(table, LV_TABLE_STYLE_CELL2, c2);
	if(c3)
		lv_table_set_style(table, LV_TABLE_STYLE_CELL3, c3);
	if(c4)
		lv_table_set_style(table, LV_TABLE_STYLE_CELL4, c4);
}

lv_obj_t* gui_table_nsvu_create(lv_obj_t* parent, const gui_table_nsvu_row_t* prms, uint8_t rows)
{
	lv_obj_t * table = lv_table_create(parent, NULL);
	lv_table_set_col_cnt(table, 4);
	lv_table_set_row_cnt(table, rows );

	if( prms )
	{
		if(prms->name)
			gui_table_nsvu_set_name(table, 0, prms->name);
		if(prms->separator)
			gui_table_nsvu_set_separator(table, 0, prms->separator);
		if(prms->value)
			gui_table_nsvu_set_value(table, 0, prms->value);
		if(prms->units)
			gui_table_nsvu_set_units(table, 0, prms->units);
	}
	return table;
}

lv_obj_t* gui_table_nsv_create(lv_obj_t* parent, const gui_table_nsv_row_t* prms, uint8_t rows)
{
	lv_obj_t* table = lv_table_create(parent, NULL);
	lv_table_set_col_cnt(table, 3);
	lv_table_set_row_cnt(table, rows);

	if (prms)
	{
		if (prms->name)
			gui_table_nsv_set_name(table, 0, prms->name);
		if (prms->separator)
			gui_table_nsv_set_separator(table, 0, prms->separator);
		if (prms->value)
			gui_table_nsv_set_value(table, 0, prms->value);
	}
	return table;
}

void gui_table_nsvu_set_row(lv_obj_t* table, uint8_t row, const char* n, const char* s, const char* v, const char* u)
{
	if (n)
		gui_table_nsvu_set_name(table, row, n);
	if (s)
		gui_table_nsvu_set_separator(table, row, s);
	if (v)
		gui_table_nsvu_set_value(table, row, v);
	if (u)
		gui_table_nsvu_set_units(table, row, u);
}

void gui_table_nsvu_set_col_widths(lv_obj_t* table, lv_coord_t n, lv_coord_t s, lv_coord_t v, lv_coord_t u)
{
	lv_table_set_col_width(table, 0, n);
	lv_table_set_col_width(table, 1, s);
	lv_table_set_col_width(table, 2, v);
	lv_table_set_col_width(table, 3, u);
}

void gui_table_nsv_set_col_widths(lv_obj_t* table, lv_coord_t n, lv_coord_t s, lv_coord_t v)
{
	lv_table_set_col_width(table, 0, n);
	lv_table_set_col_width(table, 1, s);
	lv_table_set_col_width(table, 2, v);
}

void gui_table_nsvu_set_row_types(lv_obj_t* table, uint8_t row, lv_table_style_t n, lv_table_style_t s, lv_table_style_t v, lv_table_style_t u)
{
	if(n != LV_TABLE_STYLE_BG)
		lv_table_set_cell_type(table, row, 0, n);
	if( s != LV_TABLE_STYLE_BG )
		lv_table_set_cell_type(table, row, 1, s);
	if(v != LV_TABLE_STYLE_BG)
		lv_table_set_cell_type(table, row, 2, v);
	if(u != LV_TABLE_STYLE_BG)
		lv_table_set_cell_type(table, row, 3, u);
}

void gui_table_nsvu_set_row_align(lv_obj_t* table, uint8_t row, lv_label_align_t n, lv_label_align_t s, lv_label_align_t v, lv_label_align_t u)
{
	lv_table_set_cell_align(table, row, 0, n);
	lv_table_set_cell_align(table, row, 1, s);
	lv_table_set_cell_align(table, row, 2, v);
	lv_table_set_cell_align(table, row, 3, u);
}

void gui_table_nsv_set_row_align(lv_obj_t* table, uint8_t row, lv_label_align_t n, lv_label_align_t s, lv_label_align_t v)
{
	lv_table_set_cell_align(table, row, 0, n);
	lv_table_set_cell_align(table, row, 1, s);
	lv_table_set_cell_align(table, row, 2, v);
}

void gui_table_nsvu_set_name(lv_obj_t* table, uint8_t row, const char* name)
{
	lv_table_set_cell_value(table, row, 0, name );
}
void gui_table_nsvu_set_separator(lv_obj_t* table, uint8_t row, const char* sep)
{
	lv_table_set_cell_value(table, row, 1, sep);
}
void gui_table_nsvu_set_value(lv_obj_t* table, uint8_t row, const char* value)
{
	lv_table_set_cell_value(table, row, 2, value);
}
void gui_table_nsvu_set_units(lv_obj_t* table, uint8_t row, const char* units)
{
	lv_table_set_cell_value(table, row, 3, units);
}
const char * gui_table_nsvu_get_value(lv_obj_t* table, uint8_t row )
{
	return lv_table_get_cell_value(table,row,2);
}


/**********************
 *   STATIC FUNCTIONS
 **********************/

