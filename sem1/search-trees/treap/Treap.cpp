#include <vector>
#include <stack>
#include <algorithm>

// Декартово дерево (дуча (дерево + куча), treap)
// Каждый элемент дерева имеет ключ (как в дереве поиска) и приоритет (по нему сортируется как куча) - отсюда и treap

// Такой структурой можно пользоваться как близким к сбалансированному деревом поиска
// Также она хорошо справляется с запросами на диапазонах 
// (и имеет модификацию "декартово дерево по неявному ключу" еще более в этом преуспевающую)

// Узел декартова дерева имеет такой вид: ключ, приоритет, левый и правый дочерни узлы
// Оба дочерних узла имеют меньший приоритет, но у левого ключ меньше чем у предка, а у правого больше

// В данной реализации представлены такие операции:
// - Построение дерева за O(n):
//		Отсортируем значения по ключу
//      Теперь каждый раз добавляя элемент мы будем знать, что это будет элемент с наибольшим ключем
//      А также, что до него это был предыдущий добавленный элемент, от него и пойдем
//      Будем сравнивать приоритеты и в случае необходимости переходить к родительскому узлу до тех пор пока не найдем нужное место
//      В конце последний элемент приоритет которого был меньше делаем левым дочерним узлом
//      
//		Узлы не хранят информации о родителях, так что такое поведение можно получить при помощи стека
//      Ведь можно заметить, что как только мы узнаем, что приоритет некоторого элемента меньше, то он и его поддерево нам более не нужны
//      Можно сказать, что нас интересует только узлы на пути от корня всегда вправо
//
// - Merge O(log n)
//		В зависимости от приоритета выбирает корневой узел, который объединит два поддерева
//
// - Split O(log n)
//		Разрез по ключу на два поддерева - меньше и больше ключа
//		Если изначальное левое поддерево имело больший ключ чем у нового родителя, то оно постепенно перевешивается на правое поддерево
//      Зеркально для правого
//      Возвращаются измененные поддеревья
//
// - Объединение двух деревьев за O(m * log n/m) 
//		Сравним приоритеты корней, очевидно, корень с наивысшим приоритетом - корень в новом дереве
//      По ключу этого корня разделим корень дерева с меньшим приоритетом
//      Левым поддеревом корня будет объединение его левого поддерева с левым поддеревом после разреза
//      Аналогично и с правым поддеревом
// 
// - Нахождение элемента по ключу за O(log n)
//		Как и в дереве поиска переходим в поддеревья в зависимости от знака в неравенстве key ? node.key
//      Пока ключи не совпадут
//

// - Удаление элемента по ключу за O(log n)
//		Сначала поиск элемента по ключу, а затем Merge его поддеревьев
//
// - Вставка элемента за O(log n)
//		Поиск места соответствующего приоритету за которым следует Split узла на два поддерева для нового элемента

struct Node
{
	int key;
	int priority;

	Node* left = nullptr;
	Node* right = nullptr;

	Node() {};

	Node(int key, int priority)
	{
		this->key = key;
		this->priority = priority;
	}

	Node(int key, int priority, Node* left, Node* right)
	{
		this->key = key;
		this->priority = priority;
		this->left = left;
		this->right = right;
	}

	bool operator <(const Node& other)
	{
		return key < other.key;
	}
};

class Treap
{
private:
	Node* root = nullptr;

	std::pair<Node*, Node*> Split(Node* tree, int key)
	{
		if (tree == nullptr)
		{
			return std::make_pair(nullptr, nullptr);
		}

		if (key > tree->key)
		{
			std::pair<Node*, Node*> subtrees = Split(tree->right, key);
			tree->right = subtrees.first;

			return std::make_pair(tree, subtrees.second);
		}
		else
		{
			std::pair<Node*, Node*> subtrees = Split(tree->left, key);
			tree->left = subtrees.second;

			return std::make_pair(subtrees.first, tree);
		}
	}

	Node* Merge(Node* first, Node* second)
	{
		if (first == nullptr)
		{
			return second;
		}

		if (second == nullptr)
		{
			return first;
		}

		if (first->priority > second->priority)
		{
			first->right = Merge(first->right, second);
			return first;
		}
		else
		{
			second->left = Merge(first, second->left);
			return second;
		}
	}

	Node* Union(Node* first, Node* second)
	{
		if (first == nullptr)
		{
			return second;
		}

		if (second == nullptr)
		{
			return first;
		}

		if (first->priority < second->priority)
		{
			std::swap(first, second);
		}

		std::pair<Node*, Node*> subtrees = Split(second, first->key);
		second->left = subtrees.first;
		second->right = subtrees.second;

		Node* result = first;
		result->left = Union(first->left, second->left);
		result->right = Union(first->right, second->right);
	}

	Node* Search(int key, Node* tree)
	{
		if (tree->key == key)
		{
			return tree;
		}

		if (key < tree->key)
		{
			return Search(key, tree->left);
		}
		else
		{
			return Search(key, tree->right);
		}
	}

	Node* Insert(Node* node, Node* tree)
	{
		if (tree == nullptr)
		{
			return node;
		}

		if (node->priority > tree->priority)
		{
			std::pair<Node*, Node*> subtrees = Split(tree, node->key);
			node->left = subtrees.first;
			node->right = subtrees.second;

			return node;
		}

		if (node->key < tree->key)
		{
			tree->left = Insert(node, tree->left);
		}
		else
		{
			tree->right = Insert(node, tree->right);
		}
	}

	Node* Remove(int key, Node* tree)
	{
		if (tree->key == key)
		{
			return Merge(tree->left, tree->right);
		}

		if (key < tree->key)
		{
			return new Node(tree->key, tree->priority,
				Remove(key, tree->left), tree->right);
		}
		else
		{
			return new Node(tree->key, tree->priority,
				tree->right, Remove(key, tree->right));
		}
	}

public:
	Treap(std::vector<Node> values)
	{
		std::sort(values.begin(), values.end());
		int valuesCount = values.size();
		
		std::stack<int> parents = std::stack<int>();

		for (int index = 0; index < valuesCount; ++index)
		{
			int last;
			while (!parents.empty() && values[parents.top()] < values[index])
			{
				last = parents.top();
				parents.pop();
			}

			if (!parents.empty())
			{
				values[parents.top()].right = &values[index];
			}
			values[index].left = &values[last];

			parents.push(index);
		}
	}

	Treap(Treap& first, Treap& second)
	{
		root = Union(first.root, second.root);
	}

	Node* Search(int key)
	{
		Search(key, root);
	}

	void Insert(Node value)
	{
		Insert(&value, root);
	}

	void Remove(int key)
	{
		Remove(key, root);
	}
};
