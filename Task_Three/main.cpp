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

const double MINIMUM = -1;
const double MAXIMUM = 1;

/*
	���������
*/
// ���� �������� �������
double ourFunction(double);

int main(void)
{
	// ��������� ��������� 1251
	setlocale(LC_ALL, ".1251");
	
	cout << "���� ��������������� �������: exp(t)/t" << endl << endl;

	SolutionIntegrals sol(MINIMUM, MAXIMUM, 1.E-4, 8);

	cout << endl << endl << "����� ��������: ";

	// ���������� ������ �������� (�������)
	sol.SimpsonMethod(ourFunction);

	cout << endl << endl << "����� ������: ";

	// ���������� ������ ������
	sol.GaussMethod(ourFunction);

	cout << endl;

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