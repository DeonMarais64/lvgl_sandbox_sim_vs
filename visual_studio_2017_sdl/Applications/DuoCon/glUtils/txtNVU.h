#ifndef TXTNVU_H
#define TXTNVU_H

#ifdef __cplusplus
extern "C" {
#endif


#include "glObjects.h"

typedef enum {
	TXTNVU_OPTS_NONE 	= 0x00,

} TXTNVU_OPTS_t;

typedef struct {
	PLbl	pLblName;
	PLbl	pLblValue;
	PLbl	pLblUnits;
} TxtNvu_t;

typedef struct {
	TxtNvu_t			*pTxtNvu;
	const lv_style_t	*pLblNSt;
	const lv_style_t	*pLblVSt;
	const lv_style_t	*pLblUSt;
	lv_coord_t			xLeft;
	lv_coord_t			y;
	lv_coord_t			xRight;
	lv_coord_t			xValueLeftOfUnits;
	PCC					pLblNTxt;
	PCC					pLblVTxt;
	PCC					pLblUTxt;
	PC					pTxtN;
	PC					pTxtV;
	PC					pTxtU;
	TXTNVU_OPTS_t		opts;
} TxtNvuCreatePrms_t;

extern TxtNvu_t * TxtNvuCreate	( TxtNvuCreatePrms_t *pPrms, PPar pPar );


#ifdef __cplusplus
}
#endif

#endif
