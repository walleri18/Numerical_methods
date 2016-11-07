#include "Matrix.h"
#include <iostream>
#include <fstream>
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

// ����� ����� ���������������
void Matrix::showConditionNumber()
{
	typeElementMatrix conditionNumber = findConditionNumber();

	cout << "����� ���������������: " << conditionNumber << endl << endl;
}

// ����� �������� ������� � ����
void Matrix::saveFileSourseMatrix()
{
	saveFileMatrix(sourseMatrix, "SourseMatrix");
}

// ����� �������� ������� � ����
void Matrix::saveFileInverseMatrix()
{
	saveFileMatrix(inverseMatrix, "InverseMatrix");
}

// ����� ��������� ������� � ����
void Matrix::saveFileEMatrix()
{
	saveFileMatrix(EMatrix, "EMatrix");
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
			cout << setw(6) << right << setprecision(5) << (*matrix[i])[j] << "|";
		}

		cout << "endl" << endl <<  endl;
	}
}

// ������� ������ ������� � ����
void Matrix::saveFileMatrix(typeMatrix matrix, string fileName)
{
	// �������� ����� � ������ fileName
	ofstream file(fileName + ".txt");

	file << fileName << endl << endl;

	for (size_t i = 0; i < n; ++i)
	{
		for (size_t j = 0; j < n; ++j)
			file << setw(6) << setprecision(5) << right << ((*matrix[i])[j]) << "|";

		file << endl;
	}
}

// ������� ���������� ������������
typeElementMatrix Matrix::determinantMatrix(typeMatrix matrix)
{
	// ��������� ������������ ����� �������
	typeElementMatrix determinant(1);

	// ����� �������
	typeMatrix copyMatrix;

	for (size_t i = 0; i < n; ++i)
	{
		copyMatrix.push_back(new vector<typeElementMatrix>);

		for (size_t j = 0; j < n; ++j)
			copyMatrix[i]->push_back((*matrix[i])[j]);
	}

	// ����������� �������
	double b(0);

	// ������ ��� ������ ������
	for (size_t i = 0; i < n; ++i)
	{
		for (size_t j = i + 1; j < n; ++j)
		{
			if ((*copyMatrix[i])[i] == 0)
			{
				if ((*copyMatrix[i])[j] == 0)
					b = 0;

				// � ������ ������ ����������� ����������
				else
					throw new int;
			}

			else
				b = (*copyMatrix[j])[i] / (*copyMatrix[i])[i];

			for (size_t k = i; k < n; ++k)
				(*copyMatrix[j])[k] = (*copyMatrix[j])[k] - (*copyMatrix[i])[k] * b;
		}

		// ��������� �����������
		determinant *= (*copyMatrix[i])[i];
	}

	return determinant;
}

// ����� ����� ���������������
typeElementMatrix Matrix::findConditionNumber()
{
	// ����� ���������������
	typeElementMatrix result(0);

	// ����� sourseMatrix
	typeElementMatrix normaSourseMatrix(0);

	// ����� inverseMatrix;
	typeElementMatrix normaInverseMatrix(0);

	// ���������� ����
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

	// ������� ����� ���������������
	result = (normaSourseMatrix * normaInverseMatrix);

	return result;
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
	// ����� LU ����������
	// ������ ������ ��� ������� LU
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

				// ��������� �������� ������� ����������� �������
				LU[i][j] = (*sourseMatrix[i])[j] - sum;
			}
			else
			{
				for (int k = 0; k < j; k++)
					sum += LU[i][k] * LU[k][j];

				if (LU[j][j] == 0)
					throw new int;

				// ��������� �������� ������ ����������� �������
				LU[i][j] = ((*sourseMatrix[i])[j] - sum) / LU[j][j];
			}
		}

	}

	// ������ ������ ��� �������� �������
	typeElementMatrix **M_obr = new typeElementMatrix *[n]; 

	for (int i = 0; i < n; i++)
		M_obr[i] = new typeElementMatrix[n];

	// ���������� �������� �������
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

	// �����������
	for (int i = 0; i < n; i++)
	{
		inverseMatrix.push_back(new vector<typeElementMatrix>);

		for (int j = 0; j < n; j++)
			inverseMatrix[i]->push_back(M_obr[i][j]);
	}

	// ������������ ������
	for (int i = 0; i < n; i++)
	{
		delete[] M_obr[i];
		delete[] LU[i];
	}

	delete[] M_obr;
	delete[] LU;

	// ����� ������
	//// ����������� �������� �������
	//typeMatrix matrix;

	//for (int i = 0; i < n; ++i)
	//{
	//	matrix.push_back(new vector<typeElementMatrix>);

	//	for (int j = 0; j < n; ++j)
	//	{
	//		matrix[i]->push_back((*sourseMatrix[i])[j]);
	//	}
	//}

	//// �������� ��������� ������� 
	//typeElementMatrix **M_obr = new typeElementMatrix*[n];

	//for (int i = 0; i < n; i++)
	//{
	//	M_obr[i] = new typeElementMatrix[n];

	//	inverseMatrix.push_back(new vector<typeElementMatrix>);

	//	for (int j = 0; j < n; j++)
	//		M_obr[i][j] = 0;

	//	M_obr[i][i] = 1;
	//}

	//// ������ ��� ������� ������
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
	////�������� ��� ���������� ��������� �������� �������
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

	//// �����������
	//for (int i = 0; i < n; i++)
	//{
	//	for (int j = 0; j < n; j++)
	//		inverseMatrix[i]->push_back(M_obr[i][j]);
	//}

	//// ������������ ������
	//for (int i = 0; i < n; i++)
	//	delete[]M_obr[i];

	//delete[]M_obr;
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