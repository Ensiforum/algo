#include <stdexcept>

// Структура данных "Персистентная очередь"
// Это означает что структура позволяет хранить свои состояния и к ним можно вернуться
// Данная реализация опирается на реализацию персистентного дека и является функциональной
// То есть при изменении возвращает новую версию, но не поддерживает какой-либо откат или выбор версии напрямую

// Персистентная (функциональная) очередь устроена таким образом:
// Она содержит значение головы, хвоста и персистентная очередь из элементов между ними
// Основное отличие как раз в наличии очереди посередине, которая позволяет достаточно быстро и без больших затрат по памяти создавать новые версии
// Очередь посередине содержит уже не по одному элементу, а по паре, ее же очередь посередине уже пару пар и так далее
// Это позволяет получить оценку O (log N) для извлечения, удаления и добавления - максимальное количество внутренних очередей
// Также это сэкономит некоторое количество памяти, ведь меняться будет только какая-то из очередей

// Возможно улучшить оценку, для этого надо применить буферы (отсутствуют в данной реализации)
// Мы разрешим хранить несколько больше элементов чем в изначальной версии, однако если такое переполнение существует, то его надо будет исправить
// Все также может появиться необходимость спуститься в самый низ, но вероятность этого будет меньше

// К сожалению, внутреннее устройство темплейтов в C++ не позволяет определить внутреннюю очередь как PersistentQueue<std::pair<T*, T*>>
// Компилятор будет пытаться рекурсивно создавать классы пока у него не закончится память
//
// Примечание: иногда очень хотелось бы чтобы на каких-то больших значениях этот процесс останавливался и создавал заглушку, 
// которая выкидывала бы ошибку при попытке создания объекта класса, но на практике была бы недосягаемой 
// (надо еще поискать компьютер памяти которого хватит на тысячный слой очереди) 
//
// В данной реализации роль пары выполняет класс PairVector
// Ему хватает лишь шаблона для изначального типа, а основной функционал в возможности получить половину вектора или склеить его из двух других

template <class T>
class PersistentQueue
{
private:
	template <class TT>
	class PairVector
	{
	private:
		std::vector<TT> underlyingVector;
		int size;

	public:
		PairVector(TT value)
		{
			underlyingVector = std::vector<TT>{ value };
			size = 1;
		}

		PairVector(std::vector<TT> values)
		{
			underlyingVector = values;
			size = values.size();
		}

		PairVector(const PairVector<TT>& first, const PairVector<TT>& second)
		{
			underlyingVector = std::vector<TT>();
			underlyingVector.insert(underlyingVector.end(), first.underlyingVector.begin(), first.underlyingVector.end());
			underlyingVector.insert(underlyingVector.end(), second.underlyingVector.begin(), second.underlyingVector.end());
			size = first.size + second.size;
		}

		PairVector<TT>* First()
		{
			return new PairVector<TT>(std::vector<T>(underlyingVector.begin(), underlyingVector.begin() + (size / 2)));
		}

		PairVector<TT>* Second()
		{
			return new PairVector<TT>(std::vector<T>(underlyingVector.begin() + (size / 2), underlyingVector.end()));
		}

		TT ToSingleValue()
		{
			return underlyingVector[0];
		}
	};

	PairVector<T>* head;
	PairVector<T>* tail;
	PersistentQueue<T>* child;

	PersistentQueue<T>* Enqueue(PairVector<T>* value)
	{
		if (tail == nullptr)
		{
			return new PersistentQueue<T>(head, value, child);
		}
		else
		{
			if (child == nullptr)
			{
				child = new PersistentQueue<T>();
			}
			return new PersistentQueue<T>(head, nullptr, child->Enqueue(new PairVector<T>(*tail, *value)));
		}
	}

public:
	PersistentQueue()
	{
		head = nullptr;
		tail = nullptr;
		child = nullptr;
	}

	PersistentQueue(PairVector<T>* left, PairVector<T>* right, PersistentQueue<T>* child)
	{
		this->head = left;
		this->tail = right;
		this->child = child;
	}

	PairVector<T>* Peek()
	{
		bool emptyHead = head == nullptr;
		bool emptyTail = tail == nullptr;
		bool emptyChild = child == nullptr;

		if (!emptyHead)
		{
			return head;
		}

		if (!emptyChild)
		{
			return (child->Peek())->First();
		}

		if (!emptyTail)
		{
			return tail;
		}

		throw std::logic_error("No elements in empty queue");
	}

	PersistentQueue<T>* Dequeue()
	{
		bool emptyHead = head == nullptr;
		bool emptyTail = tail == nullptr;
		bool emptyChild = child == nullptr;

		if (!emptyHead)
		{
			if (emptyTail && emptyChild)
			{
				return nullptr;
			}

			return new PersistentQueue<T>(nullptr, tail, child);
		}

		if (!emptyChild)
		{
			PairVector<T>* newLeft = child->Peek()->Second();
			return new PersistentQueue<T>(newLeft, tail, child->Dequeue());
		}

		if (!emptyTail)
		{
			return nullptr;
		}

		throw std::logic_error("No elements in empty queue");
	}

	PersistentQueue<T>* Enqueue(T value)
	{
		if (tail == nullptr)
		{
			return new PersistentQueue<T>(head, new PairVector<T>(value), child);
		}
		else
		{
			if (child == nullptr)
			{
				child = new PersistentQueue<T>();
			}
			return new PersistentQueue<T>(head, nullptr, child->Enqueue(new PairVector<T>(*tail, PairVector<T>(value))));
		}
	}
};
