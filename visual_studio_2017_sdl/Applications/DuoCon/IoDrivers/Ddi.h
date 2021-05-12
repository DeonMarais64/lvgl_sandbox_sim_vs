#ifndef DDI_H
#define DDI_H

#include "C-FPoint.h"


typedef enum {
	DDI_FAULT_NONE			= 0,
	DDI_FAULT_POWER			= 1,
	DDI_FAULT_LIMIT_UPPER	= 2,
	DDI_FAULT_LIMIT_LOWER	= 4,
} eDdi_Fault_t;

typedef V (*Ddi_CbFault) ( eDdi_Fault_t, B );

extern V Ddi_Init ( V );

extern V Ddi_CardRdyHandler	( V );
extern V Ddi_UiPsAHandler	( V );
extern V Ddi_UiPsBHandler	( V );
extern V Ddi_UiPsCHandler	( V );

extern  eDdi_Fault_t Ddi_FaultCallbackSet ( Ddi_CbFault );
extern  eDdi_Fault_t Ddi_FaultStatusGet ( V );


extern PCC Ddi_CardRdyGetStr	( V );
extern PCC Ddi_UiPsAGetStr		( V );
extern PCC Ddi_UiPsBGetStr		( V );
extern PCC Ddi_UiPsCGetStr		( V );

extern SI	Ddi_MtPulseCntGet		( V );
extern FP	Ddi_RamDisplacementGet	( V );
extern FP	Ddi_RamSpeedGet			( V );

extern V	Ddi_RamDisplacementSuspend ( V );
extern V	Ddi_RamDisplacementResume ( V );

extern V	Ddi_RamSpeedZero		( V );

extern FP	Ddi_RamSpeedGetAndClear	( V );

extern V	Ddi_EveryTick_InsideISR	( V );


#endif
