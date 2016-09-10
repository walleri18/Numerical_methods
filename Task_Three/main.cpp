/*
	������ ��������:
		������� 2 ����� �� ����������� �������������� ������� � ����������
		����� ������� �������������

	������� �3. ������� �23.
	���� ������ ����������� � ���, ����� � ������� ��������� ������� ��������� ���������� ��������.

	� ������� ����� ��� ����� ������������� �����, ������� ����� ����� ������������ ��� ����� ��������������� �������.
	����� ������ ������ ��� ������������ ���������� ourFunction � �������� ���������� � main.cpp

	P.S: ���������� ������ ����� �� ����. 
*/
#include "SolutionIntegrals.h"
#include <iostream>
#include <cmath>

using namespace std;

const double MINIMUM = -10;
const double MAXIMUM = 10;

/*
	���������
*/
// ���� �������� �������
double ourFunction(double);

// ������ ����������� ����� �������
double firstDerivativeOurFunction(double);

// ������ ����������� ����� �������
double secondDerivativeOurFunction(double);

int main(void)
{
	// ��������� ��������� 1251
	setlocale(LC_ALL, ".1251");
	
	SolutionIntegrals sol(MINIMUM, MAXIMUM, 1.E-4, 4);

	// ���������� ������ �������� (�������)
	sol.SimpsonMethod(ourFunction);

	// ���������� ������ ������
	sol.GaussMethod(ourFunction);

	return 0;
}

// ���� �������� �������
double ourFunction(double argument)
{
	double resultOurFunction(0);

	if (argument != 0)
		resultOurFunction = exp(argument) / argument;

	return resultOurFunction;
}

// ������ ����������� ����� �������
double firstDerivativeOurFunction (double argument)
{
	double resultFirstDerivativeOurFunction(0);



	return resultFirstDerivativeOurFunction;
}

// ������ ����������� ����� �������
double secondDerivativeOurFunction (double argument)
{
	double resultSecondDerivativeOurFunction(0);



	return resultSecondDerivativeOurFunction;
}