#ifndef UTILS_H_
#define UTILS_H_

#include "C-FPoint.h"

/* Debugger helper macro */
#define DoNothing()	asm("nop")

/*+ Bit tables, macros and functions  */
extern CU8	bits4[4];
extern CU8	bits8[8];
extern CU16	bits16[16];
extern CU32	bits32[32];
extern CU64	bits64[64];

extern CU8	bits4Rev[4];
extern CU8	bits8Rev[8];
extern CU16	bits16Rev[16];
extern CU32	bits32Rev[32];
extern CU64	bits64Rev[64];

/* With Sanity checks */
#define SetBit(v,i)			v |= Bits64(i)
#define ClrBit(v,i)			v &= Bits64Not(i)
#define BitIsSet(v,i)		((((v)&Bits64(i))) != 0)
#define BitIsClr(v,i)		((((v)&Bits64(i))) == 0)

/* Without Sanity checks */
#define BIT(i)				(1ull<<(i))
#define SET_BIT(v,i)		v |=  BIT(i)
#define CLR_BIT(v,i)		v &= ~BIT(i)
#define BIT_IS_SET(v,i)		(((v) & BIT(i)) != 0)
#define BIT_IS_CLR(v,i)		(((v) & BIT(i)) == 0)
/* Table method */
#define Bit_Is_Set(v,i)		(((v) & bits64[i]) != 0)
#define Bit_Is_Clr(v,i)		(((v) & bits64[i]) == 0)

/* With Sanity checks */
#define BITS8(n)	((n)< 8 ? bits8[n] :0)
#define BITS16(n)	((n)<16 ? bits16[n]:0)
#define BITS32(n)	((n)<32 ? bits32[n]:0)
#define BITS64(n)	((n)<64 ? bits64[n]:0)

extern U8	Bits8		( U8 u8 );
extern U8	Bits8Not	( U8 u8 );
extern U16	Bits16		( U8 u8 );
extern U16	Bits16Not	( U8 u8 );
extern U32	Bits32		( U8 u8 );
extern U32	Bits32Not	( U8 u8 );
extern U64	Bits64		( U8 u8 );
extern U64	Bits64Not	( U8 u8 );

/*- Bit tables, macros and functions  */

extern B ParseB		( PCC str, PB pVal );
extern B ParseSC	( PCC str, PSC pVal, I base );
extern B ParseUC	( PCC str, PUC pVal, I base );
extern B ParseSS	( PCC str, PSS pVal, I base );
extern B ParseUS	( PCC str, PUS pVal, I base );
extern B ParseSI	( PCC str, PSI pVal, I base );
extern B ParseUI	( PCC str, PUI pVal, I base );
extern B ParseSL	( PCC str, PSL pVal, I base );
extern B ParseUL	( PCC str, PUL pVal, I base );
extern B ParseSLL	( PCC str, PSLL pVal, I base );
extern B ParseULL	( PCC str, PULL pVal, I base );
extern B ParseFLT   ( PCC str, PFLT pVal );
extern B ParseDBL	( PCC str, PDBL pVal );

extern B ParseFLT_MinMax	( PCC str, PFLT pVal, FLT mn, FLT mx );
extern B ParseDBL_MinMax	( PCC str, PDBL pVal, DBL mn, DBL mx );

#if FP_BITS == 32
#define ParseFP			ParseFLT
#define ParseFP_MinMax	ParseFLT_MinMax
#else
#define ParseFP			ParseDBL
#define ParseFP_MinMax	ParseDBL_MinMax
#endif

extern B SanitizeFP	( PFP pVal, FP mn, FP mx );
extern B SanitizeUI	( PUI pVal, UI mn, UI mx );
extern B SanitizeU16	( PU16 pVal, U16 mn, U16 mx );
extern B SanitizeU32	( PU32 pVal, U32 mn, U32 mx );

extern B ParseSanitizeFP	( PCC str, PFP pVal, FP mn, FP mx );
extern B ParseSanitizeUI	( PCC str, PUI pVal, UI mn, UI mx );
extern B ParseSanitizeU32	( PCC str, PU32 pVal, U32 mn, U32 mx );

extern UI AbsDifference		( UI a, UI b );

extern FP FpFixDecimalDigits	( FP val, UI n );

extern PFP	FpCopyArray			( PFP pTo, PCFP pFr, UI cnt );
extern PFP	FpCopyFixDecArray	( PFP pTo, PCFP pFr, UI cnt, UI dig );
extern FP	FpCmpArray			( PCFP pF1, PCFP pF2, UI cnt );
extern FP	FpMinArray			( PCFP pF, UI cnt );
extern FP	FpMaxArray			( PCFP pF, UI cnt );

extern FP FpRandomMinMax    ( FP mn, FP mx );
extern UI RandMnMx    		( UI mn, UI mx );

extern FP DifferenceRatio   	( FP denom, FP num );
extern FP AbsDifferenceRatio	( FP denom, FP num );
extern FP Ratio             	( FP denom, FP num );

#endif /* UTILS_H_ */
