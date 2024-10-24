#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#define C (long double) 0.4
#define N (long unsigned int) 2

typedef long double step_t;
typedef long double *vector_t;
struct __matrix_t {
    vector_t *storage;
    size_t size;
    size_t length;
};
typedef struct __matrix_t matrix_t;

void vector_display(const vector_t vector);
void matrix_display(const matrix_t matrix);
void matrix_save_csv(const char *filename, const matrix_t matrix);

vector_t vector_create(vector_t vector);
void vector_free(vector_t *vector);

matrix_t matrix_create(size_t n);
void matrix_append(matrix_t *matrix, vector_t vector);
void matrix_free(matrix_t *matrix);

vector_t van_der_pol(step_t t, vector_t prev);

#endif