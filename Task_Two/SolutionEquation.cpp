#include "SolutionEquation.h"
#include <iostream>

SolutionEquation::SolutionEquation(double beginSegment,
								   double endSegment,
								   double precision) : 
	precision(precision), xNext(0), xPrev(0), iteration(0)
{
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
}

SolutionEquation::~SolutionEquation()
{
	delete iterationVector;
}

void SolutionEquation::NewtonMethod()
{
	if (!isRoot())
	{
		std::cout << std::endl << "No roots in this interval ["
			<< beginSegment << ", " << endSegment << "] "
			<< std::endl;

		return;
	}

	// ���� ��������� �����
	xPrev = findStartingPoint();

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
	// ����� ���� ��������
	for (int i = 0; i < iterationVector->size(); i++)
	{
		std::cout << std::endl << "Iteration #" << i + 1
			<< ": " << (*iterationVector)[i];
	}

	// ����� ������ �����
	std::cout << std::endl << std::endl << "Root = "
		<< (*iterationVector)[iteration - 1] << std::endl;
}

/*
	���� ����� ��� ����� ��������� ����� ������������
*/
double SolutionEquation::ourFunction(double argument)
{
	double resultOurFunction(0);

	resultOurFunction = 3 * std::pow(argument, 2) *
		std::cos(argument) - 1.5 * std::sin(argument) + 0.2;

	return resultOurFunction;
}

/*
	���� ����� ��� ����� ��������� ����� ������������
*/
double SolutionEquation::firstDerivativeOurFunction
(double argument)
{
	double resultFirstDerivativeOurFunction(0);

	resultFirstDerivativeOurFunction = -1.5 *
		std::cos(argument) + 6 * argument *
		std::cos(argument) - 3 * std::pow(argument, 2)
		* std::sin(argument);

	return resultFirstDerivativeOurFunction;
}

/*
	���� ����� ��� ����� ��������� ����� ������������
*/
double SolutionEquation::secondDerivativeOurFunction
(double argument)
{
	double resultSecondDerivativeOurFunction(0);

	resultSecondDerivativeOurFunction = 6 * 
		std::cos(argument) - 3 * std::pow(argument, 2)
		* std::cos(argument) + 1.5 * std::sin(argument)
		- 12 * argument * std::sin(argument);

	return resultSecondDerivativeOurFunction;
}

bool SolutionEquation::isRoot()
{
	return ((ourFunction(beginSegment)
			 * ourFunction(endSegment) > 0) ? 
			false : true);
}

double SolutionEquation::findStartingPoint()
{
	if (ourFunction(beginSegment) *
		secondDerivativeOurFunction(beginSegment) > 0)
		return beginSegment;

	return endSegment;
}
