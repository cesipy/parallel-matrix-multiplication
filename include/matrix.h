#ifndef MATRIX_H
#define MATRIX_H

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <pthread.h>

#define MAX_RANDOM 100
#define MIN_RANDOM -1

#define PADDING 7

void print_matrix(size_t rows, size_t cols, int** matrix);
int** matrix_multiplication_squared(size_t rows, size_t cols, int** a, int** b);

int** generate_matrix(size_t rows, size_t cols);
void free_matrix(size_t rows, size_t cols, int** a);
int** allocate_matrix(size_t rows, size_t cols);
int initialize_threads(int size, int** a, int** b);


/* from test.c */

void initialize_matrix(size_t rows, size_t cols, int** alloc_matrix, int matrix[rows][cols]);
int test_matrix1[3][3];
int test_matrix2[3][3];
int result_matrix_1x2[3][3];
int test_matrix3[4][4];


typedef struct {
    int** a;
    int** b;
    int** result_matrix;
    int a_i;
    int a_j;
}param_t;



#endif