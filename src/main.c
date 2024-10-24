#include <stdio.h>
#include <stdlib.h>

#include "functions.h"
#include "methods.h"

int main(int argc, char **argv)
{
	long double T = 15;
	long int I = 100;
	vector_t y0 = vector_copy((vector_t) & ((long double[2]) { -2, 2 }));

	matrix_t matrix = solve_middle_point(T, I, y0);
	matrix_save_csv("./export/middle_point.csv", matrix);
	matrix_free(&matrix);

	matrix = solve_runge_kutta_4(T, I, y0);
	matrix_save_csv("./export/runge_kutta_4.csv", matrix);
	matrix_free(&matrix);

	matrix = solve_bashforth(T, I, y0);
	matrix_save_csv("./export/bashforth.csv", matrix);
	matrix_free(&matrix);

	matrix = solve_adams_moulton(T, I, y0, 10e-3, 10e3);
	matrix_save_csv("./export/adams_moulton.csv", matrix);
	matrix_free(&matrix);

	vector_free(&y0);

	return 0;
}
