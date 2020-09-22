#include <binheap_alt.h>

#define PARENT(node) ((node-1)/2)
#define LEFT_CHILD(node) (2*(node) + 1)
#define RIGHT_CHILD(node) (2*(node + 1))

#define VALID_NODE(H, node) ((H)->num_of_elem>(node))

#define ADDR(H, node) ((H)->A+(((H)->key_pos)[node])*((H)->key_size))
#define INDEX_OF(H, addr) H->rev_pos[(((addr)-((H)->A))/(H)->key_size)]

int is_heap_empty_alt(const binheap_type *H)
{
  return H->num_of_elem==0;
}

const void *min_value_alt(const binheap_type *H)
{
  if (is_heap_empty_alt(H))
    return NULL;
  
  // the minimum is stored in the
  // root a.k.a. A[0]
  return ADDR(H, 0);
}

const void *extract_min_alt(binheap_type *H)
{
  if (is_heap_empty_alt(H))
    return NULL;

  // swapping the keys among the root (A[0])
  // and the right-most leaf of the
  // last level (A[num_of_elements-1])
  swap_keys_alt(H, 0, H->num_of_elem-1);

  // deleting the right-most leaf of thee
  // last level (A[num_of_elem-1])
  H->num_of_elem--;

  heapify_alt(H, 0);

  return ADDR(H, H->num_of_elem);
}

void swap_keys_alt(binheap_type *H, unsigned int n_a, unsigned int n_b)
{

  unsigned int pos_a = H->key_pos[n_a];
  unsigned int pos_b = H->key_pos[n_b];

  H->key_pos[n_a] = pos_b;
  H->key_pos[n_b] = pos_a;
  
  unsigned int tmp = H->rev_pos[pos_a];

  H->rev_pos[pos_a] = H->rev_pos[pos_b];
  H->rev_pos[pos_b] = tmp;
}

void heapify_alt(binheap_type *H, unsigned int node)
{
  unsigned int dst_node = node, child;

  do {
    node = dst_node;

    // find the minimum among node and
    // its children                                          
    child = RIGHT_CHILD(node);

    if (VALID_NODE(H, child) && H->leq(ADDR(H, child), ADDR(H, dst_node))) { 
      dst_node = child;
    }

    child = LEFT_CHILD(node);
    if (VALID_NODE(H, child) && H->leq(ADDR(H, child), ADDR(H, dst_node))) {
      dst_node = child;
    }

    // if the minimum is not in node
    // swap the keys                                           
    if (dst_node != node) {
      swap_keys_alt(H, dst_node, node);
    }
    
  } while (dst_node != node);
}

const void *find_the_max_alt(void *A, 
			     const unsigned int num_of_elem,
			     const size_t key_size, 
			     total_order_type leq)
{
  if(num_of_elem==0){
    return NULL;
  }

  const void *max_value = A;
  
  // for all the values in A
  for (const void *addr=A+key_size;
       addr!=A+num_of_elem*key_size;
       addr+=key_size)
    {
      // if addr > max_value
      if (!leq(addr, max_value)) {
	max_value = addr;
      }
    }
  
  return max_value;
}

binheap_type *build_heap_alt(void *A, 
			     const unsigned int num_of_elem,
			     const unsigned int max_size,  
			     const size_t key_size, 
			     total_order_type leq)
{
  binheap_type *H = (binheap_type *) malloc(sizeof(binheap_type));

  H->A = A;
  H->num_of_elem = num_of_elem;
  H->max_size = max_size;
  H->key_size = key_size;
  H->leq = leq;
  H->max_order_value = malloc(key_size);

  H->rev_pos = (unsigned int *) malloc(sizeof(unsigned int)*max_size);
  H->key_pos = (unsigned int *) malloc(sizeof(unsigned int)*max_size);

  H->real_dim = num_of_elem;
  
  if (num_of_elem==0) {
    return H;
  }

  // find the maximum among A[:num_of_elem-1]
  // and store it in max_order_value
  const void *value = find_the_max_alt(A, num_of_elem, key_size, leq);

  memcpy(H->max_order_value, value, key_size);

  for (unsigned int i=0; i<num_of_elem; i++) {
    H->key_pos[i] = i;
    H->rev_pos[i] = i;
  }

  // fix the heap property from the second
  // last level up to the root
  for(unsigned int i=num_of_elem/2; i>0; i--) {
    heapify_alt(H, i);
  }
  heapify_alt(H, 0);

  return H;
}

void delete_heap_alt(binheap_type *H)
{
  free(H->max_order_value);
  free(H->key_pos);
  free(H->rev_pos);
  free(H);
  
}

const void *decrease_key_alt(binheap_type *H, void *node, const void *value)
{
  unsigned int node_idx = INDEX_OF(H, node);

  // if the node does not belong to H or *value>*node
  // return NULL
  if (!VALID_NODE(H, node_idx) || !(H->leq(value, node))) {
    return NULL;
  }

  memcpy(node, value, H->key_size);

  unsigned int parent_idx = PARENT(node_idx);

  // if node_idx==0 then parent does not exist
  if (node_idx==0) {   
    parent_idx = 0;
  }

  void *parent = ADDR(H, parent_idx);

  while((node_idx != 0) && (!H->leq(parent, value))) {

    // swap parent and node keys
    swap_keys_alt(H, parent_idx, node_idx);

    // focus on the node's parent
    node = parent;
    node_idx = parent_idx;

    parent_idx = PARENT(node_idx);

    // if node_idx==0 the parent does not exists
    if (node_idx==0) {   
      parent_idx = 0;
    }

    parent = ADDR(H, parent_idx);

  }

    return node;
}

const void *insert_value_alt(binheap_type *H, const void *value)
{

  // if the heap is already full
  if (H->max_size == H->real_dim) {
    return NULL;
  }

  // if the new value is > than *max_order_value
  if (H->num_of_elem==0 || !H->leq(value, H->max_order_value)) {
    memcpy(H->max_order_value, value, H->key_size);
  }

  H->key_pos[H->num_of_elem] = H->real_dim;
  H->rev_pos[H->real_dim] = H->num_of_elem;

  // get the position of the new node
  void *new_node_addr = ADDR(H, H->num_of_elem);
  memcpy(new_node_addr, H->max_order_value, H->key_size);

  // increase the size of the heap
  H->num_of_elem++;
  H->real_dim++;

  // decrease the key of the new node
  return decrease_key_alt(H, new_node_addr, value);
}

void print_heap_alt(const binheap_type *H, 
		    void (*key_printer)(const void *value))
{
  unsigned int next_level_node = 1; // stores the index of the
                                    // left-most node of the
                                    // next level

  for (unsigned int node = 0; node < H->num_of_elem; node++) {
    if(node == next_level_node) {
      printf("\n");
      next_level_node=LEFT_CHILD(node);
    } else {
      printf("\t");
    }

    key_printer(ADDR(H, node));
  }
  printf("\n");
}
