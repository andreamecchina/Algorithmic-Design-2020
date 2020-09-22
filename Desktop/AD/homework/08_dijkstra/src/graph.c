#include "graph.h"

#define max_neighbours 5
#define max_weight 10

graph* build_graph(size_t dim) {
  
  graph* G = (graph*)malloc(sizeof(graph));
  G->dim = dim;
  G->V = malloc(sizeof(int)*dim);
  G->adj = malloc(sizeof(adjnode*)*dim);

  for (size_t i = 0; i < dim; i++) {
    G->V[i] = rand()%max_neighbours;
    G->adj[i] = malloc(sizeof(adjnode)*G->V[i]);
    
    int* aux = malloc(sizeof(int)*G->V[i]);

    for (size_t j = 0; j < G->V[i]; j++) {
      G->adj[i][j].id = rand()%dim;

      size_t temp = 0;
      while (temp < G->V[i]) {

	if (G->adj[i][j].id == aux[temp]) {
          G->adj[i][j].id = rand()%dim;
          temp = 0;
          continue;
        }
	
        temp++;
      }
      
      aux[j] = G->adj[i][j].id;
      G->adj[i][j].weight = 1+rand()%max_weight;

    }
    
    free(aux);
  }
  
  return G;
}

void deallocate_graph(graph* G) {
  free(G->V);

  for (size_t i = 0; i < G->dim; i++) {
    free(G->adj[i]);
  }

  free(G->adj);
  free(G);
}
