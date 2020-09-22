# Binary Heaps Homework 2

The makefile is generated running `cmake CMakeLists.txt`. The compilation is then simply performed with `make`.

The plot in point $1$ is obtained using the Gnuplot script `plot_alt.gp` in the `tests` directory. The data used for the plot are contained in the files `time_alt.dat` and `time.dat` in the same directory.

## 1. Avoid Swapping Array

The implementation for this exercise is contained in the files `binheap_alt.c` and in its relative header `binheap_alt.h`.

Two auxiliary arrays of unsigned integers are included as part of the structure `binheap_type`, they are

+ `key_pos` reporting the position of the key of a node,

+ `rev_pos` reporting the node corresponding to a given position.

These arrays are allocated with dimension `max_size` and initialized with the values running from $0$ to `max_size`.

The macros `ADDR` and `INDEX_OF` are rewritten making use of these two auxiliary arrays.

The swap operation can now be performed between the unsigned integers of the two arrays and not between the input elements of $A$, which are allowed to any complex structure in principle.

Also the unsigned integer `real_dim` is included as part of the structure to keep trace of where a new node can be inserted. This value is initialized as the number of elements in the heap.

A check is added to the function to decrease a key value to deal with the case of a node index being $0$. When inserting a new node `real_dim` is increased by $1$ and also the arrays `key_pos` and `rev_pos` are updated. 

The test `test_insert_value_alt` is used to check that everything is working correctly. The other test `test_delete_min_alt` measures the time took to build $100$ heap instances and delete them one value at the time. These size $n$ of the problem keep increasing. 

The following plot compares the execution times for the two heap implementation. Also the new heap implementation looks like scaling compatibly with the expected behaviour of $\mathcal{O}(n\log n)$.

![](/Users/Mec/Desktop/AD/homework/04_bin_heaps/tests/plot_alt.svg)

The heap implementation that avoids to swap the elements of $A$ takes about half of the time with respect to the previous implementation. This may be due to fact the elements filling the array $A$ are floating point numbers occupying two times the space of an unsigned integer.

Since the elements of $A$ can be any structure anyhow complex, just satisfying a total order relation, the save in time due to the swapping of only unsigned integers can be very relevant.

## 2. Pseudo Code Complexity

The algorithm under investigation is reported in the cell below, where is $A$ an array.

```pseudocode
1. def Ex2(A)
2. 		D ← build(A)
3. 		while ¬ is_empty(D)
4. 			extract_min(D)
5. 		end while
6. end def 
```

Let $|D|$ denotes the cardinality of $D$. When the time complexities are assumed to be $\text{build},\text{is_empty}\in\Theta(1)$ and $\text{extract_min}\in\Theta(|D|)$ it follows that

+ line $2$ costs $\Theta(1)$,
+ line $3$ costs $\Theta(1)$ and it is repeated $\Theta(|D|)$ times,
+ line $4$ costs $\Theta(|D|)$ and it is repeated $\Theta(|D|)$ times.

Actually the loop check function is executed one more time the function inside the loop but this can be neglected. It follows then that the overall complexity is $\Theta(1+1*|D|+|D|*|D|)=\Theta(|D|^2)$.

If instead the complexities are $\text{build}\in\Theta(|A|)$, $\text{is_empty}\in\Theta(1)$ and $\text{extract_min}\in\mathcal{O}(\log|D|)$ it follows that

+ line $2$ costs $\Theta(|A|)$,
+ line $3$ costs $\Theta(1)$ and it is repeated $\Theta(|D|)$ times,
+ line $4$ costs $\mathcal{O}(\log|D|)$ and it is repeated $\Theta(|D|)$ times.

The loop check function is again assumed to be repeated the same number of times than function inside the loop. The cardinaly of $A$ and $D$ is assumed to be the same which means $|A|=|D|$. It follows then that the overall complexity is $\Theta(|A|+1*|D|)+\mathcal{O}(|D|*\log|D|)\sim\mathcal{O}(|D|*\log|D|)$.