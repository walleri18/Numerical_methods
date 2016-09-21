/*
	������ ��������:
	������� 2 ����� �� ����������� �������������� ������� � ����������
	����� ������� �������������

	������� �4. ������� �16.
	���� ������ ����������� � ���, ����� � ������� ������ ������� �������� ���������������� �������.
	� ��������� ������� � ������� �������� ����� ������� � ��������������� �������.

	�� �������������� ���� ����� �������� � ��������������� � VS, � ���������� GUI ����� ������ � Qt.

*/
#include <iostream>
#include <cmath>
#include "Interpolation.h"

using namespace std;

/*
	���������
*/
const double MINIMUM = -1;
const double MAXIMUM = -0.1;

/*
	���������
*/
// ���� �������� �������
double ourFunction(double);

int main(void)
{
	// ��������� ��������� 1251
	setlocale(LC_ALL, ".1251");

	// ����������� ������� ��� ������� ������� � ������ ����������
	int n = 19;

	// ��� ������ ��� ���������� ������������
	Interpolation solutionInterpol(ourFunction, MINIMUM, MAXIMUM, n);

	solutionInterpol.update();

	auto argument = solutionInterpol.getArgument();
	auto resultOurFunction = solutionInterpol.getResultOurFunction();

	double resultBessel = solutionInterpol.interpolantBesselFunction(argument[n]);
	double resultOutFunction = ourFunction(argument[n]);

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