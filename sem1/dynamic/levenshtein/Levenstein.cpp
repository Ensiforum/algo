#include <vector>
#include <string>

// Расстояние Левенштейна - мера отличия двух строк
// Выражается как совокупная цена оптимального набора операций с помощью которых одну строку можна привести к другой
// В этой метрике присутствуют три операции - удаление, вставка и замена
// Существуют метрики с таким же подходом, но другим набором операций (например расстояние Дамерау-Левенштейна)
// Цены определяются по-разному, в зависимости от цели применения

// Расстояние также имеет предписание - тот самый оптимальный набор операций
// Но необходимость в предписании возникает значительно реже

// Для вычисления расстояния Левенштейна используется алгоритм Вагнера-Фишера
// Он стоит в простом вычислении значений по рекуррентной формуле:
//
// D(i, j):
// 0:  i = 0, j = 0
// i * costD: i > 0, j = 0
// j * costI: i = 0, j > 0
// min { D(i, j - 1) + costI, D(i - 1, j) + costD, D(i - 1, j - 1) + costR }: i > 0, j > 0
//
// costD - удаление, costI - вставка, costR - замена

// Очевидно:
// - что расстояние между двумя пустыми строками - 0 (1 условие)
// - что расстояние между строкой и пустой строкой - длина строки * количество удалений (2 условие)
// - что расстояние между пустой строкой и строкой - длина строки * количество вставок (3 условие)
//
// Менее очевидно расстояние между непустыми строками
// Так как подход рекуррентный, все начинается с сравнения подстрок, тем более, пустых подстрок
// Оптимальность не нарушается "неправильным порядком" операций, потому что в оптимальном порядке их можно переставлять местами
// Ведь операции не привязаны к конкретным символам
//
// Тогда:
// Чтобы единственной операцией для приведения одной подстроки к другой была вставка нужно сначала привести ее к подстроке без последнего символа
// Чтобы единственной операцией для приведения одной подстроки к другой было удаление нужно сначала привести ее к подстроке с "лишним символом"
// Чтобы единственной операцией для приведения одной подстроки к другой была замена нужно получить подстроку такой же длины 
// где все символы кроме последнего - такие же как в другой подстроке (последний тоже может совпадать, тогда замена не происходит)

// В данной реализации используется оптимизация по памяти:
// можно заметить, что в формуле для вычисления значения требуются значения лишь из последних двух строк
// поэтому только они и хранятся, что снижает требуемый объем памяти с O(N^2) до O(N)

//Стоимость операций
struct Costs {
    int deletionCost = 1;
    int insertionCost = 1;
    int replacementCost = 1;

    Costs(int deletionCost, int insertionCost, int replacementCost) {
        this->deletionCost = deletionCost;
        this->insertionCost = insertionCost;
        this->replacementCost = replacementCost;
    }

    Costs() {}
};

//Структура для восстановления предписания
struct Node {
    Node* prev;
    char operation;  //R - Replace, D - Delete, I - Insert, M - Match

    Node() {
        prev = nullptr;
        operation = ' ';
    }
};

// Расстояние + предписание
struct EditDistance {
    int distance;
    std::string prescription;

    EditDistance(int distance, std::vector<std::vector<Node*>> data) :
        distance(distance), prescription(RestorePrescription(data)) {}
};

//Восстановление предписания
std::string RestorePrescription(std::vector<std::vector<Node*>> prescription) {
    std::string answer = "";
    Node* current = prescription.back().back();
    
    while (current != nullptr) {
        answer = current->operation + answer;
        current = current->prev;
    }

    return answer;
}

//Расстояние Левенштейна
int LevensteinDistance(std::string first, std::string second, Costs costs) {
    int firstLength = first.length();
    int secondLength = second.length();
    
    std::vector<std::vector<int>> distances(2, std::vector<int>(secondLength + 2));
    for (int secondIndex = 1; secondIndex <= secondLength; ++secondIndex) {
        distances[0][secondIndex] = secondIndex * costs.insertionCost;
    }
    distances[1][0] = costs.deletionCost;

    for (int firstIndex = 1; firstIndex <= firstLength; ++firstIndex) {
        for (int secondIndex = 1; secondIndex <= secondLength; ++secondIndex) {
            bool canSubstitute = first[firstIndex - 1] != second[secondIndex - 1];
            distances[1][secondIndex] = std::min(distances[0][secondIndex] + costs.deletionCost,
                                        std::min(distances[1][secondIndex - 1] + costs.insertionCost,
                                        distances[0][secondIndex - 1] + canSubstitute * costs.replacementCost));
        }

        distances[0].swap(distances[1]);
        distances[1] = std::vector<int>(secondLength + 2);
        distances[1][0] = distances[0][0] + costs.deletionCost;
    }

    int distance = distances[0][secondLength];
    distances.clear();
    
    return distance;
}

//Расстояние Левенштейна с предписанием
EditDistance LevensteinDistanceWithPrescription(std::string first, std::string second, Costs costs) {
    int firstLength = first.length();
    int secondLength = second.length();

    std::vector<std::vector<int>> distances(2, std::vector<int>(secondLength + 2));
    std::vector<std::vector<Node*>> actions = 
        std::vector<std::vector<Node*>>(firstLength + 2, std::vector<Node*>(secondLength + 2));

    for (int secondIndex = 1; secondIndex <= secondLength; ++secondIndex) {
        distances[0][secondIndex] = secondIndex * costs.insertionCost;
        actions[0][secondIndex]->operation = 'I';
        actions[0][secondIndex]->prev = actions[0][secondIndex - 1];
    }
    distances[1][0] = costs.deletionCost;

    for (int firstIndex = 1; firstIndex <= firstLength; ++firstIndex)
    {
        actions[firstIndex][0]->operation = 'D';
        actions[firstIndex][0]->prev = actions[firstIndex - 1][0];
    }

    for (int firstIndex = 1; firstIndex <= firstLength; ++firstIndex) {
        for (int secondIndex = 1; secondIndex <= secondLength; ++secondIndex) {
            bool canSubstitute = first[firstIndex - 1] != second[secondIndex - 1];

            int deletionResult = distances[0][secondIndex] + costs.deletionCost;
            int insertionResult = distances[1][secondIndex - 1] + costs.insertionCost;
            int replacementResult = distances[0][secondIndex - 1] + canSubstitute * costs.replacementCost;
            
            if (deletionResult <= insertionResult && deletionResult <= replacementResult) {
                distances[1][secondIndex] = deletionResult;
                actions[firstIndex][secondIndex]->operation = 'D';
                actions[firstIndex][secondIndex]->prev = actions[firstIndex - 1][secondIndex];
            } else if (insertionResult <= deletionResult && insertionResult <= replacementResult) {
                distances[1][secondIndex] = insertionResult;
                actions[firstIndex][secondIndex]->operation = 'I';
                actions[firstIndex][secondIndex]->prev = actions[firstIndex][secondIndex - 1];
            } else {
                distances[1][secondIndex] = replacementResult;
                actions[firstIndex][secondIndex]->operation = canSubstitute ? 'R' : 'M';
                actions[firstIndex][secondIndex]->prev = actions[firstIndex - 1][secondIndex - 1];
            }
        }

        distances[0].swap(distances[1]);
        distances[1] = std::vector<int>(secondLength + 2);
        distances[1][0] = distances[0][0] + costs.deletionCost;
    }

    int distance = distances[0][secondLength];
    distances.clear();

    return EditDistance(distance, actions);
}
