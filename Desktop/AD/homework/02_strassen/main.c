#include <stdio.h>

#include "test.h"
#include "matrix.h"
#include "strassen.h"

int main(int argc, char *argv[]) {
  size_t n = 1 << 10;

  float **A = allocate_random_matrix(n, 7*n);
  float **B = allocate_random_matrix(7*n, 3*n);
  float **C0 = allocate_matrix(n, 3*n);
  float **C1 = allocate_matrix(n, 3*n);
  float **C2 = allocate_matrix(n, 3*n);
  
  printf("n_A\tm_A\tm_B\tNaive Alg.\tStrassen's Alg.\tStrassen's Opt.\tSame result\n");
  for (size_t j = 1; j <= n; j *= 2) {

    printf("%ld\t%ld\t%ld\t", j,  7*j, 3*j);
    fflush(stdout);

    printf("%lf\t", test(naive_matrix_multiplication, C0, A, B, j, 7*j, 3*j));
    fflush(stdout);

    printf("%lf\t", test(strassen_matrix_multiplication, C1, A, B, j, 7*j, 3*j));
    fflush(stdout);

    printf("%lf\t", test(strassen_matrix_multiplication_opt, C2, A, B, j, 7*j, 3*j));
    fflush(stdout);

/*
if (j == 32) {
printf("\n\n");
  for (size_t y = 0; y < j; y++) {
    for (size_t x = 0; x < 7*j; x++) {
      printf("%d ", (int) A[y][x]);
    }
    printf("\n");
  }
printf("\n\n");
  for (size_t y = 0; y < 7*j; y++) {
    for (size_t x = 0; x < 3*j; x++) {
      printf("%d ", (int) B[y][x]);
    }
    printf("\n");
  }
printf("\n\n");
  for (size_t y = 0; y < j; y++) {
    for (size_t x = 0; x < 3*j; x++) {
      printf("%d ", (int) C0[y][x]);
    }
    printf("\n");
  }
printf("\n\n");
  for (size_t y = 0; y < j; y++) {
    for (size_t x = 0; x < 3*j; x++) {
      printf("%d ", (int) C1[y][x]);
    }
    printf("\n");
  }

printf("\n\n");
  for (size_t y = 0; y < j; y++) {
    for (size_t x = 0; x < 3*j; x++) {
      printf("%d ", (int) C2[y][x]);
    }
    printf("\n");
  }

}
*/   
    printf("%d\n", same_matrix((float const *const *const)C0,
                               (float const *const *const)C1,
                               (float const *const *const)C2, j, 3*j));

  }

  deallocate_matrix(A, n);
  deallocate_matrix(B, 7*n);
  deallocate_matrix(C0, n);
  deallocate_matrix(C1, n);
  deallocate_matrix(C2, n);

  return 0;
}
