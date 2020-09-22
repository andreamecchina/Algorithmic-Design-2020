#include <stdlib.h>
#include <string.h>

#include "heap_functions_alt.h"

void *init_heap_alt(void *A, 
                const unsigned int num_of_elem, 
                const size_t elem_size, 
                total_order_type cmp)
{
  return (void *)build_heap_alt(A, num_of_elem, 
                                num_of_elem, elem_size, cmp);
}

void destroy_heap_alt(void *heap) 
{
  delete_heap_alt(heap);
}

void keep_extracting_the_min_heap_alt(void *heap)
{
  while (!is_heap_empty_alt((binheap_type *)heap)) {
    extract_min_alt((binheap_type *)heap);
  }
}