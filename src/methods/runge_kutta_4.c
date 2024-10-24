#include "functions.h"
#include "methods.h"

matrix_t solve_runge_kutta_4(long double T, long int I, vector_t y0)
{
	matrix_t matrix = matrix_create(I + 1);
	matrix_append(&matrix, vector_copy(y0));

	vector_t y_i = vector_copy(y0);
	vector_t y_inter = vector_copy(y0);
	vector_t y_next, k1, k2, k3, k4;

	long double h = T / I;

	for (long int i = 0; i < I; i++) {
		long int t_i = i * h;

		k1 = van_der_pol(t_i, y_i);
		for (int n = 0; n < N; n++) {
			y_inter[n] = y_i[n] + (h / 2) * k1[n];
		}
		k2 = van_der_pol(t_i + (h / 2), y_inter);
		for (int n = 0; n < N; n++) {
			y_inter[n] = y_i[n] + (h / 2) * k2[n];
		}
		k3 = van_der_pol(t_i + (h / 2), y_inter);
		for (int n = 0; n < N; n++) {
			y_inter[n] = y_i[n] + h * k3[n];
		}
		k4 = van_der_pol(t_i + h, y_inter);

		y_next = y_i;
		for (int n = 0; n < N; n++) {
			y_next[n] =
			    y_i[n] + h / 6 * (k1[n] + 2 * k2[n] + 2 * k3[n] +
					      k4[n]);
		}

		vector_free(&k1);
		vector_free(&k2);
		vector_free(&k3);
		vector_free(&k4);

		matrix_append(&matrix, vector_copy(y_next));
	}

	vector_free(&y_i);
	vector_free(&y_inter);

	return matrix;
}
