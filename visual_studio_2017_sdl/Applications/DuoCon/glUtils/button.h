/*
 * button.h
 *
 *  Created on: 03 May 2018
 *      Author: Deon-Marais
 */

#ifndef BUTTON_H_
#define BUTTON_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "glObjects.h"

typedef enum {
	BUT_OPTS_NONE	= 0x00,
	BUT_OPTS_SIZE	= 0x01,
	BUT_OPTS_ID		= 0x02,
	BUT_OPTS_LBL1	= 0x04,
	BUT_OPTS_LBL2	= 0x08,
} BUTTON_OPTS_t;

typedef struct {
	lv_obj_t	*pBtn;
	lv_obj_t 	*pLbl1;
	lv_obj_t 	*pLbl2;
} Button_t;

typedef struct {
	Button_t				*pButton;
	const lv_style_t 		*pBtnSt;
	lv_coord_t				w;
	lv_coord_t				h;
	lv_event_cb_t			action;
//	lv_obj_user_data_t		id;
	U8						id;
	const lv_style_t		*pLbl1St;
	PCC						pLbl1Txt;
	const lv_style_t 		*pLbl2St;
	PCC						pLbl2Txt;
	BUTTON_OPTS_t			opts;
} ButtonCreatePrms_t;

extern lv_obj_t * BtnCreate2Lbls ( ButtonCreatePrms_t *pPrms, lv_obj_t *pPar );

#ifdef __cplusplus
}
#endif

#endif /* BUTTON_H_ */
