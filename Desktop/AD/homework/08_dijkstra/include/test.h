#ifndef __TEST__
#define __TEST__

#include "heap.h"
#include <time.h>

/** @struct test function
 *  @brief This function is used to test the 
 *         implementations od Dijkstra algorithms.
 *
 *  It returns the running time.
 */
double test(pair (*f)(graph *, int), graph * G, int source);

#endif
