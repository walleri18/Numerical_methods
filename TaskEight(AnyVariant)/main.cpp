#include <iostream>
#include "MonteCarloMethod.h"

/*
	Прототипы
*/
// Наша функция F(x, y)
double FourFunction(double x, double y);

/*
	Компораторы
*/
bool ComOne(double x, double y);
bool ComTwo(double x, double y);

using namespace std;

int main(void)
{
	setlocale(LC_ALL, ".1251");

	// Векторов компараторов
	vector<Comporator> vectorComporator;

	vectorComporator.push_back(ComOne);
	vectorComporator.push_back(ComTwo);

	// Объект для расчёта объёма цилиндроида
	MonteCarloMethod solve(FourFunction, -2, 1, -3, 3, 100000, vectorComporator);

	// Вывод
	for (int i = 0; i < 15; i++)
		solve.showResultVolumeCylindroid();

	return 0;
}
/*
	Реализации
*/
// Наша функция F(x, y)
double FourFunction(double x, double y)
{
	return (2 * x + 3 * y);
}

/*
	Компораторы
*/
bool ComOne(double x, double y)
{
	return (x > -2 && x < 1);
}

bool ComTwo(double x, double y)
{
	return (y > (-1 + x) && y < (1 - x));
}
