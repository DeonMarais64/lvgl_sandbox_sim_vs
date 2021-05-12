#include "gui.h"

typedef struct {
	lv_obj_t * obj;
	lv_style_t style;
	void(*callback)( bool);
} modal_t;

static void mbox_event_cb(lv_obj_t *mbox, lv_event_t evt)
{
    if(evt == LV_EVENT_DELETE)
    {
    	modal_t * modal = lv_obj_get_user_data(mbox);

    	lv_obj_reset_style_list( modal->obj, LV_OBJ_PART_MAIN );
    	lv_style_reset( &modal->style );
        lv_obj_del_async(modal->obj);

    	if( modal->callback )
    	{
    		const char * pressed = lv_msgbox_get_active_btn_text(mbox);
    		B ret = strncmp(pressed, "Apply", 5) == 0;
    		modal->callback(ret);
    	}
    	lv_mem_free(modal);
    }
    else if(evt == LV_EVENT_VALUE_CHANGED)
    {
        lv_msgbox_start_auto_close(mbox, 0);
    }
}

void gui_msgbox( const char * msg, void(*callback)(bool) )
{
	modal_t * modal = lv_mem_alloc(sizeof(modal_t));
	modal->callback = callback;

    lv_style_init(&modal->style);
    lv_style_set_bg_color(&modal->style, LV_STATE_DEFAULT, LV_COLOR_BLACK);

    /* Create a base object for the modal background */
    modal->obj = lv_obj_create(lv_scr_act(), NULL);
    lv_obj_reset_style_list(modal->obj, LV_OBJ_PART_MAIN);
    lv_obj_add_style(modal->obj, LV_OBJ_PART_MAIN, &modal->style);
    lv_obj_set_pos(modal->obj, 0, 0);
    lv_obj_set_size(modal->obj, LV_HOR_RES, LV_VER_RES);
    lv_obj_set_style_local_bg_opa(modal->obj, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_OPA_50);

    /* Create the message box as a child of the modal background */
    static const char * const apply_close[] = {"Apply", "Close", ""};
    static const char * const ok[] = {"Ok", ""};

    lv_obj_t * mbox = lv_msgbox_create(modal->obj, NULL);
    lv_msgbox_add_btns( mbox, (const char **)(modal->callback ? apply_close : ok) );
    lv_msgbox_set_text( mbox, msg );
    lv_obj_align( mbox, NULL, LV_ALIGN_CENTER, 0, 0 );
    lv_obj_set_event_cb( mbox, mbox_event_cb );
    lv_obj_set_user_data( mbox, modal );
}


void gui_lbl_limits_update( lv_obj_t * lbl, eDdi_Fault_t fault )
{
	static CPCC lims[] = { "", "lower Limit", "Upper Limit", "Upper & Lower Limit" };
	UI idx = 0;
	idx |= (fault & DDI_FAULT_LIMIT_LOWER) ? 1 : 0;
	idx |= (fault & DDI_FAULT_LIMIT_UPPER) ? 2 : 0;
	lv_label_set_text_static( lbl, lims[idx] );
}


