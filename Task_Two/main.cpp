/*
	������ ��������:
		������� 2 ����� �� ����������� �������������� ������� � ����������
		����� ������� �������������

	������� �2. ������� �23.
	���� ������ ����������� � ���, ����� � ������� ��������� ������� ���������� ������ ������� ��� ���������.

	� ������� ����� ��� ����� ������������� �����, ������� ����� ����� ������������ �� ����� ���������.
	����� ������ ������ ��� ������������ ���������� ourFunction � �������� ���������� � main.cpp

	P.S: ���������� ������ ����� �� ����. 
*/
#include "SolutionEquation.h"
#include <iostream>

using namespace std;

const double MINIMUM = -1.8;
const double MAXIMUM = 0;

/*
	���������
*/
// ���� �������� �������
double ourFunction(double);

// ������ ����������� ����� �������
double firstDerivativeOurFunction(double);

// ������ ����������� ����� �������
double secondDerivativeOurFunction(double);

// ��������������� ���� ������� ��� ������ ������� ��������
double newOurFunction(double);

int main(void)
{
	// ��������� ��������� 1251
	setlocale(LC_ALL, ".1251");

	SolutionEquation sol(MINIMUM, MAXIMUM, 1.E-9);

	cout << endl << "���������� ������ �������: " << endl;

	sol.NewtonMethod(ourFunction, firstDerivativeOurFunction, secondDerivativeOurFunction);

	cout << endl << "���������� ������ ������� ��������: " << endl;

	sol.SimpleIterationMethod(ourFunction, newOurFunction, MINIMUM);

	cout << endl << "���������� ������ ����������� �������: " << endl;

	sol.HalfDivisionMethod(ourFunction);

	cout << endl << "���������� ������ ����: " << endl;

	sol.DichotomyMethod(ourFunction);

	return 0;
}

// ���� �������� �������
double ourFunction(double argument)
{
	double resultOurFunction(0);

	resultOurFunction = 3 * pow(argument, 2) *
		cos(argument) - 1.5 * sin(argument) + 0.2;

	return resultOurFunction;
}

// ������ ����������� ����� �������
double firstDerivativeOurFunction (double argument)
{
	double resultFirstDerivativeOurFunction(0);

	resultFirstDerivativeOurFunction = -1.5 *
		cos(argument) + 6 * argument *
		cos(argument) - 3 * pow(argument, 2)
		* sin(argument);

	return resultFirstDerivativeOurFunction;
}

// ������ ����������� ����� �������
double secondDerivativeOurFunction (double argument)
{
	double resultSecondDerivativeOurFunction(0);

	resultSecondDerivativeOurFunction = 6 *
		cos(argument) - 3 * pow(argument, 2)
		* cos(argument) + 1.5 * sin(argument)
		- 12 * argument * sin(argument);

	return resultSecondDerivativeOurFunction;
}

// ��������������� ���� ������� ��� ������ ������� ��������
double newOurFunction(double argument)
{
	double resultNewOurFunction(0);

	resultNewOurFunction =
		sqrt(1 / (2 * tan(argument)) - 1 / (15 * cos(argument)));

	return resultNewOurFunction;
}