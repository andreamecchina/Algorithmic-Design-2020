#include "graph.h"
#include "array.h"
#include "heap.h"
#include "test.h"

int main(void) {

  size_t graph_size = 10;
  graph* G = build_graph(graph_size);

  printf("Test graph:\n");
  for (size_t i = 0; i < graph_size; i++) {
    for (size_t j = 0; j < G->V[i]; j++) {
      printf("starting node: %zu\tdestination node: %d\tweight: %d\n",
	     i, G->adj[i][j].id,  G->adj[i][j].weight);
    }
  }

  int source = 0;
  printf("\nSource %d\n", source);

  pair results_array = dijkstra_array(G, source);
  printf("\nArray based version: \n");
  for (size_t i = 0; i < graph_size; i++) {
    printf("node: %zu, distance: %d, predecessor: %d\n",
	   i, results_array.dist[i], results_array.pred[i]);
  }

  free(results_array.dist);
  free(results_array.pred);
  
  pair results_heap = dijkstra_heap(G, source); 
  printf("\nHeap based version: \n");
  for (size_t i = 0; i < graph_size; i++) {
    printf("node: %zu, distance: %d, predecessor: %d\n",
	   i, results_heap.dist[i], results_heap.pred[i]);
  }

  free(results_heap.dist);
  free(results_heap.pred);

  deallocate_graph(G);

  size_t n = (1 << 15);
    
  printf("\nPerformance test: \n");
  printf("Size\tOn Arrays\tOn Heaps\n");
  for (size_t j = 16; j <= n; j *= 2) {
    graph* H = build_graph(j);
    printf("%ld\t%f\t%f\n", j,
	   test(dijkstra_array, H, source),
	   test(dijkstra_heap, H, source));
    deallocate_graph(H);
  }
  
  return 0;
}
