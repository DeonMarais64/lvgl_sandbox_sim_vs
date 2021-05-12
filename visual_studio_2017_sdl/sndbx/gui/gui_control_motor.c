/**
 * @file gui_control_motor.c
 *
 */

/*********************
 *      INCLUDES
 *********************/

#include "gui_control_motor.h"
#include "gui_btn.h"

/*********************
 *      DEFINES
 *********************/
//#define TXT_RECOLOR LV_TXT_COLOR_CMD
#define RECOLOR(txt,color)  LV_TXT_COLOR_CMD color txt LV_TXT_COLOR_CMD
/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/

//static lv_obj_t label_create(lv_obj_t* par, );

/**********************
 *  STATIC VARIABLES
 **********************/

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

lv_obj_t* gui_ctrlmotor_rs_create(lv_obj_t * par, lv_event_cb_t event_cb)
{
    //lv_obj_set_auto_realign(btn1, true);
    //lv_btn_set_fit(btn1, LV_FIT_TIGHT);

    lv_obj_t* cnt = lv_cont_create(par, NULL);
    lv_obj_set_height(cnt, lv_obj_get_height(par));
    lv_obj_set_width(cnt, lv_obj_get_width(par) / 10);

    Button_t button;
    gui_btn_control_prms_t prms = {
        .pButton = &button,
        .w = lv_obj_get_width(cnt),
        .h = 80,
        .event_cb = event_cb,
        .id = 1,
        .pLbl1Txt = RECOLOR(LV_SYMBOL_PLAY,"00ff00 "),
        .opts = (gui_btn_control_opts_t)(BUT_OPTS_NONE
                        | BUT_OPTS_SIZE
                        | BUT_OPTS_ID
                        | BUT_OPTS_LBL1
         )
     };
    const lv_font_t *font = lv_theme_get_font_title();

    gui_btn_contol_create(cnt, &prms);
    lv_label_set_recolor(button.pLbl1, true);
    lv_obj_set_style_local_text_font(button.pLbl1, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, font);
    lv_obj_align(button.pBtn, NULL, LV_ALIGN_IN_TOP_MID, 0, 0);

    lv_obj_t *lbl = lv_label_create(cnt, NULL);
    lv_label_set_align(lbl, LV_LABEL_ALIGN_CENTER);
    lv_label_set_text_static(lbl, "M\nA\nN\nU\nA\nL");
    lv_obj_set_style_local_text_font(lbl, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, font);
    lv_obj_align(lbl, NULL, LV_ALIGN_CENTER, 0, 0);

    prms.pLbl1Txt = RECOLOR(LV_SYMBOL_STOP, "ff0000 ");
    prms.id = 2;
    gui_btn_contol_create(cnt, &prms);
    lv_label_set_recolor(button.pLbl1, true);
    lv_obj_set_style_local_text_font(button.pLbl1, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, font);
    lv_obj_align(button.pBtn, NULL, LV_ALIGN_IN_BOTTOM_MID, 0, 0);

    return cnt;
}

lv_obj_t* gui_ctrlmotor_uds_create(lv_obj_t * par, lv_event_cb_t event_cb)
{
    lv_obj_t* cnt = lv_cont_create(par, NULL);
    lv_obj_set_height(cnt, lv_obj_get_height(par));
    lv_obj_set_width(cnt, lv_obj_get_width(par) / 10);

    Button_t button;
    gui_btn_control_prms_t prms = {
        .pButton = &button,
        .w = 80,
        .h = 80,
        .event_cb = event_cb,
        .opts = (gui_btn_control_opts_t)(BUT_OPTS_NONE
                        | BUT_OPTS_SIZE
                        | BUT_OPTS_ID
                        | BUT_OPTS_LBL1
         )
     };
    const lv_font_t *font_icon = lv_theme_get_font_title();
    const lv_font_t* font_icon_name = lv_theme_get_font_small();

    prms.pLbl1Txt = RECOLOR(LV_SYMBOL_STOP, "ff0000 ");
    prms.id = 3;
    gui_btn_contol_create(cnt, &prms);
    lv_label_set_recolor(button.pLbl1, true);
    lv_obj_set_style_local_text_font(button.pLbl1, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, font_icon);
    lv_obj_align(button.pBtn, NULL, LV_ALIGN_CENTER, 0, 0);

    prms.opts |= BUT_OPTS_LBL2;
    prms.id = 1;
    prms.pLbl1Txt = RECOLOR(LV_SYMBOL_UP, "00ff00 "),
    prms.pLbl2Txt = "Up",
    gui_btn_contol_create(cnt, &prms);
    lv_label_set_recolor(button.pLbl1, true);
    lv_obj_set_style_local_text_font(button.pLbl1, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, font_icon);
    lv_obj_set_style_local_text_font(button.pLbl2, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, font_icon_name);
    lv_obj_align(button.pBtn, NULL, LV_ALIGN_IN_TOP_MID, 0, 0);

    prms.id = 2;
    prms.pLbl1Txt = "Down",
    prms.pLbl2Txt = RECOLOR(LV_SYMBOL_DOWN, "00ff00 ");
    gui_btn_contol_create(cnt, &prms);
    lv_obj_set_style_local_text_font(button.pLbl1, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, font_icon_name);
    lv_obj_set_style_local_text_font(button.pLbl2, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, font_icon);
    lv_label_set_recolor(button.pLbl2, true);
    lv_obj_align(button.pBtn, NULL, LV_ALIGN_IN_BOTTOM_MID, 0, 0);

    return cnt;
}



/**********************
 *   STATIC FUNCTIONS
 **********************/
