#include <stdlib.h>
#include <stdio.h>

#define PADDING 4


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


int main(int argc, char* argv[]) 
{
    int matrix[4][4] = {{0, 1, 2, 3}, 
                        {4, 5, 6, 7}, 
                        {8, 9, 10, 11}, 
                        {12, 13, 14, 15}
                        };

    print_matrix(4, 4, matrix);

    return 0;
}