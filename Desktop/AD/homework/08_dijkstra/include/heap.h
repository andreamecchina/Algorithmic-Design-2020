#ifndef __HEAP__
#define __HEAP__

#include "array.h"
#include "graph.h"
#include "binheap_alt.h"

/**********************************************************************                    
 * The extraction of the minimum from the heap is performed                      
 * swapping it with the last element and reducing the size of the heap.
 *                                                                                         
 * @param q is the binary heap.
 **********************************************************************/
int extract_min_heap(binheap_type* q);

/**********************************************************************                    
 * Updates the value of the distance when using the 
 * heap based representation of the priority queue.                  
 *
 * @q is the binary heap.
 * @param i is the index of the value to be changed.                     
 * @param new_dist is the new value to be inserted.
 **********************************************************************/
void update_distance_heap(binheap_type* q, int i, const void* new_dist);

/**********************************************************************                    
 * Updates the value of the distance and of 
 * the predecessor of a node when needed.                 
 *
 * @param q is the binaty heap.
 * @param i is the index of the node whose distance must be changed.      
 * @param j is the index of the node with the new distance.      
 * @param weight is the weight of the connecting edge.                     
 * @param dist is the distances array.
 * @param pred is the predecessors array.
 **********************************************************************/
void relax_distance_heap(binheap_type* q, int i, int j, int weight, int* dist, int* pred);

/**********************************************************************                    
 * Uses all of the functions of the heap based implementation 
 * of the queue to perform the Dijkstra algorithm.
 *
 * @param G is graph dealing with.                   
 * @param source is the source node for the algorithm.
 **********************************************************************/
pair dijkstra_heap(graph *G, int source);

#endif
