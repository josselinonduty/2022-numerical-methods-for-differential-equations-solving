#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "functions.h"
#include "methods.h"

matrix_t solve_adams_moulton(long double T, long int I, vector_t y0,
			     long double epsilon, long int max_iter)
{
	matrix_t matrix = matrix_create(I + 1);
	matrix_append(&matrix, vector_copy(y0));

	vector_t y_i = vector_copy(y0);
	vector_t y_next = vector_copy(y0);
	vector_t y_inter, y_inter_prev;
	vector_t J = malloc(N * N * sizeof(long double));
	vector_t G = vector_copy(y0);

	long double h = T / I;
	long double alpha = 5 * h / 12;

	y_inter = van_der_pol(0, y_i);
	for (long int i = 1; i < I; i++) {
		long int t_i = i * h;

		y_inter_prev = y_inter;
		y_inter = van_der_pol(t_i, y_i);

		long int k = 0;
		long double norm = 1;
		while (norm > epsilon && k++ < max_iter) {
			G[0] =
			    alpha * y_i[1] - y_i[0] + (y_i[0] +
						       h / 12 * (8 *
								 y_inter[0] -
								 y_inter_prev
								 [0]));
			G[1] =
			    alpha * (C * (1 - y_i[0] * y_i[0]) * y_i[1] -
				     y_i[0]) - y_i[1] + (y_i[1] +
							 h / 12 * (8 *
								   y_inter[1] -
								   y_inter_prev
								   [1]));

			J[0] = -1;	// 0b00
			J[1] = alpha;	// 0b01
			J[2] = -alpha * (2 * C * y_i[0] * y_i[1] + 1);	// 0b10
			J[3] = +alpha * C * (1 - y_i[0] * y_i[0]) - 1;	// 0b11

			long double det = J[0] * J[3] - J[2] * J[1];
			y_next[0] = y_i[0] - (J[3] * G[0] - J[1] * G[1]) / det;
			y_next[1] = y_i[1] - (-J[2] * G[0] + J[0] * G[1]) / det;

			norm =
			    abs(sqrt
				(y_next[0] * y_next[0] +
				 y_next[1] * y_next[1]) - y_i[0] * y_i[0] +
				y_i[1] * y_i[1]);
		}

		for (long int n = 0; n < N; n++) {
			y_i[n] = y_next[n];
		}

		matrix_append(&matrix, vector_copy(y_next));
		vector_free(&y_inter_prev);
	}

	vector_free(&y_i);
	vector_free(&y_next);
	vector_free(&y_inter);
	vector_free(&y_inter_prev);
	free(J);
	vector_free(&G);

	return matrix;
}
