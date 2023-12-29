#include "../include/matrix.h"

#define PADDING 7


int main(int argc, char* argv[]) 
{
    int matrix[4][4] = {{0, 1, 2, 3}, 
                        {4, 5, 6, 7}, 
                        {8, 9, 10, 11}, 
                        {12, 13, 14, 15}
                        };

    int matrix1[3][3] = {{10, 1, 123}, {-5, 3, 11}, {7, -15, 9}};
    int matrix2[3][3] = {{-14, 3, -2}, {6, 7, 8}, {-4, 1, 15}};

    srand(time(0));

    size_t sz = 10;
    int** a = generate_matrix(sz, sz);
    int** b = generate_matrix(sz, sz);

    print_matrix(sz, sz, a);
    printf("\n  *\n");
    print_matrix(sz, sz, b);
    printf("\n  =\n");

    multiplication_squared(sz, sz, a, b);

    free_matrix(sz, sz, a);
    free_matrix(sz, sz, b);

    return 0;
}

/* -------------------------------------------------------------------- */


void print_matrix(size_t rows, size_t cols, int** matrix)
{

    for (int i=0; i<rows; i++) 
    {
        for (int j=0; j<cols; j++) 
        {
            printf("%*d ", PADDING,  matrix[i][j]);
        }
        printf("\n");    
    }
}


void multiplication_squared(size_t rows, size_t cols, int** a, int** b)
{
    int** result_matrix = allocate_matrix(rows, cols);

    for (int i=0; i<rows; i++) 
    {
        for (int j=0; j<cols; j++) 
        {
            int sum = 0;
            for (int k=0; k<rows; k++)
            {
                sum += a[i][k] * b[k][j];
            }
            result_matrix[i][j] = sum;
        }
    }

    print_matrix(rows, cols, result_matrix);
    free_matrix(rows, cols, result_matrix);
}