#include <stdio.h>
#include <stdlib.h>

#include "functions.h"
#include "methods.h"

matrix_t solve_bashforth(long double T, long int I, vector_t y0)
{
	matrix_t matrix = matrix_create(I + 1);
	matrix_append(&matrix, vector_copy(y0));

	vector_t y_i = vector_copy(y0);
	vector_t y_next, y_inter_prev, y_inter, y_inter_update;

	long double h = T / I;

	// Initialise y_1 using Middle Point technique
	y_inter = van_der_pol(0, y0);
	for (int n = 0; n < N; n++) {
		y_inter[n] = y_i[n] + h / 2 * y_inter[n];
	}

	y_inter_update = van_der_pol(h / 2, y_inter);
	y_next = y_i;
	for (int n = 0; n < N; n++) {
		y_next[n] += h * y_inter_update[n];
	}

	matrix_append(&matrix, vector_copy(y_next));
	vector_free(&y_inter);
	vector_free(&y_inter_update);

	y_inter = van_der_pol(0, y0);
	for (long int i = 1; i < I; i++) {
		long int t_i = i * h;

		y_inter_prev = y_inter;
		y_inter = van_der_pol(t_i, y_i);

		for (long int n = 0; n < N; n++) {
			y_next[n] += h / 2 * (3 * y_inter[n] - y_inter_prev[n]);
		}
		y_i = y_next;

		matrix_append(&matrix, vector_copy(y_next));
		vector_free(&y_inter_prev);
	}

	vector_free(&y_i);
	vector_free(&y_inter_prev);
	vector_free(&y_inter);

	return matrix;
}
