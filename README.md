# Arborescence

# Arborescence
## What is Arborescence?
* In graph theory, Edmonds' algorithm is an algorithm for finding a spanning arborescence of minimum weight. 
* It is the directed analog of the minimum spanning tree problem. 

## Implementation
* C++ implementation of Edmond’s Branching Algorithm to find minimum cost arborescence.
* Given a graph with positive edges returns minimum arborescence cost and distance of i-th vertex from source vertex

### Algorithm
1. Initialization: Start with an source vertex as the root of the arborescence.
2. Cycle Detection and Elimination: Find cycles in the current arborescence and eliminate them by removing one edge from each cycle. This ensures that the resulting structure remains an arborescence.
3. Dual Variables Calculation: Calculate dual variables for each node in the graph. These dual variables represent the "cost" of including a particular node in the arborescence.
4. Negative Cycle Detection: If there is a node with a negative dual variable, it indicates the presence of a negative-cost cycle in the reduced cost graph (original cost minus dual variables). This cycle can be used to improve the current arborescence.
5. Branching Decision: Choose an edge to branch on based on certain criteria. This edge will be excluded from the arborescence for now, creating two subproblems.
6. Subproblem Solving: Recursively solve the two subproblems created by branching. One subproblem includes the chosen edge, while the other does not.
7. Merge Solutions: Combine the solutions obtained from the two subproblems to update the current arborescence.
8. Repeat Steps 2-7: Repeat steps 2 through 7 until no further improvements can be made or until a termination criterion is met.

### Input Format
First line: Number of Test Cases T and then follows their description
For each test case,
first row indicate N M s (single space separated)
where
* N is number of vertices in directed graph where vertices are labelled 1 to N (not 0 indexing)
* M is the number of edges and
* s is the index of source vertex
* Then M rows mentioning u v w(u,v) (single space separated, where u and v are vertex ids and w is weight, Safely assume all edge weights are non-negative, else print -1 for the output)

### Output Format
T rows corresponding to T test cases
Output row for each test case has 2N+1+1 entries (all single space separated) where first entry is the total sum of min cost arborescence and then N entries corresponding to vertices V1, V2, V3..., VN providing the distance of i-th vertex from the source vertex s. (Indicate -1 if unreachable) and then Symbol # and then N entries (corresponding to vertices V1, V2, V3..., VN) providing the label of the parent node through which one reaches i-th vertex (basically second last node in path from source vertex to that i-th vertex. (Indicate 0 if no parent i.e. for source vertex and -1 if vertex i not reachable)

### Running Time Complexity
The running time of this algorithm is O(EV).This is as fast as Prim's algorithm for an undirected minimum spanning tree.
