#include "SolutionApproximation.h"
#include <time.h>
#include <stdlib.h>

// �����������
SolutionApproximation::SolutionApproximation(Function ourFunction, double beginSegment, double endSegment, int orderApproximatFunction, int m, int c) :
	ourFunction(ourFunction), beginSegment(beginSegment),
	endSegment(endSegment),
	n(n), m(m), c(c)
{}

// ������ ourFunction
void SolutionApproximation::setOurFunction(Function ourFunction)
{
	this->ourFunction = ourFunction;
}

// ������ ourFunction
Function SolutionApproximation::getOurFunction() const
{
	return this->ourFunction;
}

// ������ ������ ������� (a)
void SolutionApproximation::setBeginSegment(double beginSegment)
{
	this->beginSegment = beginSegment;
}

// ������ ������ ������� (a)
double SolutionApproximation::getBeginSegment() const
{
	return this->beginSegment;
}

// ������ ����� ������� (b)
void SolutionApproximation::setEndSegment(double endSegment)
{
	this->endSegment = endSegment;
}

// ������ ����� ������� (b)
double SolutionApproximation::getEndSegment() const
{
	return this->endSegment;
}

// ������ ������� ���������������� ������� (n)
void SolutionApproximation::setValueN(int n)
{
	this->n = n;
}

// ������ ������� ���������������� ������� (n)
int SolutionApproximation::getValueN() const
{
	return this->n;
}

// ������ �������� (m)
void SolutionApproximation::setValueM(int m)
{
	this->m = m;
}

// ������ �������� (m)
int SolutionApproximation::getValueM() const
{
	return this->m;
}

// ������ �������� (c)
void SolutionApproximation::setValueC(int c)
{
	this->c = c;
}

// ������ �������� (c)
int SolutionApproximation::getValueC() const
{
	return this->c;
}

// ������ ������� �������� X_i
std::vector<double> SolutionApproximation::getVectorX_i() const
{
	return this->vectorX_i;
}

// ������ ������� �������� F_i
std::vector<double> SolutionApproximation::getVectorF_i() const
{
	return this->vectorF_i;
}

// ������ ������� �������
std::vector<double> SolutionApproximation::getResiduals() const
{
	return this->residuals;
}

// ���������� ���������������� ������� � � ������
void SolutionApproximation::update()
{
	// �������
	clear();

	// ������������� X_i
	createdVectorX_i();

	// ������������� F_i
	createdVectorF_i();

	// ������������� ����������� �������
	createdMatrix();

	// ���������� �������������
	KramerSolve();

	// ���������� �������
	searchResiduals();
}

// ��������� ����������������� ��������
double SolutionApproximation::ApproximationPolynom(double X)
{
	double resultAppPolynom(0);

	for (int i = 0; i < polynomialCoefficients.size(); ++i)
	{
		resultAppPolynom += (polynomialCoefficients[i] * pow(X, i));
	}

	return resultAppPolynom;
}

// ������� ���� �������� �� ������ ������
void SolutionApproximation::clear()
{
	this->vectorF_i.clear();

	this->vectorX_i.clear();

	matrix.clear();

	polynomialCoefficients.clear();

	residuals.clear();
}

// �������� ������� �������� X_i
void SolutionApproximation::createdVectorX_i()
{
	for (int i = 0; i <= m; ++i)
	{
		vectorX_i.push_back(beginSegment
							+ i * (endSegment - beginSegment) / m);
	}
}

// �������� ������� �������� F_i
void SolutionApproximation::createdVectorF_i()
{
	// ����� �������
    srand(time(NULL));

	// ��������� ����� � ��������� [0 ; 1]
	double z_i(0);
	
	// ����� �� �������� (k)
	int k(0);

	for (int i = 0; i < vectorX_i.size(); ++i)
	{
		// ���������� ��������� ����� � �������� [0 ; 1]
		z_i = rand() % 2;

		// ������ �������� 22 � ��������� � ����� ����� � �� ������
		if (z_i < 0.5)
			k = -1;
		else
			k = 1;

		// ���������� ������ �������� 22 � ��������� � �� ������.
		// ����� ����
		vectorF_i.push_back(ourFunction(vectorX_i[i]) * (1
													   + k * z_i / c));
	}
}

// �������� ����������� �������
void SolutionApproximation::createdMatrix()
{
	// ������������ ���������� �������������
	int maxCountK = n + 1;

	/*
		������� ������
	*/
	// �������� ������� ������
	std::vector<double> rowZero(maxCountK + 1);

	// ���������� ������� ������
	rowZero[0] = n;

	// ����� ����� ������� �������� ���������
	for (int i = 1; i < maxCountK; ++i)
	{
		rowZero[i] = 0;

		for (int j = 1; j < vectorX_i.size(); ++j)
		{
			rowZero[i] += pow(vectorX_i[j], i);
		}
	}

	// ������ ����� ������� �������� ���������
	rowZero[rowZero.size() - 1] = 0;

	for (int i = 1; i < vectorF_i.size(); ++i)
	{
		rowZero[rowZero.size() - 1] += vectorF_i[i];
	}

	/*
		����-������� ������
	*/
	// ������ ����-������� �����
	std::vector< std::vector<double> > postRow(maxCountK - 1);

	// ���������� ����-������� �����
	for (int k = 1; k < (maxCountK - 1); ++k)
	{
		// �������� ������
		std::vector<double> row(maxCountK + 1);

		// ����� ����� ������� �������� ���������
		for (int j = 0; j < maxCountK; ++j)
		{
			row[j] = 0;

			for (int i = 1; i < vectorX_i.size(); ++i)
			{
				row[j] += pow(vectorX_i[i], j + k);
			}
		}

		// ������ ����� ������� �������� ���������
		row[postRow.size() - 1] = 0;

		for (int i = 1; i < vectorF_i.size(); ++i)
		{
			row[postRow.size() - 1] 
				+= (vectorF_i[i] * pow(vectorX_i[i], k));
		}

		// �������� ������
		postRow.push_back(row);
	}

	// ���������� ����������� �������
	matrix.push_back(rowZero);

	for (int i = 0; i < postRow.size(); ++i)
	{
		matrix.push_back(postRow[i]);
	}
}

// ������� ������������ ������� ������
double SolutionApproximation::GaussDeterminant()
{
	// �����������
	double resultDeterminant(1);

	// ���������� ����� � �������
	int countRow = matrix.size();

    // ����������� �������
    std::vector< std::vector<double> > copyMatrix = matrix;

	// ������ ��� ������ ������
	for (int i = 0; i < countRow; ++i)
	{
		for (int j = i + 1; j < countRow; ++j)
		{
			if (copyMatrix[i][i] == 0)
				throw new int;

			double b = copyMatrix[j][i] / copyMatrix[i][i];

			for (int k = i; k < countRow; ++k)
				copyMatrix[j][k] = copyMatrix[j][k]
				- copyMatrix[i][k] * b;
		}

		// ���������� ������������
		resultDeterminant *= copyMatrix[i][i];
	}

	return resultDeterminant;
}

// ���������� ������������� (������� ������� �������� ��������� ������� �������)
void SolutionApproximation::KramerSolve()
{
	// ����������� ������������
	std::vector<double> X;

	// ������ �������������
	std::vector<double> vectorDeterminant(matrix.size());

	// ��������� ������ ��� �������� ������� �������
	std::vector<double> tmpColumn(matrix.size());

	for (int i = 0; i < (matrix.size() + 1); ++i)
	{
        vectorDeterminant[i] = GaussDeterminant();

		// ���������������� ������ �������� �������
		for (int j = 0; j < matrix.size(); j++)
		{
			if (i > 0)
				// ��������������� �������� ������
				matrix[j][i - 1] = tmpColumn[j];

			// ��������� �������� i - ������� ������� � ���������� tmpColumn
			tmpColumn[j] = matrix[j][i];

			// � i - ������� ������� ���������� ������� ��������� ������
			matrix[j][i] = matrix[j][matrix.size()];
		}
	}

	// ���������� ����������
	for (int i = 1; i < (matrix.size() + 1); ++i)
		X.push_back(vectorDeterminant[i] / vectorDeterminant[0]);

	polynomialCoefficients = X;
}

// ���������� �������
void SolutionApproximation::searchResiduals()
{
	/*
		������� ���������� �������
		
		e = b - A * k,

		���  e - ������ �������,
		b - ������ ��������� ������
		A - ������� ������������� ������� �������� ���������(��� ��������� ������)
		k - ������ ��������� ������������� ���������������� ��������
	*/
	// ������ �������
	std::vector<double> eps(polynomialCoefficients.size());

	// ������ ���������� ��������� ������� (A) �� (k)
	std::vector<double> resultMulti(polynomialCoefficients.size());

	// ������������ ������� (A) �� (k)
	for (int i = 0; i < matrix.size(); ++i)
	{
		resultMulti[i] = 0;

		for (int j = 0; j < polynomialCoefficients.size(); ++j)
		{
			resultMulti[i] += (matrix[i][j] * polynomialCoefficients[j]);
		}
	}

	// ���������� ������� �������
	for (int i = 0; i < eps.size(); ++i)
	{
		eps[i] = matrix[i][matrix.size() - 1] - resultMulti[i];
	}

	residuals = eps;
}