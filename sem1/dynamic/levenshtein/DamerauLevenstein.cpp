#include <vector>
#include <string>

// Расстояние Дамерау-Левенштейна

// Является "дополненной" версией расстояния Левенштейна 
// https://github.com/2vitalik/algo/blob/main/sem1/dynamic/levenshtein/Levenstein.cpp

// Автор (Дамерау) вводит также операцию транспозиции 
// Ведь по исследованиям на которые он опирался около 80% ошибок при вводе - символы в неправильном порядке
// Что по большей части справедливо
// Поэтому расстояние Дамерау-Левенштейна и его упрощенная версия на данный момент одни из самых широкоиспользуемых метрик для нечеткого поиска

// Вычисляется расстояние Дамерау-Левенштейна по принципу схожему с расстоянием Левенштейна
// Доказательство правильности формулы ровно такое же - порядок значения не имеет

// Упрощенное расстояние Дамерау-Левенштейна:
// Упрощенное расстояние Дамерау-Левенштейна при поиске возможных транспозиций смотрит всего лишь на один слой назад в глубину
// Это позволяет применять такую же оптимизацию по памяти как и в случае с расстоянием Левенштейна
// Однако это нарушает изначальное определение расстояния Дамерау-Левенштейна
// Что можно оправдать тем что в большинстве случаев перепутанные местами буквы будут находиться недалеко друг от друга
// Тем более, что расстояние Дамерау-Левенштейна введено как более практичная замена расстоянию Левенштейна

// Правильное расстояние Дамерау-Левенштейна:
// Нахождение корректного расстояния Дамерау-Левенштейна требует хранения всех данных полученных в ходе вычисления рекуррентной последовательности
// Для того чтобы проверять транспозицию на произвольную глубину будем хранить информацию о последнем вхождении символа в подстроку
// Тогда N - 1 первых символов уже совпадают (мы нашли расстояние до них, а если их меньше, то просто вставим их), 
// По последнему символу мы и нашли данный префикс, а все лишние символы удаляются

// Оценка по времени: O(N^2) для обоих алгоритмов
// Оценка по памяти: O(N) для упрощенного и O(N^2) для корректного

const int INF = -1;
const int OFFSET = 128;

//Стоимость операций
struct Costs {
    int deletionCost = 1;
    int insertionCost = 1;
    int replacementCost = 1;
    int transpositionCost = 1;

    Costs(int deletionCost, int insertionCost, 
          int replacementCost, int transpositionCost) {
        this->deletionCost = deletionCost;
        this->insertionCost = insertionCost;
        this->replacementCost = replacementCost;
        this->transpositionCost = transpositionCost;
    }

    Costs() {}
};

//Структура для восстановления предписания
struct Node {
    Node* prev;
    char operation;  //R - Replace, D - Delete, I - Insert, T - Transpose, M - Match

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

//Упрощенное расстояние Дамерау-Левенштейна
int DamerauLevensteinSimplified(const std::string& first, const std::string& second, const Costs& costs) {
    int firstLength = first.length();
    int secondLength = second.length();
    std::vector<std::vector<int>> distances(3, std::vector<int>(secondLength + 2));

    for (int secondIndex = 1; secondIndex <= secondLength + 1; ++secondIndex) {
        distances[0][secondIndex] = secondIndex * costs.insertionCost;
    }
    distances[1][0] = costs.deletionCost;
    distances[2][0] = 2 * costs.deletionCost;

    for (int secondIndex = 1; secondIndex <= secondLength; ++secondIndex) {
        bool canSubstitute = first[0] != second[secondIndex - 1];
        
        distances[1][secondIndex] = std::min(distances[0][secondIndex] + costs.deletionCost,
            std::min(distances[1][secondIndex - 1] + costs.insertionCost,
                distances[0][secondIndex - 1] + canSubstitute * costs.replacementCost));
    }

    for (int firstIndex = 2; firstIndex <= firstLength; ++firstIndex) {
        for (int secondIndex = 1; secondIndex <= secondLength; ++secondIndex) {
            bool canSubstitute = first[firstIndex - 1] != second[secondIndex - 1];
            
            distances[2][secondIndex] = std::min(distances[1][secondIndex] + costs.deletionCost,
                std::min(distances[2][secondIndex - 1] + costs.insertionCost,
                    distances[1][secondIndex - 1] + canSubstitute * costs.replacementCost));
            
            if (firstIndex - 1 && secondIndex - 1 && first[firstIndex - 1] == second[secondIndex - 2] &&
                first[firstIndex - 2] == second[secondIndex - 1]) {
                distances[2][secondIndex] = std::min(distances[2][secondIndex],
                    distances[0][secondIndex] + costs.transpositionCost);
            }
        }

        distances[0].swap(distances[1]);
        distances[1].swap(distances[2]);
        distances[2] = std::vector<int>(secondLength + 2);
        distances[2][0] = distances[1][0] + costs.deletionCost;
    }

    int distance = distances[1][secondLength];
    distances.clear();
    return distance;
}

//Упрощенное расстояние Дамерау-Левенштейна с предписанием
EditDistance DamerauLevensteinSimplifiedWithPrescription(const std::string& first, const std::string& second, const Costs& costs) {
    int firstLength = first.length();
    int secondLength = second.length();

    std::vector<std::vector<Node*>> prescription(firstLength + 2, std::vector<Node*>(secondLength + 2, new Node()));
    std::vector<std::vector<int>> distances(3, std::vector<int>(secondLength + 2));

    for (int secondIndex = 1; secondIndex <= secondLength + 1; ++secondIndex) {
        distances[0][secondIndex] = secondIndex * costs.insertionCost;
        prescription[0][secondIndex]->operation = 'I';
        prescription[0][secondIndex]->prev = prescription[0][secondIndex - 1];
    }
    distances[1][0] = costs.deletionCost;
    prescription[1][0]->operation = 'D';
    prescription[1][0]->prev = prescription[0][0];

    distances[2][0] = 2 * costs.deletionCost;
    prescription[2][0]->operation = 'D';
    prescription[2][0]->prev = prescription[1][0];

    for (int secondIndex = 1; secondIndex <= secondLength; ++secondIndex) {
        bool canSubstitute = first[0] != second[secondIndex - 1];

        int deletion = distances[0][secondIndex] + costs.deletionCost;
        int insertion = distances[1][secondIndex - 1] + costs.insertionCost;
        int replacement = distances[0][secondIndex - 1] + canSubstitute * costs.replacementCost;

        if (deletion <= insertion && deletion <= replacement) {
            distances[1][secondIndex] = deletion;
            prescription[1][secondIndex]->operation = 'D';
            prescription[1][secondIndex]->prev = prescription[0][secondIndex];
        } else if (insertion <= deletion && insertion << replacement) {
            distances[1][secondIndex] = insertion;
            prescription[1][secondIndex]->operation = 'I';
            prescription[1][secondIndex]->prev = prescription[1][secondIndex - 1];
        } else {
            distances[1][secondIndex] = replacement;
            prescription[1][secondIndex]->operation = 'R';
            prescription[1][secondIndex]->prev = prescription[0][secondIndex - 1];
        }
    }

    for (int firstIndex = 2; firstIndex <= firstLength; ++firstIndex) {
        for (int secondIndex = 1; secondIndex <= secondLength; ++secondIndex) {
            bool canSubstitute = first[firstIndex - 1] != second[secondIndex - 1];

            int deletion = distances[1][secondIndex] + costs.deletionCost;
            int insertion = distances[2][secondIndex - 1] + costs.insertionCost;
            int replacement = distances[1][secondIndex - 1] + canSubstitute * costs.replacementCost;

            if (deletion <= insertion && deletion <= replacement) {
                distances[2][secondIndex] = deletion;
                prescription[firstIndex][secondIndex]->operation = 'D';
                prescription[firstIndex][secondIndex]->prev = prescription[firstIndex - 1][secondIndex];
            }
            else if (insertion <= deletion && insertion << replacement) {
                distances[2][secondIndex] = insertion;
                prescription[firstIndex][secondIndex]->operation = 'I';
                prescription[firstIndex][secondIndex]->prev = prescription[firstIndex][secondIndex - 1];
            }
            else {
                distances[2][secondIndex] = replacement;
                prescription[firstIndex][secondIndex]->operation = 'R';
                prescription[firstIndex][secondIndex]->prev = prescription[firstIndex - 1][secondIndex - 1];
            }

            if (firstIndex - 1 && secondIndex - 1 && first[firstIndex - 1] == second[secondIndex - 2] &&
                first[firstIndex - 2] == second[secondIndex - 1]) {

                int transposition = distances[0][secondIndex] + costs.transpositionCost;

                if (transposition < distances[2][secondIndex]) {
                    distances[2][secondIndex] = transposition;
                    prescription[firstIndex][secondIndex]->operation = 'T';
                    prescription[firstIndex][secondIndex]->prev = prescription[firstIndex - 2][secondIndex];
                }
            }
        }

        distances[0].swap(distances[1]);
        distances[1].swap(distances[2]);
        distances[2] = std::vector<int>(secondLength + 2);
        distances[2][0] = distances[1][0] + costs.deletionCost;
    }

    int distance = distances[1][secondLength];
    distances.clear();
    return EditDistance(distance, prescription);
}

//Корректный алгоритм нахождения расстояния Дамерау-Левенштейна
int DamerauLevenstein(const std::string& first, const std::string& second, const Costs& costs) {
    int firstLength = first.length();
    int secondLength = second.length();

    if (firstLength == 0 || secondLength == 0) {
        return std::max(firstLength, secondLength);
    }

    std::vector<std::vector<int>> distances(firstLength + 2, std::vector<int>(secondLength + 2));

    for (int firstIndex = 0; firstIndex < firstLength + 1; ++firstIndex) {
        distances[firstIndex + 1][1] = firstIndex * costs.deletionCost;
        distances[firstIndex + 1][0] = INF;
    }

    for (int secondIndex = 0; secondIndex < secondLength + 1; ++secondIndex) {
        distances[1][secondIndex + 1] = secondIndex * costs.insertionCost;
        distances[0][secondIndex + 1] = INF;
    }

    std::string alphabet = first + second;
    std::vector<int> lastPosition(256);

    for (int firstIndex = 1; firstIndex <= firstLength; ++firstIndex) {
        int last = 0;
        
        for (int secondIndex = 1; secondIndex <= secondLength; ++secondIndex) {
            
            int lastEncounterInFirst = lastPosition[second[secondIndex] + 128];
            int lastEncounterInSecond = last;
            
            if (first[firstIndex] == second[secondIndex]) {
                distances[firstIndex + 1][secondIndex + 1] = distances[firstIndex][secondIndex];
                last = secondIndex;
            } else {
                distances[firstIndex + 1][secondIndex + 1] =
                    std::min(distances[firstIndex][secondIndex + 1] + costs.deletionCost,
                        std::min(distances[firstIndex + 1][secondIndex] + costs.insertionCost,
                            distances[firstIndex][secondIndex] + costs.replacementCost));
            }
            distances[firstIndex + 1][secondIndex + 1] =
                std::min(distances[firstIndex + 1][secondIndex + 1],
                    distances[lastEncounterInFirst][lastEncounterInSecond] + costs.transpositionCost +
                    (firstIndex - lastEncounterInFirst - 1) * costs.deletionCost +
                    (secondIndex - lastEncounterInSecond - 1) * costs.insertionCost);
            
            lastPosition[first[firstIndex] + OFFSET] = firstIndex;
        }
    }

    int distance = distances[firstLength][secondLength];
    distances.clear();
    return distance;
}

//Расстояние Дамерау-Левенштейна с предписанием
EditDistance DamerauLevensteinWithPrescription(const std::string& first, const std::string& second, const Costs& costs) {
    int firstLength = first.length();
    int secondLength = second.length();

    std::vector<std::vector<Node*>> prescription(firstLength + 2, std::vector<Node*>(secondLength + 2, new Node()));
    std::vector<std::vector<int>> distances(firstLength + 2, std::vector<int>(secondLength + 2));

    if (firstLength == 0 || secondLength == 0) {
        distances.clear();
        return EditDistance(std::max(firstLength, secondLength), prescription);
    }

    for (int firstIndex = 0; firstIndex < firstLength + 1; ++firstIndex) {
        distances[firstIndex + 1][1] = firstIndex * costs.deletionCost;
        prescription[firstIndex + 1][1]->operation = 'D';
        prescription[firstIndex + 1][0]->operation = 'D';
        prescription[firstIndex + 1][1]->prev = prescription[firstIndex][0];
        distances[firstIndex + 1][0] = INF;
    }

    for (int secondIndex = 0; secondIndex < secondLength + 1; ++secondIndex) {
        distances[1][secondIndex + 1] = secondIndex * costs.insertionCost;
        prescription[1][secondIndex + 1]->operation = 'I';
        prescription[0][secondIndex + 1]->operation = 'I';
        prescription[1][secondIndex + 1]->prev = prescription[0][secondIndex];
        distances[0][secondIndex + 1] = INF;
    }

    std::string alphabet = first + second;
    std::vector<int> lastPosition(256);

    for (int firstIndex = 1; firstIndex <= firstLength; ++firstIndex) {
        int last = 0;
        
        for (int secondIndex = 1; secondIndex <= secondLength; ++secondIndex) {
            int lastEncounterInFirst = lastPosition[second[secondIndex - 1] + 128];
            int lastEncounterInSecond = last;
            
            if (first[firstIndex - 1] == second[secondIndex - 1]) {
                distances[firstIndex + 1][secondIndex + 1] = distances[firstIndex][secondIndex];
                prescription[firstIndex + 1][secondIndex + 1]->operation = 'M';
                prescription[firstIndex + 1][secondIndex + 1]->prev = prescription[firstIndex][secondIndex];
                last = secondIndex;
            } else {
                int deletion = distances[firstIndex][secondIndex + 1] + costs.deletionCost;
                int insertion = distances[firstIndex + 1][secondIndex] + costs.insertionCost;
                int replacement = distances[firstIndex][secondIndex] + costs.replacementCost;
                
                if (deletion <= insertion && deletion <= replacement) {
                    distances[firstIndex + 1][secondIndex + 1] = deletion;
                    prescription[firstIndex + 1][secondIndex + 1]->operation = 'D';
                    prescription[firstIndex + 1][secondIndex + 1]->prev = prescription[firstIndex][secondIndex + 1];
                } else if (insertion <= deletion && insertion <= replacement) {
                    distances[firstIndex + 1][secondIndex + 1] = insertion;
                    prescription[firstIndex + 1][secondIndex + 1]->operation = 'I';
                    prescription[firstIndex + 1][secondIndex + 1]->prev = prescription[firstIndex + 1][secondIndex];
                } else {
                    distances[firstIndex + 1][secondIndex + 1] = replacement;
                    prescription[firstIndex + 1][secondIndex + 1]->operation = 'R';
                    prescription[firstIndex + 1][secondIndex + 1]->prev = prescription[firstIndex][secondIndex];
                }
            }
            int transposition = distances[lastEncounterInFirst][lastEncounterInSecond] + costs.transpositionCost +
                (firstIndex - lastEncounterInFirst - 1) * costs.deletionCost +
                (secondIndex - lastEncounterInSecond - 1) * costs.insertionCost;
            
            if (distances[firstIndex + 1][secondIndex + 1] > transposition) {
                distances[firstIndex + 1][secondIndex + 1] = transposition;
                prescription[firstIndex + 1][secondIndex + 1]->operation = 'T';
                prescription[firstIndex + 1][secondIndex + 1]->prev = prescription[lastEncounterInFirst][lastEncounterInSecond];
            }

            lastPosition[first[firstIndex - 1] + OFFSET] = firstIndex;
        }
    }

    int distance = distances[firstLength][secondLength];
    distances.clear();
    return EditDistance(distance, prescription);
}
