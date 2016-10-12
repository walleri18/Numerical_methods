/*
	Работу выполнил:
	Туров Виталий Александрович
	Группа: 05154
	Задание №5. Вариант №16.
*/
#include <iostream>
#include "SolutionApproximation.h"

using namespace std;

/*
	Прототипы
*/
// Наша функция
double ourFunction(double);

int main(void)
{
	setlocale(LC_ALL, ".1251");
	
	return 0;
}
/*
	Реализации
*/
// Наша функция
double ourFunction(double argument)
{
	double resultOurFunction(0);

	resultOurFunction = exp(-argument) * cos(argument);

	return resultOurFunction;
}