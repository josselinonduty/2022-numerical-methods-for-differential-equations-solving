#include <stdio.h>
#include <stdlib.h>

#include "functions.h"

void vector_display(const vector_t vector)
{
	printf("[%Lf, %Lf]", vector[0], vector[1]);
}

void matrix_display(const matrix_t matrix)
{
	printf("%lix%li", N, matrix.size);
	for (size_t i = 0; i < matrix.size; i++) {
		vector_display(matrix.storage[i]);
	}
}

vector_t vector_create(vector_t vector)
{
	vector_t vec = (vector_t) malloc(N * sizeof(long double));

	for (int i = 0; i < N; i++) {
		vec[i] = vector[i];
	}

	return vec;
}

void vector_free(vector_t *vector)
{
	free(*vector);
	*vector = NULL;
}

vector_t van_der_pol(step_t t, vector_t prev)
{
	return vector_create((vector_t) & ((long double[2]) {
					   prev[1],
					   C * (1 -
						prev[0] * prev[0]) *
					   prev[1] - prev[0]
					   }));
}
