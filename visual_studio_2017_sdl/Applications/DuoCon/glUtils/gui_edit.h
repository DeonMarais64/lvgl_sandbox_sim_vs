#ifndef GUI_EDIT_H
#define GUI_EDIT_H

#include "lvgl.h"
#include "C-FPoint.h"

typedef V(*gui_edit_fp_cb_t)( FP, B );
typedef V(*gui_edit_str_cb_t)( PC, B );

extern void gui_edit_fp( PCC prompt, FP val, FP mn, FP mx, gui_edit_fp_cb_t );

extern void gui_edit_str( PCC prompt, PCC val, ST len_min, ST len_max, gui_edit_str_cb_t );


#endif
