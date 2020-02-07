#include "utilsStr.h"
#include "C99libs.h"

//CC hexNib[16] = "0123456789ABCDEF";
CC hexNib[16] = "0123456789abcdef";

U8 HexNibVal ( U8 nib )
{
	if( (nib >= '0') && (nib <= '9') )
		return nib - '0';
	else
	{
//		nib = tolower( nib );
		nib |= 0x20;

		return (nib >= 'a') && ( nib <= 'f') ? nib - 'a' + 10 : 0;
	}
}

/**
-----------------------------------------------------------------------------------------------------------------------------------
Alphabet, and Alpha numeric character rotation functions.
*/

C AlphaRotN ( C c, S8 n )
{
    C   min, max;

    if( (c >= 'A') && (c <= 'Z') )
        min = 'A', max = 'Z';
    else if( (c >= 'a') && (c <= 'z') )
        min = 'a', max = 'z';
    else
        return c;

    {
        U8  no = (n >= 0) ? n : -n;
        c += (n >= 0) ? no % 26 : - (no % 26);
    }

    if( c < min)
        c += 26;
    else if( c > max)
        c -= 26;

    return c;
}

C NumRotN ( C c, S8 n)
{
    if( (c >= '0') && (c <= '9') )
    {
        U8  no = (n >= 0) ? n : -n;
        c += (n >= 0) ? no % 10 : - (no % 10);
    }
    else
        return c;

    if( c < '0')
        c += 10;
    else if( c > '9')
        c -= 10;

    return c;
}

C AlphaNumRotN ( C c, S8 n )
{
    C   min, max, maxRot;

    if( (c >= '0') && (c <= '9') )
        min = '0', max = '9', maxRot = 10;
    else if( (c >= 'A') && (c <= 'Z') )
        min = 'A', max = 'Z', maxRot = 26;
    else if( (c >= 'a') && (c <= 'z') )
        min = 'a', max = 'z', maxRot = 26;
    else
        return c;

    {
        U8  no = (n >= 0) ? n : -n;
        c += (n >= 0) ? no % maxRot : - (no % maxRot);
    }

    if( c < min)
        c += maxRot;
    else if( c > max)
        c -= maxRot;

    return c;
}

/**
-----------------------------------------------------------------------------------------------------------------------------------
Ascii rot
*/

C AsciiRotN ( C c, S8 n)
{
    return c + n;
}

/**
-----------------------------------------------------------------------------------------------------------------------------------
USSD response handling
*/

C * StrToLower ( C * sp)
{
    C *cp;

    for( cp = sp; *cp; ++cp)
        *cp = tolower( *cp);

    return sp;
}

C * StrToUpper ( C * sp)
{
    C *cp;

    for( cp = sp; *cp; ++cp)
        *cp = toupper( *cp);

    return sp;
}

void StrReverse ( C * s)
{
	int i;
	ST j;
    C c;

    for (i = 0, j = strlen(s)-1; i<j; i++, j--)
    {
        c    = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}

/**
-----------------------------------------------------------------------------------------------------------------------------------
String utility functions, some of these destroy the string.
*/

/*
    Remove all instances of a C in a string;
    StrRemoveChar( "1234..5678", '.') =>   "12345678"
*/
V StrRemoveChar ( PC s, C c )
{
    for( ; *s ; )
        if( *s == c )
            strcpy( s, s+1 );
        else
            ++s;
}

V StrReplaceChar ( PC s, C frc, C toc )
{
    for( ; *s ; )
        if( *s == frc )
                *s++ = toc;
            else
                ++s;
}

PCC StrFirstDigit ( PCC s )
{
    for( ; *s; ++s )
        if( isdigit(*s) )
            break;

    return s;
}

U32 StrNumToInt ( PC s )
{
    if( !(s = (PC)StrFirstDigit(s)) )
       return 0;

    StrRemoveChar( s, '.' );

    return atoi(s);
}

// Shift the string n characters to the right
V StrShift ( PC s, S8 n )
{
    C * sc = s;
    C * sn;

    while( *s ) s++; // Find end of string
    sn = s+n;
    do {
        *sn-- = *s--;
    } while( s >= sc );
}

/**
-----------------------------------------------------------------------------------------------------------------------------------
String compare functions.
These Return the position of the trailing NULL. Not the target string.
*/

#if 0
PC StrNCmp ( PCC s, C * s1)
{
    size_t s1l  = strlen( s1 );

    if( !strncmp(s, s1, s1l) )
        return (C *)(s+s1l);
    else
        return NULL;
}
#endif

PCC StrChrAnyCase ( PCC s, I c )
{
    C ch = toupper( (C)c );

    for( ; toupper(*s) != ch; ++s )
        if( *s == '\0' )
            return NULL;

    return s;
}

PCC StrCmp ( PCC s, PCC mts )
{
    size_t mtsl = strlen(mts);

    if( !strcmp( s, mts) )
        return s + mtsl;
    else
        return (PCC)NULL;
}

PCC StrCmpAnyCase ( PCC s1, PCC s2 )
{
    for( ; *s1 ; ++s1, ++s2 )
    {
        C c1 = *s1, c2 = *s2;
        if( (c1 >= 'A') && (c1 <= 'Z') ) c1 += 'a' - 'A';
        if( (c2 >= 'A') && (c2 <= 'Z') ) c2 += 'a' - 'A';
        if( c1 != c2 )
            return NULL;
    }
    return (*s1 == '\0') && (*s2 == '\0') ? s1 : NULL;
}

PCC StrStr ( PCC s, PCC mts )
{
    size_t mtsl = 0;

    if( (s = strstr(s, mts)) != NULL )
        mtsl = strlen( mts );

    return s + mtsl;
}

PCC StrStrAnyCase ( PCC s1, PCC s2 )
{
    if( *s2 == '\0' )
        return s1;

    for( ;(s1 = StrChrAnyCase(s1, *s2)) != 0; ++s1 )
    {
        const C *sc1, *sc2;

        for( sc1 = s1+1, sc2 = s2; ; ++sc1 )
            if( *++sc2 == '\0' )
                return s1;
            else if( toupper(*sc1) != toupper(*sc2) )
                break;
    }

    return NULL;
}

PCC StrNCmpN ( PCC s1, PCC s2, size_t s2l )
{	/* Returns end of string or NULL */
    if( !strncmp(s1, s2, s2l) )
        return s1 + s2l;
    else
        return (PCC)NULL;
}

PCC StrNCmpNAnyCase ( PCC s1, PCC s2, size_t s2l )
{ 	/* Returns end of string or NULL */
    for( ; *s1 && s2l ; ++s1, ++s2, --s2l )
        if( toupper(*s1) != toupper(*s2) )
            return NULL;

    return s2l == 0 ? s1 : NULL;
}

/**
-----------------------------------------------------------------------------------------------------------------------------------
String copy functions.
These Return the position of the trailing NULL. Not the target string.
*/

PC StrCpy ( PC s1, PCC s2 )
{
    strcpy( s1, s2 );

    return s1 + strlen(s1);
}

/*
Like strncpy, except :
    1.  ALWAYS adds a trailing null character.
    2.  Returns the position of the trailing NULL. Not the target string.
*/

PC StrNCpy ( PC s1, PCC s2, size_t size )
{
    strncpy( s1, s2, size );
    s1[size] = '\0';

    return s1 + strlen(s1);
}

/**
-----------------------------------------------------------------------------------------------------------------------------------
String to number conversion functions.

Standard c string to number conversion functions are :-

double              atof     (const    char *);
int                 atoi     (const    char *);
long                atol     (const    char *);
long long           atoll    (const    char *);

float               strtof   (const    char *_Restrict,    char **_Restrict);
double              strtod   (const    char *_Restrict,    char **_Restrict);
long double         strtold  (const    char *_Restrict,    char **_Restrict);
long                strtol   (const    char *_Restrict,    char **_Restrict, int);
unsigned long       strtoul  (const    char *_Restrict,    char **_Restrict, int);
long long           strtoll  (const    char *_Restrict,    char **_Restrict, int);
unsigned long long  strtoull (const    char *_Restrict,    char **_Restrict, int);
intmax_t            strtoimax(const    char *_Restrict,    char **_Restrict, int);
uintmax_t           strtoumax(const    char *_Restrict,    char **_Restrict, int);
intmax_t            wcstoimax(const _Wchart *_Restrict, _Wchart **_Restrict, int);
uintmax_t           wcstoumax(const _Wchart *_Restrict, _Wchart **_Restrict, int);

*/

UI  StrToU ( PC *s )
{
    UI retval = 0;
/*
    while( isdigit(**s)){
        retval *= 10;
        retval += **s - '0';
        (*s)++;
    }
*/
    for( C c = **s; c >= '0' && c <='9'; ++(*s), c = **s )
        retval *= 10, retval += c - '0';

    return retval;
}

U32 StrToU32 ( PC *s )
{
    U32 retval = 0;

    for( C c = **s; c >= '0' && c <='9'; ++(*s), c = **s )
        retval *= 10, retval += c - '0';

    return retval;
}

U64 StrToU64 ( PC *s )
{
    U64 retval = 0;

    for( C c = **s; c >= '0' && c <='9'; ++(*s), c = **s )
        retval *= 10, retval += c - '0';

    return retval;
}

UI  atoU ( PCC s )
{
    UI retval = 0;
/*
    while( isdigit(*s)){
        retval *= 10;
        retval += *s - '0';
        s++;
    }
*/
    for( C c = *s; c >= '0' && c <='9'; c = *++s )
        retval *= 10, retval += c - '0';

    return retval;
}

U32 atoU32 ( PCC s )
{
    U32 retval = 0;

    for( C c = *s; c >= '0' && c <='9'; c = *++s )
        retval *= 10, retval += c - '0';

    return retval;
}

U64 atoU64 ( PCC s )
{
    U64 retval = 0;

    for( C c = *s; (c >= '0') && ( c <='9' ); c = *++s )
        retval *= 10, retval += c - '0';

    return retval;
}

U8 axtoU8 ( PCC hex )
{
	return (HexNibVal(hex[0]) << 4) | HexNibVal(hex[1]);
}


/**
-----------------------------------------------------------------------------------------------------------------------------------
Number to string conversion functions.
*/


/*
C * llnum2str( C *s, unsigned long long n)
{
    unsigned long long nc = n;

    do{
        s++;
        nc /= 10;
    }while( nc);

    *s = 0;

    do{
        *--s =  '0' + (n % 10);
        n /= 10;
    }while( n);

    return( s);
}
*/

#if UTILS_STR_USE_XTOA
PC ltoa ( S32 n, PC s, I base )
{
    S32         i, sign;
    ldiv_t      d;

    if( (base < 2) || (base > 16) )
    {
        s[0] = '\0';
        return s;
    }

/* Record sign                      */
    if( (sign = n) < 0 )
        n = -n;

    i = 0;
/* Generate digits in reverse order */
    do {
        d       = ldiv( n, base);
        s[i++]  = hexNib[d.rem];
    } while( (n = d.quot) > 0 );

    if (sign < 0)
        s[i++] = '-';
    s[i] = '\0';

    StrReverse(s);

    return s;
}

PC lltoa ( S64 n, PC s, I base )
{
    S64         i, sign;
    lldiv_t     d;

    if( (base < 2) || (base > 16) )
    {
        *s = '\0';
        return s;
    }

    if ((sign = n) < 0)
        n = -n;

    i = 0;
    do {
        d       = lldiv( n, base);
        s[i++]  = hexNib[ d.rem];
    } while ((n = d.quot) > 0);

    if (sign < 0)
        s[i++] = '-';
    s[i] = '\0';

    StrReverse(s);

    return s;
}
#endif
/* LToA == ltoa( n, s, 10) */
PC LToA ( S32 n, PC s )
{
    S32         i, sign;
    ldiv_t      d;

    if ((sign = n) < 0)
        n = -n;

    i = 0;
    do {
        d       = ldiv( n, 10);
        s[i++]  = (C)(d.rem + '0');
    } while ((n = d.quot) > 0);

    if (sign < 0)
        s[i++] = '-';
    s[i] = '\0';

    StrReverse(s);

    return s;
}

/* LLToA == lltoa( n, s, 10) */
PC LLToA ( S64 n, PC s )
{
    S64         i, sign;
    lldiv_t     d;

    if ((sign = n) < 0)
        n = -n;

    i = 0;
    do {
        d       = lldiv( n, 10);
        s[i++]  = (C)(d.rem + '0');
    } while ((n = d.quot) > 0);

    if (sign < 0)
        s[i++] = '-';
    s[i] = '\0';

    StrReverse(s);

    return s;
}

#if 0

// Deon. Check this, don't know if it works !!
/**
 *  C++ version 0.4 C * style "itoa":
 *  Written by Lukás Chmela
 *  Released under GPLv3.
 */
PC itoa( I value, PC result, I base );
PC itoa( I value, PC result, I base )
{
    if( base < 2 || base > 36 )
    {
        *result = '\0';
        return result;
    }

    C *ptr = result, *ptr1 = result, tmp_char;
    I tmp_value;

    do {
        tmp_value = value;
        value    /= base;
        *ptr++    = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz"[35+(tmp_value-value*base)];
    } while( value );

    if( tmp_value < 0 )
        *ptr++ = '-';
    *ptr-- = '\0';

    while( ptr1 < ptr )
    {
        tmp_char = *ptr;
        *ptr--   = *ptr1;
        *ptr1++  = tmp_char;
    }

    return result;
}

#endif

UI GetIdFrZzStrAnyCase ( PCC pZzStr, PCC pPrmStr, UI maxStrId )
{
	UI i;

	for( i = 0; *pZzStr && i <= maxStrId; ++i )
	{
		UI slen = (UI)strlen(pZzStr);
		if( StrNCmpAnyCase( pZzStr, pPrmStr ) )
			break;
		else
			pZzStr += slen + (UI)1;
	}

	return i;
}

B GetIdFrStrLstAnyCase ( PUI pId, PCC *pStrLst, PCC pPrmStr, UI lstCnt )
{
	for( UI i = 0; (i<lstCnt) && *pStrLst; ++i, ++pStrLst )
	{
		UI slen = (UI)strlen( *pStrLst );
//		if( StrCmpAnyCase( *pStrLst, pPrmStr ) )
		if( StrNCmpNAnyCase( *pStrLst, pPrmStr, slen ) )
		{
			*pId = i;
			return true;
		}
	}

	return false;
}

