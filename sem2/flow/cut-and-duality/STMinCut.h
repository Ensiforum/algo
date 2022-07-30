/* Author: Oleh Toporkov */

#pragma once
#include <vector>
#include <queue>
#include <tuple>
#include <type_traits>

template<typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
class STMinCut {
public:
    STMinCut(const std::vector<std::vector<T>>& graph, size_t s, size_t t) :
        graph(graph), rGraph(graph), s(s), t(t) {
        minCut();
    }

    int64_t operator()() const {
        return st;
    }

    std::vector<std::tuple<size_t, size_t, int64_t>> getEdges() const {
        return edges;
    }

private:
    std::vector<std::vector<T>> graph;
    std::vector<std::vector<T>> rGraph;
    size_t s, t;
    int64_t st = 0;
    std::vector<std::tuple<size_t, size_t, int64_t>> edges;

    bool bfs(std::vector<int64_t>& parent) {
        std::vector<bool> visited(rGraph.size(), false);
        std::queue<size_t> q;
        q.push(s);
        visited[s] = true;
        parent[s] = -1;
        while (!q.empty()) {
            int64_t u = q.front();
            q.pop();
            for (size_t v = 0; v < rGraph.size(); v++) {
                if (!visited[v] && rGraph[u][v] > 0) {
                    q.push(v);
                    parent[v] = u;
                    visited[v] = true;
                }
            }
        }
        return visited[t];
    }

    void dfs(std::vector<bool>& visited, size_t v) {
        visited[v] = true;
        for (size_t i = 0; i < rGraph.size(); i++) {
            if (rGraph[v][i] && !visited[i]) {
                dfs(visited, i);
            }
        }
    }

    void minCut() {
        int64_t u, v;
        std::vector<int64_t> parent(rGraph.size());
        while (bfs(parent)) {
            int64_t pathFlow = INT64_MAX;
            for (v = t; v != s; v = parent[v]) {
                u = parent[v];
                pathFlow = std::min(pathFlow, (int64_t)rGraph[u][v]);
            }
            for (v = t; v != s; v = parent[v]) {
                u = parent[v];
                rGraph[u][v] -= pathFlow;
                rGraph[v][u] += pathFlow;
            }
        }

        std::vector<bool> visited(rGraph.size(), false);
        dfs(visited, s);
        for (size_t i = 0; i < rGraph.size(); i++) {
            for (size_t j = 0; j < rGraph.size(); j++) {
                if (visited[i] && !visited[j] && graph[i][j]) {
                    st += graph[i][j];
                    edges.push_back(std::make_tuple(i, j, graph[i][j]));
                }
            }
        }
    }
};