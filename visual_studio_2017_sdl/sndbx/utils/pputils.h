/*
 * pputils.h
 *
 * Created: 2015-03-20 09:21:10
 *  Author: Deon Marais
 */

#ifndef PPUTILS_H_
#define PPUTILS_H_

#include <stddef.h>

//#define SIZEOF(x) (char*)(&x+1)-(char*)(&x)

#define GLUE_B(x,y)				x##y
#define GLUE(x,y)				GLUE_B(x,y)

#ifndef MISRA1998
#define GLUE3_B(x,y,z)			x##y##z
#define GLUE3(x,y,z)			GLUE3_B(x,y,z)
#endif

#define STRINGIFY_B(x)			#x
#define STRINGIFY(x)			STRINGIFY_B(x)

#define NB_ARRAY_ITEMS(a)		(sizeof(a)/sizeof(a[0]))

#define SIZEOF_ALIGNED(T)		((sizeof(T)+sizeof(PV)-1)&(ST)~(sizeof(PV)-1))

/* Typedefs */
/* Qualified Types from Base type */
#define TYPEDEF_QFS(T)						\
typedef const T				GLUE(C,T);		\
typedef volatile T 			GLUE(V,T);		\
typedef volatile const T 	GLUE(VC,T)

/* It seems that VAssistX does not recognize restrict */
/* Pointer to all types, base and qualified */
#define TYPEDEF_PTRS(T)									\
typedef T	*							GLUE(P,T),		\
			*const						GLUE(CP,T),		\
			*volatile					GLUE(VP,T),		\
			*volatile const				GLUE(VCP,T),	\
			*__restrict					GLUE(RP,T),		\
			*__restrict const			GLUE(RCP,T),	\
			*__restrict volatile		GLUE(RVP,T),	\
			*__restrict volatile const	GLUE(RVCP,T)

#define TYPEDEF_QFS_PTRS(T)		\
TYPEDEF_QFS(T);					\
TYPEDEF_PTRS(T);				\
TYPEDEF_PTRS(GLUE(C,T));		\
TYPEDEF_PTRS(GLUE(V,T));		\
TYPEDEF_PTRS(GLUE(VC,T))

/* Complete type creation of datatypes, all variants */
#define TYPEDEF(BT,T)	\
typedef BT T;			\
TYPEDEF_QFS_PTRS(T)

/* Pointers to function creation, 0 to 6 parameters */
#define PF_1P_TYPE(r,p1)	\
	GLUE(					\
		GLUE3(_,r,_PFN_),	\
		GLUE(p1,_)			\
	)
#define PF_2P_TYPE(r,p1,p2)	\
	GLUE3(					\
		GLUE3(_,r,_PFN_),	\
		GLUE3(p1,_,p1),		\
		_					\
	)
#define PF_3P_TYPE(r,p1,p2,p3)	\
	GLUE3(						\
		GLUE3(_,r,_PFN_),		\
		GLUE3(p1,_,p2),			\
		GLUE3(_,p3,_)			\
	)
#define PF_4P_TYPE(r,p1,p2,p3,p4)	\
	GLUE3(							\
		GLUE3(_,r,_PFN_),			\
		GLUE3(p1,_,p2),				\
		GLUE(						\
			GLUE3(_,p3,_),			\
			GLUE(p4,_)				\
		)							\
	)
#define PF_5P_TYPE(r,p1,p2,p3,p4,p5)	\
	GLUE3(								\
		GLUE3(_,r,_PFN_),				\
		GLUE3(p1,_,p2),					\
		GLUE3(							\
			GLUE3(_,p3,_),				\
			GLUE3(p4,_,p5),				\
			_							\
		)								\
	)
#define PF_6P_TYPE(r,p1,p2,p3,p4,p5,p6)	\
	GLUE3(								\
		GLUE3(_,r,_PFN_),				\
		GLUE3(p1,_,p2),					\
		GLUE3(							\
			GLUE3(_,p3,_),			    \
			GLUE3(p4,_,p5),			    \
			GLUE3(_,p6,_)			    \
		)								\
	)
#define TYPEDEF_PFN_1P(r,p1)	\
typedef	r (*					\
			PF_1P_TYPE(r,p1)	\
		)						\
		(p1)
#define TYPEDEF_PFN_2P(r,p1,p2)	\
typedef r (*					\
			PF_2P_TYPE(r,p1,p2)	\
		)						\
		(p1,p2)
#define TYPEDEF_PFN_3P(r,p1,p2,p3)	\
typedef r (*						\
			PF_3P_TYPE(r,p1,p2,p3)	\
		)							\
		(p1,p2,p3)
#define TYPEDEF_PFN_4P(r,p1,p2,p3,p4)	\
typedef r (*							\
			PF_4P_TYPE(r,p1,p2,p3,p4)	\
		)								\
		(p1,p2,p3,p4)
#define TYPEDEF_PFN_5P(r,p1,p2,p3,p4,p5)	\
typedef r (*								\
			PF_5P_TYPE(r,p1,p2,p3,p4,p5)	\
		)									\
		(p1,p2,p3,p4,p5)
#define TYPEDEF_PFN_6P(r,p1,p2,p3,p4,p5,p6)	\
typedef r (*								\
			PF_6P_TYPE(r,p1,p2,p3,p4,p5,p6)	\
		)									\
		(p1,p2,p3,p4,p5,p6)

#endif /* PPUTILS_H_ */
