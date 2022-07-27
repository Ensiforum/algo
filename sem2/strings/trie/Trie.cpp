#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

// Trie - бор (иногда префиксное дерево)
// Структура данных хранящая строки в виде дерева с узлами-символами
// Она позволяет добавлять строку и проверять наличие строки за O(N), где N - длина строки
// Также бор, если реализовывать его через массив, позволяет за O(N), где N - количество хранимых строк время выводить их упорядоченно 

// Название префиксное дерево пошло от принципа добавления узлов:
// Начиная от корня и первого символа строки есть ли в боре символ (есть ли у текущего узла ребенок соответствующий символу)
// Если символ отсутствует, то добавляется новый узел и к нему совершается переход, 
// иначе просто совершается переход к уже существующему узлу
//
// Узел, который был выбран последним отмечается как конец некоторой строки
// Это позволяет восстанавливать строки или проверять их наличие в боре, пользуясь им как автоматом
// К тому же, несколько измененный бор создается для алгоритма Ахо-Корасик и тоже используется как автомат

// Основные тонкости реализации заключаются в реализации узла
// - Во-первых, возможно давать терминальным узлам ссылаться на некоторые значения и использовать бор как ассоциативную структуру данных
// - Во-вторых, можно по-разному определять способ хранения существующих детей узла:
//		- Массив, что позволит хранить данные упорядоченно, но с увеличенными требованиями по памяти в среднем 
//		  (размер массива соответствует размеру алфавита)
//      - Хэш-таблица, что позволит занять гораздо меньше памяти, но это повлияет на возможность выводить данные упорядоченно
//      - Дерево поиска, что также позволит занять гораздо меньше памяти, но также повлияет и на скорость работы
//
// Так как необходимость выводить данные из бора упорядоченно довольно редка, то оптимальным вариантом выглядит использование хэш-таблиц

class Trie
{
private:
	class Node
	{
	private:
		bool isTerminal = false;
		std::unordered_map<char, Node*> next = std::unordered_map<char, Node*>();

	public:
		bool IsTerminal()
		{
			return isTerminal;
		}

		void SetAsTerminal()
		{
			isTerminal = true;
		}

		void AddNext(const char character, Node* nextNode)
		{
			next[character] = nextNode;
		}

		Node* GetNext(const char character)
		{
			if (next.count(character) == 0)
			{
				return nullptr;
			}

			return next[character];
		}
	};

	Node* root = new Node();

public:
	void AddWord(const std::string& word)
	{
		Node* currentNode = root;
		for (const char character : word)
		{
			if (currentNode->GetNext(character) == nullptr)
			{
				currentNode->AddNext(character, new Node());
			}

			currentNode = currentNode->GetNext(character);
		}

		currentNode->SetAsTerminal();
	}

	Trie() {}

	Trie(const std::string& word)
	{
		AddWord(word);
	}

	Trie(const std::vector<std::string>& words)
	{
		for (const std::string& word : words)
		{
			AddWord(word);
		}
	}

	bool IsStored(const std::string& word)
	{
		Node* currentNode = root;
		for (const char character : word)
		{
			currentNode = currentNode->GetNext(character);

			if (currentNode == nullptr)
			{
				return false;
			}
		}

		return currentNode->IsTerminal();
	}
}; 
