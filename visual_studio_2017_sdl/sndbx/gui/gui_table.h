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
} gui_table_nsvu_row_t;

typedef struct {
	const char* name;
	const char* separator;
	const char* value;
} gui_table_nsv_row_t;

/**********************
 * GLOBAL PROTOTYPES
 **********************/
extern void gui_table_set_cell_styles(lv_obj_t* table, lv_style_t* bg, lv_style_t* c1, lv_style_t* c2, lv_style_t* c3, lv_style_t* c4);

extern lv_obj_t* gui_table_nsvu_create(lv_obj_t* parent, const gui_table_nsvu_row_t * prms, uint8_t rows );
extern void gui_table_nsvu_set_row(lv_obj_t* table, uint8_t row, const char * n, const char* s, const char* v, const char* u );
extern void gui_table_nsvu_set_col_widths(lv_obj_t* table, lv_coord_t n, lv_coord_t s, lv_coord_t v, lv_coord_t u);
extern void gui_table_nsvu_set_row_types(lv_obj_t* table, uint8_t row, uint8_t n, uint8_t  s, uint8_t v, uint8_t  u );
extern void gui_table_nsvu_set_row_align(lv_obj_t* table, uint8_t row, lv_label_align_t n, lv_label_align_t s, lv_label_align_t v, lv_label_align_t u);
extern void gui_table_nsvu_set_name(lv_obj_t* table, uint8_t row, const char* name);
extern void gui_table_nsvu_set_separator(lv_obj_t* table, uint8_t row, const char* sep);
extern void gui_table_nsvu_set_value(lv_obj_t* table, uint8_t row, const char* value);
extern void gui_table_nsvu_set_units(lv_obj_t* table, uint8_t row, const char * units);
extern const char * gui_table_nsvu_get_value(lv_obj_t* table, uint8_t row );

extern lv_obj_t* gui_table_nsv_create(lv_obj_t* parent, const gui_table_nsv_row_t* prms, uint8_t rows);
extern void gui_table_nsv_set_col_widths(lv_obj_t* table, lv_coord_t n, lv_coord_t s, lv_coord_t v);
extern void gui_table_nsv_set_row_align(lv_obj_t* table, uint8_t row, lv_label_align_t n, lv_label_align_t s, lv_label_align_t v);


void gui_table_c2_row_roll(lv_obj_t* table, int16_t roll_cnt);
void gui_table_c1_row_roll(lv_obj_t* table, int16_t roll_cnt);

/**********************
 *      MACROS
 **********************/

#define gui_table_nsv_set_row(t,r,n,s,v)	gui_table_nsvu_set_row(t,r,n,s,v,NULL)
#define gui_table_nsv_set_row(t,r,n,s,v)	gui_table_nsvu_set_row(t,r,n,s,v,NULL)
#define gui_table_nsv_set_row_types(t,r,n,s,v)	gui_table_nsvu_set_row_types(t,r,n,s,v,LV_TABLE_PART_BG)

#define gui_table_nsv_set_name				gui_table_nsvu_set_name
#define gui_table_nsv_set_separator			gui_table_nsvu_set_separator
#define gui_table_nsv_set_value				gui_table_nsvu_set_value


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*GUI_TABLE_H*/
