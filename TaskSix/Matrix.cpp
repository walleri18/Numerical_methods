#include "Matrix.h"
#include <iostream>
#include <iomanip>

using namespace std;

// �����������
Matrix::Matrix(Function ourFunction, int n) : ourFunction(ourFunction), n(n)
{}

// ������ �������� �������
typeMatrix Matrix::getSourseMatrix() const
{
	return this->sourseMatrix;
}

// ������ �������� �������
typeMatrix Matrix::getInverseMatrix() const
{
	return this->inverseMatrix;
}

// ������ ��������� �������
typeMatrix Matrix::getEMatrix() const
{
	return this->EMatrix;
}

// ����� �������� �������
void Matrix::showSourseMatrix()
{
	// ����� ��������� ������
	cout << "�������� �������: " << endl << endl;

	// ����� ����� �������
	showMatrix(sourseMatrix);
}

// ����� �������� �������
void Matrix::showInverseMatrix()
{
	// ����� ��������� ������
	cout << "�������� �������: " << endl << endl;

	// ����� ����� �������
	showMatrix(inverseMatrix);
}

// ����� ��������� �������
void Matrix::showEMatrix()
{
	// ����� ��������� ������
	cout << "��������� �������: " << endl << endl;

	// ����� ����� �������
	showMatrix(EMatrix);
}

// ����� ������������ �������� �������
void Matrix::showDeterminantSourseMatrix()
{
	typeElementMatrix determinant = determinantMatrix(sourseMatrix);

	cout << "����������� �������� �������: " << determinant << endl << endl;
}

// ����� ������������ �������� �������
void Matrix::showDeterminantInverseMatrix()
{
	typeElementMatrix determinant = determinantMatrix(inverseMatrix);

	cout << "����������� �������� �������: " << determinant << endl << endl;
}

// ���������� ������� � ����������� ��� ��
void Matrix::update()
{
	// �������
	clear();

	// �������� �������� ������� (A)
	createdSourseMatrix();

	// �������� �������� ������� (A^(-1))
	createdInverseMatrix();

	// �������� ��������� ������� (B)
	createdEMatrix();
}

// ������� ������� ������
void Matrix::clear()
{
	// ������� �������� �������
	if (!sourseMatrix.empty())
		for (size_t i = 0, maxI(sourseMatrix.size()); i < maxI; ++i)
			if (sourseMatrix[i] != nullptr)
				delete sourseMatrix[i];

	sourseMatrix.clear();

	// ������� �������� �������
	if (!inverseMatrix.empty())
		for (size_t i = 0, maxI(inverseMatrix.size()); i < maxI; ++i)
			if (inverseMatrix[i] != nullptr)
				delete inverseMatrix[i];

	inverseMatrix.clear();

	// ������� ��������� �������
	if (!EMatrix.empty())
		for (size_t i = 0, maxI(EMatrix.size()); i < maxI; ++i)
			if (EMatrix[i] != nullptr)
				delete EMatrix[i];

	EMatrix.clear();
}

// ������� ������ �������
void Matrix::showMatrix(typeMatrix matrix)
{
	for (size_t i = 0, maxI(matrix.size()); i < maxI; ++i)
	{
		for (size_t j = 0, maxJ(matrix[i]->size()); j < maxJ; ++j)
		{
			cout << setw(10) << right << setprecision(9) << (*matrix[i])[j] << "|";
		}

		cout << "endl" << endl <<  endl;
	}
}

// ������� ���������� ������������
typeElementMatrix Matrix::determinantMatrix(typeMatrix matrix)
{
	// ��������� ������������ ����� �������
	typeElementMatrix determinant(1);

	// ����������� �������
	double b(0);

	// ������ ��� ������ ������
	for (size_t i = 0, maxI(matrix.size()); i < maxI; ++i)
	{
		for (size_t j = i + 1, maxJ(matrix[i]->size()); j < maxJ; ++j)
		{
			if ((*matrix[i])[i] == 0)
			{
				if ((*matrix[i])[j] == 0)
					b = 0;

				// � ������ ������ ����������� ����������
				else
					throw new int;
			}

			else
				b = (*matrix[j])[i] / (*matrix[i])[i];

			for (size_t k = i, maxK(matrix.size()); k < maxK; ++k)
				(*matrix[j])[k] = (*matrix[j])[k] - (*matrix[i])[k] * b;
		}

		// ��������� �����������
		determinant *= (*matrix[i])[i];
	}

	return determinant;
}

// �������� �������� �������
void Matrix::createdSourseMatrix()
{
	for (size_t i = 0, maxI(n); i < maxI; ++i)
	{
		// �������� ����� �������
		sourseMatrix.push_back(new vector<typeElementMatrix>);

		// ���������� �����
		for (size_t j = 0, maxJ(n); j < maxJ; ++j)
			(*sourseMatrix[i]).push_back(ourFunction(i, j));
	}
}

// ���������� �������� �������
void Matrix::createdInverseMatrix()
{
	// ����������� �������� �������
	typeMatrix matrix;

	for (int i = 0; i < n; ++i)
	{
		matrix.push_back(new vector<typeElementMatrix>);

		for (int j = 0; j < n; ++j)
		{
			matrix[i]->push_back((*sourseMatrix[i])[j]);
		}
	}

	// �������� ��������� ������� 
	typeElementMatrix **M_obr = new typeElementMatrix*[n];

	for (int i = 0; i < n; i++)
	{
		M_obr[i] = new typeElementMatrix[n];

		inverseMatrix.push_back(new vector<typeElementMatrix>);

		for (int j = 0; j < n; j++)
			M_obr[i][j] = 0;

		M_obr[i][i] = 1;
	}

	// ������ ��� ������� ������
	double a(0), b(0);

	for (int i = 0; i < n; i++)
	{
		a = (*matrix[i])[i];

		for (int j = i + 1; j < n; j++)
		{
			b = (*matrix[j])[i];

			for (int k = 0; k < n; k++)
			{
				(*matrix[j])[k] = (*matrix[i])[k] * b - (*matrix[j])[k] * a;

				M_obr[j][k] = M_obr[i][k] * b - M_obr[j][k] * a;
			}
		}
	}
	//�������� ��� ���������� ��������� �������� �������
	double sum(0);
	for (int i = 0; i < n; i++)
	{
		for (int j = n - 1; j >= 0; j--)
		{
			sum = 0;

			for (int k = n - 1; k > j; k--)
				sum += (*matrix[j])[k] * M_obr[k][i];

			if ((*matrix[j])[j] == 0)
				throw new int;

			M_obr[j][i] = (M_obr[j][i] - sum) / (*matrix[j])[j];
		}
	}

	// �����������
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
			inverseMatrix[i]->push_back(M_obr[i][j]);
	}

	// ������������ ������
	for (int i = 0; i < n; i++)
		delete[]M_obr[i];

	delete[]M_obr;
}

// ���������� ��������� �������. (B)
void Matrix::createdEMatrix()
{
	// �������� ��������� �������
	for (size_t i = 0; i < n; ++i)
	{
		// �������� ����� ��������� �������
		EMatrix.push_back(new vector<typeElementMatrix>);

		for (size_t j = 0; j < n; ++j)
			EMatrix[i]->push_back(0);
	}

	// ��������� A * A^(-1)
	for (size_t i = 0; i < n; ++i)
		for (size_t j = 0; j < n; ++j)
			for (size_t k = 0; k < n; ++k)
				(*EMatrix[i])[j] += ((*sourseMatrix[i])[k]) * ((*inverseMatrix[k])[j]);

}