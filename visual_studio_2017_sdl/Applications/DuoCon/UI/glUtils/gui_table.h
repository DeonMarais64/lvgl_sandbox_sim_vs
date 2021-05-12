/**
 * @file gui_table.h
 *
 */
#ifndef GUI_TABLE_H
#define GUI_TABLE_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#if 0 && defined LV_CONF_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif


/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

typedef struct {
	const char* name;
	const char* separator;
	const char* value;
	const char* units;
} gui_table_c4_row_t;

typedef struct {
	const char* name;
	const char* separator;
	const char* value;
} gui_table_c3_row_t;

typedef struct {
	const char* name;
	const char* value;
	const char* units;
} gui_table_nvu_row_t;

/**********************
 * GLOBAL PROTOTYPES
 **********************/

extern lv_obj_t* gui_table_create(lv_obj_t* parent, uint8_t rows, uint8_t cols);

extern void gui_table_set_col_type(lv_obj_t* table, uint16_t col, uint8_t type );

extern void gui_table_set_cell_styles(lv_obj_t* table, lv_style_t* bg, lv_style_t* st1, lv_style_t* st2, lv_style_t* st3, lv_style_t* st4);

extern lv_obj_t* gui_table_nsvu_create(lv_obj_t* parent, const gui_table_c4_row_t * prms, uint8_t rows );

extern void gui_table_c5_set_row(lv_obj_t* table, uint8_t row, const char * c0, const char* c1, const char* c2, const char* c3, const char* c4);
extern void gui_table_c5_set_col_widths(lv_obj_t* table, lv_coord_t c0, lv_coord_t c1, lv_coord_t c2, lv_coord_t c3, lv_coord_t c4);
extern void gui_table_c5_set_row_types(lv_obj_t* table, uint8_t row, uint8_t tc0, uint8_t  tc1, uint8_t tc2, uint8_t tc3, uint8_t tc4);
extern void gui_table_c5_set_row_align(lv_obj_t* table, uint8_t row, lv_label_align_t ac0, lv_label_align_t ac1, lv_label_align_t ac2, lv_label_align_t ac3, lv_label_align_t ac4);
extern void gui_table_c5_set_types(lv_obj_t* table, uint8_t rows, uint8_t tc0, uint8_t tc1, uint8_t tc2, uint8_t tc3, uint8_t tc4);
extern void gui_table_c5_set_aligns(lv_obj_t* table, uint8_t rows, lv_label_align_t ac0, lv_label_align_t ac1, lv_label_align_t ac2, lv_label_align_t ac3, lv_label_align_t ac4);

extern void gui_table_c4_set_row(lv_obj_t* table, uint8_t row, const char * c0, const char* c1, const char* c2, const char* c3);
extern void gui_table_c4_set_col_widths(lv_obj_t* table, lv_coord_t c0, lv_coord_t c1, lv_coord_t c2, lv_coord_t c3);
extern void gui_table_c4_set_row_types(lv_obj_t* table, uint8_t row, uint8_t tc0, uint8_t  tc1, uint8_t tc2, uint8_t  tc3);
extern void gui_table_c4_set_row_align(lv_obj_t* table, uint8_t row, lv_label_align_t ac0, lv_label_align_t ac1, lv_label_align_t ac2, lv_label_align_t ac3);
extern void gui_table_c4_set_types(lv_obj_t* table, uint8_t rows, uint8_t tc0, uint8_t tc1, uint8_t tc2, uint8_t tc3);
extern void gui_table_c4_set_aligns(lv_obj_t* table, uint8_t rows, lv_label_align_t ac0, lv_label_align_t ac1, lv_label_align_t ac2, lv_label_align_t ac3);

extern void gui_table_c3_set_row(lv_obj_t* table, uint8_t row, const char* c0, const char* c1, const char* c2);
extern void gui_table_c3_set_row_types(lv_obj_t* table, uint8_t row, uint8_t tc0, uint8_t tc1, uint8_t tc2);
extern void gui_table_c3_set_types(lv_obj_t* table, uint8_t rows, uint8_t c0, uint8_t c1, uint8_t c2);
extern void gui_table_c3_set_aligns(lv_obj_t* table, uint8_t rows, lv_label_align_t ac0, lv_label_align_t ac1, lv_label_align_t ac2);
extern void gui_table_c2_set_aligns(lv_obj_t* table, uint8_t rows, lv_label_align_t ac0, lv_label_align_t ac1 );

extern void gui_table_c2_set_rows(lv_obj_t* table, const char* c0, const char* c1);
extern void gui_table_c3_set_rows(lv_obj_t* table, const char* c0, const char* c1, const char* c2);

extern void gui_table_c2_row_swap( lv_obj_t * table, uint16_t a, uint16_t b );
extern void gui_table_row_swap( lv_obj_t * table, uint16_t r1, uint16_t r2 );


extern void gui_table_c2_row_roll( lv_obj_t * table, int16_t roll_cnt );

extern void gui_table_roll( lv_obj_t * table, int roll_cnt );

extern void gui_table_c0_set_value(lv_obj_t* table, uint8_t row, const char* name);
extern void gui_table_c1_set_value(lv_obj_t* table, uint8_t row, const char* sep);
extern void gui_table_c2_set_value(lv_obj_t* table, uint8_t row, const char* value);
extern void gui_table_c3_set_value(lv_obj_t* table, uint8_t row, const char* units);

extern const char * gui_table_c0_get_value(lv_obj_t* table, uint8_t row);
extern const char * gui_table_c1_get_value(lv_obj_t* table, uint8_t row);
extern const char * gui_table_c2_get_value(lv_obj_t* table, uint8_t row);
extern const char * gui_table_c3_get_value(lv_obj_t* table, uint8_t row);

extern lv_obj_t* gui_table_nsv_create(lv_obj_t* parent, const gui_table_c3_row_t* prms, uint8_t rows);

extern void gui_table_c3_set_col_widths(lv_obj_t* table, lv_coord_t n, lv_coord_t s, lv_coord_t v);
extern void gui_table_c3_set_row_align(lv_obj_t* table, uint8_t row, lv_label_align_t ac0, lv_label_align_t ac1, lv_label_align_t ac2);

/**********************
 *      MACROS
 **********************/

#define gui_table_nsv_set_row(t,r,n,s,v)	gui_table_c4_set_row(t,r,n,s,v,NULL)
#define gui_table_nsv_set_row_types(t,r,n,s,v)	gui_table_c4_set_row_types(t,r,n,s,v,LV_TABLE_PART_BG)
#define gui_table_nsv_set_row_align			gui_table_c3_set_row_align

#define gui_table_nsv_set_name				gui_table_c0_set_value
#define gui_table_nsv_set_separator			gui_table_c1_set_value
#define gui_table_nsv_set_value				gui_table_c2_set_value
#define gui_table_nsv_get_name				gui_table_c0_get_value
#define gui_table_nsv_get_value				gui_table_c2_get_value
#define gui_table_nsv_get_units				gui_table_c3_get_value


#define gui_table_nvu_create(p,prms, rows)	gui_table_nsv_create(p,(const gui_table_c3_row_t*)prms,rows)
#define gui_table_nvu_set_row				gui_table_nsv_set_row
#define gui_table_nvu_set_row_types			gui_table_nsv_set_row_types
//#define gui_table_nvu_set_col_widths		gui_table_c3_set_col_widths
#define gui_table_nvu_set_row_align			gui_table_nsv_set_row_align
#define gui_table_nvu_set_name				gui_table_nsv_set_name
#define gui_table_nvu_set_value				gui_table_nsv_set_separator
#define gui_table_nvu_set_units				gui_table_nsv_set_value
#define gui_table_nvu_get_name				gui_table_nsvu_get_name
#define gui_table_nvu_get_value				gui_table_nsvu_get_separator
#define gui_table_nvu_get_units				gui_table_nsvu_get_value

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*GUI_TABLE_H*/
