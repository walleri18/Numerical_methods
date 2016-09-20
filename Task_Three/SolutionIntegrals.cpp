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

#ifdef DEBUG

	std::cout << "�������� [" << this->beginSegment << "; " << this->endSegment << "]" << std::endl
		<< "���������� ������ ����� ����� " << coutNumber << std::endl << std::endl
		<< "������ � �������� �������� ��������!!!";

#endif // DEBUG

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

	// ������ �����������
	std::vector<double> resultIntegral(vectorSegment.size());

	// ������� �����������
	for (int i = 0; i < vectorSegment.size(); ++i)
	{

		// �������������� ��������� (n)
		numberSplits = 4;
		
		// ��������� ����������
		double IPrev(0), INext(0);

		// ���� ��������� ��� �� ������ ����� � ����
		bool first(true);

		do
		{
			if (first)
			{
				IPrev = SimpsonFormula(ourFunction, numberSplits, vectorSegment[i].beginSegment, vectorSegment[i].endSegment);
				first = false;
			}
			else
				IPrev = INext;

			INext = SimpsonFormula(ourFunction, numberSplits * 2, vectorSegment[i].beginSegment, vectorSegment[i].endSegment);

#ifdef DEBUG

			std::cout << std::endl << std::endl
				<< "------------------------------" << std::endl
				<< "���������� ���������: " << numberSplits * 2
				<< std::endl << std::endl
				<< "��������� ��� ����� ���������� ���������: "
				<< std::setprecision(coutNumber) << INext;

			// ���������� �������������� ���������
			countSplit->push_back(numberSplits * 2);
			resultSplit->push_back(INext);

#endif // DEBUG

			// ����������� ���������� ��������� � ��� ����
			numberSplits *= 2;

			// ����������� � ���������� ���������
			if (numberSplits >= INT_MAX)
				break;

		} while ((std::fabs(INext - IPrev) / 15.) > precision);

		//std::cout << std::endl << "------------------------------";

		// ���������� ������ ����������
		resultIntegral.push_back(INext);

	}

	// ��������� ����� ����������
	double tmpSumIntegral(0);

	// ���������
	for (int i = 0; i < resultIntegral.size(); i++)
	{
		tmpSumIntegral += resultIntegral[i];
	}

	resultSolutionIntegral = tmpSumIntegral;

	// ����� �����������
	show();
}

// ����� ������
void SolutionIntegrals::GaussMethod(Function ourFunction)
{
	// ������� �������������� ����������
	clear();

	// �������������� ��������� (n)
	numberSplits = 8;

	// ������ ����������� ����������
	std::vector<double> resultIntegral;

	int tmp = vectorSegment.size();

	// ������� ����������
	for (int i = 0; i < vectorSegment.size(); ++i)
	{
		resultIntegral.push_back(GaussFormula(ourFunction, numberSplits, vectorSegment[i].beginSegment, vectorSegment[i].endSegment));
	}

	// ��������� ���������� ����� ����������
	double tmpSumIntegral(0);

	// �������� ����� ���������
	for (int i = 0; i < resultIntegral.size(); i++)
	{
		tmpSumIntegral += resultIntegral[i];
	}
	
	// ���������� ���������� �������
	resultSolutionIntegral = tmpSumIntegral;

	// ����� �����������
	show();
}

void SolutionIntegrals::show()
{
#ifdef DEBUG
	std::cout << std::endl << std::endl
		<< "������������� ��������� ���������� ��������������: "
		<< std::setprecision(coutNumber)
		<< resultSolutionIntegral << std::endl
		<< std::endl;
#endif // DEBUG
}

void SolutionIntegrals::clear()
{
	countSplit->clear();
	resultSplit->clear();
	resultSolutionIntegral = 0;

	// �������
	vectorSegment.clear();

	// ��������� �� ��������� ��������
	vectorSegment.push_back(Segment(beginSegment, -0.5));
	vectorSegment.push_back(Segment(-0.5, -0.3));
	vectorSegment.push_back(Segment(-0.3, -0.1));
	vectorSegment.push_back(Segment(-0.1, -0.01));
	vectorSegment.push_back(Segment(0.01, 0.1));
	vectorSegment.push_back(Segment(0.1, 0.5));
	vectorSegment.push_back(Segment(0.5, endSegment));
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

// ������
void SolutionIntegrals::setEndSegment(double newEndSegment)
{
	this->endSegment = newEndSegment;
}

// ������� ��������
double SolutionIntegrals::SimpsonFormula(Function ourFunction, unsigned int N, double beginSegment, double endSegment)
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
	for (unsigned int i = 1; i <= (N / 2); i++)
	{
		tmpSum += ourFunction(beginSegment + h * (2 * i - 1));
	}

	// ����������� ��������� ������ ���������
	tmpSum *= 4;
	resultSimpsonFormula += tmpSum;

	// ��������� ������ ���������
	tmpSum = 0;

	for (unsigned int i = 2; i <= (N / 2); i++)
	{
		tmpSum += ourFunction(beginSegment + h * (2 * i - 2));
	}

	// ����������� ��������� ������ ���������
	tmpSum *= 2;
	resultSimpsonFormula += tmpSum;

	resultSimpsonFormula *= (h / 3.);

	return resultSimpsonFormula;
}

double SolutionIntegrals::GaussFormula(Function ourFunction, unsigned int N, double beginSegment, double endSegment)
{
	// ��������� ����������
	double resultGaussFormula(0);

	// ������������
	for (unsigned int i = 0; i < N; i++)
	{
		resultGaussFormula += A[i] * ourFunction((beginSegment + endSegment)
												 / 2 + ((endSegment - beginSegment) / 2) * t[i]);
	}


	resultGaussFormula *= (endSegment - beginSegment) / 2;

	return resultGaussFormula;
}

// ������� �������� 
double SolutionIntegrals::ExpIntegrateEi(double X)
{
	// ������� ����������
	long double Factorial(int n);

	double resultExpIntegrateEi(1);

	resultExpIntegrateEi = C + log(X);

	// ��������� ���������� �����
	long double tmpSum(0);

	for (int n = 1; n <= 5 * (int)((X / 2) + 0.5); n++)
	{
		tmpSum += (pow(X, n)) / (Factorial(n) * (long double)(n));
	}

	resultExpIntegrateEi += tmpSum;

	return resultExpIntegrateEi;
}

// ������� ����������
long double Factorial(int n)
{
	long double tmpResult(1);

	if (n == 0)
		return tmpResult;

	else
	{
		for (int i = n; i >= 1; i--)
		{
			tmpResult *= i;
		}

		return tmpResult;
	}
}