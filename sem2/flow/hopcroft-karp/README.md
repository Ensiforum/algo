<h1>Hopcroft–Karp Algorithm for Maximum Matching</h1>
<p>A matching in a Bipartite Graph is a set of the edges chosen in such a way that no two edges share an endpoint. A maximum matching is a matching of maximum size (maximum number of edges). In a maximum matching, if any edge is added to it, it is no longer a matching. There can be more than one maximum matching for a given Bipartite Graph.</p>
<p>Hopcroft Karp algorithm is an improvement over the Ford Fulkerson algorithm that runs in O(√V x E) time. Let us define few terms before we discuss the algorithm. Let us define few terms before we discuss the algorithm:</p>
<p><b><i>Free Node or Vertex:</i></b> Given a matching M, a node that is not part of matching is called free node. Initially all vertices as free (See first graph of below diagram). In second graph, u2 and v2 are free. In third graph, no vertex is free. </p>
<p><b><i>Matching and Not-Matching edges:</b></i> Given a matching M, edges that are part of matching are called Matching edges and edges that are not part of M (or connect free nodes) are called Not-Matching edges. In first graph, all edges are non-matching. In second graph, (u0, v1), (u1, v0) and (u3, v3) are matching and others not-matching. </p>
<p><b><i>Alternating Paths:</i></b> Given a matching M, an alternating path is a path in which the edges belong alternatively to the matching and not matching. All single edges paths are alternating paths. Examples of alternating paths in middle graph are u0-v1-u2 and u2-v1-u0-v2. </p>

<p><b><i>Augmenting path: </i></b>Given a matching M, an augmenting path is an alternating path that starts from and ends on free vertices. All single edge paths that start and end with free vertices are augmenting paths. In below diagram, augmenting paths are highlighted with blue color. Note that the augmenting path always has one extra matching edge. The Hopcroft Karp algorithm is based on below concept. A matching M is not maximum if there exists an augmenting path. It is also true other way, i.e, a matching is maximum if no augmenting path exists So the idea is to one by one look for augmenting paths. And add the found paths to current matching. </p>


<p>Hopcroft Karp Algorithm:</p>
<br>
<ol>
<li>Initialize Maximal Matching M as empty.
</li>
<li>While there exists an Augmenting Path p
	<ul>
		<li>Remove matching edges of p from M and add not-matching edges of p to M</li>
		<li>(This increases size of M by 1 as p starts and ends with a free vertex)</li>
	</ul>
</li>
<li>Return M. 
</li>
</ol>

<div align = "center">
<p>Below diagram shows working of the algorithm.</p>
<img src = "https://media.geeksforgeeks.org/wp-content/cdn-uploads/HopcroftKarp1.png">

</div>

<p>In the initial graph all single edges are augmenting paths and we can pick in any order. In the middle stage, there is only one augmenting path. We remove matching edges of this path from M and add not-matching edges. In final matching, there are no augmenting paths so the matching is maximum. </p>
