/*
 * gui_btn.c
 *
 *  Created on: 03 May 2018
 *      Author: Deon-Marais
 */

#include "gui_btn.h"
lv_obj_t * BtnCreate2Lbls ( ButtonCreatePrms_t *pPrms, lv_obj_t *pPar )
{
	if( !pPrms ) return NULL;

	pPrms->pButton->pBtn = lv_btn_create( pPar, NULL );

#if LV_USE_ANIMATION && LV_BTN_INK_EFFECT
    lv_btn_set_ink_in_time(pPrms->pButton->pBtn, 200);
    lv_btn_set_ink_wait_time(pPrms->pButton->pBtn, 100);
    lv_btn_set_ink_out_time(pPrms->pButton->pBtn, 500);
#endif

	if( pPrms->pBtnSt )
        //lv_obj_set_style( pPrms->pButton->pBtn, (lv_style_t*)pPrms->pBtnSt );
		;//lv_obj_add_style( pPrms->pButton->pBtn, LV_STATE_DEFAULT, (lv_style_t*)pPrms->pBtnSt );
    if( pPrms->opts & BUT_OPTS_SIZE )
    {
        lv_obj_set_size( pPrms->pButton->pBtn, pPrms->w, pPrms->h );
    }
    if( pPrms->event_cb )
        lv_obj_set_event_cb( pPrms->pButton->pBtn, pPrms->event_cb );
    if( pPrms->opts & BUT_OPTS_ID )
        lv_obj_set_user_data( pPrms->pButton->pBtn, (lv_obj_user_data_t)pPrms->id );

    if( pPrms->opts & BUT_OPTS_LBL1 )
    {
    	pPrms->pButton->pLbl1 = lv_label_create( pPrms->pButton->pBtn, NULL );
    	if( pPrms->pLbl1St )
            //lv_obj_set_style( pPrms->pButton->pLbl1, (lv_style_t*)pPrms->pLbl1St );
    		;//lv_obj_add_style( pPrms->pButton->pLbl1, LV_STATE_DEFAULT, (lv_style_t*)pPrms->pLbl1St );
        if( pPrms->opts & BUT_OPTS_LBL2 )
        	lv_obj_align( pPrms->pButton->pLbl1, NULL, LV_ALIGN_IN_TOP_MID, 0, 0 );
        else
        	lv_obj_align( pPrms->pButton->pLbl1, NULL, LV_ALIGN_CENTER, 0, 0 );
        if( pPrms->pLbl1Txt )
        {
        	lv_label_set_text_static( pPrms->pButton->pLbl1, pPrms->pLbl1Txt );
        	lv_label_set_align( pPrms->pButton->pLbl1, LV_LABEL_ALIGN_CENTER );
        }

        if( pPrms->opts & BUT_OPTS_LBL2 )
        {
        	pPrms->pButton->pLbl2 = lv_label_create( pPrms->pButton->pBtn, NULL );
        	if( pPrms->pLbl2St )
                //lv_obj_set_style( pPrms->pButton->pLbl2, (lv_style_t*)pPrms->pLbl2St );
        		;//lv_obj_add_style( pPrms->pButton->pLbl2, LV_STATE_DEFAULT, (lv_style_t*)pPrms->pLbl2St );
       		lv_obj_align( pPrms->pButton->pLbl2, pPrms->pButton->pLbl1, LV_ALIGN_OUT_BOTTOM_MID, 0, 0 );
            if( pPrms->pLbl2Txt )
            {
            	lv_label_set_text_static( pPrms->pButton->pLbl2, pPrms->pLbl2Txt );
            	lv_label_set_align( pPrms->pButton->pLbl2, LV_LABEL_ALIGN_CENTER );
            }
        }
    }
    return pPrms->pButton->pBtn;
}

lv_obj_t* gui_btn_contol_create(lv_obj_t* par, gui_btn_control_prms_t* pPrms) 
{
	if( !pPrms ) return NULL;

	pPrms->pButton->pBtn = lv_btn_create( par, NULL );

    if( pPrms->opts & BUT_OPTS_SIZE )
    {
        lv_obj_set_size( pPrms->pButton->pBtn, pPrms->w, pPrms->h );
    }
    if( pPrms->event_cb )
        lv_obj_set_event_cb( pPrms->pButton->pBtn, pPrms->event_cb );
    if( pPrms->opts & BUT_OPTS_ID )
        lv_obj_set_user_data( pPrms->pButton->pBtn, (lv_obj_user_data_t)pPrms->id );

    if( pPrms->opts & BUT_OPTS_LBL1 )
    {
    	pPrms->pButton->pLbl1 = lv_label_create( pPrms->pButton->pBtn, NULL );
        if( pPrms->opts & BUT_OPTS_LBL2 )
        	lv_obj_align( pPrms->pButton->pLbl1, NULL, LV_ALIGN_IN_TOP_MID, 0, 0 );
        else
        	lv_obj_align( pPrms->pButton->pLbl1, NULL, LV_ALIGN_CENTER, 0, 0 );
        if( pPrms->pLbl1Txt )
        {
            lv_label_set_text_static( pPrms->pButton->pLbl1, pPrms->pLbl1Txt );
        	lv_label_set_align( pPrms->pButton->pLbl1, LV_LABEL_ALIGN_CENTER );
        }

        if( pPrms->opts & BUT_OPTS_LBL2 )
        {
        	pPrms->pButton->pLbl2 = lv_label_create( pPrms->pButton->pBtn, NULL );
       		lv_obj_align( pPrms->pButton->pLbl2, pPrms->pButton->pLbl1, LV_ALIGN_OUT_BOTTOM_MID, 0, 0 );
            if( pPrms->pLbl2Txt )
            {
                lv_label_set_text_static( pPrms->pButton->pLbl2, pPrms->pLbl2Txt );
            	lv_label_set_align( pPrms->pButton->pLbl2, LV_LABEL_ALIGN_CENTER );
            }
        }
    }
    return pPrms->pButton->pBtn;
}

static void event_cb_default(lv_obj_t* btn, lv_event_t e)
{
    (void)btn;
    (void)e;
}

lv_obj_t* gui_btn_create (lv_obj_t* parent, const char* txt, lv_event_cb_t event_cb, uint8_t id, lv_font_t* font)
{
    Button_t button;
    gui_btn_control_prms_t prms = {
        .pButton = &button,
        .event_cb = event_cb ? event_cb : event_cb_default,
        .id = id,
        .pLbl1Txt = txt ? txt : "Button",
        .opts = (gui_btn_control_opts_t)(BUT_OPTS_NONE
                        | BUT_OPTS_ID
                        | BUT_OPTS_LBL1
         )
    };

    gui_btn_contol_create( parent, &prms );
    if( font )
        lv_obj_set_style_local_text_font(button.pLbl1, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, font);

    return button.pBtn;
}

/**
 * Disable toolbar button
 */
void gui_btn_disable ( lv_obj_t* btn )
{
    lv_btn_set_state(btn, LV_BTN_STATE_DISABLED);
    lv_obj_set_click( btn, false );
}

/**
 * Enable toolbar button
 */
void gui_btn_enable ( lv_obj_t* btn )
{
    lv_btn_set_state(btn, LV_BTN_STATE_RELEASED);
    lv_obj_set_click( btn, true );
}

