#pragma once
#include <vector>

/*
	Новый тип - тип указателя на функцию
*/
typedef double(*Function)(double);

/*
	Этот класс обеспечивает логику работы
	решений интегралов с помощью численных методов.

	В данном классе реализованно два типа численных метода:
	1) Метод Симпсона;
	2) Метод Гаусса.

	Публичные методы предоставляемые этим классом являются
	вызовом выполнения вычисления интеграла
	с помощью одного из численных методов.

	Класс был построен таким образом, чтобы его не нужно было переписывать.
	Для этого были использзованны указатели на функции, которые нужно будет передавать в main.

	Приятного использования моего класса =)
*/
class SolutionIntegrals
{
// Данные
private:

	/*
		Границы отрезка на котором численно вычисляется интеграл
	*/
	// Начало отрезка
	double beginSegment;

	// Конец отрезка
	double endSegment;

	/*
		Точность вычислений
	*/
	double precision;

	/*
		Результат вычислений (I)
	*/
	double resultSolutionIntegral;

	/*
		Необходимые параметры для метода Симпсона
	*/
	// Количество шагов (h)
	double countSteps;

	// Число разбиений (n)
	int numberSplits;

	/*
		Необходимые параметры для метода Гаусса
	*/
	// Коэффициенты квадратурной формулы
	std::vector<double> A;

	// Нули полинома Лежандра
	std::vector<double> t;

	/*
		Дополнительные параметры
	*/
	// Количество знаков после точки для приближений
	int coutNumber;

// Функциональность
public:

	// Загрузка необходимых данных
	SolutionIntegrals(double beginSegment, double endSegment,
					  double precision,
					  int coutNumber);

	// Освобождение ресурсов
	~SolutionIntegrals();

	// Метод Симпсона
	void SimpsonMethod(Function ourFunction);

	// Метод Гаусса
	void GaussMethod(Function ourFunction);

private:

	/*
		Общий функционал
	*/
	// Вывод результата
	void show();

	// Получение данных
	double getResultSolutionIntegral() const;

	/*
		Для метода Симпсона
	*/
	// Формула Симпсона для вычисления интеграла с определённым разбиением.
	double SimpsonFormula(Function ourFunction, int N);
};