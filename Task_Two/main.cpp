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
#include <cmath>

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

// Первая производная нашей преобразованной функции
double firstDerivativeNewOurFunction(double);

int main(void)
{
	// Установка кодировки 1251
	setlocale(LC_ALL, ".1251");

	SolutionEquation sol(MINIMUM, MAXIMUM, 1.E-9);

	cout << endl << endl << "Выполнение метода Ньютона: " << endl;

	sol.NewtonMethod(ourFunction, firstDerivativeOurFunction, secondDerivativeOurFunction);

	cout << endl << endl << "Выполнение метода Простых итераций: " << endl;

	sol.SimpleIterationMethod(newOurFunction, firstDerivativeNewOurFunction, MINIMUM);

	cout << endl << endl << "Выполнение метода Половинного деления: " << endl;

	sol.HalfDivisionMethod(ourFunction);

	cout << endl << endl << "Выполнение метода Хорд: " << endl;

	sol.DichotomyMethod(ourFunction);

	return 0;
}

// Наша исходная функция
double ourFunction(double argument)
{
	double resultOurFunction(0);

	resultOurFunction = 3 * pow(argument, 2) *
		cos(argument) - 1.5 * sin(argument) + 0.2;

	//resultOurFunction = pow(argument, 5) - 4 * pow(argument, 4) - 3 * pow(argument, 3) + 2 * argument + 1;

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

	//resultFirstDerivativeOurFunction = 5 * pow(argument, 4) - 16 * pow(argument, 3) - 9 * pow(argument, 2) + 2;

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

	//resultSecondDerivativeOurFunction = 20 * pow(argument, 3) - 48 * pow(argument, 2) - 18 * argument;

	return resultSecondDerivativeOurFunction;
}

// Преобразованная наша функция для метода простых итераций
double newOurFunction(double argument)
{
	double resultNewOurFunction(0);

	resultNewOurFunction =
		pow((1 / (2 * tan(argument)) - 1 / (15 * cos(argument))), (1 / 2.));

	//resultNewOurFunction = argument - ourFunction(argument) / firstDerivativeOurFunction(argument);

	return resultNewOurFunction;
}

double sec(double argument)
{
	double resultSec(0);

	resultSec = (1 / cos(argument));

	return resultSec;
}

// Первая производная нашей преобразованной функции
double firstDerivativeNewOurFunction(double argument)
{
	double resultFirstDerivativeNewOurFunction(0);

	resultFirstDerivativeNewOurFunction = 
		(0.288675 * (1.5 + sec(argument) * (0.2 + 1.5 * sin(argument)) * tan(argument))) / (sqrt(sec(argument) * (0.2 + 1.5 * sin(argument))));

	return resultFirstDerivativeNewOurFunction;
}