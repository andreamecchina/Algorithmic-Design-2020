#ifndef __TEST__


double test(void (*f)(float **,
	              float const *const *const,
	              float const *const *const,
	              size_t, size_t, size_t), 
	    float **C, float** A, float **B, 
            size_t n1, size_t n2, size_t n3);

#endif // __TEST__
