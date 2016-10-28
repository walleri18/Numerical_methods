#include "SolutionApproximation.h"
#include <time.h>
#include <stdlib.h>
#include <cmath>
#include <QDebug>

// Конструктор
SolutionApproximation::SolutionApproximation(Function ourFunction, double beginSegment, double endSegment, int n, int m, int c) :
	ourFunction(ourFunction), beginSegment(beginSegment),
	endSegment(endSegment),
    n(n), m(m), c(c)
{
    matrix = NULL;
}

// Деструктор
SolutionApproximation::~SolutionApproximation()
{
	if (matrix != nullptr)
	{
		for (int i = 0; i < n + 1; ++i)
			if (matrix[i] != nullptr)
				delete[] matrix[i];

		delete[] matrix;
	}
}

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

// Геттер Вектора полиноминальных коэффициентов
std::vector<double> SolutionApproximation::getPolynomialCoefficients() const
{
	return this->polynomialCoefficients;
}

// Геттер Вектора невязок
std::vector<double> SolutionApproximation::getResiduals() const
{
	return this->residuals;
}

// Обновление аппроксимирующей функции и её данных
void SolutionApproximation::update(const bool isGeneratePoint)
{
	// Очистка
    clear(isGeneratePoint);

    if (isGeneratePoint)
    {

        // Генерирование X_i
        createdVectorX_i();

        // Генерирование F_i
        createdVectorF_i();

    }

	// Генерирование расширенной матрицы
	createdMatrix();

	// Нахождение коэффициентом
    GaussSolve();

	// Нахождение невязок
    searchResiduals();
}

// Результат аппроксимирующего полинома
double SolutionApproximation::ApproximationPolynom(double X)
{
	double resultAppPolynom(0);

    for (size_t i = 0, maxI(polynomialCoefficients.size()); i < maxI; ++i)
	{
        resultAppPolynom += (polynomialCoefficients[i] * std::pow(X, i));
	}

	return resultAppPolynom;
}

// Очистка всех векторов от старых данных
void SolutionApproximation::clear(const bool isGeneratePoint)
{
    if (isGeneratePoint)
    {

        this->vectorF_i.clear();

        this->vectorX_i.clear();

    }

//    if (matrix != NULL)
//	{
//		for (int i = 0; i < n + 1; ++i)
//			if (matrix[i] != nullptr)
//				delete[] matrix[i];

//		delete[] matrix;
//	}

	polynomialCoefficients.clear();

	residuals.clear();
}

// Создание вектора значений X_i
void SolutionApproximation::createdVectorX_i()
{
    for (int i = 0; i < (m + 1); ++i)
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

    for (size_t i = 0, maxI(vectorX_i.size()); i < maxI; ++i)
	{
        // Генерируем случайное число в пределах [0 ; 1]
        z_i = rand() / static_cast<double>(RAND_MAX);
		
		// Смотри страницу 22 в методичке в самом внизу и всё поймёшь
		if (z_i < 0.5)
			k = -1;
		else
			k = 1;

		// Аналогично смотри страницу 22 в методичке и всё поймёшь.
		// Может быть
        if (c != 0)
            vectorF_i.push_back(ourFunction(vectorX_i[i]) * (1 + k * z_i / c));
        else
            vectorF_i.push_back(ourFunction(vectorX_i[i]));
	}
}

// Создание расширенной матрицы
void SolutionApproximation::createdMatrix()
{
	// Создание матрицы
    matrix = new long double*[n + 1];

    for (int i = 0; i <= n; ++i)
	{
        matrix[i] = new long double[n + 2];
	}

    // Заполнение строк
    for (int k = 0; k <= n; ++k)
    {
        // Нулевая строка или (первая строка)
        if (k == 0)
        {
            /*
                Левая часть
            */

            // Нулевой элемент нулевой строки (первой строки)
            matrix[0][0] = m + 1;

            // Остальные элементы нулевой строки (первой строки)
            for (int i = 1; i <= n; ++i)
            {
                // Обнуляем элемент перед его заполнением
                matrix[0][i] = 0;

                for (int j = 0, maxJ(m + 1); j < maxJ; ++j)
                {
                    matrix[0][i] += std::pow(vectorX_i[j], i);
                }
            }

            /*
                Правая часть
            */
            // Элемент принадлежащий к столбцу свободных членов
            matrix[0][n + 1] = 0;

            for (int j = 0, maxJ(m + 1); j < maxJ; ++j)
            {
                matrix[0][n + 1] += vectorF_i[j];
            }

            continue;
        }

        /*
            Левая часть
        */

        for (int j = 0; j <= n; ++j)
        {
            matrix[k][j] = 0;

            for (size_t i = 0, maxI(m + 1); i < maxI; ++i)
            {
                matrix[k][j] += std::pow(vectorX_i[i], j + k);
            }
        }

        /*
            Правая часть
        */
        matrix[k][n + 1] = 0;

        for (int i = 0, maxI(m + 1); i < maxI; ++i)
        {
            matrix[k][n + 1]
                += (vectorF_i[i] * std::pow(vectorX_i[i], k));
        }
    }
}

// Нахождение коэффициентов (решение системы линейных уравнений матодом Гаусса)
void SolutionApproximation::GaussSolve()
{
	// Копирование исходного массива
    long double **matrix = new long double*[n+1];

	for (int i = 0; i < n + 1; ++i)
	{
        matrix[i] = new long double[n + 2];

		for (int j = 0; j < n + 2; ++j)
		{
			matrix[i][j] = this->matrix[i][j];
		}
	}

    // Метод Гаусса с выбором максимального элемента
    long double *x = new long double[n+1];

    for (int k = 0; k < n; ++k)
    {
        long double matrix_max = std::fabs(matrix[k][k]);

        int p=k;

        for (int i = k + 1; i < n + 1; ++i)
        {
            if (matrix_max < std::fabs(matrix[i][k]))
            {
                matrix_max=std::fabs(matrix[i][k]);

                p=i;
            }
        }

        for (int j = k; j < n + 2; ++j)
        {
            long double c = matrix[k][j];
            matrix[k][j] = matrix[p][j];
            matrix[p][j] = c;
        }

        for (int i = k + 1; i < n + 1; ++i)
        {
            for (int j = k + 1; j < n + 2; ++j)
            {
                matrix[i][j] = matrix[i][j] - matrix[i][k] * matrix[k][j] / matrix[k][k];
            }
        }
    }

    x[n] = matrix[n][n+1] / matrix[n][n];

    for (int i = n - 1;i >= 0; --i)
    {
        long double s = matrix[i][n+1];

        for (int j = n; j >= i + 1; --j)
        {
            s = s - matrix[i][j] * x[j];
        }

        x[i] = s / matrix[i][i];
    }

    // Обычный метод Гаусса
//	// Временные переменные
//	int i, j, k;

//	// Выделения места для неизвестных
//    long double *x = new long double[n + 1];

//	// Прямой ход
//	for (i = 0; i < n + 1; ++i)
//	{
//        long double a = matrix[i][i];

//		for (j = i + 1; j < n + 1; j++)
//		{
//            long double b = matrix[j][i];

//			for (k = i; k < n + 2; ++k)
//			{
//				matrix[j][k] = matrix[i][k] * b - matrix[j][k] * a;
//			}
//		}
//	}

//	// Обратный ход
//	for (i = n; i >= 0; --i)
//	{
//        long double summ(0.);

//		for (j = i + 1; j < n + 1; ++j)
//		{
//			summ += matrix[i][j] * x[j];
//		}

//		summ = matrix[i][n + 1] - summ;

//		x[i] = summ / matrix[i][i];
//	}

    // Копирование коэффициентов
    for (int i = 0; i < n + 1; ++i)
    {
        polynomialCoefficients.push_back(x[i]);
    }

	if (matrix != nullptr)
	{
		for (int i = 0; i < n + 1; ++i)
			if (matrix[i] != nullptr)
				delete[] matrix[i];

		delete[] matrix;
	}
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
	residuals.assign(polynomialCoefficients.size(), 0);

    // Вектор свободных членов
    std::vector<double> b(polynomialCoefficients.size());

    for (int i = 0, maxI(b.size()); i < maxI; ++i)
    {
        b[i] = matrix[i][n + 1];
    }

	// Вектор результата умножения матрицы (A) на (k)
    std::vector<double> resultMulti;

	// Перемножение матрицы (A) на (k)
    for (size_t i = 0, maxI(n+1); i < maxI; ++i)
	{
        resultMulti.push_back(0);

        for (size_t j = 0, maxJ(polynomialCoefficients.size()); j < maxJ; ++j)
		{
			resultMulti[i] += (matrix[i][j] * polynomialCoefficients[j]);
		}
	}

	// Вычисление вектора невязок
    for (size_t i = 0, maxI(residuals.size()); i < maxI; ++i)
	{
		residuals[i] = b[i] - resultMulti[i];
	}
}
