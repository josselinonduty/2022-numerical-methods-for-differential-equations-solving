#ifndef METHODS_H
#define METHODS_H

#include "functions.h"

matrix_t solve_middle_point(long double T, long int I, vector_t y0);
matrix_t solve_runge_kutta_4(long double T, long int I, vector_t y0);

#endif