#ifndef MATRIX_H
#define MATRIX_H

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <pthread.h>
#include <string.h>

#define MAX_RANDOM 100
#define MIN_RANDOM -1

#define PADDING 7
#define NUM_THREADS 8     // how many threads are available on machine/ 
                          // or how many cores want to be used

void print_matrix(size_t rows, size_t cols, int** matrix);
int** matrix_multiplication_squared(size_t rows, size_t cols, int** a, int** b);

int** generate_matrix(size_t rows, size_t cols);
void free_matrix(size_t rows, size_t cols, int** a);
int** allocate_matrix(size_t rows, size_t cols);
int initialize_threads_naive(int size, int** a, int** b, int** result);
double get_current_time();
void copy_matrix(size_t rows, size_t cols, int** a, int** b);
int check_matrix_dimensions(size_t, size_t, size_t, size_t);
int** matrix_multiplication(size_t, size_t, size_t, size_t, int** a, int** b);


// from new approach, also pretty naive, as it is not really dynamic
int calculate_num_operations(size_t, size_t);
int calculate_rest_operations(size_t, size_t);
void* thread_function_seminaive(void* arg);
int initialize_threads_seminaive(size_t sz, int** a, int** b, int** result);
unsigned long long matrix_checksum(size_t rows, size_t cols, int** a);

/* from test.c */

void initialize_matrix(size_t rows, size_t cols, int** alloc_matrix, int matrix[rows][cols]);
// int test_matrix1[3][3];
// int test_matrix2[3][3];
// int result_matrix_1x2[3][3];
// int test_matrix3[4][4];


typedef struct {
    int** a;
    int** b;
    int** result_matrix;
    int a_i;
    int a_j;
    int sz;         // size for squared matrix
    int num_rows;
    int tid;
}param_t;



#endif