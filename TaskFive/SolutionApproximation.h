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
	int orderApproximatFunction;

	/*
		Величина (m)
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
		Матрица для использования в системе линейных уравнений
	*/
	std::vector< std::vector<double> > matrix;

// Функционал
public:

	// Конструктор
	SolutionApproximation(Function ourFunction,
						  double beginSegment,
						  double endSegment,
						  int orderApproximatFunction,
						  int m, int c);

	// Тестирующий конструктор
	SolutionApproximation();

	/*
		Интерфес для работы с объектом из вне (API)
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

	// Сеттер Порядка аппроксимирующей функции (n)
	void setOrderApproximatFunction(int orderApproximatFunction);

	// Геттер Порядка аппроксимирующей функции (n)
	int getOrderApproximatFunction() const;

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

	// Сеттер матрицы
	void setMatrix(std::vector< std::vector<double> > matrix);

	// Геттер матрицы
	std::vector< std::vector<double> > getMatrix() const;

	// Обновление аппроксимирующей функции и её данных
	void update();

private:

	// Очистка всех векторов от старых данных
	void clear();

	// Создание вектора значений X_i
	void createdVectorX_i();

	// Создание вектора значений F_i
	void createdVectorF_i();

	// Подсчёт детерминанта методом Гаусса
	double GaussDeterminant();

	//// Нахождение коэффициентов (решение системы линейных уравнений методом Гаусса)
	//std::vector<double> GaussSolve(std::vector< std::vector<double> > matrix);

	// Нахождение коэффициентов (решение системы линейных уравнений методом Крамера)
	std::vector<double> KramerSolve();
};