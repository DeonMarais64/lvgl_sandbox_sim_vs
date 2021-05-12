#ifndef TXTNV_H
#define TXTNV_H

#ifdef __cplusplus
extern "C" {
#endif

#include "glObjects.h"

typedef enum {
	TXTNV_OPTS_NONE 	= 0x00,

} TXTNV_OPTS_t;

typedef struct {
	PLbl	pLblName;
	PLbl	pLblValue;
} TxtNv_t;

typedef struct {
	TxtNv_t			*pTxtNv;
	const lv_style_t	*pLblNSt;
	const lv_style_t	*pLblVSt;
	lv_coord_t			xLeft;
	lv_coord_t			y;
	lv_coord_t			xRight;
	lv_coord_t			xValueLeftOfRight;
	PCC					pLblNTxt;
	PCC					pLblVTxt;
	PC					pTxtN;
	PC					pTxtV;
	TXTNV_OPTS_t		opts;
} TxtNvCreatePrms_t;

extern TxtNv_t * TxtNvCreate	( TxtNvCreatePrms_t *pPrms, PPar pPar );


#ifdef __cplusplus
}
#endif

#endif
