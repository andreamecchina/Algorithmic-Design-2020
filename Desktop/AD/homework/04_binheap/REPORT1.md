# Binary Heaps Homework 1

The makefile is generated running `cmake CMakeLists.txt`. The compilation is then simply performed with `make`.

The plot in point $3$ is obtained using the Gnuplot script `plot.gp` in the `tests` directory. The data used for the plot are contained in the file `time.dat` in the same directory.

## 1. Array Based Implementation

The array based implementation of the binary heap together with its characteristic functions was already performed during the lectures.

## 2. Heapify Implementation

The implementation of an iterative version of the heapify function was already performed during the lectures.

## 3. Results

The executable `test_delete_min` tests the execution time of extracting the minimum value with respect to the total order from an heap and compares it to the time taken to extract the same minimum relative to an array for different sizes of the data structures.

The time relative to the heap implementation is that required to keep removing the minimum until the heap is empty. This time takes into account also the time required to build the heap. 

The deletion for the array is virtual meaning that once found the minimum is simply swapped with the last element and a virtual size index is decreased. The iterations are repeated until this index is zero.

Actually the execution times are relative to $100$ instances of the problem dealing with floating point numbers. The following table reports the execution times for different sizes of the data structures.


| n     | On Heaps   | On Arrays   |
| ----- | ---------- | ----------- |
| 0     | 0.000008 s | 0.000002 s  |
| 1820  | 0.039997 s | 0.521334 s  |
| 3640  | 0.079795 s | 2.117419 s  |
| 5461  | 0.125746 s | 4.705216 s  |
| 7281  | 0.171955 s | 8.364626 s  |
| 9102  | 0.203877 s | 13.103818 s |
| 10922 | 0.271601 s | 18.852955 s |
| 12743 | 0.328581 s | 25.671670 s |
| 14563 | 0.379897 s | 33.560804 s |
| 16384 | 0.411765 s | 42.697526 s |

The following plot comparing the execution times for the two data strucures as function of the size $n$ allows to see the trend. The heap data structure looks like scaling compatibly with the expected behaviour of $\mathcal{O}(n*\log(n))$, while the array data structure scales as $\Theta(n^2)$ as the problem size grows.

![](/Users/Mec/Desktop/AD/homework/04_bin_heaps/tests/plot.svg)

The executable `test_insert` was already tested during the lectures and works correctly both with min and max heaps.

##4. Leaves Indeces

The leaves of a binary heap are that nodes with no children. Recall that in the array based representation, given a node $i$,

+ his left child has index $2*i$,
+ his right child has index $2*i+1$.

Let $n$ be the number of nodes contained in the binary heap. Assuming $i\in\{\left \lfloor{n/2}\right \rfloor+1,\dots,n\}$, his left child would be indexed by $2*i\geq 2 \left \lfloor{n/2}\right \rfloor+2 > n$ and so it would not be in the heap. Therefore, a node with index in $\{\left \lfloor{n/2}\right \rfloor+1,\dots,n\}$ can't have any children.

It remains to prove that a node with no children has necessarily index in $\{\left \lfloor{n/2}\right \rfloor+1,\dots,n\}$. If a node $i$ has no children, it means also that $2*i>n$ i.e. it has no left child. This implies that $i>n/2$ and therefore $i\in\{\left \lfloor{n/2}\right \rfloor+1,\dots,n\}$.

These two directions imply that the nodes with no children are all and only those whose index belongs to $\{\left \lfloor{n/2}\right \rfloor+1,\dots,n\}$.

## 5. Worst Case Heapify

The worst case for a max heap that needs to have the heap property fixed, that is what the function heapify is for, is when the minimum value, which must be placed in a leaf, is instead in the root. In this case the function heapify needs to be called at each level of the three from the root to the leaf, all along a simple path through the height of the heap.

The maximum number of nodes in a complete heap of height $h$ is $2^{h+1}-1$ and for a heap of height $h-1$ it is $2^h-1$. It follows that the minimum number of nodes of a heap of height $h$ is $2^h-1+1=2^h$.

Then the number of nodes $n$ of a binary heap of height $h$ is such that $2^h\leq n<2^{h+1}$ which implies $h\leq \log_2n< h+1$. Since $h$ is integer it follows that the height of the heap is $h=\left \lfloor{\log_2 n}\right \rfloor$.

Then the worst case running time of heapify for a binary max heap of size $n$ is $\Omega(\log_2 n)$. This result still holds for binary heaps different from max heaps.

##6. Nodes Given Height

The fact that for an heap with $n$ element there are at most $\left \lceil{n/2^{h+1}}\right \rceil$ nodes of height $h$ can be proved by induction.

The base case for $h=0$, i.e. for the bottom of the heap, holds since $\left \lceil{n/2^{h+1}}\right \rceil = \left \lceil{n/2}\right \rceil$ is the number of leaves in an heap with $n$ nodes. This results follows directly from point $4$.

The inductive hypothesis is that the relationship to prove holds for $h-1$.  Removing all the leaves from a tree results in a new tree with $n - \left \lceil{n/2}\right \rceil =\left \lfloor{n/2}\right \rfloor$ nodes.

The inductive hypothesis implies that the number of nodes with height $h-1$ in this new heap is $\left \lceil{\left \lfloor{n/2}\right \rfloor}/2^{h-1+1}\right\rceil < \left \lceil{n/2}/2^{h}\right\rceil=\left \lceil{n}/2^{h+1}\right\rceil$. The nodes that have height $h-1$ in this tree have height $h$ in the previous tree and this completes the proof.