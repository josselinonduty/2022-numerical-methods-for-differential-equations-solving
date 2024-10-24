#include <stdio.h>
#include <stdlib.h>

#include "functions.h"
#include "methods.h"

int main(int argc, char **argv)
{
	long double T = 15;
	long int I = 10000;
	vector_t y0 = vector_create((vector_t) & ((long double[2]) { -2, 2 }));

	matrix_t matrix = solve_middle_point(T, I, y0);

	matrix_save_csv("./export/middle_point.csv", matrix);
	matrix_free(&matrix);

	return 0;
}
