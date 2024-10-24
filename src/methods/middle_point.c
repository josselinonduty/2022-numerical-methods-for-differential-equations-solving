#include <stdio.h>
#include <stdlib.h>

#include "functions.h"
#include "methods.h"

matrix_t solve_middle_point(long double T, long int I, vector_t y0)
{
	matrix_t matrix = matrix_create(I + 1);
	matrix_append(&matrix, y0);

	vector_t y_i = vector_create(y0);
	vector_t y_next, y_inter, y_inter_update;

	long double h = T / I;

	for (long int i = 0; i < I; i++) {
		long int t_i = i * h;
		y_inter = van_der_pol(t_i, y_i);
		for (int n = 0; n < N; n++) {
			y_inter[n] = y_i[n] + h / 2 * y_inter[n];
		}

		y_inter_update = van_der_pol(t_i + h / 2, y_inter);
		y_next = y_i;
		for (int n = 0; n < N; n++) {
			y_next[n] += h * y_inter_update[n];
			y_i[n] = y_next[n];
		}

		matrix_append(&matrix, vector_create(y_next));
		vector_free(&y_inter);
		vector_free(&y_inter_update);
	}

	vector_free(&y_i);

	return matrix;
}
