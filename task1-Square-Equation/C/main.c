#include "SquareSolver.h"

#include <stdio.h>  // printf, scanf_s
#include <stdlib.h> // system

int main(void)
{
	printf("Enter coefs:\n");

	ld_t a = .0l,
		 b = .0l,
		 c = .0l;
	scanf_s("%Lf %Lf %Lf", &a, &b, &c);

	printf("Solving: %Lfx^2 + %Lfx + %Lf = 0\n", a, b, c);

	ROOTS roots = SolveSquare(a, b, c);
	PrintQuadResults(&roots);

	system("pause");
	return 0;
}