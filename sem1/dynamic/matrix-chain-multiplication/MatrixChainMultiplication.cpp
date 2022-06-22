#include <vector>
#include <algorithm>
#include <type_traits>

// Оптимальная последовательность умножения матриц

// При умножении матриц использование прямого порядка умножения может во много раз увеличить количество вычислений:
// {{(5x50) (100x5)} {10x100)} => 75000 
// {(5x50) {(100x5) (10x100)}} => 7500

// Фактически, задача в правильном расставлении скобок
// Нам нужно найти такую перестановку скобок, которая будет соответствовать оптимальному порядку умножения 

// Разумеется, полный перебор является крайне неэффективным, так что стоит воспользоваться динамическим программированием
// Подойдем к задаче так: если мы нашли оптимальную перестановку от первого элемента до последнего, то мы также нашли ее для промежуточных отрезков

// Это справедливо, так как:
// - умножение в любом случае даст один и тот же ответ
// - набор матриц останется таким же
// А значит оптимальность поддерживается везде

// Тогда будем постепенно наращивать длину последовательности
// С добавлением каждого элемента будем проверять, что будет если пробовать перемножать подпоследовательности "с конца"
// А минимальны промежуточные значения сохранять и использовать для быстрого получения значения
// При этом сохранять правую границу "подцепочки"

// По правой границе подцепочки можно будет восстановить решение:
// Начиная от первого элемента - находим правую границу, по ней делим на подцепочки и так далее, пока не доходим до самих матриц:
// ((A1 (A2 A3)) ((A4 A5) A6)) => (A1 (A2 A3)) * ((A4 A5) A6) => ... 

const int INF = 10000000;

template<typename T,
	typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type
> class Matrix {
private:
	int height;
	int width;
	std::vector<std::vector<T>> values;

	Matrix Multiply(Matrix firstMatrix, Matrix secondMatrix) {
		if (firstMatrix.width != secondMatrix.height) {
			throw std::invalid_argument("Wrong dimensions for matrix multiplication");
		}

		std::vector<std::vector<T>> result =
			std::vector<std::vector<T>>(firstMatrix.height, std::vector<T>(secondMatrix.width));

		for (int row = 0; row < firstMatrix.height; ++row) {
			for (int col = 0; col < secondMatrix.width; ++col) {
				for (int index = 0; index < firstMatrix.width; ++index) {
					result[row][col] += firstMatrix.values[row][index] * secondMatrix.values[index][col];
				}
			}
		}

		return Matrix(result);
	}

public:
	Matrix(const std::vector<std::vector<T>>& values) {
		height = values.size();
		width = values[0].size();

		this->values = values;
	}

	Matrix operator* (const Matrix& matrix) {
		return Multiply(matrix);
	}

	Matrix operator*= (const Matrix& matrix) {
		return this * matrix;
	}
};

template <class T>
Matrix<T> MultiplyInOrder(int firstIndex, int secondIndex,
	const std::vector<std::vector<int>>& order, const std::vector<Matrix<T>>& matrices)
{
	if (firstIndex == secondIndex) {
		return matrices[firstIndex];
	}

	return MultiplyInOrder(firstIndex, matrices[firstIndex][secondIndex], order, matrices) *
		MultiplyInOrder(matrices[firstIndex][secondIndex] + 1, secondIndex, order, matrices);
}

template <class T>
Matrix<T> FastMatrixChainMultiplication(const std::vector<Matrix<T>>& matrices)
{
	int matricesCount = matrices.size();

	std::vector<std::vector<int>> multiplicationsCounts(matricesCount, std::vector<int>(matricesCount, 0));
	std::vector<std::vector<int>> bestMultiplication(matricesCount, std::vector<int>(matricesCount, 0));

	for (int chainLength = 2; chainLength <= matricesCount; ++chainLength)
	{
		for (int firstInRange = 0; firstInRange <= matricesCount - chainLength; ++firstInRange)
		{
			int lastInRange = firstInRange + chainLength - 1;
			multiplicationsCounts[firstInRange][lastInRange] = INF;

			for (int intermediateMatrix = firstInRange; intermediateMatrix < lastInRange; ++intermediateMatrix)
			{
				int multiplicationsCount =
					multiplicationsCounts[firstInRange][intermediateMatrix] +
					multiplicationsCounts[intermediateMatrix + 1][lastInRange] +
					sizes[firstInRange - 1] * sizes[intermediateMatrix] * sizes[lastInRange];

				if (multiplicationsCount < multiplicationsCounts[firstInRange][lastInRange])
				{
					multiplicationsCounts[firstInRange][lastInRange] = multiplicationsCount;
					bestMultiplication[firstInRange][lastInRange] = intermediateMatrix;
				}
			}
		}
	}

	return MultiplyInOrder(0, matricesCount - 1, bestMultiplication, matrices);
}
