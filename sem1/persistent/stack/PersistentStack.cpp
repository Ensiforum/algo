#include <vector>

// Структура данных "Персистентный стек"
// Персистентность означает, что структура данных так или иначе может самостоятельно вернуться в любое из своих состояний с момента создания

// Персистентный стек работает таким образом:
// При выполнении запросов Push и Pop создается запись описывающая новую версию стека
// Запись имеет такой формат: Предыдущая версия, Значение в голове стека
// При этом Push, Pop и Peek используют как аргумент версию стека
// Push - добавляет версию с заданным значением в вершиине и предыдущей версией
// Pop - откатывает стек к состоянию до добавления некоторого элемента и копирует версию этого состояния
// Peek - получает значение из головы стека в текущей версии

template <class T>
struct Record {
	int prevRecord;
	T value;

	Record(): prevRecord(-1) {}

	Record(int prevRecord, T value): 
		prevRecord(prevRecord), 
		value(value) {}

	Record Copy() {
		if (prevRecord == -1) {
			return Record();
		} else {
			return Record(prevRecord, value);
		}
	}
};

template <class T>
class PersistentStack {
private:
	std::vector<Record<T>> versions;

public:
	PersistentStack() {
		versions = std::vector<Record<T>>{ Record() };
	}

	void Push(int prevVersion, T value) {
		Record newRecord = Record(prevVersion, value);
		versions.push_back(newRecord);
	}

	T Peek(int version) {
		return versions[version].value;
	}

	T Pop(int version) {
		versions.push_back(versions[versions[version].prevVersion].Copy());
		return Peek(version);
	}
};

