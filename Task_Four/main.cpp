/*
	Работу выполнил:
	студент 2 курса по направлению Информационные системы и технологии
	Туров Виталий Александрович

	Задание №4. Вариант №16.
	Суть работы заключается в том, чтобы с помощью метода Бесселя получить интерполяционную формулу.
	И построить таблицы и графики исходной нашей функции и интерполирующей функции.

	Всё математическое ядро будет написано и протестированно в VS, а реализацию GUI будем делать в Qt.

*/
#include <iostream>
#include <cmath>
#include "Interpolation.h"

using namespace std;

/*
	Константы
*/
const double MINIMUM = -1;
const double MAXIMUM = -0.1;

/*
	Прототипы
*/
// Наша исходная функция
double ourFunction(double);

int main(void)
{
	// Установка кодировки 1251
	setlocale(LC_ALL, ".1251");

	// Максималный порядок для формулы Бесселя в данной реализации
	int n = 19;

	// Наш объект для выполнения интерполяции
	Interpolation solutionInterpol(ourFunction, MINIMUM, MAXIMUM, n);

	solutionInterpol.update();

	auto argument = solutionInterpol.getArgument();
	auto resultOurFunction = solutionInterpol.getResultOurFunction();

	double resultBessel = solutionInterpol.interpolantBesselFunction(argument[n]);
	double resultOutFunction = ourFunction(argument[n]);

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