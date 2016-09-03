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
	// Очистка от предыдущих итерациях итераций
	clearIteration();

	// Проверка на существования корня
	if (!isRoot())
	{
		std::cout << std::endl 
			<< "Нет корней на этом интервале либо их больше одного ["
			<< beginSegment << ", " << endSegment << "] "
			<< std::endl;

		return;
	}

	// Ищем начальную точку
	xPrev = findStartingPoint();

	// Считаем первое приближение
	xNext = xPrev - ourFunction(xPrev) 
		/ firstDerivativeOurFunction(xPrev);

	// Увеличиваем количество итераций
	iteration++;

	// Заносим данные в вектор
	iterationVector->push_back(xNext);

	while (std::fabs(xPrev - xNext) > precision)
	{
		xPrev = xNext;

		xNext = xPrev - ourFunction(xPrev)
			/ firstDerivativeOurFunction(xPrev);

		iteration++;

		iterationVector->push_back(xNext);
	}

	// Вывод
	show();
}

void SolutionEquation::SimpleIterationMethod()
{
	// Очистка от предыдущих итерациях итераций
	clearIteration();

	// Ищем начальную итерацию
	xNext = (beginSegment + endSegment) / 2.0;

	do
	{

		// Заносим данные в вектор
		iterationVector->push_back(xNext);

		xPrev = xNext;

		// Выполнение итерации
		xNext = newOurFunction(xPrev);

		// Увеличиваем количество итераций
		iteration++;

		// Проверка на ошибку
		if ((xPrev < beginSegment) || (xPrev > endSegment))
		{
			std::cout << std::endl << std::endl
				<< "Нет корней на этом интервале либо их больше одного ["
				<< beginSegment << ", " << endSegment
				<< "] " << std::endl;

			clearIteration();

			return;
		}

	} while (std::fabs(xPrev - xNext) < precision);

	// Вывод
	show();
}

void SolutionEquation::HalfDivisionMethod()
{
	// Очистка
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
	}

	// Вывод
	show();
}

void SolutionEquation::DichotomyMethod()
{
	while (std::fabs(endSegment - beginSegment) > precision)
	{
		beginSegment = endSegment - (endSegment - beginSegment) * ourFunction(endSegment) / (ourFunction(endSegment) - ourFunction(beginSegment));

		endSegment = beginSegment + (beginSegment - endSegment) * ourFunction(beginSegment) / (ourFunction(beginSegment) - ourFunction(endSegment));

		iteration++;

		iterationVector->push_back(endSegment);
	}

	// Вывод
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
	// Вывод всех операций
	for (int i = 0; i < iterationVector->size(); i++)
	{
		std::cout << std::endl << "Iteration #" << i + 1
			<< ": " << (*iterationVector)[i];
	}

	// Вывод самого корня
	std::cout << std::endl << std::endl << "Root = "
		<< (*iterationVector)[iteration - 1] << std::endl;
}

/*
	Этот метод при новом уравнении нужно переписывать
*/
double SolutionEquation::ourFunction(double argument)
{
	double resultOurFunction(0);

	resultOurFunction = 3 * std::pow(argument, 2) *
		std::cos(argument) - 1.5 * std::sin(argument) + 0.2;

	return resultOurFunction;
}

/*
	Этот метод при новом уравнении нужно переписывать
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
	Этот метод при новом уравнении нужно переписывать
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

double SolutionEquation::newOurFunction(double argument)
{
	double resultNewOurFunction(0);

	resultNewOurFunction =
		std::sqrt((1.5 * std::sin(argument) - 0.2)
				  / (3 * std::cos(argument)));

	return resultNewOurFunction;
}
