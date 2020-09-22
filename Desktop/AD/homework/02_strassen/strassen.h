#ifndef __STRASSEN__

void strassen_matrix_multiplication(float **C, float const *const *const A,
                                    float const *const *const B, 
				    size_t n1, size_t n2, size_t n3);

void strassen_matrix_multiplication_opt(float **C, float const *const *const A,
                                        float const *const *const B,
                                        size_t n1, size_t n2, size_t n3);

#endif //__STRASSEN__
