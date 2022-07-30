class Edge {

    constructor(startVertex, endVertex, weight) {
        if (typeof startVertex !== 'number' ||
            typeof endVertex !== 'number' ||
            typeof weight !== 'number') {
            throw new Error(`Unknown parameters type. Expected 'number'`)
        }

        this.startVertex = startVertex;
        this.endVertex = endVertex;
        this.weight = weight;
    }

    equals(other) {
        if (!(other instanceof Edge)) {
            return false;
        }
        return (this.startVertex === other.startVertex &&
            this.endVertex === other.endVertex) || (
            this.startVertex === other.endVertex &&
            this.endVertex === other.startVertex);
    }

}

function bfs(rGraph, s, t, parent) {
    let visited = new Array(rGraph.length).fill(false);
    let q = [];
    q.push(s);
    visited[s] = true;
    parent[s] = -1;
    while (q.length > 0) {
        let u = q.shift();
        for (let v = 0; v < rGraph.length; v++) {
            if (visited[v] === false && rGraph[u][v] > 0) {
                q.push(v);
                parent[v] = u;
                visited[v] = true;
            }
        }
    }

    return visited[t] === true;
}

function dfs(rGraph, s, visited) {
    visited[s] = true;
    for (let i = 0; i < rGraph.length; i++) {
        if (rGraph[s][i] !== 0 && !visited[i]) {
            dfs(rGraph, i, visited);
        }
    }
}

function minCut(graph, s, t) {
    let u, v;
    let rGraph = JSON.parse(JSON.stringify(graph));
    let parent = new Array(rGraph.length);
    while (bfs(rGraph, s, t, parent)) {
        let pathFlow = Infinity;
        for (v = t; v !== s; v = parent[v]) {
            u = parent[v];
            pathFlow = Math.min(pathFlow, rGraph[u][v]);
        }

        for (v = t; v !== s; v = parent[v]) {
            u = parent[v];
            rGraph[u][v] -= pathFlow;
            rGraph[v][u] += pathFlow;
        }
    }

    let visited = new Array(rGraph.length).fill(false);
    dfs(rGraph, s, visited);

    let minCutValue = 0;
    const edges = [];

    for (let i = 0; i < rGraph.length; i++) {
        for (let j = 0; j < rGraph.length; j++) {
            if (visited[i] && !visited[j] && graph[i][j] !== 0) {
                edges.push(new Edge(i, j, graph[i][j]));
                minCutValue += graph[i][j];
            }
        }
    }

    return {
        value: minCutValue,
        cutEdges: edges
    };
}
