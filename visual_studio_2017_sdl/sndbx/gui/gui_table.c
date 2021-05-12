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

void gui_table_set_cell_styles(lv_obj_t* table, lv_style_t* bg, lv_style_t* c1, lv_style_t* c2, lv_style_t* c3, lv_style_t* c4)
{
#if 1
	if( bg )
		lv_obj_add_style(table, LV_TABLE_PART_BG, bg);
	if( c1 )
		lv_obj_add_style(table, LV_TABLE_PART_CELL1, c1);
	if( c2 )
		lv_obj_add_style(table, LV_TABLE_PART_CELL2, c2);
	if( c3 )
		lv_obj_add_style(table, LV_TABLE_PART_CELL3, c3);
	if( c4 )
		lv_obj_add_style(table, LV_TABLE_PART_CELL4, c4);
#endif
}

lv_obj_t* gui_table_nsvu_create(lv_obj_t* parent, const gui_table_nsvu_row_t* prms, uint8_t rows)
{
	lv_obj_t * table = lv_table_create(parent, NULL);
	lv_obj_reset_style_list(table, LV_TABLE_PART_BG);
	lv_obj_reset_style_list(table, LV_TABLE_PART_CELL1);
	lv_obj_reset_style_list(table, LV_TABLE_PART_CELL2);
	lv_obj_reset_style_list(table, LV_TABLE_PART_CELL3);
	lv_obj_reset_style_list(table, LV_TABLE_PART_CELL4);
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
	lv_obj_reset_style_list(table, LV_TABLE_PART_BG);
	lv_obj_reset_style_list(table, LV_TABLE_PART_CELL1);
	lv_obj_reset_style_list(table, LV_TABLE_PART_CELL2);
	lv_obj_reset_style_list(table, LV_TABLE_PART_CELL3);
	lv_obj_reset_style_list(table, LV_TABLE_PART_CELL4);
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

#if 1
void gui_table_nsvu_set_row_types(lv_obj_t* table, uint8_t row, uint8_t n, uint8_t s, uint8_t v, uint8_t u)
{
	if( n != LV_TABLE_PART_BG )
		lv_table_set_cell_type(table, row, 0, n);
	if( s != LV_TABLE_PART_BG )
		lv_table_set_cell_type(table, row, 1, s);
	if( v != LV_TABLE_PART_BG )
		lv_table_set_cell_type(table, row, 2, v);
	if( u != LV_TABLE_PART_BG )
		lv_table_set_cell_type(table, row, 3, u);
}
#endif

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

lv_obj_t* gui_table_create(lv_obj_t* parent, uint8_t rows, uint8_t cols)
{
	lv_obj_t * table = lv_table_create(parent, NULL);
	lv_obj_reset_style_list(table, LV_TABLE_PART_BG);
	lv_obj_reset_style_list(table, LV_TABLE_PART_CELL1);
	lv_obj_reset_style_list(table, LV_TABLE_PART_CELL2);
	lv_obj_reset_style_list(table, LV_TABLE_PART_CELL3);
	lv_obj_reset_style_list(table, LV_TABLE_PART_CELL4);
	lv_table_set_col_cnt(table, cols);	/*Always set Column count, before setting Row count */
	lv_table_set_row_cnt(table, rows);

	return table;
}

void gui_table_set_col_type( lv_obj_t* table, uint16_t col, uint8_t type )
{
	if( type == LV_TABLE_PART_BG )
		return;
	uint16_t rows = lv_table_get_col_cnt( table );
	for( int i = 0; i < rows; ++i )
		lv_table_set_cell_type( table, i, col, type );
}

void gui_table_c5_set_row(lv_obj_t* table, uint8_t row, const char* c0, const char* c1, const char* c2, const char* c3, const char* c4)
{
	if( c0 )
		lv_table_set_cell_value(table, row, 0, c0);
	if( c1 )
		lv_table_set_cell_value(table, row, 1, c1);
	if( c2 )
		lv_table_set_cell_value(table, row, 2, c2);
	if( c3 )
		lv_table_set_cell_value(table, row, 3, c3);
	if( c4 )
		lv_table_set_cell_value(table, row, 4, c4);
}
void gui_table_c5_set_col_widths(lv_obj_t* table, lv_coord_t wc0, lv_coord_t wc1, lv_coord_t wc2, lv_coord_t wc3, lv_coord_t wc4)
{
	lv_table_set_col_width(table, 0, wc0);
	lv_table_set_col_width(table, 1, wc1);
	lv_table_set_col_width(table, 2, wc2);
	lv_table_set_col_width(table, 3, wc3);
	lv_table_set_col_width(table, 4, wc4);
}
void gui_table_c5_set_row_types(lv_obj_t* table, uint8_t row, uint8_t tc0, uint8_t tc1, uint8_t tc2, uint8_t tc3, uint8_t tc4)
{
	if (tc0 != LV_TABLE_PART_BG)
		lv_table_set_cell_type(table, row, 0, tc0);
	if (tc1 != LV_TABLE_PART_BG)
		lv_table_set_cell_type(table, row, 1, tc1);
	if (tc2 != LV_TABLE_PART_BG)
		lv_table_set_cell_type(table, row, 2, tc2);
	if (tc3 != LV_TABLE_PART_BG)
		lv_table_set_cell_type(table, row, 3, tc3);
	if (tc3 != LV_TABLE_PART_BG)
		lv_table_set_cell_type(table, row, 4, tc4);
}
void gui_table_c5_set_types(lv_obj_t* table, uint8_t rows, uint8_t tc0, uint8_t tc1, uint8_t tc2, uint8_t tc3, uint8_t tc4)
{
	for (int i = 0; i < rows; ++i)
		gui_table_c5_set_row_types(table, i, tc0, tc1, tc2, tc3, tc4);
}
void gui_table_c5_set_row_align(lv_obj_t* table, uint8_t row, lv_label_align_t ac0, lv_label_align_t ac1, lv_label_align_t ac2, lv_label_align_t ac3, lv_label_align_t ac4)
{
	lv_table_set_cell_align(table, row, 0, ac0);
	lv_table_set_cell_align(table, row, 1, ac1);
	lv_table_set_cell_align(table, row, 2, ac2);
	lv_table_set_cell_align(table, row, 3, ac3);
	lv_table_set_cell_align(table, row, 4, ac4);
}
void gui_table_c5_set_aligns(lv_obj_t* table, uint8_t rows, lv_label_align_t ac0, lv_label_align_t ac1, lv_label_align_t ac2, lv_label_align_t ac3, lv_label_align_t ac4)
{
	//uint16_t rows = lv_table_get_row_cnt( table );
	for (int i = 0; i < rows; ++i)
	{
		lv_table_set_cell_align(table, i, 0, ac0);
		lv_table_set_cell_align(table, i, 1, ac1);
		lv_table_set_cell_align(table, i, 2, ac2);
		lv_table_set_cell_align(table, i, 3, ac3);
		lv_table_set_cell_align(table, i, 4, ac4);
	}
}

void gui_table_c4_set_row(lv_obj_t* table, uint8_t row, const char* c0, const char* c1, const char* c2, const char* c3)
{
	if( c0 )
		lv_table_set_cell_value(table, row, 0, c0);
	if( c1 )
		lv_table_set_cell_value(table, row, 1, c1);
	if( c2 )
		lv_table_set_cell_value(table, row, 2, c2);
	if( c3 )
		lv_table_set_cell_value(table, row, 3, c3);
}
void gui_table_c4_set_col_widths(lv_obj_t* table, lv_coord_t wc0, lv_coord_t wc1, lv_coord_t wc2, lv_coord_t wc3)
{
	lv_table_set_col_width(table, 0, wc0);
	lv_table_set_col_width(table, 1, wc1);
	lv_table_set_col_width(table, 2, wc2);
	lv_table_set_col_width(table, 3, wc3);
}
void gui_table_c4_set_row_types(lv_obj_t* table, uint8_t row, uint8_t tc0, uint8_t tc1, uint8_t tc2, uint8_t tc3)
{
	if (tc0 != LV_TABLE_PART_BG)
		lv_table_set_cell_type(table, row, 0, tc0);
	if (tc1 != LV_TABLE_PART_BG)
		lv_table_set_cell_type(table, row, 1, tc1);
	if (tc2 != LV_TABLE_PART_BG)
		lv_table_set_cell_type(table, row, 2, tc2);
	if (tc3 != LV_TABLE_PART_BG)
		lv_table_set_cell_type(table, row, 3, tc3);
}
void gui_table_c4_set_types(lv_obj_t* table, uint8_t rows, uint8_t tc0, uint8_t tc1, uint8_t tc2, uint8_t tc3)
{
	for (int i = 0; i < rows; ++i)
		gui_table_c4_set_row_types(table, i, tc0, tc1, tc2, tc3);
}
void gui_table_c4_set_aligns(lv_obj_t* table, uint8_t rows, lv_label_align_t ac0, lv_label_align_t ac1, lv_label_align_t ac2, lv_label_align_t ac3)
{
	//uint16_t rows = lv_table_get_row_cnt( table );
	for (int i = 0; i < rows; ++i)
	{
		lv_table_set_cell_align(table, i, 0, ac0);
		lv_table_set_cell_align(table, i, 1, ac1);
		lv_table_set_cell_align(table, i, 2, ac2);
		lv_table_set_cell_align(table, i, 3, ac3);
	}
}


void gui_table_c2_row_roll_up(lv_obj_t* table)
{
	uint16_t rows = lv_table_get_row_cnt(table);
	if (rows < 2)
		return;

	const char* c0 = lv_table_get_cell_value(table, 0, 0);
	const char* c1 = lv_table_get_cell_value(table, 0, 1);

	char r0c0[16];
	char r0c1[16];

	strncpy(r0c0, c0, 15), r0c0[15] = '\0';
	strncpy(r0c1, c1, 15), r0c1[15] = '\0';

	for (int i = 0; i < rows - 2; ++i)
	{
		c0 = lv_table_get_cell_value(table, 1 + i, 0);
		lv_table_set_cell_value(table, i, 0, c0);

		c1 = lv_table_get_cell_value(table, 1 + i, 1);
		lv_table_set_cell_value(table, i, 1, c1);
	}

	lv_table_set_cell_value(table, rows - 1, 0, r0c0);
	lv_table_set_cell_value(table, rows - 1, 1, r0c1);
}

void gui_table_c2_row_roll_dn(lv_obj_t* table)
{
	uint16_t rows = lv_table_get_row_cnt(table);
	if (rows < 2)
		return;

	const char* c0 = lv_table_get_cell_value(table, rows - 1, 0);
	const char* c1 = lv_table_get_cell_value(table, rows - 1, 1);

	char rnc0[16];
	char rnc1[16];

	strncpy(rnc0, c0, 15), rnc0[15] = '\0';
	strncpy(rnc1, c1, 15), rnc1[15] = '\0';

	for (int i = rows - 2; i >= 0; --i)
	{
		c0 = lv_table_get_cell_value(table, i, 0);
		lv_table_set_cell_value(table, 1 + i, 0, c0);

		c1 = lv_table_get_cell_value(table, i, 1);
		lv_table_set_cell_value(table, 1 + i, 1, c1);
	}

	lv_table_set_cell_value(table, 0, 0, rnc0);
	lv_table_set_cell_value(table, 0, 1, rnc1);
}

void gui_table_c2_row_roll(lv_obj_t* table, int16_t roll_cnt)
{
	if (!roll_cnt)
		return;

	if (roll_cnt > 0)
	{
		do {
			gui_table_c2_row_roll_up(table);
			--roll_cnt;
		} while (roll_cnt);
	}
	else
	{
		do {
			gui_table_c2_row_roll_dn(table);
			++roll_cnt;
		} while (roll_cnt);
	}
}

void gui_table_c1_row_roll_up(lv_obj_t* table)
{
	uint16_t rows = lv_table_get_row_cnt(table);
	if (rows < 2)
		return;

	const char* c0 = lv_table_get_cell_value(table, 0, 0);

	char r0c0[16];
	strncpy(r0c0, c0, 15); 
	r0c0[15] = '\0';

	for (int i = 0; i < rows - 2; ++i)
	{
		c0 = lv_table_get_cell_value(table, 1 + i, 0);
		lv_table_set_cell_value(table, i, 0, c0);
	}

	lv_table_set_cell_value(table, rows - 1, 0, r0c0);
}

void gui_table_c1_row_roll_dn(lv_obj_t* table)
{
	uint16_t rows = lv_table_get_row_cnt(table);
	if (rows < 2)
		return;

	const char* c0 = lv_table_get_cell_value(table, rows - 1, 0);

	char rnc0[16];
	strncpy(rnc0, c0, 15); 
	rnc0[15] = '\0';

	for (int i = rows - 2; i >= 0; --i)
	{
		c0 = lv_table_get_cell_value(table, i, 0);
		lv_table_set_cell_value(table, 1 + i, 0, c0);
	}

	lv_table_set_cell_value(table, 0, 0, rnc0);
}


void gui_table_c1_row_roll(lv_obj_t* table, int16_t roll_cnt)
{
	if (!roll_cnt)
		return;

	if (roll_cnt > 0)
	{
		do {
			gui_table_c1_row_roll_up(table);
			--roll_cnt;
		} while (roll_cnt);
	}
	else
	{
		do {
			gui_table_c1_row_roll_dn(table);
			++roll_cnt;
		} while (roll_cnt);
	}
}

void gui_table_row_roll_up(lv_obj_t* table, uint16_t col)
{
	uint16_t rows = lv_table_get_row_cnt(table);
	if (rows < 2) return;
	uint16_t cols = lv_table_get_col_cnt(table);
	if (col >= cols) return;

	const char* c = lv_table_get_cell_value(table, 0, col);

	char r0c[16];
	strncpy(r0c, c, 15);
	r0c[15] = '\0';

	char str[16];

	for (int i = 0; i < rows - 1; ++i)
	{
		c = lv_table_get_cell_value(table, 1 + i, col);
		strncpy(str, c, 15);
		str[15] = '\0';
		lv_table_set_cell_value(table, i, col, str);
	}

	lv_table_set_cell_value(table, rows - 1, col, r0c);
}


void gui_table_row_roll_dn(lv_obj_t* table, uint16_t col)
{
	uint16_t rows = lv_table_get_row_cnt(table);
	if (rows < 2) return;
	uint16_t cols = lv_table_get_col_cnt(table);
	if (col >= cols) return;

	const char* c = lv_table_get_cell_value(table, rows - 1, col);

	char rnc[16];
	strncpy(rnc, c, 15);
	rnc[15] = '\0';

	for (int i = rows - 2; i >= 0; --i)
	{
		c = lv_table_get_cell_value(table, i, col);
		lv_table_set_cell_value(table, 1 + i, col, c);
	}

	lv_table_set_cell_value(table, 0, 0, rnc);
}

#include <stdio.h>
static void table_dump(lv_obj_t* table)
{
	uint16_t rows = lv_table_get_row_cnt(table);
	char str[128];
	int len = 0;

	for (int i = 0; i < rows; ++i)
	{
		const char* c0_str = lv_table_get_cell_value(table, i, 0);
		len += sprintf(&str[len], !len ? "%s" : ",%s", c0_str);
	}
	LV_LOG_INFO(str);
}

void gui_table_row_roll(lv_obj_t* table, int16_t col, int16_t roll_cnt)
{
	if (!roll_cnt)
		return;

	if (roll_cnt > 0)
	{
		do {
			gui_table_row_roll_up(table, col);
			table_dump(table);
			--roll_cnt;
		} while (roll_cnt);
	}
	else
	{
		do {
			gui_table_row_roll_dn(table, col);
			table_dump(table);
			++roll_cnt;
		} while (roll_cnt);
	}
}


/**********************
 *   STATIC FUNCTIONS
 **********************/

