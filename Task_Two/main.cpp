#include "SolutionEquation.h"
#include <iostream>

using namespace std;

int main(void)
{
	// Установка кодировки 1251
	setlocale(LC_ALL, ".1251");

	SolutionEquation sol(-1.8, 0, 1.E-9);

	cout << endl << "Выполнение метода Ньютона: " << endl;

	sol.NewtonMethod();

	cout << endl << "Выполнение метода Простых итераций: " << endl;

	sol.SimpleIterationMethod();

	return 0;
}