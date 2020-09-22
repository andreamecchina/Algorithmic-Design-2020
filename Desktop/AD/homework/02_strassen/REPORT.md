# Matrix Multiplication Homework

The makefile is generated running `cmake CMakeLists.txt`. The compilation is then simply performed with `make`.

## 1. Non Square Matrices Generalization

The matrix multiplication definition still holds when the dimensions of the matrices differ and its implementation is straightforward.

The generalization of the Strassen algorithm requires instead more care. A first idea is that of *padding*, which consists in

+ finding $i$ such that $2^i$ is greater or equal to the biggest size of the matrices,
+ creating two square auxiliary matrices of size $2^i$ whose non zero elements are only that coinciding to that of the original non square matrices when placed in the top left corner,
+ running the Strassen algorithm obtaing another matrix of size $2^i$ and then discarding the zero elements outside the target matrix.

This naive approach is quite memory inefficient. An improvement comes from noting that there is a threshold dimension, namely $64$, under which the naive multiplication is preferred to the Strassen algorithm.

It is then sufficient to pad up to the least value $k*2^i$ greater or equal to the biggest matrix dimension such that $k<64$. The largest matrix dimension is found using the function `longest_size` and the value of $i$ using the function `best_padding`. 

Another auxiliary function, `allocate_matrix_zeros`, is used to allocate the auxiliary matrices and the function `frame` is used to perform the padding operation.

This improved padding technique results in a much better memory usage.

## 2. Reducing Memory Allocations

A first improvement in memory allocation is obtained implementing the function `naive_aux_opt` so that the new values are directly computed into the final matrix and not stored in temporary variables and then pasted.

Nonetheless, the greatest advantages come from noting that

+ since at most two $S$ matrices are involved in the computation of each matrix $P$, it is possible to allocate just two $S$ matrices,
+ there's no need to allocate seven $P$ matrices but just one is sufficient if the final blocks of $C$ are partially computed everytime a $P$ matrix is avaiable.

These considerations are implemented in the function `strassen_aux_opt`. The optimized final user function for the matrix product is `strassen_matrix_multiplication_opt`.

The following table reports the execution times measured. $n_B$ is omitted since it must coincide with $m_A$ for the matrix product to be well defined.


| $n_A$ | $m_A$ | $m_B$ | Naive Alg.   | Strassen's Alg. | Strassen's Opt. | Same result |
| ----- | ----- | ----- | ------------ | --------------- | --------------- | ----------- |
| 1     | 7     | 3     | 0.000001 s   | 0.000025 s      | 0.000010 s      | 1           |
| 2     | 14    | 6     | 0.000003 s   | 0.000011 s      | 0.000037 s      | 1           |
| 4     | 28    | 12    | 0.000007 s   | 0.000038 s      | 0.000035 s      | 1           |
| 8     | 56    | 24    | 0.000031 s   | 0.000210 s      | 0.000203 s      | 1           |
| 16    | 112   | 48    | 0.000199 s   | 0.001367 s      | 0.001085 s      | 1           |
| 32    | 224   | 96    | 0.001413 s   | 0.009066 s      | 0.007554 s      | 1           |
| 64    | 448   | 192   | 0.011329 s   | 0.066873 s      | 0.054675 s      | 1           |
| 128   | 896   | 384   | 0.258780 s   | 0.456433 s      | 0.376677 s      | 1           |
| 256   | 1792  | 768   | 3.663378 s   | 3.165741 s      | 2.624370 s      | 1           |
| 512   | 3584  | 1536  | 36.068218 s  | 23.140998 s     | 18.416375 s     | 1           |
| 1024  | 7168  | 3072  | 297.899525 s | 161.461192 s    | 131.120015 s    | 1           |

The `same_matrix` function was updated to deal with $3$ matrices. The optimized implementation of the Strassen algorithm results in a noticeable improvement in the execution time.