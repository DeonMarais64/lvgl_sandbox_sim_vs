#include "utils.h"
#include <stdlib.h>
#include <string.h>


UI RandMnMx ( UI mn, UI mx )
{
	UI rnd = rand();

	rnd += mn;
	if( rnd < mx )
		if( mx > RAND_MAX )
		{
			if( RAND_MAX == 0x7fff )
				rnd |= rand() << 15;
			else if( RAND_MAX == 0x3fffffff )
				rnd |= rand() << 30;
			else
				rnd |= rand() << 31;
		}

	return rnd % (mx+1);
}

CU8 bits4[4] = {
	(U8)0x1, (U8)0x2, (U8)0x4, (U8)0x8,
};

CU8 bits4Rev[4] = {
	(U8)0x8, (U8)0x4, (U8)0x2, (U8)0x1,
};

CU8 bits8[8] = {
	(U8)0x01, (U8)0x02, (U8)0x04, (U8)0x08,
	(U8)0x10, (U8)0x20, (U8)0x40, (U8)0x80,
};

CU8 bits8Rev[8] = {
	(U8)0x80, (U8)0x40, (U8)0x20, (U8)0x10,
	(U8)0x08, (U8)0x04, (U8)0x02, (U8)0x01,
};

CU16 bits16[16] = {
	(U16)0x0001, (U16)0x0002, (U16)0x0004, (U16)0x0008,
	(U16)0x0010, (U16)0x0020, (U16)0x0040, (U16)0x0080,
	(U16)0x0100, (U16)0x0200, (U16)0x0400, (U16)0x0800,
	(U16)0x1000, (U16)0x2000, (U16)0x4000, (U16)0x8000,
};

CU16 bits16Rev[16] = {
	(U16)0x8000, (U16)0x4000, (U16)0x2000, (U16)0x1000,
	(U16)0x0800, (U16)0x0400, (U16)0x0200, (U16)0x0100,
	(U16)0x0080, (U16)0x0040, (U16)0x0020, (U16)0x0010,
	(U16)0x0008, (U16)0x0004, (U16)0x0002, (U16)000001,
};

CU32 bits32[32] = {
	(U32)0x00000001, (U32)0x00000002, (U32)0x00000004, (U32)0x00000008,
	(U32)0x00000010, (U32)0x00000020, (U32)0x00000040, (U32)0x00000080,
	(U32)0x00000100, (U32)0x00000200, (U32)0x00000400, (U32)0x00000800,
	(U32)0x00001000, (U32)0x00002000, (U32)0x00004000, (U32)0x00008000,
	(U32)0x00010000, (U32)0x00020000, (U32)0x00040000, (U32)0x00080000,
	(U32)0x00100000, (U32)0x00200000, (U32)0x00400000, (U32)0x00800000,
	(U32)0x01000000, (U32)0x02000000, (U32)0x04000000, (U32)0x08000000,
	(U32)0x10000000, (U32)0x20000000, (U32)0x40000000, (U32)0x80000000,
};

CU32 bits32Rev[32] = {
	(U32)0x80000000, (U32)0x40000000, (U32)0x20000000, (U32)0x10000000,
	(U32)0x08000000, (U32)0x04000000, (U32)0x02000000, (U32)0x01000000,
	(U32)0x00800000, (U32)0x00400000, (U32)0x00200000, (U32)0x00100000,
	(U32)0x00080000, (U32)0x00040000, (U32)0x00020000, (U32)0x00010000,
	(U32)0x00008000, (U32)0x00004000, (U32)0x00002000, (U32)0x00001000,
	(U32)0x00000800, (U32)0x00000400, (U32)0x00000200, (U32)0x00000100,
	(U32)0x00000080, (U32)0x00000040, (U32)0x20000020, (U32)0x00000010,
	(U32)0x00000008, (U32)0x00000004, (U32)0x00000002, (U32)0x00000001,
};

CU64 bits64[64] = {
	(U64)0x0000000000000001, (U64)0x0000000000000002, (U64)0x0000000000000004, (U64)0x0000000000000008,
	(U64)0x0000000000000010, (U64)0x0000000000000020, (U64)0x0000000000000040, (U64)0x0000000000000080,
	(U64)0x0000000000000100, (U64)0x0000000000000200, (U64)0x0000000000000400, (U64)0x0000000000000800,
	(U64)0x0000000000001000, (U64)0x0000000000002000, (U64)0x0000000000004000, (U64)0x0000000000008000,
	(U64)0x0000000000010000, (U64)0x0000000000020000, (U64)0x0000000000040000, (U64)0x0000000000080000,
	(U64)0x0000000000100000, (U64)0x0000000000200000, (U64)0x0000000000400000, (U64)0x0000000000800000,
	(U64)0x0000000001000000, (U64)0x0000000002000000, (U64)0x0000000004000000, (U64)0x0000000008000000,
	(U64)0x0000000010000000, (U64)0x0000000020000000, (U64)0x0000000040000000, (U64)0x0000000080000000,
	(U64)0x0000000100000000, (U64)0x0000000200000000, (U64)0x0000000400000000, (U64)0x0000000800000000,
	(U64)0x0000001000000000, (U64)0x0000002000000000, (U64)0x0000004000000000, (U64)0x0000008000000000,
	(U64)0x0000010000000000, (U64)0x0000020000000000, (U64)0x0000040000000000, (U64)0x0000080000000000,
	(U64)0x0000100000000000, (U64)0x0000200000000000, (U64)0x0000400000000000, (U64)0x0000800000000000,
	(U64)0x0001000000000000, (U64)0x0002000000000000, (U64)0x0004000000000000, (U64)0x0008000000000000,
	(U64)0x0010000000000000, (U64)0x0020000000000000, (U64)0x0040000000000000, (U64)0x0080000000000000,
	(U64)0x0100000000000000, (U64)0x0200000000000000, (U64)0x0400000000000000, (U64)0x0800000000000000,
	(U64)0x1000000000000000, (U64)0x2000000000000000, (U64)0x4000000000000000, (U64)0x8000000000000000,
};

CU64 bits64Rev[64] = {
	(U64)0x8000000000000000, (U64)0x4000000000000000, (U64)0x2000000000000000, (U64)0x1000000000000000,
	(U64)0x0800000000000000, (U64)0x0400000000000000, (U64)0x0200000000000000, (U64)0x0100000000000000,
	(U64)0x0080000000000000, (U64)0x0040000000000000, (U64)0x0020000000000000, (U64)0x0010000000000000,
	(U64)0x0008000000000000, (U64)0x0004000000000000, (U64)0x0002000000000000, (U64)0x0001000000000000,
	(U64)0x0000800000000000, (U64)0x0000400000000000, (U64)0x0000200000000000, (U64)0x0000100000000000,
	(U64)0x0000080000000000, (U64)0x0000040000000000, (U64)0x0000020000000000, (U64)0x0000010000000000,
	(U64)0x0000008000000000, (U64)0x0000004000000000, (U64)0x2000002000000000, (U64)0x0000001000000000,
	(U64)0x0000000800000000, (U64)0x0000000400000000, (U64)0x0000000200000000, (U64)0x0000000100000000,
	(U64)0x0000000080000000, (U64)0x0000000040000000, (U64)0x0000000020000000, (U64)0x0000000010000000,
	(U64)0x0000000008000000, (U64)0x0000000004000000, (U64)0x0000000002000000, (U64)0x0000000001000000,
	(U64)0x0000000000800000, (U64)0x0000000000400000, (U64)0x0000000000200000, (U64)0x0000000000100000,
	(U64)0x0000000000080000, (U64)0x0000000000040000, (U64)0x0000000000020000, (U64)0x0000000000010000,
	(U64)0x0000000000008000, (U64)0x0000000000004000, (U64)0x0000000000002000, (U64)0x0000000000001000,
	(U64)0x0000000000000800, (U64)0x0000000000000400, (U64)0x0000000000000200, (U64)0x0000000000000100,
	(U64)0x0000000000000080, (U64)0x0000000000000040, (U64)0x0000000000000020, (U64)0x0000000000000010,
	(U64)0x0000000000000008, (U64)0x0000000000000004, (U64)0x0000000000000002, (U64)0x0000000000000001,
};

U8 Bits8 ( U8 u8 )
{
	if( u8 > 7 )
		return 0;
	return bits8[u8];
}

U8 Bits8Not ( U8 u8 )
{
	if( u8 > 7 )
		return 0;
	return ~bits8[u8];
}

U16 Bits16 ( U8 u8 )
{
	if( u8 > 15 )
		return 0;
	return bits16[u8];
}

U16 Bits16Not ( U8 u8 )
{
	if( u8 > 15 )
		return 0;
	return ~bits16[u8];
}

U32 Bits32 ( U8 u8 )
{
	if( u8 > 31 )
		return 0;
	return bits32[u8];
}

U32 Bits32Not ( U8 u8)
{
	if( u8 > 31 )
		return 0;
	return ~bits32[u8];
}

U64 Bits64 ( U8 u8 )
{
	if( u8 > 63 )
		return 0;
	return bits64[u8];
}

U64 Bits64Not ( U8 u8 )
{
	if( u8 > 63 )
		return 0;
	return ~bits64[u8];
}

B ParseB ( PCC str, PB pVal )
{
	char *pC;
	SL val;

	val = strtol( str, &pC, 0 );
	*pVal = (B)val;

	if( pC == str || *pC != '\0' )
		return false;

	if( val < 0 || val > 1)
		return false;

	return true;
}

B ParseSC ( PCC str, PSC pVal, I base )
{
	char *pC;
	SL val;

	val = strtol( str, &pC, base );
	*pVal = (SC)val;

	if( pC == str || *pC != '\0' )
		return false;

	if( val < SCHAR_MIN || val > SCHAR_MAX )
		return false;

	return true;
}

B ParseUC ( PCC str, PUC pVal, int base )
{
	char *pC;
	UL val;

	val = strtoul( str, &pC, base );
	*pVal = (UC)val;

	if( pC == str || *pC != '\0' )
		return false;
	if( val > UCHAR_MAX )
		return false;

	return true;
}

B ParseSS ( PCC str, PSS pVal, I base )
{
	char *pC;
	SL val;

	val = strtol( str, &pC, base );
	*pVal = (SS)val;

	if( pC == str || *pC != '\0' )
		return false;
	if( val < SHRT_MIN || val > SHRT_MAX )
		return false;

	return true;
}

B ParseUS ( PCC str, PUS pVal, I base )
{
	char *pC;
	UL val;

	val = strtoul( str, &pC, base );
	*pVal = (US)val;

	if( pC == str || *pC != '\0' )
		return false;
	if( val > USHRT_MAX )
		return false;

	return true;
}

B ParseSI ( PCC str, PSI pVal, I base )
{
	char *pC;
#if INT_MAX == LONG_MAX
	*pVal = strtol( str, &pC, base );

	if( pC == str || *pC != '\0' )
		return false;
#else
	SL val;

	val = strtol( str, &pC, base );
	*pVal = (SI)val;

	if( pC == str || *pC != '\0' )
		return false;
	if( val < INT_MIN || val > INT_MAX )
		return false;
#endif

	return true;
}

B ParseUI ( PCC str, PUI pVal, I base )
{
	char *pC;
#if UINT_MAX == ULONG_MAX
	*pVal = strtoul( str, &pC, base );

	if( pC == str || *pC != '\0' )
		return false;
#else
	UL val;

	val = strtol( str, &pC, base );
	*pVal = (UI)val;

	if( pC == str || *pC != '\0' )
		return false;
	if( val > UINT_MAX )
		return false;
#endif

	return true;
}

B ParseSL ( PCC str, PSL pVal, I base )
{
	char *pC;

	*pVal = strtol( str, &pC, base );

	if( pC == str || *pC != '\0' )
		return false;

	return true;
}

B ParseUL ( PCC str, PUL pVal, I base )
{
	char *pC;

	*pVal = strtoul( str, &pC, base );

	if( pC == str || *pC != '\0' )
		return false;

	return true;
}

B ParseSLL ( PCC str, PSLL pVal, I base )
{
	char *pC;

	*pVal = strtoll( str, &pC, base );

	if( pC == str || *pC != '\0' )
		return false;

	return true;
}

B ParseULL ( PCC str, PULL pVal, I base )
{
	char *pC;

	*pVal = strtoull( str, &pC, base );

	if( pC == str || *pC != '\0' )
		return false;

	return true;
}

B ParseFLT ( PCC str, PFLT pVal )
{
	PC pC;

	*pVal = strtof( str, &pC );

	if( pC == str || *pC != '\0' )
		return false;

	return true;
}

B ParseDBL ( PCC str, PDBL pVal )
{
	PC pC;

	*pVal = strtod( str, &pC );

	if( pC == str || *pC != '\0' )
		return false;

	return true;
}

B ParseFLT_MinMax ( PCC str, PFLT pVal, FLT mn, FLT mx )
{
	FLT flt;
	if( !ParseFLT( str, &flt ) )
		return false;

	if( flt < mn || flt > mx )
		return false;

	*pVal = flt;

	return true;
}
B ParseDBL_MinMax ( PCC str, PDBL pVal, DBL mn, DBL mx )
{
	DBL dbl;
	if( !ParseDBL( str, &dbl ) )
		return false;

	if( dbl < mn || dbl > mx )
		return false;

	*pVal = dbl;

	return true;
}


B SanitizeFP ( FP * pVal, FP mn, FP mx )
{
	if( isless( *pVal, mn) )
	{
		*pVal = mn;
		return true;
	}

	if( isgreater( *pVal, mx ) )
	{
		*pVal = mx;
		return true;
	}

	return false;
}

B SanitizeUI ( UI * pVal, UI mn, UI mx )
{
	if( *pVal < mn )
	{
		*pVal = mn;
		return true;
	}

	if( *pVal > mx )
	{
		*pVal = mx;
		return true;
	}

	return false;
}

B SanitizeU16 ( U16 * pVal, U16 mn, U16 mx )
{
	if( *pVal < mn )
	{
		*pVal = mn;
		return true;
	}

	if ( *pVal > mx )
	{
		*pVal = mx;
		return true;
	}

	return false;
}

B SanitizeU32 ( U32 * pVal, U32 mn, U32 mx )
{
	if( *pVal < mn )
	{
		*pVal = mn;
		return true;
	}

	if ( *pVal > mx )
	{
		*pVal = mx;
		return true;
	}

	return false;
}

B ParseSanitizeFP ( PCC  str, PFP pVal, FP mn, FP mx )
{
	ParseFLT( str, pVal );
	return SanitizeFP( pVal, mn, mx );
}

B ParseSanitizeUI ( PCC  str, PUI pVal, UI mn, UI mx )
{
	ParseUI( str, pVal, 10 );
	return SanitizeUI( pVal, mn, mx );
}

B ParseSanitizeU32 ( PCC  str, PU32 pVal, U32 mn, U32 mx )
{
	ParseUL( str, (PUL)pVal, 10 );
	return SanitizeU32( pVal, mn, mx );
}

UI AbsDifference ( UI a, UI b )
{
	SI diff = a - b;

	return abs( diff );
}

static CFP mIdx[FP_DIG+2] = {
	(FP)1				,(FP)10				,(FP)100			,(FP)1000,
	(FP)10000			,(FP)100000			,(FP)1000000		,(FP)10000000,
#if FP_BITS	== 64
	(FP)100000000		,(FP)1000000000		,(FP)10000000000	,(FP)100000000000,
	(FP)1000000000000	,(FP)10000000000000	,(FP)100000000000000,(FP)1000000000000000,
#endif
};

FP FpFixDecimalDigits ( FP val, UI n )
{
	FP mVal;

	SanitizeUI( &n, 0, FP_DIG+1 );

	mVal = mIdx[n];

	return FpRound( val * mVal ) / mVal;
}

PFP FpCopyArray ( PFP pTo, PCFP pFr, UI cnt )
{
	return memcpy( pTo, pFr, sizeof(FP)*cnt );
}

PFP FpCopyFixDecArray ( PFP pTo, PCFP pFr, UI cnt, UI dig )
{
	PFP pRet = pTo;
	FP mVal;

	SanitizeUI( &dig, 0, FP_DIG+1 );

	mVal = mIdx[dig];

	for( UI i=0; i < cnt; ++i )
		*pTo++ = FpRound(*pFr++ * mVal) / mVal;

	return pRet;
}

FP FpCmpArray ( PCFP pF1, PCFP pF2, UI cnt )
{
	for( UI i=0; i < cnt; ++i, pF1++, pF2++ )
		if( *pF1 != *pF2 )
			return *pF1 - *pF2;

	return (FP)0;
}

FP FpMinArray ( PCFP pF, UI cnt )
{
	FP mn = *pF++;

  	UI i;
	for( i = 0; i < cnt-1; ++i, ++pF )
		if( mn != FpMin( mn, *pF ) )
			mn =  *pF;

	return mn;
}

FP FpMaxArray ( PCFP pF, UI cnt )
{
	FP mx = *pF++;

  	UI i;
	for( i = 0; i < cnt-1; ++i, ++pF )
		if( mx != FpMax( mx, *pF ) )
			mx =  *pF;

	return mx;
}

FP FpRandomMinMax( FP mn, FP mx )
{
	FP rnd = (FP)((FP)1.0/((FP)RAND_MAX))*(FP)rand();
	return mn + (mx-mn)*rnd;
}

FP DifferenceRatio ( FP denom, FP num )
{
	FP	diff, diffRatio;

	diff = denom - num;

	if( !isnormal(denom) )
		denom = (FP)1.0;

	diffRatio = diff / denom;

	return diffRatio;
}

FP AbsDifferenceRatio ( FP denom, FP num )
{
	FP	diff, diffRatio;

	denom	= FpAbs( denom );
	num		= FpAbs( num );
	diff	= denom - num;
	diff	= FpAbs( diff );

	if( !isgreater(denom, (FP)0.0) )
		denom = (FP)1.0;

	diffRatio = diff / denom;

	return diffRatio;
}

FP Ratio ( FP denom, FP num )
{
	if( !isnormal(denom) )
		denom = (FP)1.0;

	return num / denom;
}
