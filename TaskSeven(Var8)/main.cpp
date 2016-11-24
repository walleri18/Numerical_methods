#include <iostream>
#include "SolutionSystemNonlinearEquations.h"

/*
	Прототипы
*/
// Функция F(x, y)
double FourFunction(double, double);

// Функция G(x, y)
double GourFunction(double, double);

// Частная производная dF/dx
double dFdxOurFunction(double ,double);

// Частная производная dF/dy
double dFdyOurFunction(double, double);

// Частная производная dG/dx
double dGdxOurFunction(double, double);

// Частная производная dG/dy
double dGdyOurFunction(double, double);

using namespace std;

int main(void)
{
	setlocale(LC_ALL, ".1251");

	SolutionSystemNonlinearEquations sol(FourFunction, GourFunction, dFdxOurFunction, dFdyOurFunction, dGdxOurFunction, dGdyOurFunction, 0.3, 3.7, 1.e-6);

	sol.showResult();

	return 0;
}
/*
	Реализация
*/
// Функция F(x, y)
double FourFunction(double x, double y)
{
	return (std::sin(y) - x + 1);
}

// Функция G(x, y)
double GourFunction(double x, double y)
{
	return (std::tan(x * y) - x - 0.5);
}

// Частная производная dF/dx
double dFdxOurFunction(double x, double y)
{
	return -1;
}

// Частная производная dF/dy
double dFdyOurFunction(double x, double y)
{
	return (std::cos(y));
}

// Частная производная dG/dx
double dGdxOurFunction(double x, double y)
{
	return (-1 + y * (1 / std::cos(x * y)) * (1 / std::cos(x * y)));
}

// Частная производная dG/dy
double dGdyOurFunction(double x, double y)
{
	return (x * (1 / std::cos(x * y)) * (1 / std::cos(x * y)));
}