#include "Matrix.h"
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

// Конструктор
Matrix::Matrix(Function ourFunction, int n) : ourFunction(ourFunction), n(n)
{}

// Геттер исходной матрицы
typeMatrix Matrix::getSourseMatrix() const
{
	return this->sourseMatrix;
}

// Геттер обратной матрицы
typeMatrix Matrix::getInverseMatrix() const
{
	return this->inverseMatrix;
}

// Геттер единичной матрицы
typeMatrix Matrix::getEMatrix() const
{
	return this->EMatrix;
}

// Вывод исходной матрицы
void Matrix::showSourseMatrix()
{
	// Вывод заголовка вывода
	cout << "Исходная матрица: " << endl << endl;

	// Вывод самой матрицы
	showMatrix(sourseMatrix);
}

// Вывод обратной матрицы
void Matrix::showInverseMatrix()
{
	// Вывод заголовка вывода
	cout << "Обратная матрица: " << endl << endl;

	// Вывод самой матрицы
	showMatrix(inverseMatrix);
}

// Вывод единичной матрицы
void Matrix::showEMatrix()
{
	// Вывод заголовка вывода
	cout << "Единичная матрица: " << endl << endl;

	// Вывод самой матрицы
	showMatrix(EMatrix);
}

// Вывод детерминанта исходной матрицы
void Matrix::showDeterminantSourseMatrix()
{
	typeElementMatrix determinant = determinantMatrix(sourseMatrix);

	cout << "Детерминант исходной матрицы: " << determinant << endl << endl;
}

// Вывод детерминанта обратной матрицы
void Matrix::showDeterminantInverseMatrix()
{
	typeElementMatrix determinant = determinantMatrix(inverseMatrix);

	cout << "Детерминант обратной матрицы: " << determinant << endl << endl;
}

// Вывод числа обусловленности
void Matrix::showConditionNumber()
{
	typeElementMatrix conditionNumber = findConditionNumber();

	cout << "Число обусловленности: " << conditionNumber << endl << endl;
}

// Вывод исходной матрицы в файл
void Matrix::saveFileSourseMatrix()
{
	saveFileMatrix(sourseMatrix, "SourseMatrix");
}

// Вывод обратной матрицы в файл
void Matrix::saveFileInverseMatrix()
{
	saveFileMatrix(inverseMatrix, "InverseMatrix");
}

// Вывод единичной матрицы в файл
void Matrix::saveFileEMatrix()
{
	saveFileMatrix(EMatrix, "EMatrix");
}

// Обновление матрицы и результатов для неё
void Matrix::update()
{
	// Очистка
	clear();

	// Создание исходной матрицы (A)
	createdSourseMatrix();

	// Создание обратной матрицы (A^(-1))
	createdInverseMatrix();

	// Создание единичной матрицы (B)
	createdEMatrix();
}

// Функция очистки матриц
void Matrix::clear()
{
	// Очистка исходной матрицы
	if (!sourseMatrix.empty())
		for (size_t i = 0, maxI(sourseMatrix.size()); i < maxI; ++i)
			if (sourseMatrix[i] != nullptr)
				delete sourseMatrix[i];

	sourseMatrix.clear();

	// Очистка обратной матрицы
	if (!inverseMatrix.empty())
		for (size_t i = 0, maxI(inverseMatrix.size()); i < maxI; ++i)
			if (inverseMatrix[i] != nullptr)
				delete inverseMatrix[i];

	inverseMatrix.clear();

	// Очистка единичной матрицы
	if (!EMatrix.empty())
		for (size_t i = 0, maxI(EMatrix.size()); i < maxI; ++i)
			if (EMatrix[i] != nullptr)
				delete EMatrix[i];

	EMatrix.clear();
}

// Функция вывода матрицы
void Matrix::showMatrix(typeMatrix matrix)
{
	for (size_t i = 0, maxI(matrix.size()); i < maxI; ++i)
	{
		for (size_t j = 0, maxJ(matrix[i]->size()); j < maxJ; ++j)
		{
			cout << setw(6) << right << setprecision(5) << (*matrix[i])[j] << "|";
		}

		cout << "endl" << endl <<  endl;
	}
}

// Функция вывода матрицы в файл
void Matrix::saveFileMatrix(typeMatrix matrix, string fileName)
{
	// Создание файла с именем fileName
	ofstream file(fileName + ".txt");

	file << fileName << endl << endl;

	for (size_t i = 0; i < n; ++i)
	{
		for (size_t j = 0; j < n; ++j)
			file << setw(6) << setprecision(5) << right << ((*matrix[i])[j]) << "|";

		file << endl;
	}
}

// Функция вычисления детерминанта
typeElementMatrix Matrix::determinantMatrix(typeMatrix matrix)
{
	// Результат детерминанта нашей матрицы
	typeElementMatrix determinant(1);

	// Копия матрицы
	typeMatrix copyMatrix;

	for (size_t i = 0; i < n; ++i)
	{
		copyMatrix.push_back(new vector<typeElementMatrix>);

		for (size_t j = 0; j < n; ++j)
			copyMatrix[i]->push_back((*matrix[i])[j]);
	}

	// Коэффициент деления
	double b(0);

	// Прямой ход метода Гаусса
	for (size_t i = 0; i < n; ++i)
	{
		for (size_t j = i + 1; j < n; ++j)
		{
			if ((*copyMatrix[i])[i] == 0)
			{
				if ((*copyMatrix[i])[j] == 0)
					b = 0;

				// В случае ошибки выбрасываем исключение
				else
					throw new int;
			}

			else
				b = (*copyMatrix[j])[i] / (*copyMatrix[i])[i];

			for (size_t k = i; k < n; ++k)
				(*copyMatrix[j])[k] = (*copyMatrix[j])[k] - (*copyMatrix[i])[k] * b;
		}

		// Вычисляем детерминант
		determinant *= (*copyMatrix[i])[i];
	}

	return determinant;
}

// Поиск числа обусловленности
typeElementMatrix Matrix::findConditionNumber()
{
	// Число обусловленности
	typeElementMatrix result(0);

	// Норма sourseMatrix
	typeElementMatrix normaSourseMatrix(0);

	// Норма inverseMatrix;
	typeElementMatrix normaInverseMatrix(0);

	// Вычисление норм
	for (int j = 0; j < n; ++j)
	{
		typeElementMatrix tmpOne(0);
		typeElementMatrix tmpTwo(0);

		//cout << "j = " << j << endl;

		for (int i = 0; i < n; ++i)
		{
			tmpOne += fabs((*sourseMatrix[i])[j]);
			tmpTwo += fabs((*inverseMatrix[i])[j]);

			//cout << "i = " << i << endl << fabs((*sourseMatrix[i])[j]) << "\t" << fabs((*inverseMatrix[i])[j]) << endl;
		}

		if (tmpOne > normaSourseMatrix)
			normaSourseMatrix = tmpOne;

		if (tmpTwo > normaInverseMatrix)
			normaInverseMatrix = tmpTwo;
	}

	// Считаем число обусловленности
	result = (normaSourseMatrix * normaInverseMatrix);

	return result;
}

// Создание исходной матрицы
void Matrix::createdSourseMatrix()
{
	for (size_t i = 0, maxI(n); i < maxI; ++i)
	{
		// Создание строк матрицы
		sourseMatrix.push_back(new vector<typeElementMatrix>);

		// Заполнение строк
		for (size_t j = 0, maxJ(n); j < maxJ; ++j)
			(*sourseMatrix[i]).push_back(ourFunction(i, j));
	}
}

// Вычисление обратной матрицы
void Matrix::createdInverseMatrix()
{
	// Метод LU разложения
	// Создаём массив под матрицу LU
	typeElementMatrix **LU = new typeElementMatrix *[n];

	for (int i = 0; i < n; i++)
		LU[i] = new typeElementMatrix[n];

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			typeElementMatrix sum = 0;

			if (i <= j)
			{
				for (int k = 0; k < i; k++)
					sum += LU[i][k] * LU[k][j];

				// Вычисляем элементы верхней треугольной матрицы
				LU[i][j] = (*sourseMatrix[i])[j] - sum;
			}
			else
			{
				for (int k = 0; k < j; k++)
					sum += LU[i][k] * LU[k][j];

				if (LU[j][j] == 0)
					throw new int;

				// Вычисляем элементы нижней треугольной матрицы
				LU[i][j] = ((*sourseMatrix[i])[j] - sum) / LU[j][j];
			}
		}

	}

	// Создаём массив для обратной матрицы
	typeElementMatrix **M_obr = new typeElementMatrix *[n]; 

	for (int i = 0; i < n; i++)
		M_obr[i] = new typeElementMatrix[n];

	// Нахождение обратной матрицы
	for (int i = n - 1; i >= 0; i--)
	{
		for (int j = n - 1; j >= 0; j--)
		{
			typeElementMatrix sum = 0;
			if (i == j)
			{
				for (int p = j + 1; p < n; p++)
					sum += LU[j][p] * M_obr[p][j];

				M_obr[j][j] = (1 - sum) / LU[j][j];
			}

			else if (i < j)
			{
				for (int p = i + 1; p < n; p++)
					sum += LU[i][p] * M_obr[p][j];

				M_obr[i][j] = -sum / LU[i][i];
			}

			else
			{
				for (int p = j + 1; p < n; p++)
					sum += M_obr[i][p] * LU[p][j];

				M_obr[i][j] = -sum;
			}

		}
	}

	// Копирование
	for (int i = 0; i < n; i++)
	{
		inverseMatrix.push_back(new vector<typeElementMatrix>);

		for (int j = 0; j < n; j++)
			inverseMatrix[i]->push_back(M_obr[i][j]);
	}

	// Освобождение памяти
	for (int i = 0; i < n; i++)
	{
		delete[] M_obr[i];
		delete[] LU[i];
	}

	delete[] M_obr;
	delete[] LU;

	// Метод Гаусса
	//// Копирование исходной матрицы
	//typeMatrix matrix;

	//for (int i = 0; i < n; ++i)
	//{
	//	matrix.push_back(new vector<typeElementMatrix>);

	//	for (int j = 0; j < n; ++j)
	//	{
	//		matrix[i]->push_back((*sourseMatrix[i])[j]);
	//	}
	//}

	//// Создание единичной матрицы 
	//typeElementMatrix **M_obr = new typeElementMatrix*[n];

	//for (int i = 0; i < n; i++)
	//{
	//	M_obr[i] = new typeElementMatrix[n];

	//	inverseMatrix.push_back(new vector<typeElementMatrix>);

	//	for (int j = 0; j < n; j++)
	//		M_obr[i][j] = 0;

	//	M_obr[i][i] = 1;
	//}

	//// Прямой ход методом Гаусса
	//double a(0), b(0);

	//for (int i = 0; i < n; i++)
	//{
	//	a = (*matrix[i])[i];

	//	for (int j = i + 1; j < n; j++)
	//	{
	//		b = (*matrix[j])[i];

	//		for (int k = 0; k < n; k++)
	//		{
	//			(*matrix[j])[k] = (*matrix[i])[k] * b - (*matrix[j])[k] * a;

	//			M_obr[j][k] = M_obr[i][k] * b - M_obr[j][k] * a;
	//		}
	//	}
	//}
	////обратный ход нахождения элементов обратной матрицы
	//double sum(0);
	//for (int i = 0; i < n; i++)
	//{
	//	for (int j = n - 1; j >= 0; j--)
	//	{
	//		sum = 0;

	//		for (int k = n - 1; k > j; k--)
	//			sum += (*matrix[j])[k] * M_obr[k][i];

	//		if ((*matrix[j])[j] == 0)
	//			throw new int;

	//		M_obr[j][i] = (M_obr[j][i] - sum) / (*matrix[j])[j];
	//	}
	//}

	//// Копирование
	//for (int i = 0; i < n; i++)
	//{
	//	for (int j = 0; j < n; j++)
	//		inverseMatrix[i]->push_back(M_obr[i][j]);
	//}

	//// Освобождение памяти
	//for (int i = 0; i < n; i++)
	//	delete[]M_obr[i];

	//delete[]M_obr;
}

// Вычисление единичной матрицы. (B)
void Matrix::createdEMatrix()
{
	// Создание единичной матрицы
	for (size_t i = 0; i < n; ++i)
	{
		// Создание строк единичной матрицы
		EMatrix.push_back(new vector<typeElementMatrix>);

		for (size_t j = 0; j < n; ++j)
			EMatrix[i]->push_back(0);
	}

	// Умножение A * A^(-1)
	for (size_t i = 0; i < n; ++i)
		for (size_t j = 0; j < n; ++j)
			for (size_t k = 0; k < n; ++k)
				(*EMatrix[i])[j] += ((*sourseMatrix[i])[k]) * ((*inverseMatrix[k])[j]);

}