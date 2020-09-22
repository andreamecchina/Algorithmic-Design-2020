#ifndef __HEAP_FUNCTIONS__
#define __HEAP_FUNCTIONS__

#include <stdlib.h>
#include <binheap_alt.h>

void *init_heap_alt(void *A, 
                const unsigned int num_of_elem, 
				const size_t elem_size, 
                total_order_type cmp);

void destroy_heap_alt(void *heap);

void keep_extracting_the_min_heap_alt(void *heap);
            
#endif
