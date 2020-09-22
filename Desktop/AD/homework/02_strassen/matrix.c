#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "matrix.h"


int best_padding(int actual_size, int threshold) {
    int cnt = 0;
    int n = actual_size;
    while(n > threshold) {
        cnt++;
        n /= 2;
    }

    if (actual_size % (1<<cnt) == 0) {
        return actual_size;
    } else {
        return actual_size + (1<<cnt) - actual_size % (1<<cnt);
    }
}

size_t longest_size(const size_t n1,
                    const size_t n2,
                    const size_t n3)
{

  if (n1 >= n2 && n1 >= n3) {
    return n1;
  }

  if (n2 >= n1 && n2 >= n3) {
    return n2;
  }
 
  if (n3 >= n1 && n3 >= n2) {
    return n3;
  }

  return 0;
  
}

void frame(float **A_aux, float const *const *const A,
	   const size_t n1, const size_t n2)
{
  for (size_t y = 0; y < n2; y++) {
    for (size_t x = 0; x < n1; x++) {
      A_aux[x][y] = A[x][y];
    }
  }
}

void naive_matrix_multiplication(float **C,
				 float const *const *const A,
				 float const *const *const B,
				 const size_t n1,
				 const size_t n2,
				 const size_t n3) 
{  
  for (size_t y = 0; y < n1; y++) {
    for (size_t x = 0; x < n3; x++) {
      float value = 0.0;
      for (size_t z = 0; z < n2; z++) {
	value += A[y][z]*B[z][x];
      }
      C[y][x] = value;
    }
  }
}

int same_matrix(float const *const *const A,
		float const *const *const B,
                float const *const *const C,
		const size_t rows, const size_t cols) {
  for (size_t i = 0; i < rows; i++) {
    for (size_t j = 0; j < cols; j++) {
      if (A[i][j] != B[i][j] || A[i][j] != C[i][j]) {
        return 0;
      }
    }
  }

  return 1;
}

float **allocate_matrix(const size_t rows, const size_t cols) {
  float **M = (float **)malloc(sizeof(float *) * rows);

  for (size_t i = 0; i < rows; i++) {
    M[i] = (float *)malloc(sizeof(float) * cols);
  }

  return M;
}

float **allocate_matrix_zeros(const size_t rows, const size_t cols) {
  float **M = (float **)malloc(sizeof(float *) * rows);

  for (size_t i = 0; i < rows; i++) {
    M[i] = (float *)calloc(cols, sizeof(float));
  }

  return M;
}

void deallocate_matrix(float **A, const size_t rows) {
  for (size_t i = 0; i < rows; i++) {
    free(A[i]);
  }

  free(A);
}

float **allocate_random_matrix(const size_t rows, const size_t cols) {
  
  float **A = allocate_matrix(rows, cols);
  
  srand(10);
  for (size_t i = 0; i < rows; i++) {
    for (size_t j = 0; j < cols; j++) {
      A[i][j] = (rand() - RAND_MAX / 2) % 5;
    }
  }

  return A;
}

