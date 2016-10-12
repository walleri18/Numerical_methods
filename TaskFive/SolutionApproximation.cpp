#include "SolutionApproximation.h"
#include <time.h>
#include <stdlib.h>

// Конструктор
SolutionApproximation::SolutionApproximation(Function ourFunction, double beginSegment, double endSegment, int orderApproximatFunction, int m, int c) :
	ourFunction(ourFunction), beginSegment(beginSegment),
	endSegment(endSegment),
	n(n), m(m), c(c)
{}

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
void SolutionApproximation::setValueN(int n)
{
	this->n = n;
}

// Геттер Порядка аппроксимирующей функции (n)
int SolutionApproximation::getValueN() const
{
	return this->n;
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

// Геттер Вектора невязок
std::vector<double> SolutionApproximation::getResiduals() const
{
	return this->residuals;
}

// Обновление аппроксимирующей функции и её данных
void SolutionApproximation::update()
{
	// Очистка
	clear();

	// Генерирование X_i
	createdVectorX_i();

	// Генерирование F_i
	createdVectorF_i();

	// Генерирование расширенной матрицы
	createdMatrix();

	// Нахождение коэффициентом
	KramerSolve();

	// Нахождение невязок
	searchResiduals();
}

// Результат аппроксимирующего полинома
double SolutionApproximation::ApproximationPolynom(double X)
{
	double resultAppPolynom(0);

	for (int i = 0; i < polynomialCoefficients.size(); ++i)
	{
		resultAppPolynom += (polynomialCoefficients[i] * pow(X, i));
	}

	return resultAppPolynom;
}

// Очистка всех векторов от старых данных
void SolutionApproximation::clear()
{
	this->vectorF_i.clear();

	this->vectorX_i.clear();

	matrix.clear();

	polynomialCoefficients.clear();

	residuals.clear();
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
    srand(time(NULL));

	// Случайное число в интервале [0 ; 1]
	double z_i(0);
	
	// Какая та величина (k)
	int k(0);

	for (int i = 0; i < vectorX_i.size(); ++i)
	{
		// Генерируем случайное число в пределах [0 ; 1]
		z_i = rand() % 2;

		// Смотри страницу 22 в методичке в самом внизу и всё поймёшь
		if (z_i < 0.5)
			k = -1;
		else
			k = 1;

		// Аналогично смотри страницу 22 в методичке и всё поймёшь.
		// Может быть
		vectorF_i.push_back(ourFunction(vectorX_i[i]) * (1
													   + k * z_i / c));
	}
}

// Создание расширенной матрицы
void SolutionApproximation::createdMatrix()
{
	// Максимальное количество коэффициентов
	int maxCountK = n + 1;

	/*
		Нулевая строка
	*/
	// Создание нулевой строки
	std::vector<double> rowZero(maxCountK + 1);

	// Заполнение нулевой строки
	rowZero[0] = n;

	// Левая часть системы линейных уравнений
	for (int i = 1; i < maxCountK; ++i)
	{
		rowZero[i] = 0;

		for (int j = 1; j < vectorX_i.size(); ++j)
		{
			rowZero[i] += pow(vectorX_i[j], i);
		}
	}

	// Правая часть системы линейных уравнений
	rowZero[rowZero.size() - 1] = 0;

	for (int i = 1; i < vectorF_i.size(); ++i)
	{
		rowZero[rowZero.size() - 1] += vectorF_i[i];
	}

	/*
		Пост-нулевые строки
	*/
	// Вектор пост-нулевых строк
	std::vector< std::vector<double> > postRow(maxCountK - 1);

	// Заполнение пост-нулевых строк
	for (int k = 1; k < (maxCountK - 1); ++k)
	{
		// Создание строки
		std::vector<double> row(maxCountK + 1);

		// Левая часть системы линейных уравнений
		for (int j = 0; j < maxCountK; ++j)
		{
			row[j] = 0;

			for (int i = 1; i < vectorX_i.size(); ++i)
			{
				row[j] += pow(vectorX_i[i], j + k);
			}
		}

		// Правая часть системы линейных уравнений
		row[postRow.size() - 1] = 0;

		for (int i = 1; i < vectorF_i.size(); ++i)
		{
			row[postRow.size() - 1] 
				+= (vectorF_i[i] * pow(vectorX_i[i], k));
		}

		// Отправка строки
		postRow.push_back(row);
	}

	// Заполнение расширенной матрицы
	matrix.push_back(rowZero);

	for (int i = 0; i < postRow.size(); ++i)
	{
		matrix.push_back(postRow[i]);
	}
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

// Нахождение коэффициентов (решение системы линейных уравнений методом Крамера)
void SolutionApproximation::KramerSolve()
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

	polynomialCoefficients = X;
}

// Нахождение невязок
void SolutionApproximation::searchResiduals()
{
	/*
		Формула нахождения невязок
		
		e = b - A * k,

		где  e - вектор невязок,
		b - вектор свободных членов
		A - матрица коэффициентов системы линейных уравнений(без свободных членов)
		k - вектор найденных коэффициентов апроксимирующего полинома
	*/
	// Вектор невязок
	std::vector<double> eps(polynomialCoefficients.size());

	// Вектор результата умножения матрицы (A) на (k)
	std::vector<double> resultMulti(polynomialCoefficients.size());

	// Перемножение матрицы (A) на (k)
	for (int i = 0; i < matrix.size(); ++i)
	{
		resultMulti[i] = 0;

		for (int j = 0; j < polynomialCoefficients.size(); ++j)
		{
			resultMulti[i] += (matrix[i][j] * polynomialCoefficients[j]);
		}
	}

	// Вычисление вектора невязок
	for (int i = 0; i < eps.size(); ++i)
	{
		eps[i] = matrix[i][matrix.size() - 1] - resultMulti[i];
	}

	residuals = eps;
}