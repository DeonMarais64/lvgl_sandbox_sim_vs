#ifndef CTRLRCBRDISPLACE_H
#define CTRLRCBRDISPLACE_H

#include "C-Fpoint.h"
#include "controllerCbr.h"

typedef struct {
	eCbrCtrlrState_t	state;
	FP					displacement;
	UI					duration;
} CbrDisplaceStatus_t;

extern const CbrCtrlrCtdaFuns_t ctrlrCbrDisplaceFns;

extern eCbrCtrlrState_t Cbr_CtrlrDisplaceStateGet ( V );
extern V CtrlrCbrDisplace_StatusGet		( CbrDisplaceStatus_t * ps );

extern PCC CtrlrCbrDisplace_StateGetStr ( eCbrCtrlrState_t state );

extern B CtrlrCbrDisplace_HistoryStatsGet( PUI pSequence100ms, PUI pSequence1000ms );
extern UI CtrlrCbrDisplace_History100msGet( PFP pSamples, UI size, UI fromSequence );
extern UI CtrlrCbrDisplace_History1000msGet( PFP pSamples, UI size, UI fromSequence );

#endif
