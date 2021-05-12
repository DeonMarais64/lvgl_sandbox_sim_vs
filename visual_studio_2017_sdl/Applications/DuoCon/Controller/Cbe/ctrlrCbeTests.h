#ifndef CTRLRCBETESTS_H
#define CTRLRCBETESTS_H

#include "C-Fpoint.h"
#include "controllerCbe.h"

typedef struct {
	eCbeCtrlrState_t	state;
	FP					pressure;
	UI					duration;
	UI					seq_nb_max_pressure;
} CbeTestStatus_t;

extern const CtrlrCtdaFuns_t ctrlrCbeTstsFns;

extern eCbeCtrlrState_t Cbe_CtrlrTestStateGet ( V );
extern V CtrlrCbeTest_StatusGet		( CbeTestStatus_t * ps );

extern PCC CtrlrCbeTest_StateGetStr ( eCbeCtrlrState_t state );

extern B CtrlrCbeTest_HistoryStatsGet( PUI pSequence100ms, PUI pSequence1000ms );
extern UI CtrlrCbeTest_History100msGet( PFP pSamples, UI size, UI fromSequence );
extern UI CtrlrCbeTest_History1000msGet( PFP pSamples, UI size, UI fromSequence );


#endif
