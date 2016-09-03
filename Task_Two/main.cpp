#include "SolutionEquation.h"
#include <iostream>

using namespace std;

const double MINIMUM = -1.8;
const double MAXIMUM = 0;

int main(void)
{
	// ��������� ��������� 1251
	setlocale(LC_ALL, ".1251");

	SolutionEquation sol(MINIMUM, MAXIMUM, 1.E-9);

	cout << endl << "���������� ������ �������: " << endl;

	sol.NewtonMethod();

	cout << endl << "���������� ������ ������� ��������: " << endl;

	sol.SimpleIterationMethod();

	cout << endl << "���������� ������ ����������� �������: " << endl;

	sol.HalfDivisionMethod();

	cout << endl << "���������� ������ ����: " << endl;

	sol.DichotomyMethod();

	return 0;
}