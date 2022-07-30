import copy
from math import inf


def floyd_warshall(graph):
    graph = copy.deepcopy(graph)
    n = len(graph)
    assert n > 0
    assert all(len(graph[i]) == n for i in range(n))
    for k in range(n):
        for i in range(n):
            for j in range(n):
                graph[i][j] = min(graph[i][j], graph[i][k] + graph[k][j])
    return graph


# example
def main():
    graph = [
        [0, 1, inf, inf],
        [1, 0, 2, inf],
        [inf, 2, 0, 3],
        [inf, inf, 3, 0]]
    print(floyd_warshall(graph))


if __name__ == '__main__':
    main()
