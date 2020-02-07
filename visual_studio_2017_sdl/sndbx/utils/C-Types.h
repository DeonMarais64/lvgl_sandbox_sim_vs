/*
 * C-Types.h
 *
 * Auto Generated : Nov 27 2017
 *         Author : Deon Marais
 *
 * 1 Tab = 4 Spaces
 * See bottom of file for type naming conventions
 */

#ifndef C_TYPES_H
#define C_TYPES_H

#include <stdbool.h>
#include <inttypes.h>
#include <limits.h>

#include "pputils.h"

/*+ H		Type, Qualified and Pointers */
typedef int						H;
typedef const			H		CH;
typedef volatile		H		VH;
typedef volatile const	H		VCH;
typedef H
	*							PH,
	*const						CPH,
	*volatile					VPH,
	*volatile const				VCPH;
typedef CH
	*							PCH,
	*const						CPCH,
	*volatile					VPCH,
	*volatile const				VCPCH;
typedef VH
	*							PVH,
	*const						CPVH,
	*volatile					VPVH,
	*volatile const				VCPVH;
typedef VCH
	*							PVCH,
	*const						CPVCH,
	*volatile					VPVCH,
	*volatile const				VCPVCH;
/*- H */
/*+ ST		Type, Qualified and Pointers */
typedef size_t					ST;
typedef const			ST		CST;
typedef volatile		ST		VST;
typedef volatile const	ST		VCST;
typedef ST
	*							PST,
	*const						CPST,
	*volatile					VPST,
	*volatile const				VCPST;
typedef CST
	*							PCST,
	*const						CPCST,
	*volatile					VPCST,
	*volatile const				VCPCST;
typedef VST
	*							PVST,
	*const						CPVST,
	*volatile					VPVST,
	*volatile const				VCPVST;
typedef VCST
	*							PVCST,
	*const						CPVCST,
	*volatile					VPVCST,
	*volatile const				VCPVCST;
/*- ST */
/*+ PD		Type, Qualified and Pointers */
typedef ptrdiff_t				PD;
typedef const			PD		CPD;
typedef volatile		PD		VPD;
typedef volatile const	PD		VCPD;
typedef PD
	*							PPD,
	*const						CPPD,
	*volatile					VPPD,
	*volatile const				VCPPD;
typedef CPD
	*							PCPD,
	*const						CPCPD,
	*volatile					VPCPD,
	*volatile const				VCPCPD;
typedef VPD
	*							PVPD,
	*const						CPVPD,
	*volatile					VPVPD,
	*volatile const				VCPVPD;
typedef VCPD
	*							PVCPD,
	*const						CPVCPD,
	*volatile					VPVCPD,
	*volatile const				VCPVCPD;
/*- PD */
/*+ SIPTR		Type, Qualified and Pointers */
typedef intptr_t				SIPTR;
typedef const			SIPTR	CSIPTR;
typedef volatile		SIPTR	VSIPTR;
typedef volatile const	SIPTR	VCSIPTR;
typedef SIPTR
	*							PSIPTR,
	*const						CPSIPTR,
	*volatile					VPSIPTR,
	*volatile const				VCPSIPTR;
typedef CSIPTR
	*							PCSIPTR,
	*const						CPCSIPTR,
	*volatile					VPCSIPTR,
	*volatile const				VCPCSIPTR;
typedef VSIPTR
	*							PVSIPTR,
	*const						CPVSIPTR,
	*volatile					VPVSIPTR,
	*volatile const				VCPVSIPTR;
typedef VCSIPTR
	*							PVCSIPTR,
	*const						CPVCSIPTR,
	*volatile					VPVCSIPTR,
	*volatile const				VCPVCSIPTR;
/*- SIPTR */
/*+ UIPTR		Type, Qualified and Pointers */
typedef uintptr_t				UIPTR;
typedef const			UIPTR	CUIPTR;
typedef volatile		UIPTR	VUIPTR;
typedef volatile const	UIPTR	VCUIPTR;
typedef UIPTR
	*							PUIPTR,
	*const						CPUIPTR,
	*volatile					VPUIPTR,
	*volatile const				VCPUIPTR;
typedef CUIPTR
	*							PCUIPTR,
	*const						CPCUIPTR,
	*volatile					VPCUIPTR,
	*volatile const				VCPCUIPTR;
typedef VUIPTR
	*							PVUIPTR,
	*const						CPVUIPTR,
	*volatile					VPVUIPTR,
	*volatile const				VCPVUIPTR;
typedef VCUIPTR
	*							PVCUIPTR,
	*const						CPVCUIPTR,
	*volatile					VPVCUIPTR,
	*volatile const				VCPVCUIPTR;
/*- UIPTR */
/*+ V		Type, Qualified and Pointers */
//typedef void					V;
#define V void
typedef const			V		CV;
typedef volatile		V		VV;
typedef volatile const	V		VCV;
typedef V
	*							PV,
	*const						CPV,
	*volatile					VPV,
	*volatile const				VCPV;
typedef CV
	*							PCV,
	*const						CPCV,
	*volatile					VPCV,
	*volatile const				VCPCV;
typedef VV
	*							PVV,
	*const						CPVV,
	*volatile					VPVV,
	*volatile const				VCPVV;
typedef VCV
	*							PVCV,
	*const						CPVCV,
	*volatile					VPVCV,
	*volatile const				VCPVCV;
/*- V */
/*+ C		Type, Qualified and Pointers */
typedef char					C;
typedef const			C		CC;
typedef volatile		C		VC;
typedef volatile const	C		VCC;
typedef C
	*							PC,
	*const						CPC,
	*volatile					VPC,
	*volatile const				VCPC;
typedef CC
	*							PCC,
	*const						CPCC,
	*volatile					VPCC,
	*volatile const				VCPCC;
typedef VC
	*							PVC,
	*const						CPVC,
	*volatile					VPVC,
	*volatile const				VCPVC;
typedef VCC
	*							PVCC,
	*const						CPVCC,
	*volatile					VPVCC,
	*volatile const				VCPVCC;
/*- C */
/*+ SC		Type, Qualified and Pointers */
typedef signed char				SC;
typedef const			SC		CSC;
typedef volatile		SC		VSC;
typedef volatile const	SC		VCSC;
typedef SC
	*							PSC,
	*const						CPSC,
	*volatile					VPSC,
	*volatile const				VCPSC;
typedef CSC
	*							PCSC,
	*const						CPCSC,
	*volatile					VPCSC,
	*volatile const				VCPCSC;
typedef VSC
	*							PVSC,
	*const						CPVSC,
	*volatile					VPVSC,
	*volatile const				VCPVSC;
typedef VCSC
	*							PVCSC,
	*const						CPVCSC,
	*volatile					VPVCSC,
	*volatile const				VCPVCSC;
/*- SC */
/*+ UC		Type, Qualified and Pointers */
typedef unsigned char			UC;
typedef const			UC		CUC;
typedef volatile		UC		VUC;
typedef volatile const	UC		VCUC;
typedef UC
	*							PUC,
	*const						CPUC,
	*volatile					VPUC,
	*volatile const				VCPUC;
typedef CUC
	*							PCUC,
	*const						CPCUC,
	*volatile					VPCUC,
	*volatile const				VCPCUC;
typedef VUC
	*							PVUC,
	*const						CPVUC,
	*volatile					VPVUC,
	*volatile const				VCPVUC;
typedef VCUC
	*							PVCUC,
	*const						CPVCUC,
	*volatile					VPVCUC,
	*volatile const				VCPVCUC;
/*- UC */
/*+ WC		Type, Qualified and Pointers */
typedef wchar_t					WC;
typedef const			WC		CWC;
typedef volatile		WC		VWC;
typedef volatile const	WC		VCWC;
typedef WC
	*							PWC,
	*const						CPWC,
	*volatile					VPWC,
	*volatile const				VCPWC;
typedef CWC
	*							PCWC,
	*const						CPCWC,
	*volatile					VPCWC,
	*volatile const				VCPCWC;
typedef VWC
	*							PVWC,
	*const						CPVWC,
	*volatile					VPVWC,
	*volatile const				VCPVWC;
typedef VCWC
	*							PVCWC,
	*const						CPVCWC,
	*volatile					VPVCWC,
	*volatile const				VCPVCWC;
/*- WC */
/*+ S		Type, Qualified and Pointers */
typedef short					S;
typedef const			S		CS;
typedef volatile		S		VS;
typedef volatile const	S		VCS;
typedef S
	*							PS,
	*const						CPS,
	*volatile					VPS,
	*volatile const				VCPS;
typedef CS
	*							PCS,
	*const						CPCS,
	*volatile					VPCS,
	*volatile const				VCPCS;
typedef VS
	*							PVS,
	*const						CPVS,
	*volatile					VPVS,
	*volatile const				VCPVS;
typedef VCS
	*							PVCS,
	*const						CPVCS,
	*volatile					VPVCS,
	*volatile const				VCPVCS;
/*- S */
/*+ SS		Type, Qualified and Pointers */
typedef signed short			SS;
typedef const			SS		CSS;
typedef volatile		SS		VSS;
typedef volatile const	SS		VCSS;
typedef SS
	*							PSS,
	*const						CPSS,
	*volatile					VPSS,
	*volatile const				VCPSS;
typedef CSS
	*							PCSS,
	*const						CPCSS,
	*volatile					VPCSS,
	*volatile const				VCPCSS;
typedef VSS
	*							PVSS,
	*const						CPVSS,
	*volatile					VPVSS,
	*volatile const				VCPVSS;
typedef VCSS
	*							PVCSS,
	*const						CPVCSS,
	*volatile					VPVCSS,
	*volatile const				VCPVCSS;
/*- SS */
/*+ US		Type, Qualified and Pointers */
typedef unsigned short			US;
typedef const			US		CUS;
typedef volatile		US		VUS;
typedef volatile const	US		VCUS;
typedef US
	*							PUS,
	*const						CPUS,
	*volatile					VPUS,
	*volatile const				VCPUS;
typedef CUS
	*							PCUS,
	*const						CPCUS,
	*volatile					VPCUS,
	*volatile const				VCPCUS;
typedef VUS
	*							PVUS,
	*const						CPVUS,
	*volatile					VPVUS,
	*volatile const				VCPVUS;
typedef VCUS
	*							PVCUS,
	*const						CPVCUS,
	*volatile					VPVCUS,
	*volatile const				VCPVCUS;
/*- US */
/*+ I		Type, Qualified and Pointers */
typedef int						I;
typedef const			I		CI;
typedef volatile		I		VI;
typedef volatile const	I		VCI;
typedef I
	*							PI,
	*const						CPI,
	*volatile					VPI,
	*volatile const				VCPI;
typedef CI
	*							PCI,
	*const						CPCI,
	*volatile					VPCI,
	*volatile const				VCPCI;
typedef VI
	*							PVI,
	*const						CPVI,
	*volatile					VPVI,
	*volatile const				VCPVI;
typedef VCI
	*							PVCI,
	*const						CPVCI,
	*volatile					VPVCI,
	*volatile const				VCPVCI;
/*- I */
/*+ SI		Type, Qualified and Pointers */
typedef signed int				SI;
typedef const			SI		CSI;
typedef volatile		SI		VSI;
typedef volatile const	SI		VCSI;
typedef SI
	*							PSI,
	*const						CPSI,
	*volatile					VPSI,
	*volatile const				VCPSI;
typedef CSI
	*							PCSI,
	*const						CPCSI,
	*volatile					VPCSI,
	*volatile const				VCPCSI;
typedef VSI
	*							PVSI,
	*const						CPVSI,
	*volatile					VPVSI,
	*volatile const				VCPVSI;
typedef VCSI
	*							PVCSI,
	*const						CPVCSI,
	*volatile					VPVCSI,
	*volatile const				VCPVCSI;
/*- SI */
/*+ UI		Type, Qualified and Pointers */
typedef unsigned int			UI;
typedef const			UI		CUI;
typedef volatile		UI		VUI;
typedef volatile const	UI		VCUI;
typedef UI
	*							PUI,
	*const						CPUI,
	*volatile					VPUI,
	*volatile const				VCPUI;
typedef CUI
	*							PCUI,
	*const						CPCUI,
	*volatile					VPCUI,
	*volatile const				VCPCUI;
typedef VUI
	*							PVUI,
	*const						CPVUI,
	*volatile					VPVUI,
	*volatile const				VCPVUI;
typedef VCUI
	*							PVCUI,
	*const						CPVCUI,
	*volatile					VPVCUI,
	*volatile const				VCPVCUI;
/*- UI */
/*+ L		Type, Qualified and Pointers */
typedef long					L;
typedef const			L		CL;
typedef volatile		L		VL;
typedef volatile const	L		VCL;
typedef L
	*							PL,
	*const						CPL,
	*volatile					VPL,
	*volatile const				VCPL;
typedef CL
	*							PCL,
	*const						CPCL,
	*volatile					VPCL,
	*volatile const				VCPCL;
typedef VL
	*							PVL,
	*const						CPVL,
	*volatile					VPVL,
	*volatile const				VCPVL;
typedef VCL
	*							PVCL,
	*const						CPVCL,
	*volatile					VPVCL,
	*volatile const				VCPVCL;
/*- L */
/*+ SL		Type, Qualified and Pointers */
typedef signed long				SL;
typedef const			SL		CSL;
typedef volatile		SL		VSL;
typedef volatile const	SL		VCSL;
typedef SL
	*							PSL,
	*const						CPSL,
	*volatile					VPSL,
	*volatile const				VCPSL;
typedef CSL
	*							PCSL,
	*const						CPCSL,
	*volatile					VPCSL,
	*volatile const				VCPCSL;
typedef VSL
	*							PVSL,
	*const						CPVSL,
	*volatile					VPVSL,
	*volatile const				VCPVSL;
typedef VCSL
	*							PVCSL,
	*const						CPVCSL,
	*volatile					VPVCSL,
	*volatile const				VCPVCSL;
/*- SL */
/*+ UL		Type, Qualified and Pointers */
typedef unsigned long			UL;
typedef const			UL		CUL;
typedef volatile		UL		VUL;
typedef volatile const	UL		VCUL;
typedef UL
	*							PUL,
	*const						CPUL,
	*volatile					VPUL,
	*volatile const				VCPUL;
typedef CUL
	*							PCUL,
	*const						CPCUL,
	*volatile					VPCUL,
	*volatile const				VCPCUL;
typedef VUL
	*							PVUL,
	*const						CPVUL,
	*volatile					VPVUL,
	*volatile const				VCPVUL;
typedef VCUL
	*							PVCUL,
	*const						CPVCUL,
	*volatile					VPVCUL,
	*volatile const				VCPVCUL;
/*- UL */
/*+ LL		Type, Qualified and Pointers */
typedef long long				LL;
typedef const			LL		CLL;
typedef volatile		LL		VLL;
typedef volatile const	LL		VCLL;
typedef LL
	*							PLL,
	*const						CPLL,
	*volatile					VPLL,
	*volatile const				VCPLL;
typedef CLL
	*							PCLL,
	*const						CPCLL,
	*volatile					VPCLL,
	*volatile const				VCPCLL;
typedef VLL
	*							PVLL,
	*const						CPVLL,
	*volatile					VPVLL,
	*volatile const				VCPVLL;
typedef VCLL
	*							PVCLL,
	*const						CPVCLL,
	*volatile					VPVCLL,
	*volatile const				VCPVCLL;
/*- LL */
/*+ SLL		Type, Qualified and Pointers */
typedef signed long long		SLL;
typedef const			SLL		CSLL;
typedef volatile		SLL		VSLL;
typedef volatile const	SLL		VCSLL;
typedef SLL
	*							PSLL,
	*const						CPSLL,
	*volatile					VPSLL,
	*volatile const				VCPSLL;
typedef CSLL
	*							PCSLL,
	*const						CPCSLL,
	*volatile					VPCSLL,
	*volatile const				VCPCSLL;
typedef VSLL
	*							PVSLL,
	*const						CPVSLL,
	*volatile					VPVSLL,
	*volatile const				VCPVSLL;
typedef VCSLL
	*							PVCSLL,
	*const						CPVCSLL,
	*volatile					VPVCSLL,
	*volatile const				VCPVCSLL;
/*- SLL */
/*+ ULL		Type, Qualified and Pointers */
typedef unsigned long long		ULL;
typedef const			ULL		CULL;
typedef volatile		ULL		VULL;
typedef volatile const	ULL		VCULL;
typedef ULL
	*							PULL,
	*const						CPULL,
	*volatile					VPULL,
	*volatile const				VCPULL;
typedef CULL
	*							PCULL,
	*const						CPCULL,
	*volatile					VPCULL,
	*volatile const				VCPCULL;
typedef VULL
	*							PVULL,
	*const						CPVULL,
	*volatile					VPVULL,
	*volatile const				VCPVULL;
typedef VCULL
	*							PVCULL,
	*const						CPVCULL,
	*volatile					VPVCULL,
	*volatile const				VCPVCULL;
/*- ULL */
/*+ B		Type, Qualified and Pointers */
typedef bool					B;
typedef const			B		CB;
typedef volatile		B		VB;
typedef volatile const	B		VCB;
typedef B
	*							PB,
	*const						CPB,
	*volatile					VPB,
	*volatile const				VCPB;
typedef CB
	*							PCB,
	*const						CPCB,
	*volatile					VPCB,
	*volatile const				VCPCB;
typedef VB
	*							PVB,
	*const						CPVB,
	*volatile					VPVB,
	*volatile const				VCPVB;
typedef VCB
	*							PVCB,
	*const						CPVCB,
	*volatile					VPVCB,
	*volatile const				VCPVCB;
/*- B */
/*+ I8		Type, Qualified and Pointers */
typedef char					I8;
typedef const			I8		CI8;
typedef volatile		I8		VI8;
typedef volatile const	I8		VCI8;
typedef I8
	*							PI8,
	*const						CPI8,
	*volatile					VPI8,
	*volatile const				VCPI8;
typedef CI8
	*							PCI8,
	*const						CPCI8,
	*volatile					VPCI8,
	*volatile const				VCPCI8;
typedef VI8
	*							PVI8,
	*const						CPVI8,
	*volatile					VPVI8,
	*volatile const				VCPVI8;
typedef VCI8
	*							PVCI8,
	*const						CPVCI8,
	*volatile					VPVCI8,
	*volatile const				VCPVCI8;
/*- I8 */
/*+ SI8		Type, Qualified and Pointers */
typedef signed char				SI8;
typedef const			SI8		CSI8;
typedef volatile		SI8		VSI8;
typedef volatile const	SI8		VCSI8;
typedef SI8
	*							PSI8,
	*const						CPSI8,
	*volatile					VPSI8,
	*volatile const				VCPSI8;
typedef CSI8
	*							PCSI8,
	*const						CPCSI8,
	*volatile					VPCSI8,
	*volatile const				VCPCSI8;
typedef VSI8
	*							PVSI8,
	*const						CPVSI8,
	*volatile					VPVSI8,
	*volatile const				VCPVSI8;
typedef VCSI8
	*							PVCSI8,
	*const						CPVCSI8,
	*volatile					VPVCSI8,
	*volatile const				VCPVCSI8;
/*- SI8 */
/*+ UI8		Type, Qualified and Pointers */
typedef unsigned char			UI8;
typedef const			UI8		CUI8;
typedef volatile		UI8		VUI8;
typedef volatile const	UI8		VCUI8;
typedef UI8
	*							PUI8,
	*const						CPUI8,
	*volatile					VPUI8,
	*volatile const				VCPUI8;
typedef CUI8
	*							PCUI8,
	*const						CPCUI8,
	*volatile					VPCUI8,
	*volatile const				VCPCUI8;
typedef VUI8
	*							PVUI8,
	*const						CPVUI8,
	*volatile					VPVUI8,
	*volatile const				VCPVUI8;
typedef VCUI8
	*							PVCUI8,
	*const						CPVCUI8,
	*volatile					VPVCUI8,
	*volatile const				VCPVCUI8;
/*- UI8 */
/*+ I16		Type, Qualified and Pointers */
typedef S						I16;
typedef const			I16		CI16;
typedef volatile		I16		VI16;
typedef volatile const	I16		VCI16;
typedef I16
	*							PI16,
	*const						CPI16,
	*volatile					VPI16,
	*volatile const				VCPI16;
typedef CI16
	*							PCI16,
	*const						CPCI16,
	*volatile					VPCI16,
	*volatile const				VCPCI16;
typedef VI16
	*							PVI16,
	*const						CPVI16,
	*volatile					VPVI16,
	*volatile const				VCPVI16;
typedef VCI16
	*							PVCI16,
	*const						CPVCI16,
	*volatile					VPVCI16,
	*volatile const				VCPVCI16;
/*- I16 */
/*+ SI16		Type, Qualified and Pointers */
typedef SS						SI16;
typedef const			SI16	CSI16;
typedef volatile		SI16	VSI16;
typedef volatile const	SI16	VCSI16;
typedef SI16
	*							PSI16,
	*const						CPSI16,
	*volatile					VPSI16,
	*volatile const				VCPSI16;
typedef CSI16
	*							PCSI16,
	*const						CPCSI16,
	*volatile					VPCSI16,
	*volatile const				VCPCSI16;
typedef VSI16
	*							PVSI16,
	*const						CPVSI16,
	*volatile					VPVSI16,
	*volatile const				VCPVSI16;
typedef VCSI16
	*							PVCSI16,
	*const						CPVCSI16,
	*volatile					VPVCSI16,
	*volatile const				VCPVCSI16;
/*- SI16 */
/*+ UI16		Type, Qualified and Pointers */
typedef US						UI16;
typedef const			UI16	CUI16;
typedef volatile		UI16	VUI16;
typedef volatile const	UI16	VCUI16;
typedef UI16
	*							PUI16,
	*const						CPUI16,
	*volatile					VPUI16,
	*volatile const				VCPUI16;
typedef CUI16
	*							PCUI16,
	*const						CPCUI16,
	*volatile					VPCUI16,
	*volatile const				VCPCUI16;
typedef VUI16
	*							PVUI16,
	*const						CPVUI16,
	*volatile					VPVUI16,
	*volatile const				VCPVUI16;
typedef VCUI16
	*							PVCUI16,
	*const						CPVCUI16,
	*volatile					VPVCUI16,
	*volatile const				VCPVCUI16;
/*- UI16 */
/*+ S8		Type, Qualified and Pointers */
typedef int8_t					S8;
typedef const			S8		CS8;
typedef volatile		S8		VS8;
typedef volatile const	S8		VCS8;
typedef S8
	*							PS8,
	*const						CPS8,
	*volatile					VPS8,
	*volatile const				VCPS8;
typedef CS8
	*							PCS8,
	*const						CPCS8,
	*volatile					VPCS8,
	*volatile const				VCPCS8;
typedef VS8
	*							PVS8,
	*const						CPVS8,
	*volatile					VPVS8,
	*volatile const				VCPVS8;
typedef VCS8
	*							PVCS8,
	*const						CPVCS8,
	*volatile					VPVCS8,
	*volatile const				VCPVCS8;
/*- S8 */
/*+ U8		Type, Qualified and Pointers */
typedef uint8_t					U8;
typedef const			U8		CU8;
typedef volatile		U8		VU8;
typedef volatile const	U8		VCU8;
typedef U8
	*							PU8,
	*const						CPU8,
	*volatile					VPU8,
	*volatile const				VCPU8;
typedef CU8
	*							PCU8,
	*const						CPCU8,
	*volatile					VPCU8,
	*volatile const				VCPCU8;
typedef VU8
	*							PVU8,
	*const						CPVU8,
	*volatile					VPVU8,
	*volatile const				VCPVU8;
typedef VCU8
	*							PVCU8,
	*const						CPVCU8,
	*volatile					VPVCU8,
	*volatile const				VCPVCU8;
/*- U8 */
/*+ S16		Type, Qualified and Pointers */
typedef int16_t					S16;
typedef const			S16		CS16;
typedef volatile		S16		VS16;
typedef volatile const	S16		VCS16;
typedef S16
	*							PS16,
	*const						CPS16,
	*volatile					VPS16,
	*volatile const				VCPS16;
typedef CS16
	*							PCS16,
	*const						CPCS16,
	*volatile					VPCS16,
	*volatile const				VCPCS16;
typedef VS16
	*							PVS16,
	*const						CPVS16,
	*volatile					VPVS16,
	*volatile const				VCPVS16;
typedef VCS16
	*							PVCS16,
	*const						CPVCS16,
	*volatile					VPVCS16,
	*volatile const				VCPVCS16;
/*- S16 */
/*+ U16		Type, Qualified and Pointers */
typedef uint16_t				U16;
typedef const			U16		CU16;
typedef volatile		U16		VU16;
typedef volatile const	U16		VCU16;
typedef U16
	*							PU16,
	*const						CPU16,
	*volatile					VPU16,
	*volatile const				VCPU16;
typedef CU16
	*							PCU16,
	*const						CPCU16,
	*volatile					VPCU16,
	*volatile const				VCPCU16;
typedef VU16
	*							PVU16,
	*const						CPVU16,
	*volatile					VPVU16,
	*volatile const				VCPVU16;
typedef VCU16
	*							PVCU16,
	*const						CPVCU16,
	*volatile					VPVCU16,
	*volatile const				VCPVCU16;
/*- U16 */
/*+ S32		Type, Qualified and Pointers */
typedef int32_t					S32;
typedef const			S32		CS32;
typedef volatile		S32		VS32;
typedef volatile const	S32		VCS32;
typedef S32
	*							PS32,
	*const						CPS32,
	*volatile					VPS32,
	*volatile const				VCPS32;
typedef CS32
	*							PCS32,
	*const						CPCS32,
	*volatile					VPCS32,
	*volatile const				VCPCS32;
typedef VS32
	*							PVS32,
	*const						CPVS32,
	*volatile					VPVS32,
	*volatile const				VCPVS32;
typedef VCS32
	*							PVCS32,
	*const						CPVCS32,
	*volatile					VPVCS32,
	*volatile const				VCPVCS32;
/*- S32 */
/*+ U32		Type, Qualified and Pointers */
typedef uint32_t				U32;
typedef const			U32		CU32;
typedef volatile		U32		VU32;
typedef volatile const	U32		VCU32;
typedef U32
	*							PU32,
	*const						CPU32,
	*volatile					VPU32,
	*volatile const				VCPU32;
typedef CU32
	*							PCU32,
	*const						CPCU32,
	*volatile					VPCU32,
	*volatile const				VCPCU32;
typedef VU32
	*							PVU32,
	*const						CPVU32,
	*volatile					VPVU32,
	*volatile const				VCPVU32;
typedef VCU32
	*							PVCU32,
	*const						CPVCU32,
	*volatile					VPVCU32,
	*volatile const				VCPVCU32;
/*- U32 */
/*+ S64		Type, Qualified and Pointers */
typedef int64_t					S64;
typedef const			S64		CS64;
typedef volatile		S64		VS64;
typedef volatile const	S64		VCS64;
typedef S64
	*							PS64,
	*const						CPS64,
	*volatile					VPS64,
	*volatile const				VCPS64;
typedef CS64
	*							PCS64,
	*const						CPCS64,
	*volatile					VPCS64,
	*volatile const				VCPCS64;
typedef VS64
	*							PVS64,
	*const						CPVS64,
	*volatile					VPVS64,
	*volatile const				VCPVS64;
typedef VCS64
	*							PVCS64,
	*const						CPVCS64,
	*volatile					VPVCS64,
	*volatile const				VCPVCS64;
/*- S64 */
/*+ U64		Type, Qualified and Pointers */
typedef uint64_t				U64;
typedef const			U64		CU64;
typedef volatile		U64		VU64;
typedef volatile const	U64		VCU64;
typedef U64
	*							PU64,
	*const						CPU64,
	*volatile					VPU64,
	*volatile const				VCPU64;
typedef CU64
	*							PCU64,
	*const						CPCU64,
	*volatile					VPCU64,
	*volatile const				VCPCU64;
typedef VU64
	*							PVU64,
	*const						CPVU64,
	*volatile					VPVU64,
	*volatile const				VCPVU64;
typedef VCU64
	*							PVCU64,
	*const						CPVCU64,
	*volatile					VPVCU64,
	*volatile const				VCPVCU64;
/*- U64 */
/*+ IMX		Type, Qualified and Pointers */
typedef intmax_t				IMX;
typedef const			IMX		CIMX;
typedef volatile		IMX		VIMX;
typedef volatile const	IMX		VCIMX;
typedef IMX
	*							PIMX,
	*const						CPIMX,
	*volatile					VPIMX,
	*volatile const				VCPIMX;
typedef CIMX
	*							PCIMX,
	*const						CPCIMX,
	*volatile					VPCIMX,
	*volatile const				VCPCIMX;
typedef VIMX
	*							PVIMX,
	*const						CPVIMX,
	*volatile					VPVIMX,
	*volatile const				VCPVIMX;
typedef VCIMX
	*							PVCIMX,
	*const						CPVCIMX,
	*volatile					VPVCIMX,
	*volatile const				VCPVCIMX;
/*- IMX */
/*+ SIMX		Type, Qualified and Pointers */
typedef intmax_t				SIMX;
typedef const			SIMX	CSIMX;
typedef volatile		SIMX	VSIMX;
typedef volatile const	SIMX	VCSIMX;
typedef SIMX
	*							PSIMX,
	*const						CPSIMX,
	*volatile					VPSIMX,
	*volatile const				VCPSIMX;
typedef CSIMX
	*							PCSIMX,
	*const						CPCSIMX,
	*volatile					VPCSIMX,
	*volatile const				VCPCSIMX;
typedef VSIMX
	*							PVSIMX,
	*const						CPVSIMX,
	*volatile					VPVSIMX,
	*volatile const				VCPVSIMX;
typedef VCSIMX
	*							PVCSIMX,
	*const						CPVCSIMX,
	*volatile					VPVCSIMX,
	*volatile const				VCPVCSIMX;
/*- SIMX */
/*+ UIMX		Type, Qualified and Pointers */
typedef uintmax_t				UIMX;
typedef const			UIMX	CUIMX;
typedef volatile		UIMX	VUIMX;
typedef volatile const	UIMX	VCUIMX;
typedef UIMX
	*							PUIMX,
	*const						CPUIMX,
	*volatile					VPUIMX,
	*volatile const				VCPUIMX;
typedef CUIMX
	*							PCUIMX,
	*const						CPCUIMX,
	*volatile					VPCUIMX,
	*volatile const				VCPCUIMX;
typedef VUIMX
	*							PVUIMX,
	*const						CPVUIMX,
	*volatile					VPVUIMX,
	*volatile const				VCPVUIMX;
typedef VCUIMX
	*							PVCUIMX,
	*const						CPVCUIMX,
	*volatile					VPVCUIMX,
	*volatile const				VCPVCUIMX;
/*- UIMX */
/*+ SL8		Type, Qualified and Pointers */
typedef int_least8_t			SL8;
typedef const			SL8		CSL8;
typedef volatile		SL8		VSL8;
typedef volatile const	SL8		VCSL8;
typedef SL8
	*							PSL8,
	*const						CPSL8,
	*volatile					VPSL8,
	*volatile const				VCPSL8;
typedef CSL8
	*							PCSL8,
	*const						CPCSL8,
	*volatile					VPCSL8,
	*volatile const				VCPCSL8;
typedef VSL8
	*							PVSL8,
	*const						CPVSL8,
	*volatile					VPVSL8,
	*volatile const				VCPVSL8;
typedef VCSL8
	*							PVCSL8,
	*const						CPVCSL8,
	*volatile					VPVCSL8,
	*volatile const				VCPVCSL8;
/*- SL8 */
/*+ UL8		Type, Qualified and Pointers */
typedef uint_least8_t			UL8;
typedef const			UL8		CUL8;
typedef volatile		UL8		VUL8;
typedef volatile const	UL8		VCUL8;
typedef UL8
	*							PUL8,
	*const						CPUL8,
	*volatile					VPUL8,
	*volatile const				VCPUL8;
typedef CUL8
	*							PCUL8,
	*const						CPCUL8,
	*volatile					VPCUL8,
	*volatile const				VCPCUL8;
typedef VUL8
	*							PVUL8,
	*const						CPVUL8,
	*volatile					VPVUL8,
	*volatile const				VCPVUL8;
typedef VCUL8
	*							PVCUL8,
	*const						CPVCUL8,
	*volatile					VPVCUL8,
	*volatile const				VCPVCUL8;
/*- UL8 */
/*+ SL16		Type, Qualified and Pointers */
typedef int_least16_t			SL16;
typedef const			SL16	CSL16;
typedef volatile		SL16	VSL16;
typedef volatile const	SL16	VCSL16;
typedef SL16
	*							PSL16,
	*const						CPSL16,
	*volatile					VPSL16,
	*volatile const				VCPSL16;
typedef CSL16
	*							PCSL16,
	*const						CPCSL16,
	*volatile					VPCSL16,
	*volatile const				VCPCSL16;
typedef VSL16
	*							PVSL16,
	*const						CPVSL16,
	*volatile					VPVSL16,
	*volatile const				VCPVSL16;
typedef VCSL16
	*							PVCSL16,
	*const						CPVCSL16,
	*volatile					VPVCSL16,
	*volatile const				VCPVCSL16;
/*- SL16 */
/*+ UL16		Type, Qualified and Pointers */
typedef uint_least16_t			UL16;
typedef const			UL16	CUL16;
typedef volatile		UL16	VUL16;
typedef volatile const	UL16	VCUL16;
typedef UL16
	*							PUL16,
	*const						CPUL16,
	*volatile					VPUL16,
	*volatile const				VCPUL16;
typedef CUL16
	*							PCUL16,
	*const						CPCUL16,
	*volatile					VPCUL16,
	*volatile const				VCPCUL16;
typedef VUL16
	*							PVUL16,
	*const						CPVUL16,
	*volatile					VPVUL16,
	*volatile const				VCPVUL16;
typedef VCUL16
	*							PVCUL16,
	*const						CPVCUL16,
	*volatile					VPVCUL16,
	*volatile const				VCPVCUL16;
/*- UL16 */
/*+ SL32		Type, Qualified and Pointers */
typedef int_least32_t			SL32;
typedef const			SL32	CSL32;
typedef volatile		SL32	VSL32;
typedef volatile const	SL32	VCSL32;
typedef SL32
	*							PSL32,
	*const						CPSL32,
	*volatile					VPSL32,
	*volatile const				VCPSL32;
typedef CSL32
	*							PCSL32,
	*const						CPCSL32,
	*volatile					VPCSL32,
	*volatile const				VCPCSL32;
typedef VSL32
	*							PVSL32,
	*const						CPVSL32,
	*volatile					VPVSL32,
	*volatile const				VCPVSL32;
typedef VCSL32
	*							PVCSL32,
	*const						CPVCSL32,
	*volatile					VPVCSL32,
	*volatile const				VCPVCSL32;
/*- SL32 */
/*+ UL32		Type, Qualified and Pointers */
typedef uint_least32_t			UL32;
typedef const			UL32	CUL32;
typedef volatile		UL32	VUL32;
typedef volatile const	UL32	VCUL32;
typedef UL32
	*							PUL32,
	*const						CPUL32,
	*volatile					VPUL32,
	*volatile const				VCPUL32;
typedef CUL32
	*							PCUL32,
	*const						CPCUL32,
	*volatile					VPCUL32,
	*volatile const				VCPCUL32;
typedef VUL32
	*							PVUL32,
	*const						CPVUL32,
	*volatile					VPVUL32,
	*volatile const				VCPVUL32;
typedef VCUL32
	*							PVCUL32,
	*const						CPVCUL32,
	*volatile					VPVCUL32,
	*volatile const				VCPVCUL32;
/*- UL32 */
/*+ SL64		Type, Qualified and Pointers */
typedef int_least64_t			SL64;
typedef const			SL64	CSL64;
typedef volatile		SL64	VSL64;
typedef volatile const	SL64	VCSL64;
typedef SL64
	*							PSL64,
	*const						CPSL64,
	*volatile					VPSL64,
	*volatile const				VCPSL64;
typedef CSL64
	*							PCSL64,
	*const						CPCSL64,
	*volatile					VPCSL64,
	*volatile const				VCPCSL64;
typedef VSL64
	*							PVSL64,
	*const						CPVSL64,
	*volatile					VPVSL64,
	*volatile const				VCPVSL64;
typedef VCSL64
	*							PVCSL64,
	*const						CPVCSL64,
	*volatile					VPVCSL64,
	*volatile const				VCPVCSL64;
/*- SL64 */
/*+ UL64		Type, Qualified and Pointers */
typedef uint_least64_t			UL64;
typedef const			UL64	CUL64;
typedef volatile		UL64	VUL64;
typedef volatile const	UL64	VCUL64;
typedef UL64
	*							PUL64,
	*const						CPUL64,
	*volatile					VPUL64,
	*volatile const				VCPUL64;
typedef CUL64
	*							PCUL64,
	*const						CPCUL64,
	*volatile					VPCUL64,
	*volatile const				VCPCUL64;
typedef VUL64
	*							PVUL64,
	*const						CPVUL64,
	*volatile					VPVUL64,
	*volatile const				VCPVUL64;
typedef VCUL64
	*							PVCUL64,
	*const						CPVCUL64,
	*volatile					VPVCUL64,
	*volatile const				VCPVCUL64;
/*- UL64 */
/*+ SF8		Type, Qualified and Pointers */
typedef int_fast8_t				SF8;
typedef const			SF8		CSF8;
typedef volatile		SF8		VSF8;
typedef volatile const	SF8		VCSF8;
typedef SF8
	*							PSF8,
	*const						CPSF8,
	*volatile					VPSF8,
	*volatile const				VCPSF8;
typedef CSF8
	*							PCSF8,
	*const						CPCSF8,
	*volatile					VPCSF8,
	*volatile const				VCPCSF8;
typedef VSF8
	*							PVSF8,
	*const						CPVSF8,
	*volatile					VPVSF8,
	*volatile const				VCPVSF8;
typedef VCSF8
	*							PVCSF8,
	*const						CPVCSF8,
	*volatile					VPVCSF8,
	*volatile const				VCPVCSF8;
/*- SF8 */
/*+ UF8		Type, Qualified and Pointers */
typedef uint_fast8_t			UF8;
typedef const			UF8		CUF8;
typedef volatile		UF8		VUF8;
typedef volatile const	UF8		VCUF8;
typedef UF8
	*							PUF8,
	*const						CPUF8,
	*volatile					VPUF8,
	*volatile const				VCPUF8;
typedef CUF8
	*							PCUF8,
	*const						CPCUF8,
	*volatile					VPCUF8,
	*volatile const				VCPCUF8;
typedef VUF8
	*							PVUF8,
	*const						CPVUF8,
	*volatile					VPVUF8,
	*volatile const				VCPVUF8;
typedef VCUF8
	*							PVCUF8,
	*const						CPVCUF8,
	*volatile					VPVCUF8,
	*volatile const				VCPVCUF8;
/*- UF8 */
/*+ SF16		Type, Qualified and Pointers */
typedef int_fast16_t			SF16;
typedef const			SF16	CSF16;
typedef volatile		SF16	VSF16;
typedef volatile const	SF16	VCSF16;
typedef SF16
	*							PSF16,
	*const						CPSF16,
	*volatile					VPSF16,
	*volatile const				VCPSF16;
typedef CSF16
	*							PCSF16,
	*const						CPCSF16,
	*volatile					VPCSF16,
	*volatile const				VCPCSF16;
typedef VSF16
	*							PVSF16,
	*const						CPVSF16,
	*volatile					VPVSF16,
	*volatile const				VCPVSF16;
typedef VCSF16
	*							PVCSF16,
	*const						CPVCSF16,
	*volatile					VPVCSF16,
	*volatile const				VCPVCSF16;
/*- SF16 */
/*+ UF16		Type, Qualified and Pointers */
typedef uint_fast16_t			UF16;
typedef const			UF16	CUF16;
typedef volatile		UF16	VUF16;
typedef volatile const	UF16	VCUF16;
typedef UF16
	*							PUF16,
	*const						CPUF16,
	*volatile					VPUF16,
	*volatile const				VCPUF16;
typedef CUF16
	*							PCUF16,
	*const						CPCUF16,
	*volatile					VPCUF16,
	*volatile const				VCPCUF16;
typedef VUF16
	*							PVUF16,
	*const						CPVUF16,
	*volatile					VPVUF16,
	*volatile const				VCPVUF16;
typedef VCUF16
	*							PVCUF16,
	*const						CPVCUF16,
	*volatile					VPVCUF16,
	*volatile const				VCPVCUF16;
/*- UF16 */
/*+ SF32		Type, Qualified and Pointers */
typedef int_fast32_t			SF32;
typedef const			SF32	CSF32;
typedef volatile		SF32	VSF32;
typedef volatile const	SF32	VCSF32;
typedef SF32
	*							PSF32,
	*const						CPSF32,
	*volatile					VPSF32,
	*volatile const				VCPSF32;
typedef CSF32
	*							PCSF32,
	*const						CPCSF32,
	*volatile					VPCSF32,
	*volatile const				VCPCSF32;
typedef VSF32
	*							PVSF32,
	*const						CPVSF32,
	*volatile					VPVSF32,
	*volatile const				VCPVSF32;
typedef VCSF32
	*							PVCSF32,
	*const						CPVCSF32,
	*volatile					VPVCSF32,
	*volatile const				VCPVCSF32;
/*- SF32 */
/*+ UF32		Type, Qualified and Pointers */
typedef uint_fast32_t			UF32;
typedef const			UF32	CUF32;
typedef volatile		UF32	VUF32;
typedef volatile const	UF32	VCUF32;
typedef UF32
	*							PUF32,
	*const						CPUF32,
	*volatile					VPUF32,
	*volatile const				VCPUF32;
typedef CUF32
	*							PCUF32,
	*const						CPCUF32,
	*volatile					VPCUF32,
	*volatile const				VCPCUF32;
typedef VUF32
	*							PVUF32,
	*const						CPVUF32,
	*volatile					VPVUF32,
	*volatile const				VCPVUF32;
typedef VCUF32
	*							PVCUF32,
	*const						CPVCUF32,
	*volatile					VPVCUF32,
	*volatile const				VCPVCUF32;
/*- UF32 */
/*+ SF64		Type, Qualified and Pointers */
typedef int_fast64_t			SF64;
typedef const			SF64	CSF64;
typedef volatile		SF64	VSF64;
typedef volatile const	SF64	VCSF64;
typedef SF64
	*							PSF64,
	*const						CPSF64,
	*volatile					VPSF64,
	*volatile const				VCPSF64;
typedef CSF64
	*							PCSF64,
	*const						CPCSF64,
	*volatile					VPCSF64,
	*volatile const				VCPCSF64;
typedef VSF64
	*							PVSF64,
	*const						CPVSF64,
	*volatile					VPVSF64,
	*volatile const				VCPVSF64;
typedef VCSF64
	*							PVCSF64,
	*const						CPVCSF64,
	*volatile					VPVCSF64,
	*volatile const				VCPVCSF64;
/*- SF64 */
/*+ UF64		Type, Qualified and Pointers */
typedef uint_fast64_t			UF64;
typedef const			UF64	CUF64;
typedef volatile		UF64	VUF64;
typedef volatile const	UF64	VCUF64;
typedef UF64
	*							PUF64,
	*const						CPUF64,
	*volatile					VPUF64,
	*volatile const				VCPUF64;
typedef CUF64
	*							PCUF64,
	*const						CPCUF64,
	*volatile					VPCUF64,
	*volatile const				VCPCUF64;
typedef VUF64
	*							PVUF64,
	*const						CPVUF64,
	*volatile					VPVUF64,
	*volatile const				VCPVUF64;
typedef VCUF64
	*							PVCUF64,
	*const						CPVCUF64,
	*volatile					VPVCUF64,
	*volatile const				VCPVCUF64;
/*- UF64 */

/*+	Limits	*/

#define H_MIN				INT_MIN
#define H_MAX				INT_MAX
#define ST_MIN				0
#define ST_MAX				SIZE_MAX
#define PD_MIN				PTRDIFF_MIN
#define PD_MAX				PTRDIFF_MAX
#define SIPTR_MIN			INTPTR_MIN
#define SIPTR_MAX			INTPTR_MAX
#define UIPTR_MIN			0
#define UIPTR_MAX			UINTPTR_MAX

#define C_MIN				CHAR_MIN
#define C_MAX				CHAR_MAX
#define SC_MIN				SCHAR_MIN
#define SC_MAX				SCHAR_MAX
#define UC_MIN				0
#define UC_MAX				UCHAR_MAX

#define WC_MIN				WCHAR_MIN
#define WC_MAX				WCHAR_MAX
#define WI_MIN				WINT_MIN
#define WI_MAX				WINT_MAX

#define S_MIN				SHRT_MIN
#define S_MAX				SHRT_MAX
#define SS_MIN				SHRT_MIN
#define SS_MAX				SHRT_MAX
#define US_MIN				0
#define US_MAX				USHRT_MAX

#define I_MIN				INT_MIN
#define I_MAX				INT_MAX
#define SI_MIN				INT_MIN
#define SI_MAX				INT_MAX
#define UI_MIN				0
#define UI_MAX				UINT_MAX

#ifndef SL_MIN
#define SL_MIN				LONG_MIN
#define SL_MAX				LONG_MAX
#endif
#define UL_MIN				0
#define UL_MAX				ULONG_MAX

#define SLL_MIN				LLONG_MIN
#define SLL_MAX				LLONG_MAX
#define ULL_MIN				0
#define ULL_MAX				ULLONG_MAX

#define B_MIN				0
#define B_MAX				1

#define I8_MIN				CHAR_MIN
#define I8_MAX				CHAR_MAX
#define I16_MIN				SHRT_MIN
#define I16_MAX				SHRT_MAX
#define SI16_MIN			SHRT_MIN
#define SI16_MAX			SHRT_MAX
#define UI16_MIN			0
#define UI16_MAX			USHRT_MAX

#define S8_MIN				INT8_MIN
#define S8_MAX				INT8_MAX
#define U8_MIN				0
#define U8_MAX				UINT8_MAX
#define S16_MIN				INT16_MIN
#define S16_MAX				INT16_MAX
#define U16_MIN				0
#define U16_MAX				UINT16_MAX
#define S32_MIN				INT32_MIN
#define S32_MAX				INT32_MIN
#define U32_MIN				0
#define U32_MAX				UINT32_MAX
#define S64_MIN				INT64_MIN
#define S64_MAX				INT64_MAX
#define U64_MIN				0
#define U64_MAX				UINT64_MAX
#define IMX_MIN				INTMAX_MIN
#define IMX_MAX				INTMAX_MAX
#define SIMX_MIN			INTMAX_MIN
#define SIMX_MAX			INTMAX_MAX
#define UIMX_MIN			0
#define UIMX_MAX			UINTMAX_MAX

#define SL8_MIN				INT_LEAST8_MIN
#define SL8_MAX				INT_LEAST8_MAX
#define UL8_MIN				0
#define UL8_MAX				UINT_LEAST8_MAX
#define SL16_MIN			INT_LEAST16_MIN
#define SL16_MAX			INT_LEAST16_MAX
#define UL16_MIN			0
#define UL16_MAX			UINT_LEAST16_MAX
#define SL32_MIN			INT_LEAST32_MIN
#define SL32_MAX			INT_LEAST32_MAX
#define UL32_MIN			0
#define UL32_MAX			UINT_LEAST32_MAX
#define SL64_MIN			INT_LEAST64_MIN
#define SL64_MAX			INT_LEAST64_MAX
#define UL64_MIN			0
#define UL64_MAX			UINT_LEAST64_MAX

#define SF8_MIN				INT_FAST8_MIN
#define SF8_MAX				INT_FAST8_MAX
#define UF8_MIN				0
#define UF8_MAX				UINT_FAST8_MAX
#define SF16_MIN			INT_FAST16_MIN
#define SF16_MAX			INT_FAST16_MAX
#define UF16_MIN			0
#define UF16_MAX			UINT_FAST16_MAX
#define SF32_MIN			INT_FAST32_MIN
#define SF32_MAX			INT_FAST32_MAX
#define UF32_MIN			0
#define UF32_MAX			UINT_FAST32_MAX
#define SF64_MIN			INT_FAST64_MIN
#define SF64_MAX			INT_FAST64_MAX
#define UF64_MIN			0
#define UF64_MAX			UINT_FAST64_MAX

/*-	Limits	*/


/*
Conventions used for pointers and type qualifiers :
typedef Base_Type								Thing;			//	Type( Thing	)
typedef Thing				 *					PThing;		    //	Type( Pointer to an instance of Type( Thing ) )
typedef Thing				 *const				CPThing;		//	Type( Constant Pointer an instance of Type( Thing ) )
typedef Thing				 *volatile			VPThing;		//	Type( Volatile Pointer an instance of Type( Thing ) )
typedef Thing				 *volatile const	VCPThing;		//	Type( Volatile Constant Pointer an instance of Type( Thing ) )

typedef const Thing								CThing;			//	Type( Constant Thing )
typedef const Thing			 *					PCThing;		//	Type( Pointer to an instance of Type( Constant Thing ) )
typedef const Thing			 *const				CPCThing;		//	Type( Constant Pointer to an instance of Type( Constant Thing ) )
typedef const Thing			 *volatile			VPCThing;		//	Type( Volatile Pointer an instance of Type( Constant Thing ) )
typedef const Thing			 *volatile const	VCPCThing;		//	Type( Volatile Constant Pointer an instance of Type( Constant Thing ) )
Equivalent to,
typedef Thing const								CThing;			//	Type( Constant Thing )
typedef Thing const			 *					PCThing;		//	Type( Pointer to an instance of Type( Constant Thing ) )
typedef Thing const			 *const				CPCThing;		//	Type( Constant Pointer to an instance of Type( Constant Thing ) )
typedef Thing const			 *volatile			VPCThing;		//	Type( Volatile Pointer an instance of Type( Constant Thing ) )
typedef Thing const			 *volatile const	VCPCThing;		//	Type( Volatile Constant Pointer an instance of Type( Constant Thing ) )

typedef volatile Thing							VThing;			//	Type( Volatile Thing )
typedef volatile Thing		 *					PVThing;		//	Type( Pointer to an instance of Type( Volatile Thing ) )
typedef volatile Thing		 *const				CPVThing;		//	Type( Constant Pointer to an instance of Type( Volatile Thing ) )
typedef volatile Thing		 *volatile			VPVThing;		//	Type( Volatile Pointer an instance of Type( Volatile Thing ) )
typedef volatile Thing		 *volatile const	VCPVThing;		//	Type( Volatile Constant pointer an instance of Type( Volatile Thing ) )

typedef volatile const Thing					VCThing;		//	Type( Volatile Constant Thing )
typedef volatile const Thing *					PVCThing;		//	Type( Pointer to an instance of Type( Volatile Constant Thing ) )
typedef volatile const Thing *const				CPVCThing;		//	Type( Constant Pointer to an instance of Type( Volatile Constant Thing ) )
typedef volatile const Thing *volatile			VPVCThing;		//	Type( Volatile Pointer an instance of Type( Volatile Constant Thing ) )
typedef volatile const Thing *volatile const	VCPVCThing;		//	Type( Volatile Constant Pointer an instance of Type( Volatile Constant Thing ) )
*/

#endif /* C_TYPES_H	*/
