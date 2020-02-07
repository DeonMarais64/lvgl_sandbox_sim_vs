#ifndef _COMUTILS_H_
#define _COMUTILS_H_

#include "C-Types.h"
#include <string.h>

extern CC   hexNib[];
extern U8	HexNibVal	( U8 nib );
static inline C HexNib	( U8 c )
{
	return hexNib[c&0x0f];
}

/* String Find functions.                 */

extern PCC  StrFirstDigit   ( PCC s );

/* String Transformation functions.       */

extern C    AlphaNumRotN    ( C c, S8 n );
extern C    AlphaRotN       ( C c, S8 n );
extern C    NumRotN         ( C c, S8 n );
extern C    AsciiRotN       ( C c, S8 n );

extern V    StrRemoveChar   ( PC s, C  c );
extern V    StrReplaceChar  ( PC s, C frc, C toc );

extern U32  StrNumToInt     ( PC s );
extern V    StrReverse      ( PC s );
extern V    StrShift        ( PC s, S8 n );

/* String Conversion functions.           */

extern PC   StrToLower      ( PC s );
extern PC   StrToUpper      ( PC s );

/* String Compare functions.              */

extern PCC  StrChrAnyCase   ( PCC s , I c );
extern PCC  StrCmp          ( PCC s1, PCC s2 );
extern PCC  StrCmpAnyCase   ( PCC s1, PCC s2 );
extern PCC  StrStr          ( PCC s1, PCC s2 );
extern PCC  StrStrAnyCase   ( PCC s1, PCC s2 );
extern PCC  StrNCmpN        ( PCC s1, PCC s2, ST s2l );
extern PCC  StrNCmpNAnyCase ( PCC s1, PCC s2, ST s2l );

#if 1
#define STR_N_CMP(s1,s2)            StrNCmpN( (s1), (s2), strlen(s2) )
#define StrNCmp(s1,s2)              StrNCmpN( (s1), (s2), strlen(s2) )
#define STR_N_CMP_ANY_CASE(s1,s2)   StrNCmpNAnyCase( (s1), (s2), strlen(s2) )
#define StrNCmpAnyCase(s1,s2)       StrNCmpNAnyCase( (s1), (s2), strlen(s2) )
#else
#define STR_N_CMP(s1,s2)            StrNCmpN( (s1), (s2), sizeof(s2)-1 )
#define StrNCmp(s1,s2)              StrNCmpN( (s1), (s2), (sizeof(s2)==sizeof(PC)) ? strlen(s2) : sizeof(s2)-1 )
#define STR_N_CMP_ANY_CASE(s1,s2)   StrNCmpNAnyCase( (s1), (s2), sizeof(s2)-1 )
#define StrNCmpAnyCase(s1,s2)       StrNCmpNAnyCase( (s1), (s2), (sizeof(s2)==sizeof(PC)) ? strlen(s2) : sizeof(s2)-1 )
#endif

/* String copy functions.                 */

extern PC   StrCpy       ( PC s1, PCC s2 );
extern PC   StrNCpy      ( PC s1, PCC s2, ST s2l );

/* String to Number conversion functions. */

extern UI   atoU    	( PCC s );
extern U32  atoU32  	( PCC s );
extern U64  atoU64  	( PCC s );
extern U8	axtoU8		( PCC hex );

extern UI   StrToU  ( PC* s );
extern U32  StrToU32( PC* s );
extern U64  StrToU64( PC* s );

/* Number to String conversion functions. */
//#define     itoa    ltoa
#define UTILS_STR_USE_XTOA 0
#if UTILS_STR_USE_XTOA
extern PC   ltoa    ( S32 n, PC s, I base );
extern PC   lltoa   ( S64 n, PC s, I base );
#endif
#define     IToA    LToA
extern PC   LToA    ( S32 n, PC s) ;
extern PC   LLToA   ( S64 n, PC s );

/* String Search functions. */

extern UI GetIdFrZzStrAnyCase	( PCC pZzStr, PCC pPrmStr, UI maxStrId );
extern B  GetIdFrStrLstAnyCase	( PUI pId, PCC *pStrLst, PCC pPrmStr, UI lstCnt );


#endif
