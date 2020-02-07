/*
 * Variant_Types.h
 *
 * Created: 2014/04/27 01:28:47
 *  Author: Deon Marais
 */


#ifndef VARIANT_TYPES_H_
#define VARIANT_TYPES_H_

#include <time.h>
#include "C-FPoint.h"

typedef enum {
	V_B,
	V_C,
	V_SC,
	V_S8,
	V_UC,
	V_U8,
	V_SS,
	V_S16,
	V_US,
	V_U16,
	V_SI,
	V_SL,
	V_S32,
	V_UI,
	V_UL,
	V_U32,
	V_SLL,
	V_S64,
	V_ULL,
	V_U64,
	V_FP,
	V_FP32,
	V_FP64,
	V_TIME,
	V_TIME_OFFSET,
	V_DATE_TIME,
	V_YN,
	V_STRING,
	V_CSTRING,
} eVar_t;

typedef union {
	B		b;
	C		c;
	SC		sc;
	S8		s8;
	UC		uc;
	U8		u8;
	SS		ss;
	S16		s16;
	US		us;
	U16		u16;
	SI		si;
	SL		sl;
	S32		s32;
	UI		ui;
	UL		ul;
	U32		u32;
	SLL		sll;
	S64		s64;
	ULL		ull;
	U64		u64;
	FP		fp;
	FP32	fp32;
	FP64	fp64;
	time_t	time;
	PC		pc;
	PCC		pcc;
} Var64, *PVar64;
typedef const Var64 CVar64;
typedef CVar64 *PCVar64;

typedef const PVar64	CPVar64;

typedef union {
	B		b;
	C		c;
	SC		sc;
	S8		s8;
	UC		uc;
	U8		u8;
	SS		ss;
	S16		s16;
	US		us;
	U16		u16;
	SI		si;
	SL		sl;
	S32		s32;
	UI		ui;
	UL		ul;
	U32		u32;
#if FP_BITS == 32
	FP		fp;
#endif
	FP32	fp32;
	time_t	time;
	PC		pc;
	PCC		pcc;
} Var32;	/* Variant types <= 32 bits */

typedef union {
	PV		pv;
	PB		pb;
	PC		pc;
	PSC		psc;
	PS8		ps8;
	PUC		puc;
	PU8		pu8;
	PSS		pss;
	PS16	ps16;
	PUS		pus;
	PU16	pu16;
	PSI		psi;
	PSL		psl;
	PS32	ps32;
	PUI		pui;
	PUL		pul;
	PU32	pu32;
	PSLL	psll;
	PS64	ps64;
	PULL	pull;
	PU64	pu64;
	PFP		pfp;
	PFP32	pfp32;
	PFP64	pfp64;
	time_t	*ptime;
	PCC		*ppcc;
} VarP;
typedef const VarP CVarP;

#if 0
typedef struct {
	eVar_t	vt;
	Var64	v;
} Variant_t;

typedef struct {
	eVar_t	vt;
	VarP	vp;
} VarP_t;
#endif


#endif /* VARIANT_TYPES_H_ */
