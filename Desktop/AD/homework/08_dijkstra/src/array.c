#include "array.h"

queue *build_queue(size_t dim) {
  queue *queue = malloc(sizeof(queue));
  
  queue->size = dim;
  queue->array = malloc(sizeof(int)*dim);
  
  for (size_t i = 0; i < dim; i++) {
    queue->array[i] = i;
  }
  return queue;
}

void swap(int* arr, int i, int j) {
  int temp;
  temp = arr[i];
  
  arr[i] = arr[j];
  arr[j] = temp;
}

int extract_min_array(queue* q, int* dist) {
  size_t index = 0;
  
  for (size_t i = 1; i < q->size; i++) {
    if (dist[q->array[i]] < dist[q->array[index]]) {
      index = i;
    }
  }
  swap(q->array, q->size-1, index);
  q->size--;
  
  return q->size;
}

void update_distance_array(int id_u, int new_dist, int* dist) {
  dist[id_u] = new_dist;
}

void init_sssp(graph *G, int* dist, int* pred) {
  for (size_t i = 0; i < G->dim; i++) {
    dist[i] = infty;
    pred[i] = NIL;
  }
}

void relax_distance_array(int id_u, int id_v, int weight, int* dist, int* pred) {
  if (dist[id_u] + weight < dist[id_v]) {
    update_distance_array(id_v, dist[id_u]+weight, dist);
    pred[id_v] = id_u;
  }
}

pair dijkstra_array(graph* G, int source) {
  int* dist = malloc(sizeof(int)*G->dim);
  int* pred = malloc(sizeof(int)*G->dim);
  
  init_sssp(G, dist, pred); 
  dist[source] = 0;
  
  queue* q = build_queue(G->dim);
  
  while (!(q->size == 0)) {
    int v = extract_min_array(q, dist);
    
    for (size_t i = 0; i < G->V[q->array[v]]; i++) {
      relax_distance_array(q->array[v],
			   G->adj[q->array[v]][i].id,
			   G->adj[q->array[v]][i].weight,
			   dist, pred);
    } 
  }
  
  free(q->array);
  free(q);
  
  pair results;
  results.dist = dist;
  results.pred = pred;
  
  return results;
}
