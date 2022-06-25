#include <vector>
#include <limits>

const int INF = std::numeric_limits<int>::max();

// Двоичная куча
// Куча - дерево, в котором элемент-родитель (или его ключ) всегда больше или всегда меньше ребенка
// Двоичная куча - сбалансированное дерево, у каждого элемента которого не более двух детей

// В данной реализации куча строится по минимуму - родитель меньше ребенка

// Реализация:
// Элементы хранятся в динамическом массиве и доступ к ним организован по индексу
// Для этого положим, что дерево заполняется по уровням и слево направо
// Тогда это будет справедливо при такой нумерации: родитель(i) = (i - 1)/2, левый(i) = 2 * i + 1, правый(i) = 2 * i + 2

// Чтобы поддерживать "кучность" используются две операции:
// - Просеивание вверх - вершина, возможно, ниже чем должна быть, она меняется местами с предками пока не встанет на свое законное место
// - Просеивание вниз - вершина, наоборот, возможно, выше чем должна быть и спускается вниз, меняясь обязательно с наименьшим ребенком

// Используя эти операции в данной реализации:
// - Строится куча - операция Heapify
//   Если начиная с последнего элемента и до первого делать просеивание вниз, то в конце будет получена куча
//   Это работает, так как куча после текущего элемента упорядочена правильно и мы упорядочиваем элементы выше
//   В данной реализации просеивание ведется от середины, а не от конца, так как у вершин после середины нет детей
//   Логично, что куча с одним элементом упорядочена
//
// - Добавляется элемент - операция Insert
//   Элемент добавляется в конец и просеивается вверх
//
// - Извлекается минимум - операция ExtractMin
//   Сохраняется значение в корне и возвращается в самом конце
//   Далее последний элемент становится корнем, а массив с элементами сокращается
//   После этого последний элемент просеивается вниз

// Кучи часто являются основой для структуры данных очередь с приоритетом
// Эту роль здесь выполняет функция ExtractMin

// Требования по времени: 
// Построение - O(N), так как количество вершин на высоте h <= ceil(n/2^h)
// Тогда максимальное количество операций в построении - h от 1 до log N: n/2^h * 2 * h => 2 * n * h/2^h => 2 * n * (2 /(2 - 1))^ 2 => 4n
//
// Вставка и извлечение минимума - O(log N), так как просеивания ограничены высотой дерева, так как оно сбалансированное, то высота log N

// Требования по памяти: O(N), ведь ничего кроме массива и не потребовалось

class BinaryHeap
{
private:
	std::vector<int> heap;

	void SiftDown(int currentElement)
	{
		int leftChild = currentElement * 2 + 1;
		int rightChild = currentElement * 2 + 2;

		int minValue = std::min(heap[leftChild], heap[rightChild]);
		
		if (minValue == INF)
		{
			return;
		}

		if (minValue > heap[currentElement])
		{
			return;
		}

		if (minValue == heap[leftChild])
		{
			std::swap(heap[currentElement], heap[leftChild]);
			SiftDown(leftChild);
		}
		else
		{
			std::swap(heap[currentElement], heap[rightChild]);
			SiftDown(rightChild);
		}
	}

	void SiftUp(int currentElement)
	{
		int parent = (currentElement - 1) / 2;

		if (heap[currentElement] < heap[parent] && currentElement != 0)
		{
			std::swap(heap[currentElement], heap[parent]);
			SiftUp(parent);
		}
	}

	void Heapify()
	{
		int middle = (heap.size() - 2) / 2;

		for (int index = middle; index >= 0; --index)
		{
			SiftDown(index);
		}
	}

public:
	int operator[] (int index)
	{
		if (heap.size() <= index || index < 0)
		{
			return heap[index];
		}

		return INF;
	}

	BinaryHeap(const std::vector<int>& values)
	{
		heap = values;
		Heapify();
	}

	BinaryHeap Merge(BinaryHeap& otherHeap)
	{
		heap.insert(heap.end(), otherHeap.heap.begin(), otherHeap.heap.end());
		Heapify();
	}

	int ExtractMin()
	{
		int min = heap[0];

		heap[0] = heap[heap.size() - 1];
		heap.pop_back();
		SiftDown(0);

		return min;
	}

	void Insert(int value)
	{
		heap.push_back(value);
		SiftUp(heap.size() - 1);
	}
};
