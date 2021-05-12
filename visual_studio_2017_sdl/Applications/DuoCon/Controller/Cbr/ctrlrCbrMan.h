#ifndef CTRLRCBEMAN_H
#define CTRLRCBEMAN_H

#include "C-Fpoint.h"
#include "controllerCbr.h"

typedef struct {
	B	limitUpper;
	B	limitLower;
	FP	pressure;
	FP	displacement;
	FP	motorSpeed;
	S8	motorState;		/* Forward > 0; Stopped == 0; Reverse < 0 */
} CbrManRunStatus_t;

extern const CbrCtrlrCtdaFuns_t ctrlrCbrManFns;

extern V CtrlrCbrMan_StatusGet		( CbrManRunStatus_t * ps );
extern V CtrlrCbrMan_MotorSetState	( S8 state );
extern V CtrlrCbrMan_MotorSpeedSet	( FP percentage );

#endif
