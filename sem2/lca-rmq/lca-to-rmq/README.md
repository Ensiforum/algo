# REDUCTION FROM LCA TO RMQ
Now, let’s show how we can use RMQ for computing LCA queries. Actually, we will reduce the LCA problem to RMQ in linear time, so every algorithm that solves the RMQ problem will solve the LCA problem too. Let’s show how this reduction can be done using an example:

![image](https://user-images.githubusercontent.com/101459465/179843780-5102490b-9356-42db-b187-949c5f686eeb.png)


![image](https://user-images.githubusercontent.com/101459465/179843812-290302cc-0bea-46fa-a527-b480a3b557b4.png)

Notice that LCAT(u, v) is the closest node from the root encountered between the visits of u and v during a depth first search of T. So, we can consider all nodes between any two indices of u and v in the Euler Tour of the tree and then find the node situated on the smallest level between them. For this, we must build three arrays:

E[1, 2*N-1] – the nodes visited in an Euler Tour of T; E[i] is the label of i-th visited node in the tour

L[1, 2*N-1] – the levels of the nodes visited in the Euler Tour; L[i] is the level of node E[i]
H[1, N] – H[i] is the index of the first occurrence of node i in E (any occurrence would be good, so it’s not bad if we consider the first one)


Assume that H[u] < H[v] (otherwise you must swap u and v). It’s easy to see that the nodes between the first occurrence of u and the first occurrence of v are E[H[u]…H[v]]. Now, we must find the node situated on the smallest level. For this, we can use RMQ. So, LCAT(u, v) = E[RMQL(H[u], H[v])] (remember that RMQ returns the index). Here is how E, L and H should look for the example:

![image](https://user-images.githubusercontent.com/101459465/179843869-fdb4535d-0407-4e24-814d-bc9952b11371.png)

Notice that consecutive elements in L differ by exactly 1.
