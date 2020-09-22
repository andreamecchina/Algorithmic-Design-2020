#include "bubble_sort.h"
#include "swap.h"

#define ADDR(A, idx, elem_size) ((A)+((idx)*(elem_size)))

void bubble_sort(void *A, const unsigned int n, 
                 const size_t elem_size, 
                 total_order leq)
{
  for (unsigned int i = n-1; i >= 1; i--) {
    for (unsigned int j = 0; j<i; j++) {
      if (leq(ADDR(A, j+1, elem_size), ADDR(A, j, elem_size))) {
	swap(ADDR(A, j, elem_size), ADDR(A, j+1, elem_size), elem_size);
      }
    }
  }
}
