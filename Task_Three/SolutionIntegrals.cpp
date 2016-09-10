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

	std::cout << "Интервал [" << this->beginSegment << "; " << this->endSegment << "]" << std::endl
		<< "Количество знаков после точки " << coutNumber << std::endl << std::endl
		<< "ОТВЕТЫ В ПРЕДЕЛАХ МАШИННОЙ ТОЧНОСТИ!!!";

	// Установление коэффициентов квадратурной формулы
	A.push_back(0.10122854);
	A.push_back(0.22238104);
	A.push_back(0.31370664);
	A.push_back(0.36268378);
	A.push_back(0.36268378);
	A.push_back(0.31370664);
	A.push_back(0.22238104);
	A.push_back(0.10122854);

	// Установление Нулей полинома Лежандра
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

void SolutionIntegrals::SimpsonMethod(Function ourFunction)
{
	//// Рассчитаем шаг
	//countSteps = (endSegment - beginSegment) / numberSplits;

	///*
	//	Заведём временные переменные для расчёта
	//*/
	//// Для позиции
	//double X(beginSegment);

	//// Для результата вычисления
	//double F = ourFunction(X);

	//// Для подсчёта номера разбиения
	//int numberIteration(1);

	//// Первое приближение
	//resultSolutionIntegral = F;

	//while (true)
	//{
	//	// Вычисление в новой позиции
	//	X += countSteps;

	//	// Вычисление функции в новой позиции
	//	F = ourFunction(X);

	//	// Следующее вычисление приближения
	//	resultSolutionIntegral += 4 * F;

	//	// Следующее разбиение
	//	numberIteration += 2;

	//	if (numberIteration >= numberSplits)
	//		break;

	//	else
	//	{
	//		// Следующая позиция
	//		X += countSteps;

	//		// Вычисление функции в новой позиции
	//		F = ourFunction(X);

	//		// Следующее вычисление приближения
	//		resultSolutionIntegral += 2 * F;
	//	}
	//}

	///*
	//	Конечные расчёты
	//*/
	//// Последняя позиция
	//X = endSegment;

	//// Последнее вычисление функции
	//F = ourFunction(X);

	//// Последнее вычисление приближения
	//resultSolutionIntegral = (resultSolutionIntegral + F)
	//	* (countSteps / 3);

	/*
		Альтернативное решение
	*/
	/*countSteps = (endSegment - beginSegment) / numberSplits;

	resultSolutionIntegral = 0;

	double x0 = beginSegment;
	double x1 = endSegment + countSteps;

	for (unsigned i = 0; i <= numberSplits - 1; i++) {
		resultSolutionIntegral += ourFunction(x0) + 4 * ourFunction(x0 + countSteps / 2) + ourFunction(x1);

		x0 += countSteps;
		x1 += countSteps;
	}

	resultSolutionIntegral = (countSteps / 6) * resultSolutionIntegral;*/

	/*
		Второе альтернативное решение
	*/
	// Первоначальное разбиение (n)
	numberSplits = 4;

	if (beginSegment == endSegment)
	{
		resultSolutionIntegral = 0;

		show();

		return;
	}

	// Вычисляем шаг (h)
	countSteps = (endSegment - beginSegment) / numberSplits;

	// Временные переменные
	double IPrev(0), INext(0), tmpSum(0);

	do
	{
		// Начальная установка
		IPrev = INext;
		INext = 0;

		// Вычисляем сумму на концах отрезка
		INext = (ourFunction(beginSegment)
				 + ourFunction(endSegment));

		// Вычисляем первую сумму
		for (int i = 1; i <= (numberSplits / 2); i++)
		{
			tmpSum += ourFunction(beginSegment
								  + countSteps * (2 * i - 1));
		}

		// Заканчиваем вычислять второе слагаемое
		tmpSum *= 4;
		INext += tmpSum;

		// Вычисляем третье слагаемое
		tmpSum = 0;

		for (int i = 2; i <= (numberSplits / 2); i++)
		{
			tmpSum += ourFunction(beginSegment + countSteps * (2 * i - 2));
		}

		// Заканчиваем вычислять третье слагаемое
		tmpSum *= 2;
		INext += tmpSum;

		INext *= (countSteps / 3);

		std::cout << std::endl << std::endl
			<< "------------------------------" << std::endl
			<< "Количество разбиений: " << numberSplits
			<< std::endl << std::endl
			<< "Результат для этого количества разбиений: "
			<< std::setprecision(coutNumber) << INext;

		// Увеличиваем количество разбиений в два раза
		numberSplits *= 2;

		// Вычисляем шаг новый шаг (h)
		countSteps = (endSegment - beginSegment) / numberSplits;

	} while (std::fabs(INext - IPrev) < precision);

	std::cout << std::endl << "------------------------------";

	// Присвоение нового результата
	resultSolutionIntegral = INext;

	// Вывод результатов
	show();
}

void SolutionIntegrals::GaussMethod(Function ourFunction)
{
	// Временные переменные
	double tmpSum(0);

	for (int i = 0; i < A.size(); i++)
	{
		tmpSum += A[i] * ourFunction((beginSegment + endSegment) / 2 + ((endSegment - beginSegment) / 2) * t[i]);
	}

	tmpSum *= (endSegment - beginSegment) / 2;

	resultSolutionIntegral = tmpSum;

	// Вывод
	show();
}

void SolutionIntegrals::show()
{
	/*char select('Y');

	std::cout << std::endl << std::endl << "Начать вывод?(Y/N): ";
	std::cin >> select;

	if (select == 'N')
		return;*/

	std::cout << std::endl << std::endl
		<< "Окончательный результат численного интегрирования: "
		<< std::setprecision(coutNumber)
		<< resultSolutionIntegral << std::endl
		<< std::endl;

}