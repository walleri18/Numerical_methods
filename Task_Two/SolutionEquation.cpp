#include "SolutionEquation.h"
#include <iostream>

SolutionEquation::SolutionEquation(double beginSegment,
								   double endSegment,
								   double precision) : 
	precision(precision), xNext(0), xPrev(0), iteration(0)
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
	if (!isRoot(ourFunction))
	{
		std::cout << std::endl 
			<< "��� ������ �� ���� ��������� ���� �� ������ ������ ["
			<< beginSegment << ", " << endSegment << "] "
			<< std::endl;

		return;
	}

	// ���� ��������� �����
	xPrev = findStartingPoint(ourFunction, secondDerivativeOurFunction);

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

		if (iteration > 10000)
			break;
	}

	// �����
	show();
}

void SolutionEquation::SimpleIterationMethod(Function newOurFunction, double argument)
{
	// ������� �� ���������� ��������� ��������
	clearIteration();

	// ��������� �����������
	xPrev = argument;

	iterationVector->push_back(xPrev);

	iteration++;

	xNext = newOurFunction(xPrev);

	// ������� ������ � ������
	iterationVector->push_back(xNext);

	iteration++;

	while (std::fabs(xNext - xPrev) > precision)
	{
		xPrev = xNext;

		// ���������� ��������
		xNext = newOurFunction(xPrev);

		// ����������� ���������� ��������
		iteration++;

		// ������� ������ � ������
		iterationVector->push_back(xNext);

		// �������� �� ������
		/*if ((xNext < beginSegment) || (xNext > endSegment))
		{
			std::cout << std::endl
				<< "��� ������ �� ���� ��������� ���� �� ������ ������ ["
				<< beginSegment << ", " << endSegment
				<< "] " << std::endl;

			show();

			clearIteration();

			return;
		}*/

		// ����������� �� ���������� ��������
		if (iteration > 10000)
			break;

	}

	// �����
	show();
}

void SolutionEquation::HalfDivisionMethod(Function ourFunction)
{
	// �������
	clearIteration();

	xNext = (beginSegment + endSegment) / 2;

	iteration++;

	iterationVector->push_back(xNext);

	while (std::fabs(ourFunction(xNext)) > precision)
	{
		if (ourFunction(xNext) > 0)
			endSegment = xNext;

		else
			beginSegment = xNext;

		xNext = (beginSegment + endSegment) / 2;

		iteration++;

		iterationVector->push_back(xNext);

		if (iteration > 10000)
			break;
	}

	// �����
	show();
}

void SolutionEquation::DichotomyMethod(Function ourFunction)
{
	while (std::fabs(endSegment - beginSegment) > precision)
	{
		beginSegment = endSegment - (endSegment - beginSegment) 
			* ourFunction(endSegment) / (ourFunction(endSegment) - ourFunction(beginSegment));

		endSegment = beginSegment + (beginSegment - endSegment) 
			* ourFunction(beginSegment) / (ourFunction(beginSegment) - ourFunction(endSegment));

		iteration++;

		iterationVector->push_back(endSegment);

		if (iteration > 10000)
			break;
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
	char select('Y');

	std::cout << std::endl << std::endl << "������ �����?(Y/N): ";
	std::cin >> select;

	if (select == 'N')
		return;

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

bool SolutionEquation::isRoot(Function ourFunction)
{
	return ((ourFunction(beginSegment)
			 * ourFunction(endSegment) > 0) ? 
			false : true);
}

double SolutionEquation::findStartingPoint(Function ourFunction, Function secondDerivativeOurFunction)
{
	if (ourFunction(beginSegment) *
		secondDerivativeOurFunction(beginSegment) > 0)
		return beginSegment;

	return endSegment;
}