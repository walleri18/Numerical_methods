#include "SolutionEquation.h"
#include <iostream>

SolutionEquation::SolutionEquation(double beginSegment,
								   double endSegment,
								   double precision) : 
	precision(precision), xNext(0), xPrev(0), iteration(0),
	QSimpleIterationMethod(0), isQ(false)
{
	// Если пользователь перепутал один конец отрезка с другим
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
	// Очистка от предыдущих итерациях итераций
	clearIteration();

	// Проверка на существования корня
	if (!isRootNewtonMethod(ourFunction))
	{
		std::cout << std::endl 
			<< "Нет корней на этом интервале либо их больше одного ["
			<< beginSegment << ", " << endSegment << "] "
			<< std::endl;

		return;
	}

	// Ищем начальную точку
	xPrev = findStartingPointNewtonMethod(ourFunction, secondDerivativeOurFunction);

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

void SolutionEquation::SimpleIterationMethod(Function newOurFunction, Function firstDerivativeNewOurFunction, double argument)
{
	// Очистка от предыдущих итерациях итераций
	clearIteration();

	// Проверка на работоспособность данного метода
	if (!isJobSimpleIterationMethod(firstDerivativeNewOurFunction))
	{
		std::cout << std::endl << std::endl << "Метод просты итераций на данном отрезке [" << beginSegment << "; " << endSegment << "] не сходиться." << std::endl << "Найти корень на данном отрезке для данного уравнения этим методом не представляется возможным.";

		return;
	}

	// Начальное приближение
	xPrev = argument;

	iterationVector->push_back(xPrev);

	iteration++;

	xNext = newOurFunction(xPrev);

	// Заносим данные в вектор
	iterationVector->push_back(xNext);

	iteration++;

	while (std::fabs(xNext - xPrev) > (precision * (1 - QSimpleIterationMethod) / QSimpleIterationMethod))
	{
		xPrev = xNext;

		// Выполнение итерации
		xNext = newOurFunction(xPrev);

		// Увеличиваем количество итераций
		iteration++;

		// Заносим данные в вектор
		iterationVector->push_back(xNext);

	}

	// Вывод
	show();
}

void SolutionEquation::HalfDivisionMethod(Function ourFunction)
{
	// Очистка
	clearIteration();

	// Необходимые переменные для данного метода
	double begin(beginSegment), end(endSegment), X(0);

	// Проверка на работоспособность данного метода
	if (!(ourFunction(begin) * ourFunction(end) < 0))
	{
		std::cout << std::endl << std::endl << "Метод Деления на данном отрезке [" << beginSegment << "; " << endSegment << "] не сходиться." << std::endl << "Найти корень на данном отрезке для данного уравнения этим методом не представляется возможным.";

		return;
	}

	do
	{

		// Выполнение итерации
		X = (begin + end) / 2;

		// Увеличение количества итераций
		iteration++;

		// Сохранение данной итерации
		iterationVector->push_back(X);

		if (ourFunction(begin) * ourFunction(X) < 0)
			end = X;

		else
			begin = X;


	} while ((end - begin) > precision);

	// Вывод
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
	char select('Y');

	std::cout << std::endl << std::endl << "Начать вывод?(Y/N): ";
	std::cin >> select;

	if (select == 'N')
		return;

	// Вывод всех операций
	for (int i = 0; i < iterationVector->size(); i++)
	{
		std::cout << std::endl << "Итерация #" << i + 1
			<< ": " << (*iterationVector)[i];
	}

	// Вывод самого корня
	std::cout << std::endl << std::endl << "Корень = "
		<< (*iterationVector)[iteration - 1] << std::endl;
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
	// Для начала ищем величину Q
	findQSimpleIterationMethod(firstDerivativeNewOurFunction);

	// Если Q не найденно
	if (!isQ)
		return false;

	// Проверяем условие сходимости метода Простых итераций
	for (double x = beginSegment; x <= endSegment; x += 0.1)
	{
		if (std::fabs(firstDerivativeNewOurFunction(x)) > QSimpleIterationMethod)
			return false;
	}

	// Если так, то метод работает в данном случае
	return true;
}

void SolutionEquation::findQSimpleIterationMethod(Function firstDerivativeNewOurFunction)
{
	// Первое значение
	QSimpleIterationMethod = DBL_MIN;

	// Ищем максимальное значение
	for (double x = beginSegment; x <= endSegment; x += 0.1)
	{
		if ((std::fabs(firstDerivativeNewOurFunction(x)) < 1) > QSimpleIterationMethod)
		{
			QSimpleIterationMethod = std::fabs(firstDerivativeNewOurFunction(x));

			isQ = true;
		}
	}
}