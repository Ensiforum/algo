#include <algorithm>
#include <vector>
#include <limits>

int MAX = std::numeric_limits<int>::max();

// СНМ - система непересекающихся множеств
// Эта структура данных подходит для случаев, когда главное - необходимость знать о связности между элементами
// Например, так можно найти компоненты связности или проверять правильность данных записанных как разница между значениями двух элементов

// Основные операции СНМ:
// GetRepresentative(find) - есть вершина, что выбрана представлять некоторе множество, эта функция ее находит
// Join(union) - мы узнали, что два независимых множества на самом деле зависимы и объединяем их в одно

// Данная реализация поддерживает такие операции:
// - нахождение представителя множества
// - получение аггрегированного значения (аггрегация от представителя к элементу)
// - получение ассоциированного значения

// При чем амортизированная оценка для каждой из операций O(1)
// Для операции получения ассоциированного значения это очевидно
// Для получения представителя, а также аггрегированного значения это доказывается таким образом:
// Особенность этой реализации - представление в виде дерева
// Чтобы получить представителя нужно подняться до корня и вернуть его
// Чтобы объединить множества достаточно сделать одного представителя родителем другого

// Однако это даст O(1) для объединения, но O(N) для нахождения представителя
// Чтобы ускорить нахождение представителя при каждом вызове функции GetRepresentative будем подвешивать все вершины которые мы прошли сразу к корню
// Также будем хранить размер и подвешивать меньшие по размеру к большим
// Тогда в следующий раз доступ будет за O(1), с учетом того, что при частых запросах операция GetRepresentative будет выполняться тоже часто
// можно сказать, что мы просто выполнили операцию лишний раз для каждой вершины (это действительно так, от каждой вершины мы сделали один подъем вверх)

class Node
{
	Node* parent;
	int min;
	int delta;
	int size;

public:
	Node(int value)
	{
		parent = nullptr;
		min = value;
		delta = value;
		size = 1;
	}

	Node* GetRepresentative()
	{
		Node* representative = this;

		std::vector<Node*> children = std::vector<Node*>();
		std::vector<int> deltas = std::vector<int>();
		int min = MAX;
		
		// Надо выполнять аггрегацию
		while (parent != nullptr)
		{
			children.push_back(representative);
			deltas.push_back(representative->delta);
			min = std::min(min, representative->min);
			representative = parent;
		}

		int count = children.size();
		int accumulator = 0;

		for (int index = count - 1; index >= 0; --index)
		{
			accumulator += deltas[index];
			children[index]->delta = accumulator;
			children[index]->min = min;
			children[index]->parent = representative;
		}

		return representative;
	}

	void Join(Node* other)
	{
		Node* representative = GetRepresentative();
		Node* otherRepresentative = other->GetRepresentative();

		int commonMin = std::min(otherRepresentative->min, representative->min);

		if (representative->size > otherRepresentative->size)
		{
			otherRepresentative->parent = representative;
			otherRepresentative->min = commonMin;
			otherRepresentative->size += representative->size;
		}
		else
		{
			representative->parent = representative;
			representative->min = commonMin;
			representative->size += otherRepresentative->size;
		}
	}

	int GetMin()
	{
		return  GetRepresentative()->min;
	}

	int GetAggregatedValue()
	{
		Node* representative = GetRepresentative();
		return delta + representative->delta;
	}
};
