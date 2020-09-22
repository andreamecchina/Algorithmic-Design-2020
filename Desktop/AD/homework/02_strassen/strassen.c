#include <math.h>

#include "matrix.h"

void sub_matrix_blocks(float **C, float const *const *const A,
		       float const *const *const B,
		       const size_t C_f_row, const size_t C_f_col,
		       const size_t A_f_row, const size_t A_f_col,
		       const size_t B_f_row, const size_t B_f_col,
		       const size_t n)
{
  for (size_t y = 0; y < n; y++) {
    for (size_t x = 0; x < n; x++) {
      C[y+C_f_row][x+C_f_col] =
	A[y+A_f_row][x+A_f_col] - B[y+B_f_row][x+B_f_col];
    }
  }
}

void sum_matrix_blocks(float **C, float const *const *const A,
                       float const *const *const B,
                       const size_t C_f_row, const size_t C_f_col,
                       const size_t A_f_row, const size_t A_f_col,
                       const size_t B_f_row, const size_t B_f_col,
                       const size_t n)
{
  for (size_t y = 0; y < n; y++) {
    for	(size_t x = 0; x < n; x++) {
      C[y+C_f_row][x+C_f_col] =	
        A[y+A_f_row][x+A_f_col] + B[y+B_f_row][x+B_f_col];
    }
  }
}

void naive_aux(float **C, float const *const *const A,
               float const *const *const B,
               const size_t C_f_row, const size_t C_f_col,
               const size_t A_f_row, const size_t A_f_col,
               const size_t B_f_row, const size_t B_f_col,
               const size_t n)
{
  for (size_t y = 0; y < n; y++) {
    for (size_t x = 0; x < n; x++) {
      float value = 0.0;
      for (size_t z = 0; z < n; z++) {
        value += A[y + A_f_row][z + A_f_col]*B[z + B_f_row][x + B_f_col];
      }
      C[y + C_f_row][x + C_f_col] = value;
    }
  }  
}

void naive_aux_opt(float **C, float const *const *const A,
                   float const *const *const B,
                   const size_t C_f_row, const size_t C_f_col,
                   const size_t A_f_row, const size_t A_f_col,
                   const size_t B_f_row, const size_t B_f_col,
                   const size_t n)
{
  for (size_t y = 0; y < n; y++) {
    for (size_t x = 0; x < n; x++) {
      C[y + C_f_row][x + C_f_col] = 0.0;
      for (size_t z = 0; z < n; z++) {
        C[y + C_f_row][x + C_f_col] += A[y + A_f_row][z + A_f_col]*B[z + B_f_row][x + B_f_col];
      }
    }
  }  
}

void strassen_aux(float **C, float const *const *const A,
		  float const *const *const B,
		  const size_t C_f_row, const size_t C_f_col,
		  const size_t A_f_row, const size_t A_f_col,
		  const size_t B_f_row, const size_t B_f_col,
		  const size_t n)
{
  if (n <= 64) {
    naive_aux(C, A, B,
	      C_f_row, C_f_col,
	      A_f_row, A_f_col,
	      B_f_row, B_f_col,
	      n);
    return;
  }

  size_t n2 = n/2; // This is the size of the blocks

  float ***S = (float ***)malloc(sizeof(float **) * 10);
  for (size_t i = 0; i < 10; i++) {
    S[i] = allocate_matrix(n2, n2);
  }

  float	***P = (float ***)malloc(sizeof(float **) * 7);
  for (size_t i = 0; i < 7; i++) {
    P[i] = allocate_matrix(n2, n2);
  }

  // S1 = B12 - B22
  sub_matrix_blocks(S[0], B, B,
		    0, 0,
		    B_f_row, B_f_col + n2,
		    B_f_row + n2, B_f_col + n2,
		    n2);

  // P1 = A11 x S1
  strassen_aux(P[0], A, (const float* const *const) S[0],
	       0, 0,
	       A_f_row, A_f_col,
	       0, 0,
	       n2);

  // S2 = A11 + A12
  sum_matrix_blocks(S[1], A, A,
                    0, 0,
                    A_f_row, A_f_col,
                    A_f_row, A_f_col + n2,
                    n2);

  // P2 = S2 x B22
  strassen_aux(P[1], (const float* const *const) S[1], B,
               0, 0,
               0, 0,
               B_f_row + n2, B_f_col + n2,
               n2);
  
  // S3 = A21 + A22
  sum_matrix_blocks(S[2], A, A,
                    0, 0,
                    A_f_row + n2, A_f_col,
                    A_f_row + n2, A_f_col + n2,
                    n2);

  // P3 = S3 x B11
  strassen_aux(P[2], (const float* const *const) S[2], B,
               0, 0,
               0, 0,
               B_f_row, B_f_col,
               n2);
  
  // S4 = B21 - B11
  sub_matrix_blocks(S[3], B, B,
                    0, 0,
                    B_f_row + n2, B_f_col,
                    B_f_row, B_f_col,
                    n2);
  // P4 = A22 x S4
  strassen_aux(P[3], A, (const float* const *const) S[3],
               0, 0,
	       A_f_row + n2, A_f_col + n2,
               0, 0,
               n2);
  
  // S5 = A11 + A22
  sum_matrix_blocks(S[4], A, A,
                    0, 0,
                    A_f_row, A_f_col,
                    A_f_row + n2, A_f_col + n2,
                    n2);
  
  // S6 = B11 + B22
  sum_matrix_blocks(S[5], B, B,
                    0, 0,
                    B_f_row, B_f_col,
                    B_f_row + n2, B_f_col + n2,
                    n2);
  // P5 = S5 x S6
  strassen_aux(P[4], (const float* const *const) S[4],
	       (const float* const *const) S[5],
               0, 0,
               0, 0,
               0, 0,
               n2);
  
  // S7 = A12 - A22
  sub_matrix_blocks(S[6], A, A,
                    0, 0,
                    A_f_row, A_f_col + n2,
                    A_f_row + n2, A_f_col + n2,
                    n2);
  
  // S8 = B21 + B22
  sum_matrix_blocks(S[7], B, B,
                    0, 0,
                    B_f_row + n2, B_f_col,
                    B_f_row + n2, B_f_col + n2,
                    n2);
  
  // P6 = S7 x S8
  strassen_aux(P[5], (const float* const *const) S[6],
	       (const float* const *const) S[7],
               0, 0,
               0, 0,
               0, 0,
               n2);
  
  // S9 = A11 - A21
  sub_matrix_blocks(S[8], A, A,
                    0, 0,
                    A_f_row, A_f_col,
                    A_f_row + n2, A_f_col,
                    n2);

  // S10 = B11 + B12
  sum_matrix_blocks(S[9], B, B,
                    0, 0,
                    B_f_row, B_f_col,
                    B_f_row, B_f_col + n2,
                    n2);
  
  // P7 = S9 x S10
  strassen_aux(P[6], (const float* const *const) S[8],
               (const float* const *const) S[9],
               0, 0,
               0, 0,
               0, 0,
               n2);

  // C11 = P5 + P4 - P2 + P6
  sum_matrix_blocks(C, (const float* const *const) P[4],
		    (const float* const *const) P[3],
                    C_f_row, C_f_col,
                    0, 0,
		    0, 0,
                    n2);

  sub_matrix_blocks(C, (const float* const *const) C,
                    (const float* const *const) P[1],
                    C_f_row, C_f_col,
		    C_f_row, C_f_col,
                    0, 0,
                    n2);

  sum_matrix_blocks(C, (const float* const *const) C,
                    (const float* const *const) P[5],
                    C_f_row, C_f_col,
                    C_f_row, C_f_col,
                    0, 0,
                    n2);
  
  // C12 = P1 + P2
  sum_matrix_blocks(C, (const float* const *const) P[0],
                    (const float* const *const) P[1],
                    C_f_row, C_f_col + n2,
                    0, 0,
                    0, 0,
                    n2);

  // C21 = P3 + P4
  sum_matrix_blocks(C, (const float* const *const) P[2],
                    (const float* const *const) P[3],
                    C_f_row + n2, C_f_col,
                    0, 0,
                    0, 0,
                    n2);

  // C22 = P5 + P1 - P3 - P7 
  sum_matrix_blocks(C, (const float* const *const) P[4],
                    (const float* const *const) P[0],
                    C_f_row + n2, C_f_col + n2,
                    0, 0,
                    0, 0,
                    n2);

  sub_matrix_blocks(C, (const float* const *const) C,
                    (const float* const *const) P[2],
                    C_f_row + n2, C_f_col + n2,
                    C_f_row + n2, C_f_col + n2,
                    0, 0,
                    n2);

  sub_matrix_blocks(C, (const float* const *const) C,
                    (const float* const *const) P[6],
                    C_f_row + n2, C_f_col + n2,
                    C_f_row + n2, C_f_col + n2,
                    0, 0,
                    n2);

  for (size_t i = 0; i < 10; i++) {
    deallocate_matrix(S[i], n2);
  }
  free(S);

  for (size_t i = 0; i < 7; i++) {
    deallocate_matrix(P[i], n2);
  }
  free(P);
  
}

void strassen_aux_opt(float **C, 
                      float const *const *const A,
		      float const *const *const B,
		      const size_t C_f_row, const size_t C_f_col,
		      const size_t A_f_row, const size_t A_f_col,
		      const size_t B_f_row, const size_t B_f_col,
		      const size_t n)
{
  if (n <= 64) {
    naive_aux(C, A, B,
	      C_f_row, C_f_col,
	      A_f_row, A_f_col,
	      B_f_row, B_f_col,
	      n);
    return;
  }

  size_t n2 = n/2; // This is the size of the blocks

  float **S0 = allocate_matrix(n2, n2);
  float **S1 = allocate_matrix(n2, n2);
  float **P = allocate_matrix(n2, n2);
  float **aux = allocate_matrix_zeros(n2, n2);

  // S1 = B12 - B22
  sub_matrix_blocks(S1, B, B,
		    0, 0,
		    B_f_row, B_f_col + n2,
		    B_f_row + n2, B_f_col + n2,
		    n2);

  // P1 = A11 x S1
  strassen_aux_opt(P, A, (const float* const *const) S1,
	           0, 0,
	           A_f_row, A_f_col,
	           0, 0,
	           n2);

  // C12 += P1
  sum_matrix_blocks(C, (const float* const *const) aux,
                    (const float* const *const) P,
                    C_f_row, C_f_col + n2,
                    0, 0,
                    0, 0,
                    n2);
  // C22 += P1
  sum_matrix_blocks(C, (const float* const *const) aux,
                    (const float* const *const) P,
                    C_f_row + n2, C_f_col + n2,
                    0, 0,
                    0, 0,
                    n2);

  // S2 = A11 + A12
  sum_matrix_blocks(S0, A, A,
                    0, 0,
                    A_f_row, A_f_col,
                    A_f_row, A_f_col + n2,
                    n2);

  // P2 = S2 x B22
  strassen_aux_opt(P, (const float* const *const) S0, B,
                   0, 0,
                   0, 0,
                   B_f_row + n2, B_f_col + n2,
                   n2);

  // C11 -= P2
  sub_matrix_blocks(C, (const float* const *const) aux,
                    (const float* const *const) P,
                    C_f_row, C_f_col,
                    0, 0,
                    0, 0,
                    n2);

  // C12 += P2
  sum_matrix_blocks(C, (const float* const *const) C,
                    (const float* const *const) P,
                    C_f_row, C_f_col + n2,
                    C_f_row, C_f_col + n2,
                    0, 0,
                    n2);
  
  // S3 = A21 + A22
  sum_matrix_blocks(S0, A, A,
                    0, 0,
                    A_f_row + n2, A_f_col,
                    A_f_row + n2, A_f_col + n2,
                    n2);

  // P3 = S3 x B11
  strassen_aux_opt(P, (const float* const *const) S0, B,
                   0, 0,
                   0, 0,
                   B_f_row, B_f_col,
                   n2);

  // C21 += P3
  sum_matrix_blocks(C, (const float* const *const) aux,
                    (const float* const *const) P,
                    C_f_row + n2, C_f_col,
                    0, 0,
                    0, 0,
                    n2);

  // C22 -= P3
  sub_matrix_blocks(C, (const float* const *const) C,
                    (const float* const *const) P,
                    C_f_row + n2, C_f_col + n2,
                    C_f_row + n2, C_f_col + n2,
                    0, 0,
                    n2);

  // S4 = B21 - B11
  sub_matrix_blocks(S1, B, B,
                    0, 0,
                    B_f_row + n2, B_f_col,
                    B_f_row, B_f_col,
                    n2);
  // P4 = A22 x S4
  strassen_aux_opt(P, A, (const float* const *const) S1,
                   0, 0,
	           A_f_row + n2, A_f_col + n2,
                   0, 0,
                   n2);

  // C11 += P4
  sum_matrix_blocks(C, (const float* const *const) C,
                    (const float* const *const) P,
                    C_f_row, C_f_col,
                    C_f_row, C_f_col,
                    0, 0,
                    n2);

  // C21 += P4
  sum_matrix_blocks(C, (const float* const *const) C,
                    (const float* const *const) P,
                    C_f_row + n2, C_f_col,
                    C_f_row + n2, C_f_col,
                    0, 0,
                    n2);

  // S5 = A11 + A22
  sum_matrix_blocks(S0, A, A,
                    0, 0,
                    A_f_row, A_f_col,
                    A_f_row + n2, A_f_col + n2,
                    n2);
  
  // S6 = B11 + B22
  sum_matrix_blocks(S1, B, B,
                    0, 0,
                    B_f_row, B_f_col,
                    B_f_row + n2, B_f_col + n2,
                    n2);

  // P5 = S5 x S6
  strassen_aux_opt(P, (const float* const *const) S0,
	           (const float* const *const) S1,
                   0, 0,
                   0, 0,
                   0, 0,
                   n2);

  // C11 += P5
  sum_matrix_blocks(C, (const float* const *const) C,
                    (const float* const *const) P,
                    C_f_row, C_f_col,
                    C_f_row, C_f_col,
                    0, 0,
                    n2);

  // C22 += P5
  sum_matrix_blocks(C, (const float* const *const) C,
                    (const float* const *const) P,
                    C_f_row + n2, C_f_col + n2,
                    C_f_row + n2, C_f_col + n2,
                    0, 0,
                    n2);

  // S7 = A12 - A22
  sub_matrix_blocks(S0, A, A,
                    0, 0,
                    A_f_row, A_f_col + n2,
                    A_f_row + n2, A_f_col + n2,
                    n2);
  
  // S8 = B21 + B22
  sum_matrix_blocks(S1, B, B,
                    0, 0,
                    B_f_row + n2, B_f_col,
                    B_f_row + n2, B_f_col + n2,
                    n2);
  
  // P6 = S7 x S8
  strassen_aux_opt(P, (const float* const *const) S0,
	           (const float* const *const) S1,
                   0, 0,
                   0, 0,
                   0, 0,
                   n2);

  // C11 += P6
  sum_matrix_blocks(C, (const float* const *const) C,
                    (const float* const *const) P,
                    C_f_row, C_f_col,
                    C_f_row, C_f_col,
                    0, 0,
                    n2);
  
  // S9 = A11 - A21
  sub_matrix_blocks(S0, A, A,
                    0, 0,
                    A_f_row, A_f_col,
                    A_f_row + n2, A_f_col,
                    n2);

  // S10 = B11 + B12
  sum_matrix_blocks(S1, B, B,
                    0, 0,
                    B_f_row, B_f_col,
                    B_f_row, B_f_col + n2,
                    n2);
  
  // P7 = S9 x S10
  strassen_aux_opt(P, (const float* const *const) S0,
                   (const float* const *const) S1,
                   0, 0,
                   0, 0,
                   0, 0,
                   n2);

  // C22 -= P7
  sub_matrix_blocks(C, (const float* const *const) C,
                    (const float* const *const) P,
                    C_f_row + n2, C_f_col + n2,
                    C_f_row + n2, C_f_col + n2,
                    0, 0,
                    n2);

  deallocate_matrix(S0, n2);
  deallocate_matrix(S1, n2);
  deallocate_matrix(P, n2);
  deallocate_matrix(aux, n2);

}

void strassen_matrix_multiplication(float **C, float const *const *const A,
                                    float const *const *const B,
				    size_t n1, size_t n2, size_t n3) 
{

  size_t longest = longest_size(n1, n2, n3);

  const size_t n = best_padding(longest, 64);

  float **A_aux = allocate_matrix_zeros(n, n);
  float **B_aux = allocate_matrix_zeros(n, n);
  float **C_aux = allocate_matrix_zeros(n, n);

  frame(A_aux, A, n1, n2);
  frame(B_aux, B, n2, n3);
   
  strassen_aux(C_aux, (float const *const *const) A_aux, (float const *const *const) B_aux,
	       0, 0,
	       0, 0,
	       0, 0,
	       n);
  frame(C, (float const *const *const) C_aux, n1, n3);

  deallocate_matrix(A_aux, n);
  deallocate_matrix(B_aux, n);
  deallocate_matrix(C_aux, n);
 
}

void strassen_matrix_multiplication_opt(float **C, float const *const *const A,
					float const *const *const B,
					size_t n1, size_t n2, size_t n3)
{

  size_t longest = longest_size(n1, n2, n3);

  const size_t n = best_padding(longest, 64);

  float **A_aux = allocate_matrix_zeros(n, n);
  float **B_aux = allocate_matrix_zeros(n, n);
  float **C_aux = allocate_matrix_zeros(n, n);

  frame(A_aux, A, n1, n2);
  frame(B_aux, B, n2, n3);
  
  strassen_aux_opt(C_aux, (float const *const *const) A_aux, (float const *const *const) B_aux,
                   0, 0,
		   0, 0,
		   0, 0,
		   n);

  frame(C, (float const *const *const) C_aux, n1, n3);

  deallocate_matrix(A_aux, n);
  deallocate_matrix(B_aux, n);
  deallocate_matrix(C_aux, n);

}
