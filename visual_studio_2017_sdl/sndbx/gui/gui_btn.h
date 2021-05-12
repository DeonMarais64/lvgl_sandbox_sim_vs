/*
 * gui_btn.h
 *
 *  Created on: 03 May 2018
 *      Author: Deon-Marais
 */

#ifndef GUI_BTN_H_
#define GUI_BTN_H_

/*********************
  *      INCLUDES
  *********************/
#if 0 && defined LV_CONF_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    BUT_OPTS_NONE	= 0x00,
    BUT_OPTS_SIZE	= 0x01,
    BUT_OPTS_ID		= 0x02,
    BUT_OPTS_LBL1	= 0x04,
    BUT_OPTS_LBL2	= 0x08,
} BUTTON_OPTS_t;

typedef struct {
    lv_obj_t *pBtn;
    lv_obj_t *pLbl1;
    lv_obj_t *pLbl2;
} Button_t;

typedef struct {
    Button_t			*pButton;
    const lv_style_t 	*pBtnSt;
    lv_coord_t			w;
    lv_coord_t			h;
    lv_event_cb_t		event_cb;
    uint8_t				id;
    const lv_style_t	*pLbl1St;
    const char          *pLbl1Txt;
    const lv_style_t    *pLbl2St;
    const char          *pLbl2Txt;
    BUTTON_OPTS_t		opts;
} ButtonCreatePrms_t;

extern lv_obj_t * BtnCreate2Lbls ( ButtonCreatePrms_t *pPrms, lv_obj_t *pPar );

#define gui_btn_control_opts_t BUTTON_OPTS_t

typedef struct {
    Button_t*               pButton;
    lv_coord_t		        w;
    lv_coord_t		        h;
    lv_event_cb_t	        event_cb;
    uint8_t			        id;
    const char*             pLbl1Txt;
    const char*             pLbl2Txt;
    gui_btn_control_opts_t	opts;
} gui_btn_control_prms_t;

extern lv_obj_t* gui_btn_contol_create(lv_obj_t* pPar, gui_btn_control_prms_t* pPrms );

extern lv_obj_t* gui_btn_create(lv_obj_t* parent, const char* txt, lv_event_cb_t event_cb, uint8_t id, lv_font_t* font);

extern void gui_btn_disable ( lv_obj_t* btn );
extern void gui_btn_enable ( lv_obj_t* btn );

#define gui_btn_get_id(btn) \
    (uint8_t)(uintptr_t)lv_obj_get_user_data(btn)

#define gui_btn_set_id(btn,id) \
    lv_obj_set_user_data(btn,(lv_obj_user_data_t)id)

#ifdef __cplusplus
}
#endif

#endif /* GUI_BTN_H_ */
