#include "SolutionApproximation.h"
#include <time.h>

// �����������
SolutionApproximation::SolutionApproximation(Function ourFunction, double beginSegment, double endSegment, int orderApproximatFunction, int m, int c) :
	ourFunction(ourFunction), beginSegment(beginSegment),
	endSegment(endSegment),
	orderApproximatFunction(orderApproximatFunction), m(m), c(c)
{}

SolutionApproximation::SolutionApproximation(){}

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
void SolutionApproximation::setOrderApproximatFunction(int orderApproximatFunction)
{
	this->orderApproximatFunction = orderApproximatFunction;
}

// ������ ������� ���������������� ������� (n)
int SolutionApproximation::getOrderApproximatFunction() const
{
	return this->orderApproximatFunction;
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

// ������ �������
void SolutionApproximation::setMatrix(std::vector<std::vector<double>> matrix)
{
	this->matrix = matrix;
}

// ������ �������
std::vector<std::vector<double>> SolutionApproximation::getMatrix() const
{
	return this->matrix;
}

// ���������� ���������������� ������� � � ������
void SolutionApproximation::update()
{
	// �������
	clear();

	// ������������� x_i
	createdVectorX_i();

	// ������������� F_i
	createdVectorF_i();
}

// ������� ���� �������� �� ������ ������
void SolutionApproximation::clear()
{
	this->vectorF_i.clear();

	this->vectorX_i.clear();

	matrix.clear();
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
    //srand(time(NULL));

	// ��������� ����� � ��������� [0 ; 1]
	double z_i(0);
	
	// ����� �� �������� (k)
	int k(0);

//	for (int i = 0; i < vectorX_i.size(); ++i)
//	{
//		// ���������� ��������� ����� � �������� [0 ; 1]
//		z_i = rand() % 2;

//		// ������ �������� 22 � ��������� � ����� ����� � �� ������
//		if (z_i < 0.5)
//			k = -1;
//		else
//			k = 1;

//		// ���������� ������ �������� 22 � ��������� � �� ������.
//		// ����� ����
//		vectorF_i.push_back(ourFunction(vectorX_i[i]) * (1
//													   + k * z_i / c));
//	}
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

//
//// ���������� ������������� (������� ������� �������� ��������� ������� ������)
//std::vector<double> SolutionApproximation::GaussSolve(std::vector< std::vector<double> > matrix)
//{
//	// ������ �����������
//	std::vector<double> X(matrix.size() - 1);
//
//	// ������ ���
//	for (int i = 0; i < (matrix.size() - 1); ++i)
//	{
//		double a = matrix[i][i];
//
//		for (int j = i + 1; j < (matrix.size() - 1); ++j)
//		{
//			double b = matrix[j][i];
//
//			for (int k = i; k < matrix.size(); ++k)
//				matrix[j][k] = matrix[i][k] * b - matrix[j][k] * a;
//		}
//	}
//
//	// �������� ���
//	for (int i = (matrix.size() - 2); i >= 0; --i)
//	{
//		double summ(0);
//
//		for (int j = (i + 1); j < (matrix.size() - 1); ++j)
//			summ += matrix[i][j] * X[j];
//
//		summ = matrix[i][(matrix.size() - 1)] - summ;
//
//		X[i] = summ / matrix[i][i];
//	}
//
//	return X;
//}

// ���������� ������������� (������� ������� �������� ��������� ������� �������)
std::vector<double> SolutionApproximation::KramerSolve()
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

	return X;
}
