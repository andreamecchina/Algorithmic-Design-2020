#include "test.h"

double test(pair (*f)(graph*, int), graph* G, int source) {

  struct timespec requestStart, requestEnd;
  double accum;
  size_t rep = 100;
  
  pair temp_result;
  
  clock_gettime(CLOCK_REALTIME, &requestStart);
  for (size_t i = 0; i < rep; ++i) temp_result = f(G, source);

  clock_gettime(CLOCK_REALTIME, &requestEnd);

  accum = (requestEnd.tv_sec - requestStart.tv_sec) +
    (requestEnd.tv_nsec - requestStart.tv_nsec) / 1E9;
    
  free(temp_result.dist);
  free(temp_result.pred);

  return accum / rep;
}
