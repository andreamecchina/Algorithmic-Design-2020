# Weighted Graphs Homework

The makefile is generated running `cmake CMakeLists.txt`. The compilation is then simply performed with `make`.

The plot in point $3$ is obtained using the Gnuplot script in the `src` directory.  The data used for the plots are contained in the file `times.dat` in the same directory.

## 1. Array Based Version

The Dijkstra algorithm solves the single source shortest paths problem, computing all the shortest paths from a single source node. The algorithm is a variation of the breadth first search algorithm in order to deal with weighted graphs. The weights are not allowed to take negative values while self loops are allowed.

All the declarations and implementations relative to the graph initialization are contained in the header file `graph.h` and in the source file `graph.c`. The graph is stored using its adjacency lists representation. The structure `adjnode` has as members an `id` identifying the node and the weight of the edge leading to it.

The `graph` structure has as members the number of nodes in the graph, an integer array representing the number of neighbours of a node in the graph and the array of adjacency lists. The function `build_graph` takes as input the number of nodes in the graph. For each node, the edges and the weights are randomly generated so that each weight is an integer value greater than $1$.

All the declarations and implementations relative to the array version of the Dijkstra algorithm are contained in the header file `array.h` and in the source file `array.c`. It follows that 

+ the function `build_queue` builds the priority queue using an array based representation. The queue is afterwards freed when empty. Using the array based representation, building the queue costs $\Theta(n)$,

+ the `extract_min_array` function swaps the element of the queue to be extracted with the last one and then reduces the size of the queue itself. Extracting the minimum from an array costs $\Theta(n)$ where $n$ is the number of elements in the array,

+ the `update_distance_array` function in the array based representation takes constant time $\Theta(1)$. 

Distances and predecessors are described using two arrays allocated into the main Dijkstra function. The infinite distance is represented by $9999$ and the null pointer by the negative predecessor $-1$. The `init_sssp` function initialises the graph setting the all the distances to infinity and all the predecessors to the null pointer.

These two arrays of integers are returned by the main `dijkstra_array` function as a `pair` structure defined in the header `array.h`.

For all of the following tests, the maximum number of neighbours of a node is set to $5$ in order to work with sparse graphs, so that the adjacency lists based representation is optimal. The weights are integers limited to the interval $[1,10]$. The source is set to the node indexed by $0$. 

All the tests results can be reproduced using the executable `test_dijkstra`. A first test deals with the following graph with $10$ nodes.

[![](https://mermaid.ink/img/eyJjb2RlIjoiZ3JhcGggTFJcbiAgMCgoMCkpLS0xLS0-OFxuICAwKCgwKSktLTQtLT45XG4gIDEoKDEpKS0tOS0tPjRcbiAgMSgoMSkpLS0xMC0tPjNcbiAgMigoMikpXG4gIDMoKDMpKVxuICA0KCg0KSktLTgtLT4yXG4gIDQoKDQpKS0tOC0tPjNcbiAgNSgoNSkpLS0xMC0tPjNcbiAgNSgoNSkpLS0xLS0-N1xuICA1KCg1KSktLTctLT44XG4gIDUoKDUpKS0tMTAtLT45XG4gIDYoKDYpKVxuICA3KCg3KSktLTMtLT42XG4gIDcoKDcpKS0tMS0tPjdcbiAgOCgoOCkpLS04LS0-MVxuICA4KCg4KSktLTQtLT4yXG4gIDgoKDgpKS0tMTAtLT45XG4gIDkoKDkpKS0tNi0tPjUiLCJtZXJtYWlkIjp7InRoZW1lIjoiZGVmYXVsdCIsImZsb3djaGFydCI6eyJjdXJ2ZSI6ImJhc2lzIn0sInRoZW1lVmFyaWFibGVzIjp7ImJhY2tncm91bmQiOiJ3aGl0ZSIsInByaW1hcnlDb2xvciI6IiNFQ0VDRkYiLCJzZWNvbmRhcnlDb2xvciI6IiNmZmZmZGUiLCJ0ZXJ0aWFyeUNvbG9yIjoiaHNsKDgwLCAxMDAlLCA5Ni4yNzQ1MDk4MDM5JSkiLCJwcmltYXJ5Qm9yZGVyQ29sb3IiOiJoc2woMjQwLCA2MCUsIDg2LjI3NDUwOTgwMzklKSIsInNlY29uZGFyeUJvcmRlckNvbG9yIjoiaHNsKDYwLCA2MCUsIDgzLjUyOTQxMTc2NDclKSIsInRlcnRpYXJ5Qm9yZGVyQ29sb3IiOiJoc2woODAsIDYwJSwgODYuMjc0NTA5ODAzOSUpIiwicHJpbWFyeVRleHRDb2xvciI6IiMxMzEzMDAiLCJzZWNvbmRhcnlUZXh0Q29sb3IiOiIjMDAwMDIxIiwidGVydGlhcnlUZXh0Q29sb3IiOiJyZ2IoOS41MDAwMDAwMDAxLCA5LjUwMDAwMDAwMDEsIDkuNTAwMDAwMDAwMSkiLCJsaW5lQ29sb3IiOiIjMzMzMzMzIiwidGV4dENvbG9yIjoiIzMzMyIsIm1haW5Ca2ciOiIjRUNFQ0ZGIiwic2Vjb25kQmtnIjoiI2ZmZmZkZSIsImJvcmRlcjEiOiIjOTM3MERCIiwiYm9yZGVyMiI6IiNhYWFhMzMiLCJhcnJvd2hlYWRDb2xvciI6IiMzMzMzMzMiLCJmb250RmFtaWx5IjoiXCJ0cmVidWNoZXQgbXNcIiwgdmVyZGFuYSwgYXJpYWwiLCJmb250U2l6ZSI6IjE2cHgiLCJsYWJlbEJhY2tncm91bmQiOiIjZThlOGU4Iiwibm9kZUJrZyI6IiNFQ0VDRkYiLCJub2RlQm9yZGVyIjoiIzkzNzBEQiIsImNsdXN0ZXJCa2ciOiIjZmZmZmRlIiwiY2x1c3RlckJvcmRlciI6IiNhYWFhMzMiLCJkZWZhdWx0TGlua0NvbG9yIjoiIzMzMzMzMyIsInRpdGxlQ29sb3IiOiIjMzMzIiwiZWRnZUxhYmVsQmFja2dyb3VuZCI6IiNlOGU4ZTgiLCJhY3RvckJvcmRlciI6ImhzbCgyNTkuNjI2MTY4MjI0MywgNTkuNzc2NTM2MzEyOCUsIDg3LjkwMTk2MDc4NDMlKSIsImFjdG9yQmtnIjoiI0VDRUNGRiIsImFjdG9yVGV4dENvbG9yIjoiYmxhY2siLCJhY3RvckxpbmVDb2xvciI6ImdyZXkiLCJzaWduYWxDb2xvciI6IiMzMzMiLCJzaWduYWxUZXh0Q29sb3IiOiIjMzMzIiwibGFiZWxCb3hCa2dDb2xvciI6IiNFQ0VDRkYiLCJsYWJlbEJveEJvcmRlckNvbG9yIjoiaHNsKDI1OS42MjYxNjgyMjQzLCA1OS43NzY1MzYzMTI4JSwgODcuOTAxOTYwNzg0MyUpIiwibGFiZWxUZXh0Q29sb3IiOiJibGFjayIsImxvb3BUZXh0Q29sb3IiOiJibGFjayIsIm5vdGVCb3JkZXJDb2xvciI6IiNhYWFhMzMiLCJub3RlQmtnQ29sb3IiOiIjZmZmNWFkIiwibm90ZVRleHRDb2xvciI6ImJsYWNrIiwiYWN0aXZhdGlvbkJvcmRlckNvbG9yIjoiIzY2NiIsImFjdGl2YXRpb25Ca2dDb2xvciI6IiNmNGY0ZjQiLCJzZXF1ZW5jZU51bWJlckNvbG9yIjoid2hpdGUiLCJzZWN0aW9uQmtnQ29sb3IiOiJyZ2JhKDEwMiwgMTAyLCAyNTUsIDAuNDkpIiwiYWx0U2VjdGlvbkJrZ0NvbG9yIjoid2hpdGUiLCJzZWN0aW9uQmtnQ29sb3IyIjoiI2ZmZjQwMCIsInRhc2tCb3JkZXJDb2xvciI6IiM1MzRmYmMiLCJ0YXNrQmtnQ29sb3IiOiIjOGE5MGRkIiwidGFza1RleHRMaWdodENvbG9yIjoid2hpdGUiLCJ0YXNrVGV4dENvbG9yIjoid2hpdGUiLCJ0YXNrVGV4dERhcmtDb2xvciI6ImJsYWNrIiwidGFza1RleHRPdXRzaWRlQ29sb3IiOiJibGFjayIsInRhc2tUZXh0Q2xpY2thYmxlQ29sb3IiOiIjMDAzMTYzIiwiYWN0aXZlVGFza0JvcmRlckNvbG9yIjoiIzUzNGZiYyIsImFjdGl2ZVRhc2tCa2dDb2xvciI6IiNiZmM3ZmYiLCJncmlkQ29sb3IiOiJsaWdodGdyZXkiLCJkb25lVGFza0JrZ0NvbG9yIjoibGlnaHRncmV5IiwiZG9uZVRhc2tCb3JkZXJDb2xvciI6ImdyZXkiLCJjcml0Qm9yZGVyQ29sb3IiOiIjZmY4ODg4IiwiY3JpdEJrZ0NvbG9yIjoicmVkIiwidG9kYXlMaW5lQ29sb3IiOiJyZWQiLCJsYWJlbENvbG9yIjoiYmxhY2siLCJlcnJvckJrZ0NvbG9yIjoiIzU1MjIyMiIsImVycm9yVGV4dENvbG9yIjoiIzU1MjIyMiIsImNsYXNzVGV4dCI6IiMxMzEzMDAiLCJmaWxsVHlwZTAiOiIjRUNFQ0ZGIiwiZmlsbFR5cGUxIjoiI2ZmZmZkZSIsImZpbGxUeXBlMiI6ImhzbCgzMDQsIDEwMCUsIDk2LjI3NDUwOTgwMzklKSIsImZpbGxUeXBlMyI6ImhzbCgxMjQsIDEwMCUsIDkzLjUyOTQxMTc2NDclKSIsImZpbGxUeXBlNCI6ImhzbCgxNzYsIDEwMCUsIDk2LjI3NDUwOTgwMzklKSIsImZpbGxUeXBlNSI6ImhzbCgtNCwgMTAwJSwgOTMuNTI5NDExNzY0NyUpIiwiZmlsbFR5cGU2IjoiaHNsKDgsIDEwMCUsIDk2LjI3NDUwOTgwMzklKSIsImZpbGxUeXBlNyI6ImhzbCgxODgsIDEwMCUsIDkzLjUyOTQxMTc2NDclKSJ9fSwidXBkYXRlRWRpdG9yIjpmYWxzZX0)](https://mermaid-js.github.io/mermaid-live-editor/#/edit/eyJjb2RlIjoiZ3JhcGggTFJcbiAgMCgoMCkpLS0xLS0-OFxuICAwKCgwKSktLTQtLT45XG4gIDEoKDEpKS0tOS0tPjRcbiAgMSgoMSkpLS0xMC0tPjNcbiAgMigoMikpXG4gIDMoKDMpKVxuICA0KCg0KSktLTgtLT4yXG4gIDQoKDQpKS0tOC0tPjNcbiAgNSgoNSkpLS0xMC0tPjNcbiAgNSgoNSkpLS0xLS0-N1xuICA1KCg1KSktLTctLT44XG4gIDUoKDUpKS0tMTAtLT45XG4gIDYoKDYpKVxuICA3KCg3KSktLTMtLT42XG4gIDcoKDcpKS0tMS0tPjdcbiAgOCgoOCkpLS04LS0-MVxuICA4KCg4KSktLTQtLT4yXG4gIDgoKDgpKS0tMTAtLT45XG4gIDkoKDkpKS0tNi0tPjUiLCJtZXJtYWlkIjp7InRoZW1lIjoiZGVmYXVsdCIsImZsb3djaGFydCI6eyJjdXJ2ZSI6ImJhc2lzIn0sInRoZW1lVmFyaWFibGVzIjp7ImJhY2tncm91bmQiOiJ3aGl0ZSIsInByaW1hcnlDb2xvciI6IiNFQ0VDRkYiLCJzZWNvbmRhcnlDb2xvciI6IiNmZmZmZGUiLCJ0ZXJ0aWFyeUNvbG9yIjoiaHNsKDgwLCAxMDAlLCA5Ni4yNzQ1MDk4MDM5JSkiLCJwcmltYXJ5Qm9yZGVyQ29sb3IiOiJoc2woMjQwLCA2MCUsIDg2LjI3NDUwOTgwMzklKSIsInNlY29uZGFyeUJvcmRlckNvbG9yIjoiaHNsKDYwLCA2MCUsIDgzLjUyOTQxMTc2NDclKSIsInRlcnRpYXJ5Qm9yZGVyQ29sb3IiOiJoc2woODAsIDYwJSwgODYuMjc0NTA5ODAzOSUpIiwicHJpbWFyeVRleHRDb2xvciI6IiMxMzEzMDAiLCJzZWNvbmRhcnlUZXh0Q29sb3IiOiIjMDAwMDIxIiwidGVydGlhcnlUZXh0Q29sb3IiOiJyZ2IoOS41MDAwMDAwMDAxLCA5LjUwMDAwMDAwMDEsIDkuNTAwMDAwMDAwMSkiLCJsaW5lQ29sb3IiOiIjMzMzMzMzIiwidGV4dENvbG9yIjoiIzMzMyIsIm1haW5Ca2ciOiIjRUNFQ0ZGIiwic2Vjb25kQmtnIjoiI2ZmZmZkZSIsImJvcmRlcjEiOiIjOTM3MERCIiwiYm9yZGVyMiI6IiNhYWFhMzMiLCJhcnJvd2hlYWRDb2xvciI6IiMzMzMzMzMiLCJmb250RmFtaWx5IjoiXCJ0cmVidWNoZXQgbXNcIiwgdmVyZGFuYSwgYXJpYWwiLCJmb250U2l6ZSI6IjE2cHgiLCJsYWJlbEJhY2tncm91bmQiOiIjZThlOGU4Iiwibm9kZUJrZyI6IiNFQ0VDRkYiLCJub2RlQm9yZGVyIjoiIzkzNzBEQiIsImNsdXN0ZXJCa2ciOiIjZmZmZmRlIiwiY2x1c3RlckJvcmRlciI6IiNhYWFhMzMiLCJkZWZhdWx0TGlua0NvbG9yIjoiIzMzMzMzMyIsInRpdGxlQ29sb3IiOiIjMzMzIiwiZWRnZUxhYmVsQmFja2dyb3VuZCI6IiNlOGU4ZTgiLCJhY3RvckJvcmRlciI6ImhzbCgyNTkuNjI2MTY4MjI0MywgNTkuNzc2NTM2MzEyOCUsIDg3LjkwMTk2MDc4NDMlKSIsImFjdG9yQmtnIjoiI0VDRUNGRiIsImFjdG9yVGV4dENvbG9yIjoiYmxhY2siLCJhY3RvckxpbmVDb2xvciI6ImdyZXkiLCJzaWduYWxDb2xvciI6IiMzMzMiLCJzaWduYWxUZXh0Q29sb3IiOiIjMzMzIiwibGFiZWxCb3hCa2dDb2xvciI6IiNFQ0VDRkYiLCJsYWJlbEJveEJvcmRlckNvbG9yIjoiaHNsKDI1OS42MjYxNjgyMjQzLCA1OS43NzY1MzYzMTI4JSwgODcuOTAxOTYwNzg0MyUpIiwibGFiZWxUZXh0Q29sb3IiOiJibGFjayIsImxvb3BUZXh0Q29sb3IiOiJibGFjayIsIm5vdGVCb3JkZXJDb2xvciI6IiNhYWFhMzMiLCJub3RlQmtnQ29sb3IiOiIjZmZmNWFkIiwibm90ZVRleHRDb2xvciI6ImJsYWNrIiwiYWN0aXZhdGlvbkJvcmRlckNvbG9yIjoiIzY2NiIsImFjdGl2YXRpb25Ca2dDb2xvciI6IiNmNGY0ZjQiLCJzZXF1ZW5jZU51bWJlckNvbG9yIjoid2hpdGUiLCJzZWN0aW9uQmtnQ29sb3IiOiJyZ2JhKDEwMiwgMTAyLCAyNTUsIDAuNDkpIiwiYWx0U2VjdGlvbkJrZ0NvbG9yIjoid2hpdGUiLCJzZWN0aW9uQmtnQ29sb3IyIjoiI2ZmZjQwMCIsInRhc2tCb3JkZXJDb2xvciI6IiM1MzRmYmMiLCJ0YXNrQmtnQ29sb3IiOiIjOGE5MGRkIiwidGFza1RleHRMaWdodENvbG9yIjoid2hpdGUiLCJ0YXNrVGV4dENvbG9yIjoid2hpdGUiLCJ0YXNrVGV4dERhcmtDb2xvciI6ImJsYWNrIiwidGFza1RleHRPdXRzaWRlQ29sb3IiOiJibGFjayIsInRhc2tUZXh0Q2xpY2thYmxlQ29sb3IiOiIjMDAzMTYzIiwiYWN0aXZlVGFza0JvcmRlckNvbG9yIjoiIzUzNGZiYyIsImFjdGl2ZVRhc2tCa2dDb2xvciI6IiNiZmM3ZmYiLCJncmlkQ29sb3IiOiJsaWdodGdyZXkiLCJkb25lVGFza0JrZ0NvbG9yIjoibGlnaHRncmV5IiwiZG9uZVRhc2tCb3JkZXJDb2xvciI6ImdyZXkiLCJjcml0Qm9yZGVyQ29sb3IiOiIjZmY4ODg4IiwiY3JpdEJrZ0NvbG9yIjoicmVkIiwidG9kYXlMaW5lQ29sb3IiOiJyZWQiLCJsYWJlbENvbG9yIjoiYmxhY2siLCJlcnJvckJrZ0NvbG9yIjoiIzU1MjIyMiIsImVycm9yVGV4dENvbG9yIjoiIzU1MjIyMiIsImNsYXNzVGV4dCI6IiMxMzEzMDAiLCJmaWxsVHlwZTAiOiIjRUNFQ0ZGIiwiZmlsbFR5cGUxIjoiI2ZmZmZkZSIsImZpbGxUeXBlMiI6ImhzbCgzMDQsIDEwMCUsIDk2LjI3NDUwOTgwMzklKSIsImZpbGxUeXBlMyI6ImhzbCgxMjQsIDEwMCUsIDkzLjUyOTQxMTc2NDclKSIsImZpbGxUeXBlNCI6ImhzbCgxNzYsIDEwMCUsIDk2LjI3NDUwOTgwMzklKSIsImZpbGxUeXBlNSI6ImhzbCgtNCwgMTAwJSwgOTMuNTI5NDExNzY0NyUpIiwiZmlsbFR5cGU2IjoiaHNsKDgsIDEwMCUsIDk2LjI3NDUwOTgwMzklKSIsImZpbGxUeXBlNyI6ImhzbCgxODgsIDEwMCUsIDkzLjUyOTQxMTc2NDclKSJ9fSwidXBkYXRlRWRpdG9yIjpmYWxzZX0)

The following table reports the shortest paths to every node and their relative distance from the source node $0$. The results are indeed correct.


| Node | Path              | Distance Computation | Overall Distance |
| ---- | ----------------- | -------------------- | ---------------- |
| 1    | 0 → 8 → 1         | $1+8$                | $9$              |
| 2    | 0 → 8 → 2         | $1+4$                | $5$              |
| 3    | 0 → 8 → 1 → 3     | $1+8+10$             | $19$             |
| 4    | 0 → 8 → 1 → 4     | $1+8+9$              | $18$             |
| 5    | 0 → 9 → 5         | $4+6$                | $10$             |
| 6    | 0 → 9 → 5 → 7 → 6 | $4+6+1+3$            | $14$             |
| 7    | 0 → 9 → 5 → 7     | $4+6+1$              | $11$             |
| 8    | 0 → 8             | $1$                  | $1$              |
| 9    | 0 → 9             | $4$                  | $4$              |

## 2. Binary Heap Based Version

All the declarations and implementations relative to the heap version of the Dijkstra algorithm are contained in the header file `heap.h` and in the source file `heap.c`. It follows that 

+ the function `build_heap_alt` builds the priority queue using an heap based representation of it and costs $\Theta(n)$,

+ the `extract_min_heap` extracts the minimum from the heap and costs $\mathcal{O}(\log n)$, where $n$ is the number of nodes in the heap priority queue,

+ the `update_distance_heap` function in the heap based representation takes constant time $\mathcal{O}(\log n)$. 

These functions, together with the main Dijkstra function in the heap based representation, make use of the binary heap library already implemented in the source file `binheap_alt.c` whose relative header is `binheap_alt.h`.

This alternative implementation of the algorithm is tested on the very same graph above and the results correctly match.

## 3. Results

The function `test`, implemented in the source file `test.c` and declared in the relative header, is used to test and compare both of the two Dijkstra algorithm implementations for increasing sizes of randomly generated graphs. The measured times are an average of $100$ measurements.

The Dijkstra algorithm is a kind of meta algorithm since its complexity depends on the data structure used to represent the priority queue, in particular

+ the complexity is $\Theta(|V|^2+|E|)$ when using an array based representation,
+ the complexity is $\mathcal{O}((|V|+|E|)*\log |V|)$ for an heap based representation instead.

![](/Users/Mec/Desktop/AD/homework/08_dijkstra/src/plot.svg)

The obtained results are reported in the above plot, having on its horizontal axis the number of nodes in the graph $|V|$, labeled as $n$. As expected, the array based representation is quadratic in the number of nodes in the graph while the heap based implementation scales much better.