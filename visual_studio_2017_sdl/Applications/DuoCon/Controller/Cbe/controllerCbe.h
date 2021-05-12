#ifndef CONTROLLERCBE_H
#define CONTROLLERCBE_H

#include "Fun-Types.h"
#include "IoDrivers/Ddi.h"

extern volatile eDdi_Fault_t cbeFault;

typedef enum {
	CTRLR_CBE_NONE,
	CTRLR_CBE_ZERO,
	CTRLR_CBE_MAN,
	CTRLR_CBE_TSTCS,
	CTRLR_CBE_TSTACV,
	CTRLR_CBE_TSTFACT,
	CTRLR_CBE_TSTBRKS,
	CTRLR_CBE_TSTCLNDS,
} eCbeCtrlrId_t;

typedef V (*CtrlrCreateFn) (eCbeCtrlrId_t);
typedef _V_PFN_PV_	CtrlrTaskFn;
typedef _V_PFN_V_	CtrlrDestroyFn;
typedef _V_PFN_V_	CtrlrAbortFn;

typedef enum {
	ST_CBE_NONE,
	ST_CBE_INIT,
	ST_CBE_RUNNING,
	ST_CBE_COMPLETE,
	ST_CBE_STOPPED,
	ST_CBE_ABORTED,
	ST_CBE_FAULT,
} eCbeCtrlrState_t;

typedef struct {
	CtrlrCreateFn	create;
	CtrlrTaskFn		task;
	CtrlrDestroyFn	destroy;
	CtrlrAbortFn	abort;
} CtrlrCtdaFuns_t, *PCtrlrCtdaFuns_t;
typedef const CtrlrCtdaFuns_t 	CCtrlrCtdaFuns_t;
typedef CCtrlrCtdaFuns_t * 		PCCtrlrCtdaFuns_t;

extern V Cbe_ControllerChange	( eCbeCtrlrId_t newCtrlrId );
extern V Cbe_ControllerAbort 	( eCbeCtrlrId_t newCtrlrId );

extern eDdi_Fault_t Cbe_ControllerFaultStatusGet ( V );

extern eCbeCtrlrId_t Cbe_ControllerIdGet  ( V );


extern V Cbe_ControllerInit		( U8 priority );

#endif
