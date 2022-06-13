#include <vector>
#include <algorithm>
#include <type_traits>

std::vector<bool> AsBinary(int value) {
	std::vector<bool> binaryRepresentation = std::vector<bool>();

	if (value == 0) {
		binaryRepresentation.push_back(0);
	} else {
		while (value != 0) {
			binaryRepresentation.push_back(value % 2);
			value /= 2;
		}
	}

	std::reverse(binaryRepresentation.begin(), binaryRepresentation.end());
	return binaryRepresentation;
}

// Класс матрицы в котором для выполнения операции возведения в степень используется бинарное возведение в степень
// Суть бинарного возведения в степень - использовать уже известные нам промежуточные значения (матрица в степени 2^N)
// Таким образом для возведения в степень N достаточно знать log N промежотучных значений
// Для получения промежуточных значений также достаточно выполнить log N возведений в квадрат (M(k) = M(k-1)^2)

// В любом случае для выполнения бинарного возведения в степень необходимо найти все промежуточные значения
// А также необходимо найти двоичное представление степени
// Если сделать это заранее, то вычисление искомого значения можно производить одновременно с вычислением промежуточного значения

// С помощью такого подхода можно быстро решать такие задачи:
// - нахождение количества путей длины N в графе
// - вычисление N-ого числа в последовательности Фибоначчи

// Подробнее о вычислении N-ого числа в последовательности Фибоначчи:
//
// Таким способом можно решать многие похожие задачи, главное привести их к такому виду:
// X(n) * M = X(n + 1)
// где X - вектор с некоторыми значениями (тут X(n) это [F(n), F(n + 1)], а X(n + 1) - [F(n + 1), F(n + 2)])
// M - матрица, умножив на которую X(n) получим X(n + 1)
// Тогда, если матрица будет, например, в степени 2 => X(n) * M^2 = X(n + 2)
//
// Чтобы найти такую матрицу необходимо заменить ее элементы неизвестными и решить систему уравнений:
// [F(n), F(n + 1)] * [[Q(1, 1), Q(1, 2)], [Q(2, 1), Q(2, 2)]] = [Q(1, 1) * F(n) + Q(2, 1) * F(n + 1), Q(1, 2) * F(n) + Q(2, 2) * F(n + 1)]

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

	// Создается единичная матрица
	Matrix(int height, int width) {
		this->height = height;
		this->width = width;

		values = std::vector<std::vector<T>>(height, std::vector<T> width);

		for (int row = 0; row < height; ++row) {
			int col = row;
			values[row][col] = 1;
		}
	}

	Matrix operator* (const Matrix& matrix) {
		return Multiply(matrix);
	}

	Matrix operator*= (const Matrix& matrix) {
		return this * matrix;
	}

	Matrix Exponentiate(int power) {
		// Получаем представление степени в двоичном формате
		std::vector<bool> bits = AsBinary(power);
		std::reverse(bits.begin(), bits.end());

		// Создаем единичную матрицу и матрицу для возведения в квадрат
		Matrix* accumulatedAnswer = new Matrix(height, width);
		Matrix* binaryPower = this;

		// Возводим в квадрат пока действует цикл
		// И параллельно умножаем матрицу если в двоичном представлении видим единицу
		for (bool bit : bits) {
			binaryPower *= binaryPower;

			if (bit) {
				accumulatedAnswer *= binaryPower;
			}
		}

		return accumulatedAnswer;
	}
};
