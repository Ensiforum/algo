#include <vector>

// Алгоритм Воршалла (Флойда-Воршалла)
// Используется для вычисления матрицы достижимости (транзитивного замыкания) в графе

// Принцип работы такой:
// При наличии графа у нас уже есть сведения о путях длины 1 (матрица смежности), скопируем ее в матрицу транзитивности
// В ходе работы алгоритма мы будем узнавать о новых путях и заносить их в матрицу
// Если есть путь из i в k и из k в j, то есть путь из i в j (транзитом через k)
// Чтобы найти все пути нужно подставить все вершины как k
// После проверки k матрица будет содержать вершины достижимые изначально или через вершины от 1 до k

// Алгоритм требует O(N^3) времени и O(N^2) памяти
// По этой причине он не всегда эффективнее поиска в глубину на разреженных графах

// Этот алгоритм также позволяет вычслить кратчайшие расстояния, но уже сравнением расстояния напрямую (при отсутствии пути INF) и транзитом 

struct Graph {
	int verticiesCount;
	std::vector<std::vector<bool>> adjacencyMatrix;
};

template <class T>
std::vector<std::vector<T>> CopyMatrix(const std::vector<std::vector<T>>& origin) {
	int height = origin.size();
	int width = origin[0].size();

	std::vector<std::vector<T>> clone =
		std::vector<std::vector<T>>(height, std::vector<T>(width));

	for (int row = 0; row < height; ++row) {
		for (int col = 0; col < width; ++col) {
			clone[row][col] = origin[row][col];
		}
	}

	return clone;
}

std::vector<std::vector<bool>> ReachabilityMatrix(const Graph& graph) {
	std::vector<std::vector<bool>> reachabilityMatrix = CopyMatrix(graph.adjacencyMatrix);

	for (int vertex = 0; vertex < graph.verticiesCount; ++vertex) {
		for (int row = 0; row < graph.verticiesCount; ++row) {
			for (int col = 0; col < graph.verticiesCount; ++col) {
				reachabilityMatrix[row][col] = reachabilityMatrix[row][col] ||
					(reachabilityMatrix[row][vertex] && reachabilityMatrix[vertex][col]);
			}
		}
	}

	return reachabilityMatrix;
}
