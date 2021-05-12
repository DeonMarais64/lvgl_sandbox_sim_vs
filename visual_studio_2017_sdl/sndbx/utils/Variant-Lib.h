/*
 * Variant_Lib.h
 *
 * Created: 2014/04/27 01:45:16
 *  Author: Deon Marais
 */ 


#ifndef VARIANT_LIB_H_
#define VARIANT_LIB_H_

#include "Variant-Types.h"

/**
 * VarXT == any type supported by these funtions
 * IE, B, C, SC etc
 * This pointer is typecast to the correct function pointer type and called to obtain the value
 * Make sure it is a valid function returning relavent supported type
 */
typedef PV _VarXT_PFN_V_;

extern I Var_StrToVar		( PCC s, VarP vp, eVar_t vt );
extern I Var_VarToStr		( PC s, PCC pFmt, PCVar pv, eVar_t vt );
extern I Var_VarToStrn 		( PC s, PCC pFmt, PCVar pv, ST n, eVar_t vt );
extern V Var_AssignVar		( PV pvTo, PCVar pvFr, eVar_t vt );
extern V Var_AssignVarFrFun	( PV pv, _VarXT_PFN_V_ pFun, eVar_t vt );
extern I Var_VarCmp			( PCVar pv1, PCVar pv2, eVar_t vt );

#endif /* VARIANT_LIB_H_ */
