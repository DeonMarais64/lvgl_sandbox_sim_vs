#ifndef CONTROLLERCBR_H
#define CONTROLLERCBR_H

#include "Fun-Types.h"
#include "IoDrivers/Ddi.h"

extern volatile eDdi_Fault_t cbrFault;

typedef enum {
	CTRLR_CBR_NONE,
	CTRLR_CBR_ZERO,
	CTRLR_CBR_MAN,
	CTRLR_CBR_DISPLACE,
	CTRLR_CBR_TSTCBR,
	CTRLR_CBR_TSTUCS,
	CTRLR_CBR_TSTITS,
	CTRLR_CBR_TSTMARSHALL,
} eCbrCtrlrId_t;

typedef V (*CbrCtrlrCreateFn) (eCbrCtrlrId_t);
typedef _V_PFN_PV_	CbrCtrlrTaskFn;
typedef _V_PFN_V_	CbrCtrlrDestroyFn;
typedef _V_PFN_V_	CbrCtrlrAbortFn;

typedef enum {
	ST_CBR_NONE,
	ST_CBR_INIT,
	ST_CBR_RUNNING,
	ST_CBR_COMPLETE,
	ST_CBR_STOPPED,
	ST_CBR_ABORTED,
	ST_CBR_FAULT,
} eCbrCtrlrState_t;

typedef struct {
	CbrCtrlrCreateFn	create;
	CbrCtrlrTaskFn		task;
	CbrCtrlrDestroyFn	destroy;
	CbrCtrlrAbortFn		abort;
} CbrCtrlrCtdaFuns_t, *PCbrCtrlrCtdaFuns_t;
typedef const CbrCtrlrCtdaFuns_t 	CCbrCtrlrCtdaFuns_t;
typedef CCbrCtrlrCtdaFuns_t * 		PCCbrCtrlrCtdaFuns_t;

extern V Cbr_ControllerChange	( eCbrCtrlrId_t newCtrlrId );
extern V Cbr_ControllerAbort 	( eCbrCtrlrId_t newCtrlrId );

extern eDdi_Fault_t Cbr_ControllerFaultStatusGet ( V );

extern eCbrCtrlrId_t Cbr_ControllerIdGet  ( V );


extern V Cbr_ControllerInit		( U8 priority );

#endif
