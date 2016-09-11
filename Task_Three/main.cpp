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

const double MINIMUM = -1;
const double MAXIMUM = 1;

/*
	Прототипы
*/
// Наша исходная функция
double ourFunction(double);

int main(void)
{
	// Установка кодировки 1251
	setlocale(LC_ALL, ".1251");
	
	cout << "Наша подынтегральная функция: exp(t)/t" << endl << endl;

	SolutionIntegrals sol(MINIMUM, MAXIMUM, 1.E-4, 8);

	cout << endl << endl << "Метод Симпсона: ";

	// Выполнение метода Симпсона (парабол)
	sol.SimpsonMethod(ourFunction);

	cout << endl << endl << "Метод Гаусса: ";

	// Выполнение метода Гаусса
	sol.GaussMethod(ourFunction);

	cout << endl;

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