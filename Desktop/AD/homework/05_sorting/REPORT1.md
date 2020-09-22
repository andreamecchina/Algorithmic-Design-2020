# Sorting Homework 1

The makefile is generated running `cmake CMakeLists.txt`. The compilation is then simply performed with `make`.

The plots in point $2$ are obtained using the Gnuplot scripts in the `src` directory. All the data used for the plots are contained in the file `times.dat` in the same directory.

## 1. Sorting Implementation

All the requested functions are implementend in their relative source files.

The only difference with respect to the pseudo codes in the slides is the numbering of the indeces which starts from $0$ instead that from $1$.

##2. Results

All the tests are performed running the `test_sorting` executable. The following plot reports the execution times versus the size $n$ of the input array $A$ for all of the implemented sorting algorithms. The array $A$ is randomly generated.

![](/Users/Mec/Desktop/AD/homework/05_sorting/src/plot1.svg)

For $\text{INSERTION SORT}$ the worst case time is $\mathcal{O}(n^2)$ and the best case time is $\Omega(n)$. For $\text{QUICK SORT}$ the worst case time is $\Theta(n^2)$ while the average and best case time is $\Theta(n\log n)$. Both for $\text{BUBBLE SORT}$ and $\text{SELECTION SORT}$ the time taken is $\Theta(n^2)$ while for $\text{HEAP SORT}$ the time taken is $\mathcal{O}(n\log n)$.

The results obtained are coherent with the expected behaviours. The $\text{QUICK SORT}$ and the $\text{HEAP SORT}$ results seem to overalap so the following plot reports again the results obtained for a random input array $A$ but extending the input size $n$. 

![](/Users/Mec/Desktop/AD/homework/05_sorting/src/plot2.svg)

The $\text{HEAP SORT}$ algorithm outperforms the $\text{QUICK SORT}$ one when the problem size $n$ grows.

The following plot reports the results obtained for the $\text{INSERTION SORT}$ algorithm in different scenarios. The best case time, when the array $A$ is already sorted, increases linearly while the worst case time, when $A$ is reversely ordered, increases quadratically, as expected.

The random case seems to be closer to the worst case than to the best one.

![](/Users/Mec/Desktop/AD/homework/05_sorting/src/plot3.svg)

The following plot compares instead the worst and random case for the $\text{QUICK SORT}$ algorithm.

In the worst case, when one partition is always empty, the time taken scales quadratically. In the random case instead, like in the best case, the time taken is $\Theta(n\log n)$.

![](/Users/Mec/Desktop/AD/homework/05_sorting/src/plot4.svg)

##3. Argue and Answer

*$\text{HEAP SORT}$ on an array $A$ whose length is $n$ takes time $\mathcal{O}(n)$.*

The time taken by $\text{HEAP SORT}$ is that taken to build the max heap from the input array $A$, which is $\Theta(n)$, plus the time required to extract $n$ times the minimum element with respect to the total order which is $\mathcal{O}(n\log n)$.

The overall time upper bound taken by $\text{HEAP SORT}$ is therefore $\mathcal{O}(n\log n)$, which is greater with respect to $\mathcal{O}(n)$.

The only case in which the time taken by $\text{HEAP SORT}$ can be $\mathcal{O}(n)$ is when all the elements of $A$ are equal, since in this case the time to extract $n$ times the minimum element with respect to the total order is $\Theta(n)$.

In this case in fact $\Theta(n)$ is also the overall time taken by $\text{HEAP SORT}$, from which it follows that the overall time upper bound is $\mathcal{O}(n)$.

*$\text{HEAP SORT}$ on an array $A$ whose length is $n$ takes time $\Omega(n)$.*

Since in the best case of $\text{HEAP SORT}$, in which all the element of $A$ are equal, the overall time required to sort an array of size $n$ is $\Theta(n)$, this also implies that the overall time lower bound $\Omega(n)$ is valid.

Since this result holds in the best case scenario, it is for sure always valid in every possible scenario.

*What is the worst case complexity for $\text{HEAP SORT}$?*

The worst case time taken by $\text{HEAP SORT}$ is when the procedure of extracting the minimum element with respect to the total order takes time $\mathcal{O}(n\log n)$.

In this case also the overall time taken by $\text{HEAP SORT}$ is $\mathcal{O}(n\log n)$.

*$\text{QUICK SORT}$ on an array $A$ whose length is $n$ takes time $\mathcal{O}(n^3)$*.

The time required by $\text{QUICK SORT}$ in the worst case scenario, when the array $A$ is already sorted, is $\Theta(n^2)$, which implies that the overall time upper bound is $\mathcal{O}(n^2)$.

From the properties of the big O notation it follows that $\mathcal{O}(n^2)\subseteq\mathcal{O}(n^3)$ so $\mathcal{O}(n^3)$ provides a larger upper bound. Since this result holds in the best case scenario, it is for sure always valid in every possible scenario.

*What is the complexity of $\text{QUICK SORT}$?*

The time required by $\text{QUICK SORT}$ in the worst case scenario, which is when the array $A$ is already sorted and the leftmost element is chosen as pivot, is $\Theta(n^2)$.

The best case scenario is instead that in which the partition is balanced at every step and the time taken in this case is $\Theta(n\log n)$.

On the average case, assuming all the permutations of $A$ to be equally likely, at each step is possible to have a best case scenario or a worst case one. The time required by $\text{QUICK SORT}$ is again $\Theta(n\log n)$.

*$\text{BUBBLE SORT}$ on an array $A$ whose length is $n$ takes time $\Omega(n)$*.

The $\text{BUBBLE SORT}$ algorithm linearly scans the array $A$ comparing adjacent elements and swapping them if in the wrong order.

In case of the array $A$ being already sorted, the time taken by the algorithm is $\Theta(n)$. This is the best case scenario and in this case it follows the overall time lower bound is $\Omega(n)$.

*What is the complexity of $\text{BUBBLE SORT}$?*

The $\text{BUBBLE SORT}$ algorithm consists in two nested loops running on the length $n$ of $A$ so that the time taken in the average and in the worst case scenario is $\Theta(n^2)$.

In the best case scenario, when $A$ is already sorted, the time taken by the algorithm is $\Theta(n)$.

##4. Recursive Equation

The recursive equation to be solved for $T(n)$ is a cases equation defined by

$$T(n)=\begin{cases}\Theta(1)\text{ if } n = 32 \\3*T(n/4)+\Theta(n^{3/2})\text{ otherwise}.\end{cases}$$

Fixing $c>0$, the function $cn^{3/2}$ is chosen as representative of the set $\Theta(n^{3/2})$. A recursion tree is used to visualize the process.

The following graph shows the first three levels of the tree. Each node is labeled by the cost of the relative smaller size problem solved during the recursive function calls.



[![](https://mermaid.ink/img/eyJjb2RlIjoiZ3JhcGggVERcblx0MShcImNuXigzLzIpXCIpIC0tPiAyKFwiYyhuLzQpXigzLzIpXCIpXG4gIDEoXCJjbl4oMy8yKVwiKSAtLT4gMyhcImMobi80KV4oMy8yKVwiKVxuICAxKFwiY25eKDMvMilcIikgLS0-IDQoXCJjKG4vNCleKDMvMilcIilcbiAgMihcImMobi80KV4oMy8yKVwiKSAtLT4gNShcImMobi84KV4oMy8yKVwiKVxuICAyKFwiYyhuLzQpXigzLzIpXCIpIC0tPiA2KFwiYyhuLzgpXigzLzIpXCIpXG4gIDIoXCJjKG4vNCleKDMvMilcIikgLS0-IDcoXCJjKG4vOCleKDMvMilcIilcbiAgMyhcImMobi80KV4oMy8yKVwiKSAtLT4gOChcImMobi84KV4oMy8yKVwiKVxuICAzKFwiYyhuLzQpXigzLzIpXCIpIC0tPiA5KFwiYyhuLzgpXigzLzIpXCIpXG4gIDMoXCJjKG4vNCleKDMvMilcIikgLS0-IDEwKFwiYyhuLzgpXigzLzIpXCIpXG4gIDQoXCJjKG4vNCleKDMvMilcIikgLS0-IDExKFwiYyhuLzgpXigzLzIpXCIpXG4gIDQoXCJjKG4vNCleKDMvMilcIikgLS0-IDEyKFwiYyhuLzgpXigzLzIpXCIpXG4gIDQoXCJjKG4vNCleKDMvMilcIikgLS0-IDEzKFwiYyhuLzgpXigzLzIpXCIpIiwibWVybWFpZCI6eyJ0aGVtZSI6ImRlZmF1bHQiLCJmbG93Y2hhcnQiOnsiY3VydmUiOiJiYXNpcyJ9LCJ0aGVtZVZhcmlhYmxlcyI6eyJiYWNrZ3JvdW5kIjoid2hpdGUiLCJwcmltYXJ5Q29sb3IiOiIjRUNFQ0ZGIiwic2Vjb25kYXJ5Q29sb3IiOiIjZmZmZmRlIiwidGVydGlhcnlDb2xvciI6ImhzbCg4MCwgMTAwJSwgOTYuMjc0NTA5ODAzOSUpIiwicHJpbWFyeUJvcmRlckNvbG9yIjoiaHNsKDI0MCwgNjAlLCA4Ni4yNzQ1MDk4MDM5JSkiLCJzZWNvbmRhcnlCb3JkZXJDb2xvciI6ImhzbCg2MCwgNjAlLCA4My41Mjk0MTE3NjQ3JSkiLCJ0ZXJ0aWFyeUJvcmRlckNvbG9yIjoiaHNsKDgwLCA2MCUsIDg2LjI3NDUwOTgwMzklKSIsInByaW1hcnlUZXh0Q29sb3IiOiIjMTMxMzAwIiwic2Vjb25kYXJ5VGV4dENvbG9yIjoiIzAwMDAyMSIsInRlcnRpYXJ5VGV4dENvbG9yIjoicmdiKDkuNTAwMDAwMDAwMSwgOS41MDAwMDAwMDAxLCA5LjUwMDAwMDAwMDEpIiwibGluZUNvbG9yIjoiIzMzMzMzMyIsInRleHRDb2xvciI6IiMzMzMiLCJtYWluQmtnIjoiI0VDRUNGRiIsInNlY29uZEJrZyI6IiNmZmZmZGUiLCJib3JkZXIxIjoiIzkzNzBEQiIsImJvcmRlcjIiOiIjYWFhYTMzIiwiYXJyb3doZWFkQ29sb3IiOiIjMzMzMzMzIiwiZm9udEZhbWlseSI6IlwidHJlYnVjaGV0IG1zXCIsIHZlcmRhbmEsIGFyaWFsIiwiZm9udFNpemUiOiIxNnB4IiwibGFiZWxCYWNrZ3JvdW5kIjoiI2U4ZThlOCIsIm5vZGVCa2ciOiIjRUNFQ0ZGIiwibm9kZUJvcmRlciI6IiM5MzcwREIiLCJjbHVzdGVyQmtnIjoiI2ZmZmZkZSIsImNsdXN0ZXJCb3JkZXIiOiIjYWFhYTMzIiwiZGVmYXVsdExpbmtDb2xvciI6IiMzMzMzMzMiLCJ0aXRsZUNvbG9yIjoiIzMzMyIsImVkZ2VMYWJlbEJhY2tncm91bmQiOiIjZThlOGU4IiwiYWN0b3JCb3JkZXIiOiJoc2woMjU5LjYyNjE2ODIyNDMsIDU5Ljc3NjUzNjMxMjglLCA4Ny45MDE5NjA3ODQzJSkiLCJhY3RvckJrZyI6IiNFQ0VDRkYiLCJhY3RvclRleHRDb2xvciI6ImJsYWNrIiwiYWN0b3JMaW5lQ29sb3IiOiJncmV5Iiwic2lnbmFsQ29sb3IiOiIjMzMzIiwic2lnbmFsVGV4dENvbG9yIjoiIzMzMyIsImxhYmVsQm94QmtnQ29sb3IiOiIjRUNFQ0ZGIiwibGFiZWxCb3hCb3JkZXJDb2xvciI6ImhzbCgyNTkuNjI2MTY4MjI0MywgNTkuNzc2NTM2MzEyOCUsIDg3LjkwMTk2MDc4NDMlKSIsImxhYmVsVGV4dENvbG9yIjoiYmxhY2siLCJsb29wVGV4dENvbG9yIjoiYmxhY2siLCJub3RlQm9yZGVyQ29sb3IiOiIjYWFhYTMzIiwibm90ZUJrZ0NvbG9yIjoiI2ZmZjVhZCIsIm5vdGVUZXh0Q29sb3IiOiJibGFjayIsImFjdGl2YXRpb25Cb3JkZXJDb2xvciI6IiM2NjYiLCJhY3RpdmF0aW9uQmtnQ29sb3IiOiIjZjRmNGY0Iiwic2VxdWVuY2VOdW1iZXJDb2xvciI6IndoaXRlIiwic2VjdGlvbkJrZ0NvbG9yIjoicmdiYSgxMDIsIDEwMiwgMjU1LCAwLjQ5KSIsImFsdFNlY3Rpb25Ca2dDb2xvciI6IndoaXRlIiwic2VjdGlvbkJrZ0NvbG9yMiI6IiNmZmY0MDAiLCJ0YXNrQm9yZGVyQ29sb3IiOiIjNTM0ZmJjIiwidGFza0JrZ0NvbG9yIjoiIzhhOTBkZCIsInRhc2tUZXh0TGlnaHRDb2xvciI6IndoaXRlIiwidGFza1RleHRDb2xvciI6IndoaXRlIiwidGFza1RleHREYXJrQ29sb3IiOiJibGFjayIsInRhc2tUZXh0T3V0c2lkZUNvbG9yIjoiYmxhY2siLCJ0YXNrVGV4dENsaWNrYWJsZUNvbG9yIjoiIzAwMzE2MyIsImFjdGl2ZVRhc2tCb3JkZXJDb2xvciI6IiM1MzRmYmMiLCJhY3RpdmVUYXNrQmtnQ29sb3IiOiIjYmZjN2ZmIiwiZ3JpZENvbG9yIjoibGlnaHRncmV5IiwiZG9uZVRhc2tCa2dDb2xvciI6ImxpZ2h0Z3JleSIsImRvbmVUYXNrQm9yZGVyQ29sb3IiOiJncmV5IiwiY3JpdEJvcmRlckNvbG9yIjoiI2ZmODg4OCIsImNyaXRCa2dDb2xvciI6InJlZCIsInRvZGF5TGluZUNvbG9yIjoicmVkIiwibGFiZWxDb2xvciI6ImJsYWNrIiwiZXJyb3JCa2dDb2xvciI6IiM1NTIyMjIiLCJlcnJvclRleHRDb2xvciI6IiM1NTIyMjIiLCJjbGFzc1RleHQiOiIjMTMxMzAwIiwiZmlsbFR5cGUwIjoiI0VDRUNGRiIsImZpbGxUeXBlMSI6IiNmZmZmZGUiLCJmaWxsVHlwZTIiOiJoc2woMzA0LCAxMDAlLCA5Ni4yNzQ1MDk4MDM5JSkiLCJmaWxsVHlwZTMiOiJoc2woMTI0LCAxMDAlLCA5My41Mjk0MTE3NjQ3JSkiLCJmaWxsVHlwZTQiOiJoc2woMTc2LCAxMDAlLCA5Ni4yNzQ1MDk4MDM5JSkiLCJmaWxsVHlwZTUiOiJoc2woLTQsIDEwMCUsIDkzLjUyOTQxMTc2NDclKSIsImZpbGxUeXBlNiI6ImhzbCg4LCAxMDAlLCA5Ni4yNzQ1MDk4MDM5JSkiLCJmaWxsVHlwZTciOiJoc2woMTg4LCAxMDAlLCA5My41Mjk0MTE3NjQ3JSkifX0sInVwZGF0ZUVkaXRvciI6ZmFsc2V9)](https://mermaid-js.github.io/mermaid-live-editor/#/edit/eyJjb2RlIjoiZ3JhcGggVERcblx0MShcImNuXigzLzIpXCIpIC0tPiAyKFwiYyhuLzQpXigzLzIpXCIpXG4gIDEoXCJjbl4oMy8yKVwiKSAtLT4gMyhcImMobi80KV4oMy8yKVwiKVxuICAxKFwiY25eKDMvMilcIikgLS0-IDQoXCJjKG4vNCleKDMvMilcIilcbiAgMihcImMobi80KV4oMy8yKVwiKSAtLT4gNShcImMobi84KV4oMy8yKVwiKVxuICAyKFwiYyhuLzQpXigzLzIpXCIpIC0tPiA2KFwiYyhuLzgpXigzLzIpXCIpXG4gIDIoXCJjKG4vNCleKDMvMilcIikgLS0-IDcoXCJjKG4vOCleKDMvMilcIilcbiAgMyhcImMobi80KV4oMy8yKVwiKSAtLT4gOChcImMobi84KV4oMy8yKVwiKVxuICAzKFwiYyhuLzQpXigzLzIpXCIpIC0tPiA5KFwiYyhuLzgpXigzLzIpXCIpXG4gIDMoXCJjKG4vNCleKDMvMilcIikgLS0-IDEwKFwiYyhuLzgpXigzLzIpXCIpXG4gIDQoXCJjKG4vNCleKDMvMilcIikgLS0-IDExKFwiYyhuLzgpXigzLzIpXCIpXG4gIDQoXCJjKG4vNCleKDMvMilcIikgLS0-IDEyKFwiYyhuLzgpXigzLzIpXCIpXG4gIDQoXCJjKG4vNCleKDMvMilcIikgLS0-IDEzKFwiYyhuLzgpXigzLzIpXCIpIiwibWVybWFpZCI6eyJ0aGVtZSI6ImRlZmF1bHQiLCJmbG93Y2hhcnQiOnsiY3VydmUiOiJiYXNpcyJ9LCJ0aGVtZVZhcmlhYmxlcyI6eyJiYWNrZ3JvdW5kIjoid2hpdGUiLCJwcmltYXJ5Q29sb3IiOiIjRUNFQ0ZGIiwic2Vjb25kYXJ5Q29sb3IiOiIjZmZmZmRlIiwidGVydGlhcnlDb2xvciI6ImhzbCg4MCwgMTAwJSwgOTYuMjc0NTA5ODAzOSUpIiwicHJpbWFyeUJvcmRlckNvbG9yIjoiaHNsKDI0MCwgNjAlLCA4Ni4yNzQ1MDk4MDM5JSkiLCJzZWNvbmRhcnlCb3JkZXJDb2xvciI6ImhzbCg2MCwgNjAlLCA4My41Mjk0MTE3NjQ3JSkiLCJ0ZXJ0aWFyeUJvcmRlckNvbG9yIjoiaHNsKDgwLCA2MCUsIDg2LjI3NDUwOTgwMzklKSIsInByaW1hcnlUZXh0Q29sb3IiOiIjMTMxMzAwIiwic2Vjb25kYXJ5VGV4dENvbG9yIjoiIzAwMDAyMSIsInRlcnRpYXJ5VGV4dENvbG9yIjoicmdiKDkuNTAwMDAwMDAwMSwgOS41MDAwMDAwMDAxLCA5LjUwMDAwMDAwMDEpIiwibGluZUNvbG9yIjoiIzMzMzMzMyIsInRleHRDb2xvciI6IiMzMzMiLCJtYWluQmtnIjoiI0VDRUNGRiIsInNlY29uZEJrZyI6IiNmZmZmZGUiLCJib3JkZXIxIjoiIzkzNzBEQiIsImJvcmRlcjIiOiIjYWFhYTMzIiwiYXJyb3doZWFkQ29sb3IiOiIjMzMzMzMzIiwiZm9udEZhbWlseSI6IlwidHJlYnVjaGV0IG1zXCIsIHZlcmRhbmEsIGFyaWFsIiwiZm9udFNpemUiOiIxNnB4IiwibGFiZWxCYWNrZ3JvdW5kIjoiI2U4ZThlOCIsIm5vZGVCa2ciOiIjRUNFQ0ZGIiwibm9kZUJvcmRlciI6IiM5MzcwREIiLCJjbHVzdGVyQmtnIjoiI2ZmZmZkZSIsImNsdXN0ZXJCb3JkZXIiOiIjYWFhYTMzIiwiZGVmYXVsdExpbmtDb2xvciI6IiMzMzMzMzMiLCJ0aXRsZUNvbG9yIjoiIzMzMyIsImVkZ2VMYWJlbEJhY2tncm91bmQiOiIjZThlOGU4IiwiYWN0b3JCb3JkZXIiOiJoc2woMjU5LjYyNjE2ODIyNDMsIDU5Ljc3NjUzNjMxMjglLCA4Ny45MDE5NjA3ODQzJSkiLCJhY3RvckJrZyI6IiNFQ0VDRkYiLCJhY3RvclRleHRDb2xvciI6ImJsYWNrIiwiYWN0b3JMaW5lQ29sb3IiOiJncmV5Iiwic2lnbmFsQ29sb3IiOiIjMzMzIiwic2lnbmFsVGV4dENvbG9yIjoiIzMzMyIsImxhYmVsQm94QmtnQ29sb3IiOiIjRUNFQ0ZGIiwibGFiZWxCb3hCb3JkZXJDb2xvciI6ImhzbCgyNTkuNjI2MTY4MjI0MywgNTkuNzc2NTM2MzEyOCUsIDg3LjkwMTk2MDc4NDMlKSIsImxhYmVsVGV4dENvbG9yIjoiYmxhY2siLCJsb29wVGV4dENvbG9yIjoiYmxhY2siLCJub3RlQm9yZGVyQ29sb3IiOiIjYWFhYTMzIiwibm90ZUJrZ0NvbG9yIjoiI2ZmZjVhZCIsIm5vdGVUZXh0Q29sb3IiOiJibGFjayIsImFjdGl2YXRpb25Cb3JkZXJDb2xvciI6IiM2NjYiLCJhY3RpdmF0aW9uQmtnQ29sb3IiOiIjZjRmNGY0Iiwic2VxdWVuY2VOdW1iZXJDb2xvciI6IndoaXRlIiwic2VjdGlvbkJrZ0NvbG9yIjoicmdiYSgxMDIsIDEwMiwgMjU1LCAwLjQ5KSIsImFsdFNlY3Rpb25Ca2dDb2xvciI6IndoaXRlIiwic2VjdGlvbkJrZ0NvbG9yMiI6IiNmZmY0MDAiLCJ0YXNrQm9yZGVyQ29sb3IiOiIjNTM0ZmJjIiwidGFza0JrZ0NvbG9yIjoiIzhhOTBkZCIsInRhc2tUZXh0TGlnaHRDb2xvciI6IndoaXRlIiwidGFza1RleHRDb2xvciI6IndoaXRlIiwidGFza1RleHREYXJrQ29sb3IiOiJibGFjayIsInRhc2tUZXh0T3V0c2lkZUNvbG9yIjoiYmxhY2siLCJ0YXNrVGV4dENsaWNrYWJsZUNvbG9yIjoiIzAwMzE2MyIsImFjdGl2ZVRhc2tCb3JkZXJDb2xvciI6IiM1MzRmYmMiLCJhY3RpdmVUYXNrQmtnQ29sb3IiOiIjYmZjN2ZmIiwiZ3JpZENvbG9yIjoibGlnaHRncmV5IiwiZG9uZVRhc2tCa2dDb2xvciI6ImxpZ2h0Z3JleSIsImRvbmVUYXNrQm9yZGVyQ29sb3IiOiJncmV5IiwiY3JpdEJvcmRlckNvbG9yIjoiI2ZmODg4OCIsImNyaXRCa2dDb2xvciI6InJlZCIsInRvZGF5TGluZUNvbG9yIjoicmVkIiwibGFiZWxDb2xvciI6ImJsYWNrIiwiZXJyb3JCa2dDb2xvciI6IiM1NTIyMjIiLCJlcnJvclRleHRDb2xvciI6IiM1NTIyMjIiLCJjbGFzc1RleHQiOiIjMTMxMzAwIiwiZmlsbFR5cGUwIjoiI0VDRUNGRiIsImZpbGxUeXBlMSI6IiNmZmZmZGUiLCJmaWxsVHlwZTIiOiJoc2woMzA0LCAxMDAlLCA5Ni4yNzQ1MDk4MDM5JSkiLCJmaWxsVHlwZTMiOiJoc2woMTI0LCAxMDAlLCA5My41Mjk0MTE3NjQ3JSkiLCJmaWxsVHlwZTQiOiJoc2woMTc2LCAxMDAlLCA5Ni4yNzQ1MDk4MDM5JSkiLCJmaWxsVHlwZTUiOiJoc2woLTQsIDEwMCUsIDkzLjUyOTQxMTc2NDclKSIsImZpbGxUeXBlNiI6ImhzbCg4LCAxMDAlLCA5Ni4yNzQ1MDk4MDM5JSkiLCJmaWxsVHlwZTciOiJoc2woMTg4LCAxMDAlLCA5My41Mjk0MTE3NjQ3JSkifX0sInVwZGF0ZUVkaXRvciI6ZmFsc2V9)

Starting from the root at depth level $0$ and denoting $i$ the depth level of a node, it can be seen that the complexity of a node at depth level $i$ is $c(n/4^i)^{3/2}$ and that there are $3^i$ nodes at depth level $i$. Multiplying these two expressions implies that the total cost for each depth level is $c(3/8)^in^{3/2}$. 

The recursion tree grows until the condition $n=32$ is fullfilled. Every time the depth grows $n$ is divided by $4$ and in the end the leaves will be labeled by $c$. It follows then that the stop index for the tree grow is $i^*$ such that $n/4^{i^*}=32$ which is equivalent to $i^*=(\log_2n-5)/2$.

It follows then that the total cost of the last level is $\Theta(3^{-5/2}3^{(\log_2n)/2})$. The logarithm properties allow to rewrite $\log_2n=\log_3n/\log_32$ and then the cost is rewritten as $\Theta(n^{1/(2\log_32)})$. Again, the logarithm properties allow to rewrite the last level cost as $\Theta(n^{1/2\log_23})$.

Adding up the total costs it results that $T(n)=cn^{3/2}\sum_{i=0}^{(\log_2n-5)/2}(3/8)^i+\Theta(n^{1/2\log_23})$. Extending the sum up to $+\infty$ it can be recosgnized a geometrical sum and then it follows that $T(n)\leq cn^{3/2}8/5+\Theta(n^{1/2\log_23})$. 

Since $1/2\log_23<3/2$ it follows that $T(n)\in\mathcal{O}(n^{3/2})$.