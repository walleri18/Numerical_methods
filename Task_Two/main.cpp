/*
	Работу выполнил:
		студент 2 курса по направлению Информационные системы и технологии
		Туров Виталий Александрович

	Задание №2. Вариант №23.
	Суть работы заключается в том, чтобы с помощью численных методов определить корень данного нам уравнения.

	Я написал более или менее универсальный класс, который можно будет использовать со всеми уравнения.
	Нужно только каждый раз переписывать реализацию ourFunction и подобных привидённых в main.cpp

	P.S: Реализацию класса менят не надо. 
*/
#include "SolutionEquation.h"
#include <iostream>

using namespace std;

const double MINIMUM = -1.8;
const double MAXIMUM = 0;

/*
	Прототипы
*/
// Наша исходная функция
double ourFunction(double);

// Первая производная нашей функции
double firstDerivativeOurFunction(double);

// Вторая производная нашей функции
double secondDerivativeOurFunction(double);

// Преобразованная наша функция для метода простых итераций
double newOurFunction(double);

int main(void)
{
	// Установка кодировки 1251
	setlocale(LC_ALL, ".1251");

	SolutionEquation sol(MINIMUM, MAXIMUM, 1.E-9);

	cout << endl << "Выполнение метода Ньютона: " << endl;

	sol.NewtonMethod(ourFunction, firstDerivativeOurFunction, secondDerivativeOurFunction);

	cout << endl << "Выполнение метода Простых итераций: " << endl;

	sol.SimpleIterationMethod(ourFunction, newOurFunction, MINIMUM);

	cout << endl << "Выполнение метода Половинного деления: " << endl;

	sol.HalfDivisionMethod(ourFunction);

	cout << endl << "Выполнение метода Хорд: " << endl;

	sol.DichotomyMethod(ourFunction);

	return 0;
}

// Наша исходная функция
double ourFunction(double argument)
{
	double resultOurFunction(0);

	resultOurFunction = 3 * pow(argument, 2) *
		cos(argument) - 1.5 * sin(argument) + 0.2;

	return resultOurFunction;
}

// Первая производная нашей функции
double firstDerivativeOurFunction (double argument)
{
	double resultFirstDerivativeOurFunction(0);

	resultFirstDerivativeOurFunction = -1.5 *
		cos(argument) + 6 * argument *
		cos(argument) - 3 * pow(argument, 2)
		* sin(argument);

	return resultFirstDerivativeOurFunction;
}

// Вторая производная нашей функции
double secondDerivativeOurFunction (double argument)
{
	double resultSecondDerivativeOurFunction(0);

	resultSecondDerivativeOurFunction = 6 *
		cos(argument) - 3 * pow(argument, 2)
		* cos(argument) + 1.5 * sin(argument)
		- 12 * argument * sin(argument);

	return resultSecondDerivativeOurFunction;
}

// Преобразованная наша функция для метода простых итераций
double newOurFunction(double argument)
{
	double resultNewOurFunction(0);

	resultNewOurFunction =
		sqrt(1 / (2 * tan(argument)) - 1 / (15 * cos(argument)));

	return resultNewOurFunction;
}