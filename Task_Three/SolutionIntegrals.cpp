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

	// Создание наших дополнительных параметров
	countSplit = new std::vector<int>;
	resultSplit = new std::vector<double>;
}

SolutionIntegrals::~SolutionIntegrals()
{
	// Очистка памяти
	delete countSplit;
	delete resultSplit;
}

// Метод Симпсона (метод парабол)
void SolutionIntegrals::SimpsonMethod(Function ourFunction)
{
	// Очистка дополнительных параметров
	clear();

	// Первоначальное разбиение (n)
	numberSplits = 2;

	if (beginSegment == endSegment)
	{
		resultSolutionIntegral = 0;

		show();

		return;
	}

	// Вычисляем шаг (h)
	countSteps = (endSegment - beginSegment) / numberSplits;

	// Временные переменные
	double IPrev(0), INext(0);

	do
	{
		IPrev = SimpsonFormula(ourFunction, numberSplits);
		INext = SimpsonFormula(ourFunction, numberSplits * 2);

		std::cout << std::endl << std::endl
			<< "------------------------------" << std::endl
			<< "Количество разбиений: " << numberSplits * 2
			<< std::endl << std::endl
			<< "Результат для этого количества разбиений: "
			<< std::setprecision(coutNumber) << INext;

		// Записываем дополнительные параметры
		countSplit->push_back(numberSplits);
		resultSplit->push_back(INext);

		// Увеличиваем количество разбиений в два раза
		numberSplits *= 2;

		// Вычисляем новый шаг (h)
		countSteps = (endSegment - beginSegment) / numberSplits;

	} while ((std::fabs(INext - IPrev) / 15.) > precision);

	std::cout << std::endl << "------------------------------";

	// Присвоение нового результата
	resultSolutionIntegral = INext;

	// Вывод результатов
	show();
}

// Метод Гаусса
void SolutionIntegrals::GaussMethod(Function ourFunction)
{
	// Очистка дополнительных параметров
	clear();

	// Первоначальное разбиение (n)
	numberSplits = 2;

	if (beginSegment == endSegment)
	{
		resultSolutionIntegral = 0;

		show();

		return;
	}

	// Временные переменные
	double IPrev(0), INext(0);

	do
	{
		IPrev = GaussFormula(ourFunction, numberSplits);
		INext = GaussFormula(ourFunction, numberSplits * 2);

		std::cout << std::endl << std::endl
			<< "------------------------------" << std::endl
			<< "Количество разбиений: " << numberSplits * 2
			<< std::endl << std::endl
			<< "Результат для этого количества разбиений: "
			<< std::setprecision(coutNumber) << INext;

		// Записываем дополнительные параметры
		countSplit->push_back(numberSplits);
		resultSplit->push_back(INext);

		// Увеличиваем количество разбиений в два раза
		numberSplits *= 2;

	} while (((std::fabs(INext - IPrev) / 15.) > precision) && numberSplits * 2 <= 8);

	std::cout << std::endl << "------------------------------";

	// Присвоение нового результата
	resultSolutionIntegral = INext;

	// Вывод результатов
	show();
}

void SolutionIntegrals::show()
{

	std::cout << std::endl << std::endl
		<< "Окончательный результат численного интегрирования: "
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

// Формула Симпсона
double SolutionIntegrals::SimpsonFormula(Function ourFunction, int N)
{
	// Переменная результата работы формулы Симпсона
	double resultSimpsonFormula(0);

	// Временная переменная суммы
	double tmpSum(0);

	// Переменная шага
	double h = (endSegment - beginSegment) / N;

	// Вычисляем сумму на концах отрезка
	resultSimpsonFormula = (ourFunction(beginSegment) + ourFunction(endSegment));

	// Вычисляем первую сумму
	for (int i = 1; i <= (N / 2); i++)
	{
		tmpSum += ourFunction(beginSegment + h * (2 * i - 1));
	}

	// Заканчиваем вычислять второе слагаемое
	tmpSum *= 4;
	resultSimpsonFormula += tmpSum;

	// Вычисляем третье слагаемое
	tmpSum = 0;

	for (int i = 2; i <= (N / 2); i++)
	{
		tmpSum += ourFunction(beginSegment + h * (2 * i - 2));
	}

	// Заканчиваем вычислять третье слагаемое
	tmpSum *= 2;
	resultSimpsonFormula += tmpSum;

	resultSimpsonFormula *= (h / 3.);

	return resultSimpsonFormula;
}

double SolutionIntegrals::GaussFormula(Function ourFunction, int N)
{
	// Временные переменные
	double resultGaussFormula(0);

	// Суммирование
	for (int i = 0; i < N; i++)
	{
		resultGaussFormula += A[i] * ourFunction((beginSegment + endSegment) / 2 + ((endSegment - beginSegment) / 2) * t[i]);
	}


	resultGaussFormula *= (endSegment - beginSegment) / 2;

	return resultGaussFormula;
}
