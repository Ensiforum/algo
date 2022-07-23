# Ford-Fulkerson Algorithm for Maximum Flow Problem

Given a graph which represents a flow network where every edge has a capacity. Also given two vertices source ‘s’ and sink ‘t’ in the graph, find the maximum possible flow from s to t with following constraints:

- Flow on an edge doesn’t exceed the given capacity of the edge.
- Incoming flow is equal to outgoing flow for every vertex except s and t.
For example, consider the following graph from CLRS book. 

![image](https://user-images.githubusercontent.com/101459465/180602622-6a039a47-aa49-411c-a1e1-9c412713c239.png)

The maximum possible flow in the above graph is 23. 

![image](https://user-images.githubusercontent.com/101459465/180602624-65131fbc-314c-4ce7-9fe5-02f41a335f50.png)


# Ford-Fulkerson Algorithm 
## The following is simple idea of Ford-Fulkerson algorithm:
### 1. Start with initial flow as 0.
### 2. While there is a augmenting path from source to sink. 
### 3. Add this path-flow to flow.
### 4. Return flow.
Time Complexity: Time complexity of the above algorithm is O(max_flow * E). We run a loop while there is an augmenting path. In worst case, we may add 1 unit flow in every iteration. Therefore the time complexity becomes O(max_flow * E).

How to implement the above simple algorithm? 
Let us first define the concept of Residual Graph which is needed for understanding the implementation. 

Residual Graph of a flow network is a graph which indicates additional possible flow. If there is a path from source to sink in residual graph, then it is possible to add flow. Every edge of a residual graph has a value called residual capacity which is equal to original capacity of the edge minus current flow. Residual capacity is basically the current capacity of the edge. 

Let us now talk about implementation details. Residual capacity is 0 if there is no edge between two vertices of residual graph. We can initialize the residual graph as original graph as there is no initial flow and initially residual capacity is equal to original capacity. To find an augmenting path, we can either do a BFS or DFS of the residual graph. We have used BFS in below implementation. Using BFS, we can find out if there is a path from source to sink. BFS also builds parent[] array. Using the parent[] array, we traverse through the found path and find possible flow through this path by finding minimum residual capacity along the path. We later add the found path flow to overall flow. 

The important thing is, we need to update residual capacities in the residual graph. We subtract path flow from all edges along the path and we add path flow along the reverse edges We need to add path flow along reverse edges because may later need to send flow in reverse direction

source: https://www.geeksforgeeks.org/ford-fulkerson-algorithm-for-maximum-flow-problem/
