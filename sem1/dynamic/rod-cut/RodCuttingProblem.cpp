#include <vector>
#include <algorithm>

// Задача об оптимальном разрезании стержня

// Класическая задача динамического программирования
// Представим, что есть стержень длины N, а также список цен на стержни различной длины
// Положим, что разрезание нам ничего не стоит
// Значит мы ищем самое дорогое множество стержней совокупной длины N

// Представим задачу так - мы разрезаем стержень в некотором месте, и одну из его частей больше не трогаем
// Получается, что нам нужно решать подзадачу - оптимальное разрезание второй части
// Мы поочередно разрезаем стержень на каждом делении и проверяем какое разрезание вышло максимальным

// Несложно заметить, что в таком случаи подзадачи начинают повторяться
// Добавим также список лучших цен - то есть с учетом оптимального разрезания
// Тогда если мы уже нашли цену для стержня длины K, то просто берем ее из списка

// Для восстановления решения достаточно записать в каком месте следует разрезать стержень длины K
// Тогда с помощью цикла будем "срезать" кусок и добавлять его в список и смотреть какой кусок нужно отрезать от получившегося стержня

// Алгоритм требует O(N^2) операций и использует O(N) памяти

const int NO_VAL = -1;

int BestCut(int rodLength, const std::vector<int>& priceList, std::vector<int>& cuts, std::vector<int>& splits) {
	if (cuts[rodLength] == NO_VAL) {
		int bestCut = 0;
		for (int cut = 0; cut < rodLength; ++cut) {
			int priceAfterSplit = priceList[rodLength - cut] + BestCut(cut, priceList, cuts, splits);
			
			if (priceAfterSplit > bestCut) {
				bestCut = priceAfterSplit;
				splits[rodLength] = cut;
			}
		}

		cuts[rodLength] = bestCut;
	}

	return cuts[rodLength];
}

std::vector<int> BestCutDescription(int rodLength, std::vector<int>& splits) {
	std::vector<int> cutDescription = std::vector<int>();

	while (rodLength > 0) {
		int cutPart = splits[rodLength];
		if (cutPart == 0) {
			cutPart = rodLength;
		}

		cutDescription.push_back(cutPart);
		rodLength -= cutPart;
	}

	return cutDescription;
}
