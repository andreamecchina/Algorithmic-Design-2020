#include "heap.h"

int extract_min_heap(binheap_type* q) {
  const void* n = extract_min_alt(q);
  return (n-q->A) / q->key_size;
}

void relax_distance_heap(binheap_type* q, int id_u, int id_v, int weight, int* dist, int* pred) {
  int* dist_temp = q->A;
  
  if ((dist_temp[id_u] + weight) < dist_temp[id_v]) {
    int temp = dist_temp[id_u] + weight;

    update_distance_heap(q, id_v, (void*) &temp);
    pred[id_v] = id_u;
  }
}

void update_distance_heap(binheap_type* q, int id_u, const void* new_dist) {
  void * ptr_id = q->A + (id_u)*(q->key_size);
  decrease_key_alt(q, ptr_id, new_dist);
}
   
pair dijkstra_heap(graph* G, int source) {
  int* dist = malloc(sizeof(int)*G->dim);
  int* pred = malloc(sizeof(int)*G->dim);
    
  init_sssp(G, dist, pred);
  dist[source] = 0;
    
  binheap_type* q = build_heap_alt(dist, G->dim, G->dim, sizeof(int), leq_int);
    
  while (!is_heap_empty_alt(q)) {
    int v = extract_min_heap(q);
    
    for (size_t i = 0; i < G->V[v]; i++) {
      relax_distance_heap(q, v,
			  G->adj[v][i].id,
			  G->adj[v][i].weight,
			  dist, pred);
    }  
  }
  
  delete_heap_alt(q);

  pair results;
  results.dist = dist;
  results.pred = pred;
  
  return results;
}