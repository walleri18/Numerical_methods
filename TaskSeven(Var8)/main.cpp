#include <iostream>
#include "SolutionSystemNonlinearEquations.h"

/*
	���������
*/
// ������� F(x, y)
double FourFunction(double, double);

// ������� G(x, y)
double GourFunction(double, double);

// ������� ����������� dF/dx
double dFdxOurFunction(double ,double);

// ������� ����������� dF/dy
double dFdyOurFunction(double, double);

// ������� ����������� dG/dx
double dGdxOurFunction(double, double);

// ������� ����������� dG/dy
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
	����������
*/
// ������� F(x, y)
double FourFunction(double x, double y)
{
	return (std::sin(y) - x + 1);
}

// ������� G(x, y)
double GourFunction(double x, double y)
{
	return (std::tan(x * y) - x - 0.5);
}

// ������� ����������� dF/dx
double dFdxOurFunction(double x, double y)
{
	return -1;
}

// ������� ����������� dF/dy
double dFdyOurFunction(double x, double y)
{
	return (std::cos(y));
}

// ������� ����������� dG/dx
double dGdxOurFunction(double x, double y)
{
	return (-1 + y * (1 / std::cos(x * y)) * (1 / std::cos(x * y)));
}

// ������� ����������� dG/dy
double dGdyOurFunction(double x, double y)
{
	return (x * (1 / std::cos(x * y)) * (1 / std::cos(x * y)));
}