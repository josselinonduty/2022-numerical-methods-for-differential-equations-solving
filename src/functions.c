#include <stdio.h>
#include <stdlib.h>

#include "functions.h"

void vector_display(const vector_t vector)
{
	printf("[%Lf, %Lf]", vector[0], vector[1]);
}

void matrix_display(const matrix_t matrix)
{
	printf("matrix_t(%li, %li)\n", N, matrix.length);

	for (size_t i = 0; i < matrix.length; i++) {
		vector_display(matrix.storage[i]);
		printf("\n");
	}
}

void matrix_save_csv(const char *filename, const matrix_t matrix)
{
	FILE *file = fopen(filename, "w");

	for (size_t i = 0; i < matrix.length; i++) {
		fprintf(file, "%ld\t%Lf\t%Lf\n", i, matrix.storage[i][0],
			matrix.storage[i][1]);
	}

	fclose(file);
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

matrix_t matrix_create(size_t n)
{
	matrix_t matrix = {
		.size = n,
		.length = 0,
		.storage = (vector_t *) malloc(n * sizeof(vector_t))
	};

	for (long int i = 0; i < matrix.size; i++) {
		matrix.storage[i] = NULL;
	}

	return matrix;
}

void matrix_append(matrix_t *matrix, vector_t vector)
{
	matrix->storage[matrix->length++] = vector;
}

void matrix_free(matrix_t *matrix)
{
	for (long int i = 0; i < matrix->length; i++) {
		vector_free(&(matrix->storage[i]));
	}

	matrix->size = 0;
	matrix->length = 0;
	free(matrix->storage);
	matrix->storage = NULL;
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
