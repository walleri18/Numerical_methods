#pragma once
#include <vector>

// Тип указателя на исходную функцию
typedef double(*Function)(double);

/*
	Этот класс реализует функционал для аппроксимации данных
*/
class SolutionApproximation
{
// Данные
private:

	/*
		Указатель на исходную функцию
	*/
	Function ourFunction;

	/*
		Концы отрезка аппроксимации
	*/
	// Начало отрезка (a)
	double beginSegment;

	// Конец отрезка (b)
	double endSegment;

	/*
		Порядок аппроксимирующей функции (n)
	*/
	int n;

	/*
		Количество узлов аппроксимирования (m)
	*/
	int m;

	/*
		Величина (c) значение колеблиться в пределах [2 ; 20]
	*/
	int c;

	/*
		Вектор значений X_i
	*/
	std::vector<double> vectorX_i;

	/*
		Вектор значений F_i
	*/
	std::vector<double> vectorF_i;

	/*
		Для системы решений линейных уравнений
	*/
	// Расширенная матрица
    long double **matrix;

	// Вектор коэффициентов апроксимирующего полинома
	std::vector<double> polynomialCoefficients;

	// Вектор невязок
	std::vector<double> residuals;

// Функционал
public:

	// Конструктор
	SolutionApproximation(Function ourFunction,
						  double beginSegment,
						  double endSegment,
						  int n, int m, int c);

	// Деструктор
	~SolutionApproximation();

	/*
		Интерфейс для работы с объектом из вне (API)
	*/
	// Сеттер ourFunction
	void setOurFunction(Function ourFunction);

	// Геттер ourFunction
	Function getOurFunction() const;

	// Сеттер Начала отрезка (a)
	void setBeginSegment(double beginSegment);

	// Геттер Начала отрезка (a)
	double getBeginSegment() const;

	// Сеттер Конца отрезка (b)
	void setEndSegment(double endSegment);

	// Геттер Конца отрезка (b)
	double getEndSegment() const;

	// Сеттер величины (n)
	void setValueN(int n);

	// Геттер величины (n)
	int getValueN() const;

	// Сеттер Величины (m)
	void setValueM(int m);

	// Геттер Величины (m)
	int getValueM() const;

	// Сеттер величины (c)
	void setValueC(int c);

	// Геттер величины (c)
	int getValueC() const;

	// Геттер Вектора значений X_i
	std::vector<double> getVectorX_i() const;

	// Геттер Вектора значений F_i
	std::vector<double> getVectorF_i() const;

	// Геттер Вектора полиноминальных коэффициентов
	std::vector<double> getPolynomialCoefficients() const;

	// Геттер Вектора невязок
	std::vector<double> getResiduals() const;

	// Обновление аппроксимирующей функции и её данных
    void update(const bool isGeneratePoint = true);

	// Результат аппроксимирующего полинома
	double ApproximationPolynom(double X);

private:

	// Очистка всех векторов от старых данных
    void clear(const bool isGeneratePoint);

	// Создание вектора значений X_i
	void createdVectorX_i();

	// Создание вектора значений F_i
	void createdVectorF_i();

	// Создание расширенной матрицы
	void createdMatrix();

    // Нахождение коэффициентов (решение системы линейных уравнений матодом Гаусса)
    void GaussSolve();

	// Нахождение невязок
	void searchResiduals();
};
