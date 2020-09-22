#ifndef __MATRIX__
#include <stdlib.h>

int best_padding(int actual_size, int Q);

size_t longest_size(const size_t n1, const size_t n2, const size_t n3);

void frame(float **A_aux, float const *const *const A, const size_t n1, const size_t n2);

void naive_matrix_multiplication(float **C, float const *const *const A,
                                 float const *const *const B,
                                 const size_t n1, const size_t n2, const size_t n3);

int same_matrix(float const *const *const A, 
                float const *const *const B,
	        float const *const *const C,
                const size_t rows, const size_t cols);

float **allocate_matrix(const size_t rows, const size_t cols);

float **allocate_matrix_zeros(const size_t rows, const size_t cols);

void deallocate_matrix(float **A, const size_t rows);

float **allocate_random_matrix(const size_t rows, const size_t cols);

#endif //__MATRIX__