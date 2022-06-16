#include <vector>

// Алгоритм Куна
// Используется для поиска наибольшего паросочетания в двудольных графах

// Опирается на теорему Бержа (https://en.wikipedia.org/wiki/Berge%27s_theorem)
// "Наибольшим является паросочетание для которого отсутствует дополняющий путь" 
// Дополняющий путь - чередующийся путь, в котором начальная и конечная вершина не принадлежат паросочетанию
// Чередующийся путь - путь в котором чередуются ребра покрытие и непокрытые паросочетанием

// Алгоритмы опирающиеся на теорему Бержа работают так:
// Начиная с пустого паросочетания ищется дополняющий путь
// Если он находится, то в соответствии с ним меняется текущее паросочетание

// Алгоритм Куна учитывает лишь особенности двудольных графов 
// Поэтому гарантированно правильно работать будет толькос ними

// Каким образом учитываются особенности двудольных графов:
// Известно, что нет ребер, которые будут соединять вершины в одной доле
// То есть, циклов нечетной длины - не будет (иначе алгоритм мог бы зайти в тупик)

// Сам поиск доплняющего пути довольно прост:
// - Выберем одну вершину из первой доли
// - Начнем обход в глубину до момента когда будет найдена еще не занятая вершина из второй доли или доказано обратное (везде тупики)Ж
//      - если вершина из другой доли свободна, то доплняющий путь найден
//      - если она принадлежит паросочетанию, то попробуем сделать ее парой нашей вершины и найти пару для другой
// - Сделаем так для всех вершин из первой доли

// Алгоритм работает за O(VE) так как совершает V обходов, каждый за O(E)
//
// В данной реализации есть оптимизация через жадное нахождение некоторого паросочетания, что отсечет N проверок быстрее чем за O(NE)
// где N - количество пар в найденом паросочетании
//
// Также, очень полезно выбирать как первую меньшую долю графа (так как время работы алгоритма зависит только от одной доли)

struct Graph
{
    int firstPartSize;
    int secondPartSize;

    std::vector<std::vector<int>> adjacencyMatrix;
};

std::vector<bool> GreedyMatching(const Graph& graph, std::vector<int>& matching) {
    std::vector<bool> used = std::vector<bool>(graph.firstPartSize, false);
    
    for (int vertex = 0; vertex < graph.firstPartSize; ++vertex) {
        for (int adjacentVertex : graph.adjacencyMatrix[vertex]) {
            if (matching[adjacentVertex] == -1) {
                matching[adjacentVertex] = vertex;
                used[vertex] = true;
                
                break;
            }
        }
    }

    return used;
}

bool KuhnDfs(int vertex, std::vector<bool>& used, std::vector<int>& matching,
             const std::vector<std::vector<int>>& graph) {
    if (used[vertex]) {
        return false;
    }

    used[vertex] = true;
    for (const int& neighbour : graph[vertex]) {
        if (matching[neighbour] == -1 || KuhnDfs(matching[neighbour], used, matching, graph)) {
            matching[neighbour] = vertex;
            return true;
        }
    }

    return false;
}

std::vector<int> Kuhn(const Graph& graph) {
	std::vector<int> matching = std::vector<int>(graph.secondPartSize, -1);
    std::vector<bool> used;

    std::vector<bool> usedInGreedy = GreedyMatching(graph, matching);
    for (int vertex = 0; vertex < graph.firstPartSize; ++vertex) {
        if (usedInGreedy[vertex]) {
            continue;
        }

        used = std::vector<bool>(graph.firstPartSize, false);
        KuhnDfs(vertex, used, matching, graph);
    }

    return matching;
}
