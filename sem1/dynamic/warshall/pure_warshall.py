import copy


def warshall(graph):
    graph = copy.deepcopy(graph)
    n = len(graph)
    assert n > 0
    assert all(len(graph[i]) == n for i in range(n))
    for k in range(n):
        for i in range(n):
            for j in range(n):
                graph[i][j] = graph[i][j] | (graph[i][k] & graph[k][j])
    return graph


# example
def main():
    graph = [
        [0, 1, 1, 0],
        [0, 0, 0, 1],
        [0, 0, 0, 0],
        [0, 0, 1, 0]
    ]
    print(warshall(graph))


if __name__ == '__main__':
    main()
