#pragma once
#include <vector>

// Тип элементов матрицы
typedef long double typeElementMatrix;

// Тип матрицы
typedef std::vector< std::vector<typeElementMatrix>* > typeMatrix;

// Тип специальной функции с помощью которой мы будем заполнять матрицу
typedef typeElementMatrix(*Function)(int, int);

/*
	Класс Matrix
	Реализует возможности:
	1) заполнения матрицы по специальной формуле;
	2) вычисление детерминанта этой матрицы (по методу Гаусса)
	3) нахождение обратной матрицы (по методу Гаусса)
	4) вычисление единичной матрицы (матрицы Кронекера)(с помощью перемножения исходной матрицы на обратную)
	5) найти число обусловленности
*/
class Matrix
{
// Данные
private:

	// Функция для расчёта элементов матрицы
	Function ourFunction;

	// Порядок матрицы (n)
	int n;

	// Матрица исходная (A)
	typeMatrix sourseMatrix;

	// Матрицы обратная (A^(-1))
	typeMatrix inverseMatrix;

	// Единичная матрица (B)
	typeMatrix EMatrix;

// Функциональность
public:

	// Конструктор
	Matrix(Function ourFunction, int n);

	// Геттер исходной матрицы
	typeMatrix getSourseMatrix() const;

	// Геттер обратной матрицы
	typeMatrix getInverseMatrix() const;

	// Геттер единичной матрицы
	typeMatrix getEMatrix() const;

	// Вывод исходной матрицы
	void showSourseMatrix();

	// Вывод обратной матрицы
	void showInverseMatrix();

	// Вывод единичной матрицы
	void showEMatrix();

	// Вывод детерминанта исходной матрицы
	void showDeterminantSourseMatrix();

	// Вывод детерминанта обратной матрицы
	void showDeterminantInverseMatrix();

	// Вывод числа обусловленности
	void showConditionNumber();

	// Обновление матрицы и результатов для неё
	void update();

private:

	// Функция очистки матриц
	void clear();

	// Функция вывода матрицы
	void showMatrix(typeMatrix matrix);

	// Функция вычисления детерминанта
	typeElementMatrix determinantMatrix(typeMatrix matrix);

	// Поиск числа обусловленности
	typeElementMatrix findConditionNumber();

	// Создание исходной матрицы (A)
	void createdSourseMatrix();

	// Вычисление обратной матрицы (A^(-1))
	void createdInverseMatrix();

	// Вычисление единичной матрицы. (B)
	void createdEMatrix();

};