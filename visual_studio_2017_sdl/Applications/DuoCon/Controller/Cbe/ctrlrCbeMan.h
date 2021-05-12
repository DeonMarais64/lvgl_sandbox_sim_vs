#ifndef CTRLRCBEMAN_H
#define CTRLRCBEMAN_H

#include "C-Fpoint.h"
#include "controllerCbe.h"

typedef struct {
	B	limitUpper;
	B	limitLower;
	FP	pressure;
	B	motorRunning;
	FP	motorSpeed;
} CbeManRunStatus_t;

extern const CtrlrCtdaFuns_t ctrlrCbeManFns;

extern V CtrlrCbeMan_StatusGet		( CbeManRunStatus_t * ps );
extern V CtrlrCbeMan_MotorRunSet	( B run );
extern V CtrlrCbeMan_MotorSpeedSet	( FP percentage );

#endif
