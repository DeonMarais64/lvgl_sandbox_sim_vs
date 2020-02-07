/*
 * C-FPoint.h
 *
 * Auto Generated : Dec  8 2017
 *         Author : Deon Marais
 *
 * 1 Tab = 4 Spaces
 * See bottom of "C-Types.h" for type naming conventions
 */

#ifndef C_FPOINT_H
#define C_FPOINT_H

#include <float.h>
#include <math.h>

#include "C-Types.h"


#ifndef FP_BITS
#define FP_BITS			32
//#define FP_BITS			64
#endif

#if FP_BITS != 32 && FP_BITS != 64
#error "FP_BITS must be 32 or 64"
#endif


/*+ FLT		Type, Qualified and Pointers */
typedef float					FLT;
typedef const			FLT		CFLT;
typedef volatile		FLT		VFLT;
typedef volatile const	FLT		VCFLT;
typedef FLT
	*							PFLT,
	*const						CPFLT,
	*volatile					VPFLT,
	*volatile const				VCPFLT;
typedef CFLT
	*							PCFLT,
	*const						CPCFLT,
	*volatile					VPCFLT,
	*volatile const				VCPCFLT;
typedef VFLT
	*							PVFLT,
	*const						CPVFLT,
	*volatile					VPVFLT,
	*volatile const				VCPVFLT;
typedef VCFLT
	*							PVCFLT,
	*const						CPVCFLT,
	*volatile					VPVCFLT,
	*volatile const				VCPVCFLT;
/*- FLT */
/*+ DBL		Type, Qualified and Pointers */
typedef double					DBL;
typedef const			DBL		CDBL;
typedef volatile		DBL		VDBL;
typedef volatile const	DBL		VCDBL;
typedef DBL
	*							PDBL,
	*const						CPDBL,
	*volatile					VPDBL,
	*volatile const				VCPDBL;
typedef CDBL
	*							PCDBL,
	*const						CPCDBL,
	*volatile					VPCDBL,
	*volatile const				VCPCDBL;
typedef VDBL
	*							PVDBL,
	*const						CPVDBL,
	*volatile					VPVDBL,
	*volatile const				VCPVDBL;
typedef VCDBL
	*							PVCDBL,
	*const						CPVCDBL,
	*volatile					VPVCDBL,
	*volatile const				VCPVCDBL;
/*- DBL */
/*+ LDBL		Type, Qualified and Pointers */
typedef long double				LDBL;
typedef const			LDBL	CLDBL;
typedef volatile		LDBL	VLDBL;
typedef volatile const	LDBL	VCLDBL;
typedef LDBL
	*							PLDBL,
	*const						CPLDBL,
	*volatile					VPLDBL,
	*volatile const				VCPLDBL;
typedef CLDBL
	*							PCLDBL,
	*const						CPCLDBL,
	*volatile					VPCLDBL,
	*volatile const				VCPCLDBL;
typedef VLDBL
	*							PVLDBL,
	*const						CPVLDBL,
	*volatile					VPVLDBL,
	*volatile const				VCPVLDBL;
typedef VCLDBL
	*							PVCLDBL,
	*const						CPVCLDBL,
	*volatile					VPVCLDBL,
	*volatile const				VCPVCLDBL;
/*- LDBL */
/*+ FP32		Type, Qualified and Pointers */
typedef float					FP32;
typedef const			FP32	CFP32;
typedef volatile		FP32	VFP32;
typedef volatile const	FP32	VCFP32;
typedef FP32
	*							PFP32,
	*const						CPFP32,
	*volatile					VPFP32,
	*volatile const				VCPFP32;
typedef CFP32
	*							PCFP32,
	*const						CPCFP32,
	*volatile					VPCFP32,
	*volatile const				VCPCFP32;
typedef VFP32
	*							PVFP32,
	*const						CPVFP32,
	*volatile					VPVFP32,
	*volatile const				VCPVFP32;
typedef VCFP32
	*							PVCFP32,
	*const						CPVCFP32,
	*volatile					VPVCFP32,
	*volatile const				VCPVCFP32;
/*- FP32 */
/*+ FP64		Type, Qualified and Pointers */
typedef double					FP64;
typedef const			FP64	CFP64;
typedef volatile		FP64	VFP64;
typedef volatile const	FP64	VCFP64;
typedef FP64
	*							PFP64,
	*const						CPFP64,
	*volatile					VPFP64,
	*volatile const				VCPFP64;
typedef CFP64
	*							PCFP64,
	*const						CPCFP64,
	*volatile					VPCFP64,
	*volatile const				VCPCFP64;
typedef VFP64
	*							PVFP64,
	*const						CPVFP64,
	*volatile					VPVFP64,
	*volatile const				VCPVFP64;
typedef VCFP64
	*							PVCFP64,
	*const						CPVCFP64,
	*volatile					VPVCFP64,
	*volatile const				VCPVCFP64;
/*- FP64 */
/*+	FP	*/
#if FP_BITS == 32
typedef FP32					FP;
#elif FP_BITS == 64
typedef FP64					FP;
#endif
/*-	FP	*/
/*+ FP		Type, Qualified and Pointers */
typedef const			FP		CFP;
typedef volatile		FP		VFP;
typedef volatile const	FP		VCFP;
typedef FP
	*							PFP,
	*const						CPFP,
	*volatile					VPFP,
	*volatile const				VCPFP;
typedef CFP
	*							PCFP,
	*const						CPCFP,
	*volatile					VPCFP,
	*volatile const				VCPCFP;
typedef VFP
	*							PVFP,
	*const						CPVFP,
	*volatile					VPVFP,
	*volatile const				VCPVFP;
typedef VCFP
	*							PVCFP,
	*const						CPVCFP,
	*volatile					VPVCFP,
	*volatile const				VCPVCFP;
/*- FP */
/*+	FP Unions */
typedef union {
	FP32	fp;
	U32		b;
	struct {	/* (-1)^sign * 2^(exponent-127) * 1.mantissa  or (-1)^sign * 2^(-126) * 0.Mantissa if exponent == 0 */
		U32		mantissa	: 23;
		UI		exponent	: 8;
		UI		sign		: 1;
	};
} FP32U;
typedef union {
	FP64	fp;
	U64		b;
	struct {	/* (-1)^sign * 2^(exponent-1023) * 1.mantissa  or (-1)^sign * 2^(-1022) * 0.Mantissa if exponent == 0 */
		U64		mantissa	: 52;
		UI		exponent	: 11;
		UI		sign		: 1;
	};
} FP64U;
#define TYPE_FPU 0
#if TYPE_FPU
#if FP_BITS == 32
typedef FP32U					FPU;
#elif FP_BITS == 64
typedef FP64U					FPU;
#endif
#endif
/*-	FP Unions */
/*+ FP32U		Type, Qualified and Pointers */
typedef const			FP32U	CFP32U;
typedef volatile		FP32U	VFP32U;
typedef volatile const	FP32U	VCFP32U;
typedef FP32U
	*							PFP32U,
	*const						CPFP32U,
	*volatile					VPFP32U,
	*volatile const				VCPFP32U;
typedef CFP32U
	*							PCFP32U,
	*const						CPCFP32U,
	*volatile					VPCFP32U,
	*volatile const				VCPCFP32U;
typedef VFP32U
	*							PVFP32U,
	*const						CPVFP32U,
	*volatile					VPVFP32U,
	*volatile const				VCPVFP32U;
typedef VCFP32U
	*							PVCFP32U,
	*const						CPVCFP32U,
	*volatile					VPVCFP32U,
	*volatile const				VCPVCFP32U;
/*- FP32U */
/*+ FP64U		Type, Qualified and Pointers */
typedef const			FP64U	CFP64U;
typedef volatile		FP64U	VFP64U;
typedef volatile const	FP64U	VCFP64U;
typedef FP64U
	*							PFP64U,
	*const						CPFP64U,
	*volatile					VPFP64U,
	*volatile const				VCPFP64U;
typedef CFP64U
	*							PCFP64U,
	*const						CPCFP64U,
	*volatile					VPCFP64U,
	*volatile const				VCPCFP64U;
typedef VFP64U
	*							PVFP64U,
	*const						CPVFP64U,
	*volatile					VPVFP64U,
	*volatile const				VCPVFP64U;
typedef VCFP64U
	*							PVCFP64U,
	*const						CPVCFP64U,
	*volatile					VPVCFP64U,
	*volatile const				VCPVCFP64U;
/*- FP64U */
/*+ FPU		Type, Qualified and Pointers */
#if TYPE_FPU
typedef const			FPU		CFPU;
typedef volatile		FPU		VFPU;
typedef volatile const	FPU		VCFPU;
typedef FPU
	*							PFPU,
	*const						CPFPU,
	*volatile					VPFPU,
	*volatile const				VCPFPU;
typedef CFPU
	*							PCFPU,
	*const						CPCFPU,
	*volatile					VPCFPU,
	*volatile const				VCPCFPU;
typedef VFPU
	*							PVFPU,
	*const						CPVFPU,
	*volatile					VPVFPU,
	*volatile const				VCPVFPU;
typedef VCFPU
	*							PVCFPU,
	*const						CPVCFPU,
	*volatile					VPVCFPU,
	*volatile const				VCPVCFPU;
#endif
/*- FPU */
/*+	FP Properties	*/

/*
* MIN				- min normalized positive value
* MAX				- max value
* TRUE_MIN			- min positive value
* DECIMAL_DIG		- # decimal digits of rounding precision
* DIG				- # decimal digits of precision
* MIN_10_EXP		- min decimal exponent
* MAX_10_EXP		- max decimal exponent
* EPSILON			- smallest such that 1.0+EPSILON != 1.0
* HAS_SUBNORM		- subnormal number suppor, 0 or 1t
* MANT_DIG			- # of bits in mantissa
* RADIX				- exponent radix, 2
* MIN_EXP			- min binary exponent
* MAX_EXP			- max binary exponent
*/

#define FP32_MIN			FLT_MIN
#define FP32_MAX			FLT_MAX
#define FP32_TRUE_MIN		FLT_TRUE_MIN
#define FP32_DECIMAL_DIG	FLT_DECIMAL_DIG
#define FP32_DIG			FLT_DIG
#define FP32_MIN_10_EXP		FLT_MIN_10_EXP
#define FP32_MAX_10_EXP		FLT_MAX_10_EXP
#define FP32_EPSILON		FLT_EPSILON
#define FP32_HAS_SUBNORM	FLT_HAS_SUBNORM
#define FP32_MANT_DIG		FLT_MANT_DIG
#define FP32_RADIX			FLT_RADIX
#define FP32_MIN_EXP		FLT_MIN_EXP
#define FP32_MAX_EXP		FLT_MAX_EXP

#define FP64_MIN			DBL_MIN
#define FP64_MAX			DBL_MAX
#define FP64_TRUE_MIN		DBL_TRUE_MIN
#define FP64_DECIMAL_DIG	DBL_DECIMAL_DIG
#define FP64_DIG			DBL_DIG
#define FP64_MIN_10_EXP		DBL_MIN_10_EXP
#define FP64_MAX_10_EXP		DBL_MAX_10_EXP
#define FP64_EPSILON		DBL_EPSILON
#define FP64_HAS_SUBNORM	DBL_HAS_SUBNORM
#define FP64_MANT_DIG		DBL_MANT_DIG
#ifndef DBL_RADIX
#define DBL_RADIX	FLT_RADIX
#endif
#define FP64_RADIX			DBL_RADIX
#define FP64_MIN_EXP		DBL_MIN_EXP
#define FP64_MAX_EXP		DBL_MAX_EXP

#define FP_MIN				GLUE3( FP, FP_BITS, _MIN )
#define FP_MAX				GLUE3( FP, FP_BITS, _MAX )
#define FP_TRUE_MIN			GLUE3( FP, FP_BITS, _TRUE_MIN )
#define FP_DECIMAL_DIG		GLUE3( FP, FP_BITS, _DECIMAL_DIG )
#define FP_DIG				GLUE3( FP, FP_BITS, _DIG )
#define FP_MIN_10_EXP		GLUE3( FP, FP_BITS, _MIN_10_EXP )
#define FP_MAX_10_EXP		GLUE3( FP, FP_BITS, _MAX_10_EXP )
#define FP_EPSILON			GLUE3( FP, FP_BITS, _EPSILON )
#define FP_HAS_SUBNORM		GLUE3( FP, FP_BITS, _HAS_SUBNORM )
#define FP_MANT_DIG			GLUE3( FP, FP_BITS, _MANT_DIG )
#define FP_RADIX			GLUE3( FP, FP_BITS, _RADIX )
#define FP_MIN_EXP			GLUE3( FP, FP_BITS, _MIN_EXP )
#define FP_MAX_EXP			GLUE3( FP, FP_BITS, _MAX_EXP )

/*-	FP Properties	*/

/*+	Definition of useful mathematical constants	*/

/*
* M_E			- e
* M_LOG2E		- log2(e)
* M_LOG10E		- log10(e)
* M_LN2			- ln(2)
* M_LN10		- ln(10)
* M_PI			- pi
* M_PI_2		- pi/2
* M_PI_4		- pi/4
* M_1_PI		- 1/pi
* M_2_PI		- 2/pi
* M_2_SQRTPI	- 2/sqrt(pi)
* M_SQRT2		- sqrt(2)
* M_SQRT1_2		- 1/sqrt(2)
* M_RADIAN		- 180/pi
* M_RADIAN_2	- 90/pi
*/

/* Reference values based on long doubles */
#define M_E_FP128			2.7182818284590452353602874713527l
#define M_LOG2E_FP128		1.4426950408889634073599246810019l
#define M_LOG10E_FP128		0.43429448190325182765112891891661l
#define M_LN2_FP128			0.69314718055994530941723212145818l
#define M_LN10_FP128		2.3025850929940456840179914546844l
#define M_PI_FP128			3.1415926535897932384626433832795l
#define M_PI_2_FP128		1.5707963267948966192313216916398l
#define M_PI_4_FP128		0.7853981633974483096161566084581988l
#define M_1_PI_FP128		0.31830988618379067153776752674503l
#define M_2_PI_FP128		0.6366197723675813430758134307553505349006l
#define M_2_SQRTPI_FP128	1.1283791670955125738961589031215l
#define M_SQRT2_FP128		1.4142135623730950488016887242097l
#define M_SQRT1_2_FP128		0.70710678118654752440084436210485l
#define M_RADIAN_FP128		57.295779513082320876798154814105l
#define M_RADIAN_2_FP128	(M_RADIAN_FP128/2.0l)

/* 32 Bit Values */
#define M_E_FP32			((FP32)M_E_FP128)
#define M_LOG2E_FP32		((FP32)M_LOG2E_FP128)
#define M_LOG10E_FP32		((FP32)M_LOG10E_FP128)
#define M_LN2_FP32			((FP32)M_LN2_FP128)
#define M_LN10_FP32			((FP32)M_LN10_FP128)
#define M_PI_FP32			((FP32)M_PI_FP128)
#define M_PI_2_FP32			((FP32)M_PI_2_FP128)
#define M_PI_4_FP32			((FP32)M_PI_4_FP128)
#define M_1_PI_FP32			((FP32)M_1_PI_FP128)
#define M_2_PI_FP32			((FP32)M_2_PI_FP128)
#define M_2_SQRTPI_FP32		((FP32)M_2_SQRTPI_FP128)
#define M_SQRT2_FP32		((FP32)M_SQRT2_FP128)
#define M_SQRT1_2_FP32		((FP32)M_SQRT1_2_FP128)
#define M_RADIAN_FP32		((FP32)M_RADIAN_FP128)
#define M_RADIAN_2_FP32		((FP32)M_RADIAN_2_FP128)

/* 64 Bit Values */
#define M_E_FP64			((FP64)M_E_FP128)
#define M_LOG2E_FP64		((FP64)M_LOG2E_FP128)
#define M_LOG10E_FP64		((FP64)M_LOG10E_FP128)
#define M_LN2_FP64			((FP64)M_LN2_FP128)
#define M_LN10_FP64			((FP64)M_LN10_FP128)
#define M_PI_FP64			((FP64)M_PI_FP128)
#define M_PI_2_FP64			((FP64)M_PI_2_FP128)
#define M_PI_4_FP64			((FP64)M_PI_4_FP128)
#define M_1_PI_FP64			((FP64)M_1_PI_FP128)
#define M_2_PI_FP64			((FP64)M_2_PI_FP128)
#define M_2_SQRTPI_FP64		((FP64)M_2_SQRTPI_FP128)
#define M_SQRT2_FP64		((FP64)M_SQRT2_FP128)
#define M_SQRT1_2_FP64		((FP64)M_SQRT1_2_FP128)
#define M_RADIAN_FP64		((FP64)M_RADIAN_FP128)
#define M_RADIAN_2_FP64		((FP64)M_RADIAN_2_FP128)

/* Project Values */
#define M_E_FP				((FP)M_E_FP128)
#define M_LOG2E_FP			((FP)M_LOG2E_FP128)
#define M_LOG10E_FP			((FP)M_LOG10E_FP128)
#define M_LN2_FP			((FP)M_LN2_FP128)
#define M_LN10_FP			((FP)M_LN10_FP128)
#define M_PI_FP				((FP)M_PI_FP128)
#define M_PI_2_FP			((FP)M_PI_2_FP128)
#define M_PI_4_FP			((FP)M_PI_4_FP128)
#define M_1_PI_FP			((FP)M_1_PI_FP128)
#define M_2_PI_FP			((FP)M_2_PI_FP128)
#define M_2_SQRTPI_FP		((FP)M_2_SQRTPI_FP128)
#define M_SQRT2_FP			((FP)M_SQRT2_FP128)
#define M_SQRT1_2_FP		((FP)M_SQRT1_2_FP128)
#define M_RADIAN_FP			((FP)M_RADIAN_FP128)
#define M_RADIAN_2_FP		((FP)M_RADIAN_2_FP128)

/* Values defined in some but not all math.h header files */
#ifndef M_E
#define M_E					GLUE3( M_E, _FP, 64 )
#define M_LOG2E				GLUE3( M_LOG2E, _FP, 64 )
#define M_LOG10E			GLUE3( M_LOG10E, _FP, 64 )
#define M_LN2				GLUE3( M_LN2, _FP, 64 )
#define M_LN10				GLUE3( M_LN10, _FP, 64 )
#define M_PI				GLUE3( M_PI, _FP, 64 )
#define M_PI_2				GLUE3( M_PI_2, _FP, 64 )
#define M_PI_4				GLUE3( M_PI_4, _FP, 64 )
#define M_1_PI				GLUE3( M_1_PI, _FP, 64 )
#define M_2_PI				GLUE3( M_2_PI, _FP, 64 )
#define M_2_SQRTPI			GLUE3( M_2_SQRTPI, _FP, 64 )
#define M_SQRT2				GLUE3( M_SQRT2, _FP, 64 )
#define M_SQRT1_2			GLUE3( M_SQRT1_2, _FP, 64 )
#endif
#define M_RADIAN			GLUE3( M_RADIAN, _FP, 64 )
#define M_RADIAN_2			GLUE3( M_RADIAN_2, _FP, 64 )

/*-	Definition of useful mathematical constants	*/

/*+	Inline Functions	*/
inline FP32 Fp32Abs ( FP32 n );
inline FP32 Fp32Abs ( FP32 n )
{
	return isless( n, (FP32)0.0 ) ? -n : n;
}
inline FP64 Fp64Abs ( FP64 n );
inline FP64 Fp64Abs ( FP64 n )
{
	return isless( n, (FP64)0.0 ) ? -n : n;
}
inline FP FpAbs ( FP n );
inline FP FpAbs ( FP n )
{
	return isless( n, (FP)0.0 ) ? -n : n;
}
inline FP32 Fp32Min ( FP32 a, FP32 b );
inline FP32 Fp32Min ( FP32 a, FP32 b )
{
	return islessequal( a, b ) ? a : b;
}
inline FP32 Fp32Max ( FP32 a, FP32 b );
inline FP32 Fp32Max ( FP32 a, FP32 b )
{
	return isgreaterequal( a, b ) ? a : b;
}
inline FP64 Fp64Min ( FP64 a, FP64 b );
inline FP64 Fp64Min ( FP64 a, FP64 b )
{
	return islessequal( a, b ) ? a : b;
}
inline FP64 Fp64Max ( FP64 a, FP64 b );
inline FP64 Fp64Max ( FP64 a, FP64 b )
{
	return isgreaterequal( a, b ) ? a : b;
}
inline FP FpMin ( FP a, FP b );
inline FP FpMin ( FP a, FP b )
{
	return islessequal( a, b ) ? a : b;
}
inline FP FpMax ( FP a, FP b );
inline FP FpMax ( FP a, FP b )
{
	return isgreaterequal( a, b ) ? a : b;
}
inline FP FpRound ( FP v );
inline FP FpRound ( FP v )
{
#if FP_BITS==32
	return roundf( v );
#elif FP_BITS==64
	return round( v );
#endif
}
#if 0
inline FP FpAbs ( FP v );
inline FP FpAbs ( FP v )
{
#if FP_BITS==32
	return fabsf( v );
#elif FP_BITS==64
	return fabs( v );
#endif
}
#endif
/*-	Inline Functions	*/


#endif /* C_FPOINT_H	*/
