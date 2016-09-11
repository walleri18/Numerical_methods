#include "SolutionIntegrals.h"
#include <iostream>
#include <iomanip>

SolutionIntegrals::SolutionIntegrals(double beginSegment,
								   double endSegment,
									 double precision,
									 int coutNumber) :
	precision(precision),
	coutNumber(coutNumber),
	numberSplits(10),
	resultSolutionIntegral(0)
{
	// ���� ������������ ��������� ���� ����� ������� � ������
	if (beginSegment > endSegment)
	{
		this->beginSegment = endSegment;
		this->endSegment = beginSegment;
	}

	else
	{
		this->beginSegment = beginSegment;
		this->endSegment = endSegment;
	}

	std::cout << "�������� [" << this->beginSegment << "; " << this->endSegment << "]" << std::endl
		<< "���������� ������ ����� ����� " << coutNumber << std::endl << std::endl
		<< "������ � �������� �������� ��������!!!";

	// ������������ ������������� ������������ �������
	A.push_back(0.10122854);
	A.push_back(0.22238104);
	A.push_back(0.31370664);
	A.push_back(0.36268378);
	A.push_back(0.36268378);
	A.push_back(0.31370664);
	A.push_back(0.22238104);
	A.push_back(0.10122854);

	// ������������ ����� �������� ��������
	t.push_back(-0.96028986);
	t.push_back(-0.79666648);
	t.push_back(-0.52553242);
	t.push_back(-0.18343464);
	t.push_back(0.18343464);
	t.push_back(0.52553242);
	t.push_back(0.79666648);
	t.push_back(0.96028986);

	// �������� ����� �������������� ����������
	countSplit = new std::vector<int>;
	resultSplit = new std::vector<double>;
}

SolutionIntegrals::~SolutionIntegrals()
{
	// ������� ������
	delete countSplit;
	delete resultSplit;
}

// ����� �������� (����� �������)
void SolutionIntegrals::SimpsonMethod(Function ourFunction)
{
	// ������� �������������� ����������
	clear();

	// �������������� ��������� (n)
	numberSplits = 2;

	if (beginSegment == endSegment)
	{
		resultSolutionIntegral = 0;

		show();

		return;
	}

	// ��������� ��� (h)
	countSteps = (endSegment - beginSegment) / numberSplits;

	// ��������� ����������
	double IPrev(0), INext(0);

	do
	{
		IPrev = SimpsonFormula(ourFunction, numberSplits);
		INext = SimpsonFormula(ourFunction, numberSplits * 2);

		std::cout << std::endl << std::endl
			<< "------------------------------" << std::endl
			<< "���������� ���������: " << numberSplits * 2
			<< std::endl << std::endl
			<< "��������� ��� ����� ���������� ���������: "
			<< std::setprecision(coutNumber) << INext;

		// ���������� �������������� ���������
		countSplit->push_back(numberSplits);
		resultSplit->push_back(INext);

		// ����������� ���������� ��������� � ��� ����
		numberSplits *= 2;

		// ��������� ����� ��� (h)
		countSteps = (endSegment - beginSegment) / numberSplits;

	} while ((std::fabs(INext - IPrev) / 15.) > precision);

	std::cout << std::endl << "------------------------------";

	// ���������� ������ ����������
	resultSolutionIntegral = INext;

	// ����� �����������
	show();
}

// ����� ������
void SolutionIntegrals::GaussMethod(Function ourFunction)
{
	// ������� �������������� ����������
	clear();

	// �������������� ��������� (n)
	numberSplits = 2;

	if (beginSegment == endSegment)
	{
		resultSolutionIntegral = 0;

		show();

		return;
	}

	// ��������� ����������
	double IPrev(0), INext(0);

	do
	{
		IPrev = GaussFormula(ourFunction, numberSplits);
		INext = GaussFormula(ourFunction, numberSplits * 2);

		std::cout << std::endl << std::endl
			<< "------------------------------" << std::endl
			<< "���������� ���������: " << numberSplits * 2
			<< std::endl << std::endl
			<< "��������� ��� ����� ���������� ���������: "
			<< std::setprecision(coutNumber) << INext;

		// ���������� �������������� ���������
		countSplit->push_back(numberSplits);
		resultSplit->push_back(INext);

		// ����������� ���������� ��������� � ��� ����
		numberSplits *= 2;

	} while (((std::fabs(INext - IPrev) / 15.) > precision) && numberSplits * 2 <= 8);

	std::cout << std::endl << "------------------------------";

	// ���������� ������ ����������
	resultSolutionIntegral = INext;

	// ����� �����������
	show();
}

void SolutionIntegrals::show()
{

	std::cout << std::endl << std::endl
		<< "������������� ��������� ���������� ��������������: "
		<< std::setprecision(coutNumber)
		<< resultSolutionIntegral << std::endl
		<< std::endl;

}

void SolutionIntegrals::clear()
{
	countSplit->clear();
	resultSplit->clear();
}

double SolutionIntegrals::getResultSolutionIntegral() const
{
	return resultSolutionIntegral;
}

std::vector<int>* SolutionIntegrals::getCountSplit() const
{
	return countSplit;
}

std::vector<double>* SolutionIntegrals::getResultSplit() const
{
	return resultSplit;
}

// ������� ��������
double SolutionIntegrals::SimpsonFormula(Function ourFunction, int N)
{
	// ���������� ���������� ������ ������� ��������
	double resultSimpsonFormula(0);

	// ��������� ���������� �����
	double tmpSum(0);

	// ���������� ����
	double h = (endSegment - beginSegment) / N;

	// ��������� ����� �� ������ �������
	resultSimpsonFormula = (ourFunction(beginSegment) + ourFunction(endSegment));

	// ��������� ������ �����
	for (int i = 1; i <= (N / 2); i++)
	{
		tmpSum += ourFunction(beginSegment + h * (2 * i - 1));
	}

	// ����������� ��������� ������ ���������
	tmpSum *= 4;
	resultSimpsonFormula += tmpSum;

	// ��������� ������ ���������
	tmpSum = 0;

	for (int i = 2; i <= (N / 2); i++)
	{
		tmpSum += ourFunction(beginSegment + h * (2 * i - 2));
	}

	// ����������� ��������� ������ ���������
	tmpSum *= 2;
	resultSimpsonFormula += tmpSum;

	resultSimpsonFormula *= (h / 3.);

	return resultSimpsonFormula;
}

double SolutionIntegrals::GaussFormula(Function ourFunction, int N)
{
	// ��������� ����������
	double resultGaussFormula(0);

	// ������������
	for (int i = 0; i < N; i++)
	{
		resultGaussFormula += A[i] * ourFunction((beginSegment + endSegment) / 2 + ((endSegment - beginSegment) / 2) * t[i]);
	}


	resultGaussFormula *= (endSegment - beginSegment) / 2;

	return resultGaussFormula;
}
