#include "../include/matrix.h"

#define PADDING 4


int main(int argc, char* argv[]) 
{
    int matrix[4][4] = {{0, 1, 2, 3}, 
                        {4, 5, 6, 7}, 
                        {8, 9, 10, 11}, 
                        {12, 13, 14, 15}
                        };

    int matrix1[3][3] = {{10, 1, 123}, {-5, 3, 11}, {7, -15, 9}};
    int matrix2[3][3] = {{-14, 3, -2}, {6, 7, 8}, {-4, 1, 15}};


    print_matrix(3, 3, matrix2);
    printf("\n*\n");
    print_matrix(3, 3, matrix1);
    printf("\n=\n");
    multiplication_squared(3, 3, matrix1, matrix2);

    return 0;
}

/* -------------------------------------------------------------------- */


void print_matrix(size_t rows, size_t cols, int matrix[rows][cols])
{
    size_t size_matrix = sizeof(char) * rows * cols * (PADDING +1);
    size_t offset = 0;

    char* result = malloc(size_matrix);
    // TODO: error handling for malloc

    for (int i=0; i<rows; i++) 
    {
        for (int j=0; j<cols; j++) 
        {
            offset += sprintf(result+offset, "%*d ", PADDING,  matrix[i][j]);
        }
        offset += sprintf(result+offset, "\n");
    }

    printf("%s", result);
    free(result);
}


void multiplication_squared(size_t rows, size_t cols, int a[rows][cols], int b[rows][cols])
{
    int result_matrix[rows][cols];

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
}