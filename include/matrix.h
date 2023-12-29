#ifndef MATRIX_H
#define MATRIX_H

#include <stdlib.h>
#include <stdio.h>

void print_matrix(size_t rows, size_t cols, int (*matrix)[cols]);
void multiplication_squared(size_t rows, size_t cols, int a[rows][cols], int b[rows][cols]);


#endif