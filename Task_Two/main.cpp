#include "SolutionEquation.h"
#include <iostream>

using namespace std;

int main(void)
{
	// ��������� ��������� 1251
	setlocale(LC_ALL, ".1251");

	SolutionEquation sol(-1.8, 0, 1.E-9);

	cout << endl << "���������� ������ �������: " << endl;

	sol.NewtonMethod();

	cout << endl << "���������� ������ ������� ��������: " << endl;

	sol.SimpleIterationMethod();

	return 0;
}