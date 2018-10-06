#ifndef __SQUARESOLVER_H_INCLUDED__
#define __SQUARESOLVER_H_INCLUDED__

#include <complex.h>

typedef long double ld_t;

static const ld_t EPSILON = 1.e-5L;

typedef enum 
{
	RT_NO_ROOTS,
	RT_REAL_ROOT,
	RT_REAL_ROOTS,
	RT_COMPLEX_ROOTS
} ROOTTYPE;

typedef struct tagREAL_ROOT
{
	ld_t x;
} REAL_ROOT;

typedef struct tagREAL_ROOTS
{
	ld_t x1,
		 x2;
} REAL_ROOTS;

typedef struct tagCOMPLEX_ROOTS
{
	_Lcomplex x1, // Microsoft-specific equivalent to the unimplemented C99 native type 'long double _Complex'
		      x2;
} COMPLEX_ROOTS;

typedef struct tagRoots
{
	ROOTTYPE type;
	union
	{
		REAL_ROOT     rr;
		REAL_ROOTS    rrs;
		COMPLEX_ROOTS crs;
	} DUMMYUNIONNAME;
} ROOTS;

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

ROOTS SolveSquare(ld_t a, ld_t b, ld_t c);
void PrintQuadResults(const ROOTS *cpRoots);

#ifdef __cplusplus
} // extern "C"
#endif /* __cplusplus */

#endif /* __SQUARESOLVER_H_INCLUDED__ */

