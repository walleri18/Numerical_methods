#include "SolutionEquation.h"
#include <iostream>

using namespace std;

const double MINIMUM = -1.8;
const double MAXIMUM = 0;

int main(void)
{
	// Установка кодировки 1251
	setlocale(LC_ALL, ".1251");

	SolutionEquation sol(MINIMUM, MAXIMUM, 1.E-9);

	cout << endl << "Выполнение метода Ньютона: " << endl;

	sol.NewtonMethod();

	cout << endl << "Выполнение метода Простых итераций: " << endl;

	sol.SimpleIterationMethod();

	cout << endl << "Выполнение метода Половинного деления: " << endl;

	sol.HalfDivisionMethod();

	cout << endl << "Выполнение метода Хорд: " << endl;

	sol.DichotomyMethod();

	return 0;
}