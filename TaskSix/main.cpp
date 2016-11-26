/*
	Задание №6. Вариант №16.
	Автор: Туров Виталий Александрович
	Группа: 05154
	Суть задания:
	1) построить матрицу по специальной формуле
	2) вычислить её детерминант
	3) найти обратную матрицу
	4) проверить правильность нахождения с помощью умножения исходной матрицы на обратную
	5) найти число обусловленности
*/

#include "Matrix.h"
#include <iostream>

using namespace std;

/*
	Прототипы
*/
// Наша функция
typeElementMatrix ourFunction(int i, int j);

int main(void)
{
	setlocale(LC_ALL, ".1251");

	cout << "Задача №6. Вариант №16." << endl << endl;

	// Тестирование нашего класса
	Matrix matrix(ourFunction, 2);

	try
	{
		matrix.update();
	}
	catch (...)
	{
		cout << endl << endl << "НЕВОЗМОЖНО НАЙТИ ОБРАТНУЮ МАТРИЦУ" << endl << endl;

		// Попытка вывести исходную матрицы
		matrix.showSourseMatrix();

		return 1;
	}

	// Попытка вывести исходную матрицы
	matrix.showSourseMatrix();

	// Попытка вывести обратную матрицу
	matrix.showInverseMatrix();

	// Попытка вывести единичную матрицу (B)
	matrix.showEMatrix();

	try
	{
		// Попытка вывести детерминант исходной матрицы
		matrix.showDeterminantSourseMatrix();
	}
	catch (...)
	{
		cout << endl << endl << "НЕВОЗМОЖНО ВЫЧИСЛИТЬ ДЕТЕРМИНАНТ ИСХОДНОЙ МАТРИЦЫ" << endl << endl;

		return 1;
	}

	try
	{
		// Попытка вывести детерминант обратной матрицы
		matrix.showDeterminantInverseMatrix();
	}
	catch (...)
	{
		cout << endl << endl << "НЕВОЗМОЖНО ВЫЧИСЛИТЬ ДЕТЕРМИНАНТ ОБРАТНОЙ МАТРИЦЫ" << endl << endl;

		return 1;
	}

	// Попытка вывести число обусловленности
	matrix.showConditionNumber();

	// Вывод в файлы
	matrix.saveFileSourseMatrix();
	matrix.saveFileInverseMatrix();
	matrix.saveFileEMatrix();

	cout << endl;

	return 0;
}
/*
	Реализация
*/
// Наша функция
typeElementMatrix ourFunction(int i, int j)
{
	typeElementMatrix result(0);

	result = 1 / (cos(i - j) * cos(i - j));

	//result = 1 / sin(i + j);

	return result;
}