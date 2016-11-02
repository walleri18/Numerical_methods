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

	matrix.update();

	// Попытка вывести матрицы
	matrix.showSourseMatrix();

	// Попытка вывести обратную матрицу
	matrix.showInverseMatrix();

	// Попытка вывести единичную матрицу (B)
	matrix.showEMatrix();

	// Попытка вывести детерминант исходной матрицы
	matrix.showDeterminantSourseMatrix();

	// Попытка вывести детерминант обратной матрицы
	matrix.showDeterminantInverseMatrix();

	// Попытка вывести число обусловленности
	matrix.showConditionNumber();

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

	result = static_cast<typeElementMatrix>(1) / static_cast<typeElementMatrix>(cos(static_cast<typeElementMatrix>(i) - j) * cos(static_cast<typeElementMatrix>(i) - j));

	return result;
}