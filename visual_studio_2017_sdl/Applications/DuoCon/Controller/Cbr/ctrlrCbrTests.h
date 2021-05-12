#ifndef CTRLRCBRTESTS_H
#define CTRLRCBRTESTS_H

#include "C-Fpoint.h"
#include "controllerCbr.h"

typedef struct {
	eCbrCtrlrState_t	state;
	FP					pressure;
	FP					displacement;
//	FP					speed;
	UI					duration;
	UI					seq_nb_max_pressure;
} CbrTestStatus_t;

extern const CbrCtrlrCtdaFuns_t ctrlrCbrTstsFns;

extern eCbrCtrlrState_t Cbr_CtrlrTestStateGet ( V );
extern V CtrlrCbrTest_StatusGet		( CbrTestStatus_t * ps );

extern PCC CtrlrCbrTest_StateGetStr ( eCbrCtrlrState_t state );

typedef struct {
	FP	pressure;
	FP	displacement;
} CbrCtrlrSample_t;

extern B CtrlrCbrTest_HistoryStatsGet( PUI pSequence100ms, PUI pSequence1000ms );
extern UI CtrlrCbrTest_History100msGet( CbrCtrlrSample_t *pSamples, UI size, UI fromSequence );
extern UI CtrlrCbrTest_History1000msGet( CbrCtrlrSample_t *pSamples, UI size, UI fromSequence );

#endif
