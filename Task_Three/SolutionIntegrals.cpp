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

#ifdef DEBUG

	std::cout << "Интервал [" << this->beginSegment << "; " << this->endSegment << "]" << std::endl
		<< "Количество знаков после точки " << coutNumber << std::endl << std::endl
		<< "ОТВЕТЫ В ПРЕДЕЛАХ МАШИННОЙ ТОЧНОСТИ!!!";

#endif // DEBUG

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

	// Вектор результатов
	std::vector<double> resultIntegral(vectorSegment.size());

	// Считаем резульататы
	for (int i = 0; i < vectorSegment.size(); ++i)
	{

		// Первоначальное разбиение (n)
		numberSplits = 4;
		
		// Временные переменные
		double IPrev(0), INext(0);

		// Флаг говорящий что мы только вошли в цикл
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
				<< "Количество разбиений: " << numberSplits * 2
				<< std::endl << std::endl
				<< "Результат для этого количества разбиений: "
				<< std::setprecision(coutNumber) << INext;

			// Записываем дополнительные параметры
			countSplit->push_back(numberSplits * 2);
			resultSplit->push_back(INext);

#endif // DEBUG

			// Увеличиваем количество разбиений в два раза
			numberSplits *= 2;

			// Ограничение в количестве разбиений
			if (numberSplits >= INT_MAX)
				break;

		} while ((std::fabs(INext - IPrev) / 15.) > precision);

		//std::cout << std::endl << "------------------------------";

		// Присвоение нового результата
		resultIntegral.push_back(INext);

	}

	// Временная сумма интегралов
	double tmpSumIntegral(0);

	// Суммируем
	for (int i = 0; i < resultIntegral.size(); i++)
	{
		tmpSumIntegral += resultIntegral[i];
	}

	resultSolutionIntegral = tmpSumIntegral;

	// Вывод результатов
	show();
}

// Метод Гаусса
void SolutionIntegrals::GaussMethod(Function ourFunction)
{
	// Очистка дополнительных параметров
	clear();

	// Первоначальное разбиение (n)
	numberSplits = 8;

	// Вектор результатов интегралов
	std::vector<double> resultIntegral;

	int tmp = vectorSegment.size();

	// Подсчёт интегралов
	for (int i = 0; i < vectorSegment.size(); ++i)
	{
		resultIntegral.push_back(GaussFormula(ourFunction, numberSplits, vectorSegment[i].beginSegment, vectorSegment[i].endSegment));
	}

	// Временная переменная суммы интегралов
	double tmpSumIntegral(0);

	// Получаем сумму интегрлов
	for (int i = 0; i < resultIntegral.size(); i++)
	{
		tmpSumIntegral += resultIntegral[i];
	}
	
	// Присвоение результата объекту
	resultSolutionIntegral = tmpSumIntegral;

	// Вывод результатов
	show();
}

void SolutionIntegrals::show()
{
#ifdef DEBUG
	std::cout << std::endl << std::endl
		<< "Окончательный результат численного интегрирования: "
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

	// Очистка
	vectorSegment.clear();

	// Разбиение на несколько отрезков
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

// Сеттер
void SolutionIntegrals::setEndSegment(double newEndSegment)
{
	this->endSegment = newEndSegment;
}

// Формула Симпсона
double SolutionIntegrals::SimpsonFormula(Function ourFunction, unsigned int N, double beginSegment, double endSegment)
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
	for (unsigned int i = 1; i <= (N / 2); i++)
	{
		tmpSum += ourFunction(beginSegment + h * (2 * i - 1));
	}

	// Заканчиваем вычислять второе слагаемое
	tmpSum *= 4;
	resultSimpsonFormula += tmpSum;

	// Вычисляем третье слагаемое
	tmpSum = 0;

	for (unsigned int i = 2; i <= (N / 2); i++)
	{
		tmpSum += ourFunction(beginSegment + h * (2 * i - 2));
	}

	// Заканчиваем вычислять третье слагаемое
	tmpSum *= 2;
	resultSimpsonFormula += tmpSum;

	resultSimpsonFormula *= (h / 3.);

	return resultSimpsonFormula;
}

double SolutionIntegrals::GaussFormula(Function ourFunction, unsigned int N, double beginSegment, double endSegment)
{
	// Временные переменные
	double resultGaussFormula(0);

	// Суммирование
	for (unsigned int i = 0; i < N; i++)
	{
		resultGaussFormula += A[i] * ourFunction((beginSegment + endSegment)
												 / 2 + ((endSegment - beginSegment) / 2) * t[i]);
	}


	resultGaussFormula *= (endSegment - beginSegment) / 2;

	return resultGaussFormula;
}

// Функция проверки 
double SolutionIntegrals::ExpIntegrateEi(double X)
{
	// Функция факториала
	long double Factorial(int n);

	double resultExpIntegrateEi(1);

	resultExpIntegrateEi = C + log(X);

	// Временная переменная суммы
	long double tmpSum(0);

	for (int n = 1; n <= 5 * (int)((X / 2) + 0.5); n++)
	{
		tmpSum += (pow(X, n)) / (Factorial(n) * (long double)(n));
	}

	resultExpIntegrateEi += tmpSum;

	return resultExpIntegrateEi;
}

// Функция факториала
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