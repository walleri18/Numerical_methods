#include "SolutionEquation.h"
#include <iostream>
#include <iomanip>

SolutionEquation::SolutionEquation(double beginSegment,
								   double endSegment,
								   double precision, int coutNumber) : 
	precision(precision), xNext(0), xPrev(0), iteration(0),
	QSimpleIterationMethod(0), isQ(false), coutNumber(coutNumber)
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

	iterationVector = new std::vector<double>();

	std::cout << "�������� [" << this->beginSegment << "; " << this->endSegment << "]" << std::endl
		<< "�������� " << this->precision << std::endl
		<< "���������� ������ ����� ����� " << coutNumber << std::endl << std::endl
		<< "������ � �������� �������� ��������!!!";
}

SolutionEquation::~SolutionEquation()
{
	delete iterationVector;
}

void SolutionEquation::NewtonMethod(Function ourFunction, Function firstDerivativeOurFunction, Function
									secondDerivativeOurFunction)
{
	// ������� �� ���������� ��������� ��������
	clearIteration();

	// �������� �� ������������� �����
	if (!isRootNewtonMethod(ourFunction))
	{
		std::cout << std::endl 
			<< "��� ������ �� ���� ��������� ���� �� ������ ������ ["
			<< beginSegment << ", " << endSegment << "] "
			<< std::endl;

		return;
	}

	// ���� ��������� �����
	xPrev = findStartingPointNewtonMethod(ourFunction, secondDerivativeOurFunction);

	// ������� ������ �����������
	xNext = xPrev - ourFunction(xPrev) 
		/ firstDerivativeOurFunction(xPrev);

	// ����������� ���������� ��������
	iteration++;

	// ������� ������ � ������
	iterationVector->push_back(xNext);

	while (std::fabs(xPrev - xNext) > precision)
	{
		xPrev = xNext;

		xNext = xPrev - ourFunction(xPrev)
			/ firstDerivativeOurFunction(xPrev);

		iteration++;

		iterationVector->push_back(xNext);

	}

	// �����
	show();
}

void SolutionEquation::SimpleIterationMethod(Function newOurFunction, Function firstDerivativeNewOurFunction, double argument)
{
	// ������� �� ���������� ��������� ��������
	clearIteration();

	// �������� �� ����������������� ������� ������
	if (!isJobSimpleIterationMethod(firstDerivativeNewOurFunction))
	{
		std::cout << std::endl << std::endl << "����� ������ �������� �� ������ ������� [" << beginSegment << "; " << endSegment << "] �� ���������." << std::endl << "����� ������ �� ������ ������� ��� ������� ��������� ���� ������� �� �������������� ���������.";

		return;
	}

	// ��������� �����������
	xPrev = argument;

	iterationVector->push_back(xPrev);

	iteration++;

	xNext = newOurFunction(xPrev);

	// ������� ������ � ������
	iterationVector->push_back(xNext);

	iteration++;

	while (std::fabs(xNext - xPrev) > (precision * (1 - QSimpleIterationMethod) / QSimpleIterationMethod))
	{
		xPrev = xNext;

		// ���������� ��������
		xNext = newOurFunction(xPrev);

		// ����������� ���������� ��������
		iteration++;

		// ������� ������ � ������
		iterationVector->push_back(xNext);

	}

	// �����
	show();
}

void SolutionEquation::HalfDivisionMethod(Function ourFunction)
{
	// �������
	clearIteration();

	// ����������� ���������� ��� ������� ������
	double begin(beginSegment), end(endSegment), X(0);

	// �������� �� ����������������� ������� ������
	if (!(ourFunction(begin) * ourFunction(end) < 0))
	{
		std::cout << std::endl << std::endl << "����� ������� �� ������ ������� [" << beginSegment << "; " << endSegment << "] �� ���������." << std::endl << "����� ������ �� ������ ������� ��� ������� ��������� ���� ������� �� �������������� ���������.";

		return;
	}

	do
	{

		// ���������� ��������
		X = (begin + end) / 2;

		// ���������� ���������� ��������
		iteration++;

		// ���������� ������ ��������
		iterationVector->push_back(X);

		if (ourFunction(begin) * ourFunction(X) < 0)
			end = X;

		else
			begin = X;


	} while ((end - begin) > precision);

	// �����
	show();
}

void SolutionEquation::DichotomyMethod(Function ourFunction)
{
	// �������
	clearIteration();

	// ����������� ���������� ��� ������� ������
	double begin(beginSegment), end(endSegment), X(0);

	// �������� �� ����������������� ������� ������
	if (!(ourFunction(begin) * ourFunction(end) < 0))
	{
		std::cout << std::endl << std::endl << "����� ���� �� ������ ������� [" << beginSegment << "; " << endSegment << "] �� ���������." << std::endl << "����� ������ �� ������ ������� ��� ������� ��������� ���� ������� �� �������������� ���������.";

		return;
	}

	do
	{

		// ���������� ��������
		X = begin - (ourFunction(begin) * (end - begin)) / (ourFunction(end) - ourFunction(begin));

		// ���������� ���������� ��������
		iteration++;

		// ���������� ������ ��������
		iterationVector->push_back(X);

		if (ourFunction(begin) * ourFunction(X) < 0)
			end = X;

		else
			begin = X;


	} while ((end - begin) > precision);

	// �����
	show();
}

void SolutionEquation::clearIteration()
{
	this->iteration = 0;

	iterationVector->clear();
}

std::vector<double>* SolutionEquation::getData() const
{
	return iterationVector;
}

void SolutionEquation::show()
{
	char select('Y');

	std::cout << std::endl << std::endl << "������ �����?(Y/N): ";
	std::cin >> select;

	if (select == 'N')
		return;

	// ����� ���� ��������
	for (int i = 0; i < iterationVector->size(); i++)
	{
		std::cout << std::endl << "�������� #" << i + 1
			<< ": " << std::setprecision(coutNumber) << (*iterationVector)[i];
	}

	// ����� ������ �����
	std::cout << std::endl << std::endl << "������ = "
		<< std::setprecision(coutNumber) << (*iterationVector)[iteration - 1] << std::endl;
}

bool SolutionEquation::isRootNewtonMethod(Function ourFunction)
{
	return ((ourFunction(beginSegment)
			 * ourFunction(endSegment) > 0) ? 
			false : true);
}

double SolutionEquation::findStartingPointNewtonMethod(Function ourFunction, Function secondDerivativeOurFunction)
{
	if (ourFunction(beginSegment) *
		secondDerivativeOurFunction(beginSegment) > 0)
		return beginSegment;

	else if (ourFunction(endSegment) * secondDerivativeOurFunction(endSegment) > 0)
		return endSegment;

	else
	{
		for (double x = beginSegment + 0.1; x < endSegment; x += 0.1)
			if (ourFunction(x) * secondDerivativeOurFunction(x) > 0)
				return x;
	}
}

bool SolutionEquation::isJobSimpleIterationMethod(Function firstDerivativeNewOurFunction)
{
	// ��� ������ ���� �������� Q
	findQSimpleIterationMethod(firstDerivativeNewOurFunction);

	// ���� Q �� ��������
	if (!isQ)
		return false;

	// ��������� ������� ���������� ������ ������� ��������
	for (double x = beginSegment; x <= endSegment; x += 0.1)
	{
		if (std::fabs(firstDerivativeNewOurFunction(x)) > QSimpleIterationMethod)
			return false;
	}

	// ���� ���, �� ����� �������� � ������ ������
	return true;
}

void SolutionEquation::findQSimpleIterationMethod(Function firstDerivativeNewOurFunction)
{
	// ������ ��������
	QSimpleIterationMethod = DBL_MIN;

	// ���� ������������ ��������
	for (double x = beginSegment; x <= endSegment; x += 0.1)
	{
		if ((std::fabs(firstDerivativeNewOurFunction(x)) < 1) > QSimpleIterationMethod)
		{
			QSimpleIterationMethod = std::fabs(firstDerivativeNewOurFunction(x));

			isQ = true;
		}
	}
}