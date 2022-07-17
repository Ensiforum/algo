#include <vector>
#include <queue>
#include <iostream>
#include <limits>

// Алгоритм Диница
// Это алгоритм предназначенный для нахождения максимального потока в сети
// Он относится к алгоритмам основанным на поиске блокирующего потока

// Блокирующий поток - поток такой, что любой путь из истока в сток содержит ребро из этого потока 
// Если все еще существует путь из истока в сток, то существует и блокирующий поток, ведь обратное невозможно
// (например, существует только один путь из истока в сток, значит он и является блокирующим потоком)
// Это позволяет применить теорему Форда-Фалкерсона - поток максимален если в остаточной сети отсутствуют пути из истока в сток
// То есть в нашем случае если невозможно найти блокирующий поток, то наш поток максимален

// Алгоритмы основанные на поиске блокирующего потока в основном отличаются подходом к поиску блокирующего пути
// В алгоритме Диницы поиск происходит таким образом:
//    - На основе остаточной сети строится слоистая сеть
//		Слоистая сеть - граф упорядоченный в слои при помощи обхода в ширину, сохраняются только ребра которые ведут из одного слоя в следующий,
//      а значит обратные ребра или ребра длиной в несколько слоев отсутствуют
//
//	  - Если в данной сети достижим сток, то существует хотя бы один блокирующий поток и его можно искать, иначе максимальный поток уже найден
//
//    - Пока в данной сети достижим сток ищутс блокирующие пути 
//      (это можно сделать при помощи обхода в глубину исходя из свойств слоистой сети)
//
//    - Слоистая сеть перестраивается, так как нужно учесть изменения потока 

// Сложность по времени составляет: O(V^2 * E)
// Во время каждой фазы обрабатывается до E путей длины до V -> O(VE) на фазу
// Количество фаз - O(V): если нам пришлось перестраивать слоистую сеть, то значит, что все слои до стока уже не позволяют достичь стока
// Сеть перестраивается и уже вершины из слоев, что раньше были снизу находятся над стоком, это может произойти до O(V) раз

// Но в данной реализации используется масштабирование пропускных способностей, что позволяет улучшить асимптотику до O (VE log C),
// где C наибольшая пропускная способность среди ребер
// Такая асимптотика получается из-за другой оценки количества фаз алгоритма Диницы
// В случае с масштабированием можно быть уверенным, что на каждой фазе масштабирования будут найдены все потоки искомой величины,
// А значит количество фаз будет привязано лишь к количеству фаз масштабирования 

const int MAX_POSSIBLE_FLOW = std::numeric_limits<int>::max();

struct Edge
{
	int start, end;
	int flow, capacity;

	Edge(int start, int end, int capacity)
	{
		this->start = start;
		this->end = end;
		this->capacity = capacity;
		flow = 0;
	}
};

struct Graph
{
	int verticesCount, edgesCount;
	std::vector<std::vector<int>> incidentEdges;
	std::vector<Edge> edges;
};

struct NetworkGraph
{
	Graph graph;
	int source, sink;
};

bool AuxBFS(NetworkGraph& network, std::vector<int> depth)
{
	std::queue<int> order = std::queue<int>();
	order.push(network.source);

	depth = std::vector<int>(network.graph.verticesCount, -1);
	depth[network.source] = 0;

	std::vector<Edge>& edges = network.graph.edges;
	while (!order.empty())
	{
		int vertex = order.front();
		order.pop();

		for (int edge : network.graph.incidentEdges[vertex])
		{
			if (depth[edges[edge].end] != -1)
			{
				continue;
			}

			if (edges[edge].capacity - edges[edge].flow < 1)
			{
				continue;
			}

			order.push(edges[edge].end);
			depth[edges[edge].end] = depth[vertex] + 1;
		}
	}
	return depth[network.sink] != -1;
}

int AuxDFS(NetworkGraph& network, 
		      std::vector<int> depth, std::vector<int> pointers, 
	          int vertex, int flow)
{
	if (flow == 0)
	{
		return 0;
	}

	if (vertex == network.sink)
	{
		return flow;
	}

	std::vector<std::vector<int>>& incidentEdges = network.graph.incidentEdges;
	std::vector<Edge>& edges = network.graph.edges;

	for (int& nextVertex = pointers[vertex]; nextVertex < (int)incidentEdges[vertex].size(); ++nextVertex)
	{
		int edge = incidentEdges[vertex][nextVertex];
		int endVertex = edges[edge].end;

		if (depth[vertex] + 1 != depth[endVertex] || edges[edge].capacity - edges[edge].flow < 1)
		{
			continue;
		}

		int newFlow = std::min(flow, edges[edge].capacity - edges[edge].flow);
		int pushed = AuxDFS(network, depth, pointers, endVertex, newFlow);

		if (pushed > 0)
		{
			edges[edge].flow += pushed;
			// Предполагается, что обратное ребро добавляется следом за ребром из начальной сети
			edges[edge ^ 1].flow -= pushed;
			return pushed;
		}
	}

	return 0;
}

int Dinitz(NetworkGraph& network)
{
	int maxFlow = 0;
	int pushed = 0;
	int scale = MAX_POSSIBLE_FLOW;

	std::vector<int> depth = std::vector<int>(network.graph.verticesCount, 0);
	while (scale > 0)
	{
		if (!AuxBFS(network, depth))
		{
			scale /= 2;
			continue;
		}

		std::vector<int> pointers = std::vector<int>(network.graph.verticesCount, 0);
		while ((pushed = AuxDFS(network, depth, pointers, network.source, scale)) > 0)
		{
			maxFlow += pushed;
		}
	}

	return maxFlow;
}