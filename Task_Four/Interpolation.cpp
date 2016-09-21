#include "Interpolation.h"

Interpolation::Interpolation(Function ourFunction, double beginSegment, double endSegment, int N)
	: ourFunction(ourFunction), beginSegment(beginSegment), endSegment(endSegment), N(N) {}

// ������� ������ ���������� �������
Interpolation::~Interpolation()
{
	// �������� ���� �������� � �������� ���������
	for (int i = 0; i < vectorFiniteDifference.size(); i++)
	{
		// ����� �� ���� ������ ��������� ������ �� �������
		if (!vectorFiniteDifference.empty())
			delete vectorFiniteDifference[i];
	}

	// ������� �� ���� ����������
	vectorFiniteDifference.clear();
}

// ������� ������������ �������
double Interpolation::interpolantBesselFunction(double X)
{
	// �������� Q
	findQ(X, argument[static_cast<int>(findCountNodesIntegration() / 2.)]);

	double resultBessel(0);

	// ������ ��������� �������� �������
	resultBessel += (resultOurFunction[static_cast<int>(findCountNodesIntegration() / 2.)]
					 + resultOurFunction[static_cast<int>(findCountNodesIntegration() / 2.) + 1]) / 2.;

	// ������ ���������
	resultBessel += ((Q - 0.5) * getFiniteDifference(1, 0));

	// ��������� ���������� �����
	double tmpSum(0);

	// �������� �����
	for (int k = 1; k <= N; k++)
	{
		// �������� �������
		double currentPolynom = polynom(Q, k);

		// �������� ��������� 2k
		double factorial2K = Factorial(2 * k);

		// �������� ��������� 2k+1
		double factorial2kPlusOne = Factorial(2 * k + 1);

		// �������� ��������
		double fDiffOne = getFiniteDifference(2 * k, -k);
		double fDiffTwo = getFiniteDifference(2 * k, -k + 1);
		double fDiffThree = getFiniteDifference(2 * k + 1, -k);

		tmpSum += ((currentPolynom / factorial2K) * ((fDiffOne - fDiffTwo) / 2.));

		tmpSum += ((currentPolynom / factorial2kPlusOne) * fDiffThree);
	}

	resultBessel += tmpSum;

	return resultBessel;
}

// ������ ������� N ��������������� ������� �������
void Interpolation::setN(int N)
{
	this->N = (N > 0) ? (N) : (-N);
}

// ������ ������ �������
void Interpolation::setBeginSegment(double beginSegment)
{
	this->beginSegment = beginSegment;
}

// ������ ����� �������
void Interpolation::setEndSegment(double endSegment)
{
	this->endSegment = endSegment;
}

// ������ ���������� ������� (X)
std::vector<double> Interpolation::getArgument() const
{
	return argument;
}

// ������ ����������� ������� (Y)
std::vector<double> Interpolation::getResultOurFunction() const
{
	return resultOurFunction;
}

// ���������� ������� � ���������� ����������� ����������
void Interpolation::update()
{
	// ������� ������ �������
	clear();

	// ������ ��������� ���
	findValueStep();

	// ��������� ��� ���������
	createdArgument();

	// ��������� �������� �������
	createdResultOurFunction();

	// ��������� �������� ��������
	createdFiniteDifference();
}

// ������� �������� � �������������� �������
void Interpolation::clear()
{
	// ������� ������� ���������� �������
	argument.clear();

	// ������� ������� ����������� �������
	resultOurFunction.clear();

	// ������� � ����������� ������ ������� �������� ���������
	if (!vectorFiniteDifference.empty())
		for (int i = 0; i < vectorFiniteDifference.size(); i++)
			delete vectorFiniteDifference[i];
	vectorFiniteDifference.clear();
}

// ������� ����������
long long Interpolation::Factorial(long long n)
{
	long long resultFactorial(1);

	if (n == 1 || n == 0)
		return resultFactorial;

	else
		for (int i = 1; i < n; i++)
			resultFactorial *= i;

	return resultFactorial;
}

// ����� �� �������� ���������� ��� ������� (X)
void Interpolation::createdArgument()
{
	for (int i = 0; i < findCountNodesIntegration(); i++)
		argument.push_back(beginSegment + i * valueStep);
}

// ����� �� �������� ����������� ��� ������� (Y)
void Interpolation::createdResultOurFunction()
{
	for (int i(0); i < argument.size(); i++)
		resultOurFunction.push_back(ourFunction(argument[i]));
}

// ����� �� �������� �������� ���������
void Interpolation::createdFiniteDifference()
{
	// ���������� ������������ ������� ���������
	int maxIndexOrder = findCountNodesIntegration() - 1;

	// �������� ������� ��� ���� �������� ���������
	for (int i = 0; i < maxIndexOrder; i++)
		vectorFiniteDifference.push_back(new std::vector<double>);

	// ��������� ������� �������� �������� ������� �������
	for (int i = 0; i < (resultOurFunction.size() - 1); i++)
		vectorFiniteDifference[0]->push_back(resultOurFunction[i+1]
											 - resultOurFunction[i]);

	// ��������� ��������� �������� ��������
	for (int i = 1; i < vectorFiniteDifference.size(); i++)
	{
		for (int j = 0; j < (vectorFiniteDifference[i - 1]->size() - 1); j++)
			vectorFiniteDifference[i]->push_back((*vectorFiniteDifference[i - 1])[j + 1] - (*vectorFiniteDifference[i - 1])[j]);
	}
}

// ����� �� ���������� �������� Q
void Interpolation::findQ(double X, double xZero)
{
	double resultFindQ(0);

	resultFindQ = (X - xZero) / valueStep;

	Q = resultFindQ;
}

// ����������� ���������� ����� ��������������
int Interpolation::findCountNodesIntegration() const
{
	// N * 2 - ���������� ����� ��������������
	return (N * 2) + 3;
}

// ����������� ���� ��������� (h)
void Interpolation::findValueStep()
{
	valueStep = (endSegment - beginSegment)
		/ findCountNodesIntegration();
}

// ����� ������ ������� ���������
/*
	order - ������� �������� ��������
	number - ����� �������� ��������
*/
double Interpolation::getFiniteDifference(int order, int number) const
{
	double tmpResult(0);

	// ��������� �������� ������ ��������
	/*int realNumber = N + number;*/
	int realNumber = number + static_cast<int>(findCountNodesIntegration() / 2.);

	// ���� ������ ��������
	tmpResult = (*vectorFiniteDifference[order - 1])[realNumber];

	return tmpResult;
}

// ����� ������� ��������
long double Interpolation::polynom(double Q, int K)
{
	long double resultPolynom(1);

	// ������� �������
	for (int i = 0; i <= K; i++)
		resultPolynom *= ((Q - i) * (Q + i - 1));

	return resultPolynom;
}