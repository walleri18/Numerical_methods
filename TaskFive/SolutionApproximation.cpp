#include "SolutionApproximation.h"
#include <time.h>

// Конструктор
SolutionApproximation::SolutionApproximation(Function ourFunction, double beginSegment, double endSegment, int orderApproximatFunction, int m, int c) :
	ourFunction(ourFunction), beginSegment(beginSegment),
	endSegment(endSegment),
	orderApproximatFunction(orderApproximatFunction), m(m), c(c)
{}

SolutionApproximation::SolutionApproximation(){}

// Сеттер ourFunction
void SolutionApproximation::setOurFunction(Function ourFunction)
{
	this->ourFunction = ourFunction;
}

// Геттер ourFunction
Function SolutionApproximation::getOurFunction() const
{
	return this->ourFunction;
}

// Сеттер Начала отрезка (a)
void SolutionApproximation::setBeginSegment(double beginSegment)
{
	this->beginSegment = beginSegment;
}

// Геттер Начала отрезка (a)
double SolutionApproximation::getBeginSegment() const
{
	return this->beginSegment;
}

// Сеттер Конца отрезка (b)
void SolutionApproximation::setEndSegment(double endSegment)
{
	this->endSegment = endSegment;
}

// Геттер Конца отрезка (b)
double SolutionApproximation::getEndSegment() const
{
	return this->endSegment;
}

// Сеттер Порядка аппроксимирующей функции (n)
void SolutionApproximation::setOrderApproximatFunction(int orderApproximatFunction)
{
	this->orderApproximatFunction = orderApproximatFunction;
}

// Геттер Порядка аппроксимирующей функции (n)
int SolutionApproximation::getOrderApproximatFunction() const
{
	return this->orderApproximatFunction;
}

// Сеттер Величины (m)
void SolutionApproximation::setValueM(int m)
{
	this->m = m;
}

// Геттер Величины (m)
int SolutionApproximation::getValueM() const
{
	return this->m;
}

// Сеттер величины (c)
void SolutionApproximation::setValueC(int c)
{
	this->c = c;
}

// Геттер величины (c)
int SolutionApproximation::getValueC() const
{
	return this->c;
}

// Геттер Вектора значений X_i
std::vector<double> SolutionApproximation::getVectorX_i() const
{
	return this->vectorX_i;
}

// Геттер Вектора значений F_i
std::vector<double> SolutionApproximation::getVectorF_i() const
{
	return this->vectorF_i;
}

// Сеттер матрицы
void SolutionApproximation::setMatrix(std::vector<std::vector<double>> matrix)
{
	this->matrix = matrix;
}

// Геттер матрицы
std::vector<std::vector<double>> SolutionApproximation::getMatrix() const
{
	return this->matrix;
}

// Обновление аппроксимирующей функции и её данных
void SolutionApproximation::update()
{
	// Очистка
	clear();

	// Генерирование x_i
	createdVectorX_i();

	// Генерирование F_i
	createdVectorF_i();
}

// Очистка всех векторов от старых данных
void SolutionApproximation::clear()
{
	this->vectorF_i.clear();

	this->vectorX_i.clear();

	matrix.clear();
}

// Создание вектора значений X_i
void SolutionApproximation::createdVectorX_i()
{
	for (int i = 0; i <= m; ++i)
	{
		vectorX_i.push_back(beginSegment
							+ i * (endSegment - beginSegment) / m);
	}
}

// Создание вектора значений F_i
void SolutionApproximation::createdVectorF_i()
{
	// Зерно рандома
    //srand(time(NULL));

	// Случайное число в интервале [0 ; 1]
	double z_i(0);
	
	// Какая та величина (k)
	int k(0);

//	for (int i = 0; i < vectorX_i.size(); ++i)
//	{
//		// Генерируем случайное число в пределах [0 ; 1]
//		z_i = rand() % 2;

//		// Смотри страницу 22 в методичке в самом внизу и всё поймёшь
//		if (z_i < 0.5)
//			k = -1;
//		else
//			k = 1;

//		// Аналогично смотри страницу 22 в методичке и всё поймёшь.
//		// Может быть
//		vectorF_i.push_back(ourFunction(vectorX_i[i]) * (1
//													   + k * z_i / c));
//	}
}

// Подсчёт детерминанта методом Гаусса
double SolutionApproximation::GaussDeterminant()
{
	// Детерминант
	double resultDeterminant(1);

	// Количество строк в матрице
	int countRow = matrix.size();

    // Копирование матрицы
    std::vector< std::vector<double> > copyMatrix = matrix;

	// Прямой ход метода Гаусса
	for (int i = 0; i < countRow; ++i)
	{
		for (int j = i + 1; j < countRow; ++j)
		{
			if (copyMatrix[i][i] == 0)
				throw new int;

			double b = copyMatrix[j][i] / copyMatrix[i][i];

			for (int k = i; k < countRow; ++k)
				copyMatrix[j][k] = copyMatrix[j][k]
				- copyMatrix[i][k] * b;
		}

		// Вычисление детерминанта
		resultDeterminant *= copyMatrix[i][i];
	}

	return resultDeterminant;
}

//
//// Нахождение коэффициентов (решение системы линейных уравнений методом Гаусса)
//std::vector<double> SolutionApproximation::GaussSolve(std::vector< std::vector<double> > matrix)
//{
//	// Вектор неизвестных
//	std::vector<double> X(matrix.size() - 1);
//
//	// Прямой ход
//	for (int i = 0; i < (matrix.size() - 1); ++i)
//	{
//		double a = matrix[i][i];
//
//		for (int j = i + 1; j < (matrix.size() - 1); ++j)
//		{
//			double b = matrix[j][i];
//
//			for (int k = i; k < matrix.size(); ++k)
//				matrix[j][k] = matrix[i][k] * b - matrix[j][k] * a;
//		}
//	}
//
//	// Обратный ход
//	for (int i = (matrix.size() - 2); i >= 0; --i)
//	{
//		double summ(0);
//
//		for (int j = (i + 1); j < (matrix.size() - 1); ++j)
//			summ += matrix[i][j] * X[j];
//
//		summ = matrix[i][(matrix.size() - 1)] - summ;
//
//		X[i] = summ / matrix[i][i];
//	}
//
//	return X;
//}

// Нахождение коэффициентов (решение системы линейных уравнений методом Крамера)
std::vector<double> SolutionApproximation::KramerSolve()
{
	// Неизвестные коэффициенты
	std::vector<double> X;

	// Вектор определителей
	std::vector<double> vectorDeterminant(matrix.size());

	// Временный вектор для хранения столбца матрицы
	std::vector<double> tmpColumn(matrix.size());

	for (int i = 0; i < (matrix.size() + 1); ++i)
	{
        vectorDeterminant[i] = GaussDeterminant();

		// Последовательная замена столбцов матрицы
		for (int j = 0; j < matrix.size(); j++)
		{
			if (i > 0)
				// Восстанавливаем значение стобца
				matrix[j][i - 1] = tmpColumn[j];

			// Сохраняем значение i - столбца матрицы в переменной tmpColumn
			tmpColumn[j] = matrix[j][i];

			// В i - столбец матрицы записываем столбец свободных членов
			matrix[j][i] = matrix[j][matrix.size()];
		}
	}

	// Заполнение результата
	for (int i = 1; i < (matrix.size() + 1); ++i)
		X.push_back(vectorDeterminant[i] / vectorDeterminant[0]);

	return X;
}
