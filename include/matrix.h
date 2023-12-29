#ifndef MATRIX_H
#define MATRIX_H

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define MAX_RANDOM 100
#define MIN_RANDOM -1

void print_matrix(size_t rows, size_t cols, int** matrix);
int** multiplication_squared(size_t rows, size_t cols, int** a, int** b);

int** generate_matrix(size_t rows, size_t cols);
void free_matrix(size_t rows, size_t cols, int** a);
int** allocate_matrix(size_t rows, size_t cols);

#endif