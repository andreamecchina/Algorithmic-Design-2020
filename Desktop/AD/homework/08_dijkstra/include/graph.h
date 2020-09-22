#ifndef __GRAPH__
#define __GRAPH__

#include <stdlib.h>

/** @struct adjnode
 *  @brief A structure to represent adjacency nodes in the
 *         adjacency list based representation of graphs.
 */
typedef struct adjnode {
  int id;
  int weight;       
} adjnode;

/** @struct graph                                                     
 *  @brief A structure to represent adjacency
 *         list based representation of graphs.                     
 */
typedef struct graph {
  size_t dim;
  int* V;
  adjnode** adj;
} graph;

/**********************************************************************
 * The initialisation of a graph with random values.
 * It makes use of the adjacency list representation of graphs.
 *
 * @param dim is the number of nodes in the graph.
 **********************************************************************/
graph* build_graph(size_t dim);

/**********************************************************************
 * Deallocates a graph.
 *
 * @param G it the graph to be deallocated.
 **********************************************************************/
void deallocate_graph(graph* G);

#endif
