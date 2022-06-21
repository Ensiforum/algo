#include <vector>

// Сведение задачи LCA к задаче RMQ

// В задаче LCA ведется поиск наименьшего общего предка, то есть такого, "глубина" которого в дереве меньше чем у обоих сыновей
// В задаче RMQ ведется поиск минимума на подотрезке в некотором списке

// Тогда чтобы привести LCA к RMQ нам нужно сформировать список вершин, 
// такой чтобы на подотрезке между некоторыми двумя вершинами минимумом был их наименьший общий предок

// Сделать это довольно просто, необходимо сформировать эйлеров обход используя поиск в глубину:
// - Определяем некоторую стартовую вершину, создаем массив высот и порядок вхождений в обход
// - Запускаем обход в глубину, для каждой вершины сохраняем ее вхождение, фиксируем высоту (= глубина рекурсии)
//   и добавляем в эйлеров обход (сразу же, а также после каждого поиска уже от ребенка)

// Доказательство корректности:
// Эйлеров обход выглядит таким образом:
// корень, поддерево, корень, другое поддерево...
// Так как элементы у нас разные, то и поддеревья у них отличаются (или одно из них - корень)
// Глубина у корня - минимальная, а значит используя RMQ мы найдем именно его в обоих случаях:
// - [корень, поддерево]
// - [поддерево, корень, другое поддерево]

template <class T>
struct Node
{
	std::vector<Node*> children;
	T value;
	int index;
};

template <class T>
struct Graph
{
	Node* root;
	int size;
};

template <class T>
void Dfs(const Node<T>* vertex, const int parentIndex, 
         const int height, std::vector<int>& firstVisit,
         std::vector<int>& heights, std::vector<Node<T>*>& eulerTour)
{
    firstVisit[vertex->index] = eulerTour.size();
    eulerTour.push_back(vertex);
    heights[vertex->index] = height;

    for (Node<T>* child : vertex->children)
    {
        if (child->index == parentIndex)
        {
            continue;
        }

        Dfs(child, vertex->index, height + 1);
        eulerTour.push_back(vertex);
    }
}

template <class T>
std::vector<Node<T>*> LcaToRmq(Graph<T> lcaTarget)
{
    int nodesCount = lcaTarget.size + 1;

	std::vector<int> firstVisit(nodesCount, -1);
	std::vector<int> heights(nodesCount, 0);

	std::vector<Node<T>*> eulerTour();
	eulerTour.reserve(nodesCount * 2);

    Dfs(lcaTarget.head, -1, 0);

	return eulerTour;
}
