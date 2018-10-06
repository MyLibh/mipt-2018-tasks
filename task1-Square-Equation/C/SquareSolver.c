#include "SquareSolver.h"

#include <stdio.h>   // printf
#include <math.h>    // sqrt, pow
#include <stdbool.h>

static inline bool IsZero(ld_t x, ld_t eps)
{
	return (x > -eps && x < eps);
}

ROOTS SolveSquare(ld_t a, ld_t b, ld_t c)
{
	ROOTS result = { RT_NO_ROOTS };
	if (IsZero(a, EPSILON))
		return result;

	// TODO: Remove repeated calculations
	ld_t disk = powl(b, 2) - 4.l * a * c;
	if(disk > 0.l)
	{
		ld_t sqrt_disk = sqrtl(disk);

		result.type                  = RT_REAL_ROOTS;
		result.DUMMYUNIONNAME.rrs.x1 = (-b + sqrt_disk) / (2.l * a);
		result.DUMMYUNIONNAME.rrs.x2 = (-b - sqrt_disk) / (2.l * a);
	}
	else if (IsZero(disk, EPSILON))
	{
		result.type = RT_REAL_ROOT;
		result.DUMMYUNIONNAME.rr.x = -b / (2.l * a);
	}
	else
	{
		ld_t sqrt_neg_disk = sqrtl(-disk);

		result.type = RT_COMPLEX_ROOTS;
		result.DUMMYUNIONNAME.crs.x1 = _LCbuild(-b / (2.l * a), +sqrt_neg_disk / (2.l * a));
		result.DUMMYUNIONNAME.crs.x2 = _LCbuild(-b / (2.l * a), -sqrt_neg_disk / (2.l * a));
	}

	return result;
}

void PrintQuadResults(const ROOTS *cpRoots)
{
	if (cpRoots->type == RT_NO_ROOTS)
		printf("No roots");
	else if (cpRoots->type == RT_REAL_ROOT)
		printf("Real root: %Lf", cpRoots->DUMMYUNIONNAME.rr.x);
	else if (cpRoots->type == RT_REAL_ROOTS)
		printf("Real roots: %Lf, %Lf", cpRoots->DUMMYUNIONNAME.rrs.x1, cpRoots->DUMMYUNIONNAME.rrs.x2);
	else
		printf("Complex roots: (%.1f,%+.1fi), (%.1f,%+.1fi)", creall(cpRoots->DUMMYUNIONNAME.crs.x1), cimagl(cpRoots->DUMMYUNIONNAME.crs.x1), 
			                                                  creall(cpRoots->DUMMYUNIONNAME.crs.x2), cimagl(cpRoots->DUMMYUNIONNAME.crs.x2));

	printf("\n");
}