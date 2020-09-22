#ifndef __ARRAY__
#define __ARRAY__

#include "graph.h"
#include <stdio.h>

#define infty 9999
#define NIL -1

/** @struct queue
 *  @brief A priority queue for
 *         undiscovered nodes.
 */
typedef struct queue {
  int* array;
  size_t size;
} queue;

/** @struct pair
 *  @brief To store distances and
 *         predecessors arrays.
 */
typedef struct pair {
  int* dist;       
  int* pred;       
} pair;

/**********************************************************************
 * The initialisation of the priority queue.
 *
 * @param dim is the number of nodes in the graph.
 **********************************************************************/
queue* build_queue(size_t dim);

/**********************************************************************                    
 * The extraction of the minimum from the queue is performed                      
 * swapping it with the last element and reducing the size of the queue.
 *                                                                                         
 * @param q is the priority queue.                                         
 * @param dist is the distances array.
 **********************************************************************/
int extract_min_array(queue* q, int* dist);

/**********************************************************************                    
 * Updates the value of the distance when using the 
 * array based representation of the priority queue.                  
 *
 * @param i is the index of the value to be changed.                     
 * @param new_dist is the new value to be inserted.
 * @param dist is the distances array.
 **********************************************************************/
void update_distance_array(int i, int new_dist, int* dist);

/**********************************************************************                    
 * Initialises the distances and the 
 * predecessors of the nodes in the graph.         
 *
 * @param G is graph dealing with.                     
 * @param dist is the distances array.
 * @param pred is the predecessors array.
 **********************************************************************/
void init_sssp(graph *G, int* dist, int* pred);

/**********************************************************************                    
 * Updates the value of the distance and of 
 * the predecessor of a node when needed.                 
 *
 * @param i is the index of the node whose distance must be changed.      
 * @param j is the index of the node with the new distance.      
 * @param weight is the weight of the connecting edge.                     
 * @param dist is the distances array.
 * @param pred is the predecessors array.
 **********************************************************************/
void relax_distance_array(int i, int j, int weight, int* dist, int* pred);

/**********************************************************************                    
 * Uses all of the functions of the array based implementation 
 * of the queue to perform the Dijkstra algorithm.
 *
 * @param G is graph dealing with.                   
 * @param source is the source node for the algorithm.
 **********************************************************************/
pair dijkstra_array(graph *G, int source);

#endif
