/*
	Работу выполнил:
		студент 2 курса по направлению Информационные системы и технологии
		Туров Виталий Александрович

	Задание №3. Вариант №23.
	Суть работы заключается в том, чтобы с помощью численных методов вычислить опрделённый интеграл.

	Я написал более или менее универсальный класс, который можно будет использовать для любых подынтегральных функций.
	Нужно только каждый раз переписывать реализацию ourFunction и подобных привидённых в main.cpp

	P.S: Реализацию класса менят не надо. 
*/
#include "SolutionIntegrals.h"
#include <iostream>
#include <cmath>

using namespace std;

const double MINIMUM = -10;
const double MAXIMUM = 10;

/*
	Прототипы
*/
// Наша исходная функция
double ourFunction(double);

// Первая производная нашей функции
double firstDerivativeOurFunction(double);

// Вторая производная нашей функции
double secondDerivativeOurFunction(double);

int main(void)
{
	// Установка кодировки 1251
	setlocale(LC_ALL, ".1251");
	
	SolutionIntegrals sol(MINIMUM, MAXIMUM, 1.E-4, 4);

	// Выполнение метода Симпсона (парабол)
	sol.SimpsonMethod(ourFunction);

	// Выполнение метода Гаусса
	sol.GaussMethod(ourFunction);

	return 0;
}

// Наша исходная функция
double ourFunction(double argument)
{
	double resultOurFunction(0);

	if (argument != 0)
		resultOurFunction = exp(argument) / argument;

	return resultOurFunction;
}

// Первая производная нашей функции
double firstDerivativeOurFunction (double argument)
{
	double resultFirstDerivativeOurFunction(0);



	return resultFirstDerivativeOurFunction;
}

// Вторая производная нашей функции
double secondDerivativeOurFunction (double argument)
{
	double resultSecondDerivativeOurFunction(0);



	return resultSecondDerivativeOurFunction;
}