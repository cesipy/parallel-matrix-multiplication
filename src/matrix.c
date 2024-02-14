#include "../include/matrix.h"

// generates a random matrix for testing, etc
int** generate_matrix(size_t rows, size_t cols) 
{
    int** a = allocate_matrix(rows, cols);
    if (a == NULL) 
    {
        exit(EXIT_FAILURE);
    }

    for (int i=0; i<rows; i++) 
    {
        for (int j=0; j<cols; j++)
        {
            // generates matrix entries with values in the range {MIN_RANDOM, ..., MAX_RANDOM}
            int random_number = rand() %  (MAX_RANDOM +1 - MIN_RANDOM) + MIN_RANDOM;
            a[i][j] = random_number;
        }
    }

    return a;
}


/**
 * frees matrix
*/
void free_matrix(size_t rows, size_t cols, int** a) 
{
    for (int i=0; i<rows; i++)
    {
        free(a[i]);
    }

    free(a);
}


/**
 *  allocates matrix of of size `rows` x `cols`.
*/
int** allocate_matrix(size_t rows, size_t cols) 
{
    int** a = (int**)malloc(rows * sizeof(int*));
    if (a == NULL) 
    {
        perror("allocationg matrix");
        return NULL;
    }

    for (int i=0; i<rows; i++) 
    {
        a[i] = (int*)malloc(cols * sizeof(int));
        if (a[i] == NULL) 
        {
            perror("allocationg matrix");
            return NULL;
        }   
    }

    return a;
}


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


/**
 * multiplies two squared matrices, using the standard, unicore approach.
*/
int** matrix_multiplication_squared(size_t rows, size_t cols, int** a, int** b)
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
    matrix_checksum(rows, cols, result_matrix);

    return result_matrix;
}


/**
 * multiplies two matrixes. checks if mutliplication is possible - are dimensions matching?
*/
int** matrix_multiplication(size_t rows1, size_t cols1, size_t rows2, size_t cols2, int** a, int** b) 
{

    int** result_matrix = allocate_matrix(rows1, cols2);  
    int sum;

    for (int i=0; i<rows1; i++) 
    {
        for (int j=0; j<cols2; j++) 
        {
            sum = 0;
            for (int k=0; k<cols1; k++)
            {
                sum += a[i][k] * b[k][j];
            }
            result_matrix[i][j] = sum;
        }
    }

    return result_matrix;
}


// copies entries from matrix[][] to a int**
// works good for test matrices, that are not dynamically allocated, 
// but need dynamic allocation for each thread, so they can work on one matrix in parallel.
void initialize_matrix(size_t rows, size_t cols, int** alloc_matrix, int matrix[rows][cols]) 
{
    for (int i=0; i<rows; i++) 
    {
        for (int j=0; j<cols; j++)
        {
            alloc_matrix[i][j] = matrix[i][j];
        }
    }
} 


// calculates the entries for one row.
void* thread_function_naive(void* arg) 
{
    param_t* param = arg;
    int** res = param->result_matrix;
    int** a   = param->a;
    int** b   = param->b;
    int a_i   = param->a_i;
    int a_j   = 0;
    int sz    = param->sz;
    int sum   = 0;

    for (int i=0; i<sz; i++)
    {
        sum = 0;
        for (int j=0; j<sz; j++)
        {
            sum += a[a_i][j] * b[j][i];
        }
        res[a_i][a_j] = sum;
        a_j += 1;
    }
    
    return NULL;
}


// creates a thread for each entry. therefore, `size` threads are created. 
int initialize_threads_naive(int size, int** a, int** b, int** result) 
{
    int       num_threads = size;
    pthread_t threads[num_threads];
    param_t*  arguments[num_threads];

    int**     result_matrix = allocate_matrix(size, size);

    // initialize arguments for thread
    for (int i=0; i<size; i++)
    {
        arguments[i] = malloc(sizeof(param_t));
        arguments[i]->a = a;
        arguments[i]->b = b;
        arguments[i]->result_matrix = result_matrix;
        arguments[i]->a_i = i;
        arguments[i]->sz = size;
    }

    // initialize threads
    for (int i=0; i<num_threads; i++)
    {
       
        int status = pthread_create(&threads[i], NULL, &thread_function_naive, (void*)arguments[i]);
        if (status != 0)
        {
            perror("thread initialisation");
            free_matrix(size, size, a);
            free_matrix(size, size, b);
            exit(EXIT_FAILURE);
        }
    }

    // join all threads
    for (int i=0; i<num_threads; i++)
    {
        int status = pthread_join(threads[i], NULL);
        // TODO: error handling
    }
    copy_matrix(size, size, result_matrix, result);
    matrix_checksum(size, size, result_matrix);

    // free argument-array
    for (int i=0; i<num_threads; i++)
    {
        free(arguments[i]);
    }

    free_matrix(size, size, result_matrix);
    return 1;    
}


double get_current_time()
{
    struct timespec now;
    clock_gettime(CLOCK_REALTIME, &now);
    return now.tv_sec + now.tv_nsec*1e-9;
}



/**
 * initializes NUM_THREADS threads and allocates their work.
 * workload is defined dynamically in parameters
 * seminaive, as this approach only works for matrices with sz = NUM_THREADS * z
 * where z is an integer
 * 
 * works only for squared matrices of size `sz` where `sz` is a multiple of `NUM_THREADS`
*/
int initialize_threads_seminaive(size_t sz, int** a, int** b, int** result) {

    pthread_t threads[NUM_THREADS];
    param_t* arguments[NUM_THREADS];
    int num_operations = sz / NUM_THREADS;

    int** result_matrix = allocate_matrix(sz, sz);

    // set up arguments
    for (int i=0; i<NUM_THREADS; i++)
    {
        arguments[i]        = malloc(sizeof(param_t));
        arguments[i]->a     = a;
        arguments[i]->b     = b;
        arguments[i]->result_matrix = result_matrix;
        arguments[i]->a_i   = i * num_operations;
        arguments[i]->sz    = sz;
        arguments[i]->num_rows = num_operations;
        arguments[i]->tid   = i;
    }

    // create threads
    for (int i=0; i<NUM_THREADS; i++) 
    {
        int status = pthread_create(&threads[i], NULL, &thread_function_seminaive, (void*)arguments[i]);
        if (status != 0)
        {
            perror("thread initialisation");
            free_matrix(sz, sz, a);
            free_matrix(sz, sz, b);
            exit(EXIT_FAILURE);
        }
    }

    // join threads
    for (int i=0; i< NUM_THREADS; i++) 
    {
        int status = pthread_join(threads[i], NULL);
        // TODO: error handling
    }

    copy_matrix(sz, sz, result_matrix, result);
    matrix_checksum(sz, sz, result_matrix);

    for (int i=0; i< NUM_THREADS; i++) 
    {
        free(arguments[i]);
    }

    // clean up 
    free_matrix(sz, sz, result_matrix);
    return 1;     
}


/**
 * thread function for 'seminaive' implementation.
 * 
*/
void* thread_function_seminaive(void* arg) {
    param_t* param = arg;
    int** res      = param->result_matrix;
    int** a        = param->a;
    int** b        = param->b;
    int a_i        = param->a_i;
    int og_ai      = a_i;
    int a_j        = 0;
    int sz         = param->sz;
    int num_rows   = param->num_rows;
    int sum        = 0;

    for (int k=0; k<num_rows; k++)
    {
        for (int i=0; i<sz; i++)
        {
            sum = 0;
            for (int j=0; j<sz; j++) 
            {
                sum += a[a_i][j] * b[j][i];
            }
            res[a_i][a_j] = sum;
            a_j+= 1;
        }
        a_i+= 1;
        a_j = 0; // reset column index after each row
    }
    
    return NULL;
}


/**
 * copies `soure` matrix to `destination` matrix pointer.
*/
void copy_matrix(size_t rows, size_t cols, int** source, int** destination) {
    for (int i=0; i<rows; i++) {
        for (int j=0; j<cols; j++) {
            destination[i][j] = source[i][j];
        }
    }
}


unsigned long long matrix_checksum(size_t rows, size_t cols, int** a) 
{
    long long checksum = 0;
    for (int i=0; i<rows; i++) 
    {
        for (int j=0; j<cols; j++) 
        {
            checksum+= a[i][j];
        }
    }

    printf("checksum: %lld \n", checksum);
    return checksum;
}


int calculate_num_operations(size_t rows, size_t cols) {
    size_t total_size = rows * cols;
    size_t num_threads = total_size / NUM_THREADS;

    printf("number of threads to be created: %zu\n", num_threads);
    return num_threads;
}


int calculate_rest_operations(size_t rows, size_t cols) {
    return 1;
}

/**
 * mxn * n'xp => mxp 
 * is n = n'?
*/
int check_matrix_dimensions(size_t rows1, size_t cols1, size_t rows2, size_t cols2)
{
    return cols1 == rows2;
}