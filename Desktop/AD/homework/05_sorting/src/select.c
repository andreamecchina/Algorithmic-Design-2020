#include "select.h"
#include "quick_sort.h"
#include "swap.h"

#define ADDR(A, idx, elem_size) ((A)+((idx)*(elem_size)))

int are_equal(const void* a, const void* b, total_order leq)
{
  return leq(a, b) && leq(b, a);
}

pair tripartition(void *A,
		  size_t i,
		  size_t j,
		  size_t p,
		  const size_t elem_size,
		  total_order leq)
{
  swap(ADDR(A, p, elem_size), ADDR(A, i, elem_size), elem_size);
  p = i;
  i++;
  j--;
  
  unsigned int s = 0;

  while (i <= j) {
 
    if (leq(ADDR(A, i, elem_size), ADDR(A, p, elem_size)) &&
	!(are_equal(ADDR(A, i, elem_size), ADDR(A, p, elem_size), leq))) {
      swap(ADDR(A, i, elem_size), ADDR(A, p-s, elem_size), elem_size);
      p = i;
      i++;
    } else if (leq(ADDR(A, p, elem_size), ADDR(A, i, elem_size)) &&
	       !(are_equal(ADDR(A, i, elem_size), ADDR(A, p, elem_size), leq))) {
      swap(ADDR(A, i, elem_size), ADDR(A, j, elem_size), elem_size);
      j--;
    } else{
      p = i;
      i++;
      s++;
    }
  }
         
  swap(ADDR(A, p, elem_size), ADDR(A, j, elem_size), elem_size);

  pair k;
  k.left = j-s;
  k.right = j;
  
  return k;
}

unsigned int select_pivot(void* A,
			  const unsigned int n,
			  const size_t elem_size, total_order leq)
{

  if (n < 10) {
    quick_sort(A, n, elem_size, leq);
    return n/2;
  }
    
  unsigned int chunks = n/5;
  unsigned int c_l, c_r;
  
  for (unsigned int c = 0; c < chunks; c++) {
    c_l = 1 + c*5;
    c_r = 5 + c*5;

    quick_sort(ADDR(A, c_l, elem_size), c_r-c_l, elem_size, leq);
    
    swap(ADDR(A, c, elem_size), ADDR(A, c_l+2, elem_size), elem_size);
  }
    
  return select_index(A, chunks-1, chunks/2, elem_size, leq);
}

unsigned int select_index(void *A,
			  const unsigned int n,
			  const unsigned int i,
			  const size_t elem_size,
			  total_order leq)
{
  if (n < 10) {
    quick_sort(A, n, elem_size, leq);
    return i;
  }
    
  unsigned int p = select_pivot(A, n, elem_size, leq);
  
  pair k = tripartition(A, 0, n, p, elem_size, leq);
  
  if (i < k.left) {
    return select_index(A, k.left-1, i, elem_size, leq);
  }
  
  if (i > k.right) {
    return select_index(ADDR(A, k.right, elem_size), n-k.right-1, i, elem_size, leq);
  }
  
  return i;
}

void quicksort_aux(void *A,
		   size_t l,
		   size_t r,
		   const size_t elem_size,
		   total_order leq)
{
  while (l < r) {

    unsigned int p = l + select_pivot(ADDR(A, l, elem_size), r-l, elem_size, leq);
    pair k = tripartition(A, l, r, p, elem_size, leq);
    
    quicksort_aux(A, l, k.left, elem_size, leq);
    l = k.right + 1;
  }
}

void quick_sort_select(void *A, const unsigned int n,
		       const size_t elem_size,
		       total_order leq)
{
  quicksort_aux(A, 0, n, elem_size, leq);
}
