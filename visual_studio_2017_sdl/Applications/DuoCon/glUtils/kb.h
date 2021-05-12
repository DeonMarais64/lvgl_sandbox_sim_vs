#ifndef KB_H
#define KB_H

#ifdef __cplusplus
extern "C" {
#endif

#include "glObjects.h"

extern CPCC kb_map_num[];
extern CPCC kb_map_num_fp[];
extern CPCC kb_map_time[];
extern CPCC kb_map_date[];

enum {
	KB_MODE_DEFAULT,
	KB_MODE_NUM,
	KB_MODE_TIME,
	KB_MODE_DATE,
};
typedef U8 KbMode_t;


enum {
	KB_OPT_NONE				= 0x00,
	KB_OPT_MODE_NUM			= 0x01,
	KB_OPT_MODE_TIME		= 0x02,
	KB_OPT_MODE_DATE		= 0x04,
	KB_OPT_MODE_ONE_LINE	= 0x08,
	KB_OPT_MODE_PW			= 0x10,
	KB_OPT_MODE_TXT_SEL		= 0x20,
	KB_OPT_SIZE_DEFAULT		= 0x40,	/* Project not LVGL defaults */
};
typedef U8 KbTaOpts_t;

typedef struct {
	CPCC			pTaTxt;
	CPCC			*pMap;
	lv_coord_t		wKb;
	lv_coord_t		hKb;
	lv_coord_t		wTa;
	lv_coord_t		hTa;
	lv_event_cb_t	pCb;
	KbTaOpts_t 		opts;
} KbCreatePrms_t;

extern PKb KbCreate ( PPar pPar,  const KbCreatePrms_t * pPrms );
extern lv_res_t KbDestroy ( PKb pKb );

#ifdef __cplusplus
}
#endif

#endif

