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
}

SolutionIntegrals::~SolutionIntegrals()
{}

// ����� �������� (����� �������)
void SolutionIntegrals::SimpsonMethod(Function ourFunction)
{
	// �������������� ��������� (n)
	numberSplits = 4;

	if (beginSegment == endSegment)
	{
		resultSolutionIntegral = 0;

		show();

		return;
	}

	// ��������� ��� (h)
	countSteps = (endSegment - beginSegment) / numberSplits;

	// ��������� ����������
	double IPrev(0), INext(0), tmpSum(0);

	do
	{
		IPrev = SimpsonFormula(ourFunction, numberSplits);
		INext = SimpsonFormula(ourFunction, numberSplits * 2);

		std::cout << std::endl << std::endl
			<< "------------------------------" << std::endl
			<< "���������� ���������: " << numberSplits
			<< std::endl << std::endl
			<< "��������� ��� ����� ���������� ���������: "
			<< std::setprecision(coutNumber) << INext;

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
	// ��������� ����������
	double tmpSum(0);

	// ������������
	for (int i = 0; i < A.size(); i++)
	{
		tmpSum += A[i] * ourFunction((beginSegment + endSegment) / 2 + ((endSegment - beginSegment) / 2) * t[i]);
	}


	tmpSum *= (endSegment - beginSegment) / 2;

	resultSolutionIntegral = tmpSum;

	// �����
	show();
}

void SolutionIntegrals::show()
{
	/*char select('Y');

	std::cout << std::endl << std::endl << "������ �����?(Y/N): ";
	std::cin >> select;

	if (select == 'N')
		return;*/

	std::cout << std::endl << std::endl
		<< "������������� ��������� ���������� ��������������: "
		<< std::setprecision(coutNumber)
		<< resultSolutionIntegral << std::endl
		<< std::endl;

}

double SolutionIntegrals::getResultSolutionIntegral() const
{
	return resultSolutionIntegral;
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
