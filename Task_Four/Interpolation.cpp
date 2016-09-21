#include "Interpolation.h"

Interpolation::Interpolation(Function ourFunction, double beginSegment, double endSegment, int N)
	: ourFunction(ourFunction), beginSegment(beginSegment), endSegment(endSegment), N(N) {}

// Очистка памяти выделенную вручную
Interpolation::~Interpolation()
{
	// Удаление всех векторов в конечных разностях
	for (int i = 0; i < vectorFiniteDifference.size(); i++)
	{
		// Чтобы не было ошибкы проверяем вектор на пустоту
		if (!vectorFiniteDifference.empty())
			delete vectorFiniteDifference[i];
	}

	// Очистка от всех указателей
	vectorFiniteDifference.clear();
}

// Функция интерполяции Бесселя
double Interpolation::interpolantBesselFunction(double X)
{
	// Выясняем Q
	findQ(X, argument[static_cast<int>(findCountNodesIntegration() / 2.)]);

	double resultBessel(0);

	// Первое слагаемое полинома Бесселя
	resultBessel += (resultOurFunction[static_cast<int>(findCountNodesIntegration() / 2.)]
					 + resultOurFunction[static_cast<int>(findCountNodesIntegration() / 2.) + 1]) / 2.;

	// Второе слагаемое
	resultBessel += ((Q - 0.5) * getFiniteDifference(1, 0));

	// Временная переменная суммы
	double tmpSum(0);

	// Вычислим сумму
	for (int k = 1; k <= N; k++)
	{
		// Вычислим полином
		double currentPolynom = polynom(Q, k);

		// Вычислим факториал 2k
		double factorial2K = Factorial(2 * k);

		// Вычислим факториал 2k+1
		double factorial2kPlusOne = Factorial(2 * k + 1);

		// Конечные разности
		double fDiffOne = getFiniteDifference(2 * k, -k);
		double fDiffTwo = getFiniteDifference(2 * k, -k + 1);
		double fDiffThree = getFiniteDifference(2 * k + 1, -k);

		tmpSum += ((currentPolynom / factorial2K) * ((fDiffOne - fDiffTwo) / 2.));

		tmpSum += ((currentPolynom / factorial2kPlusOne) * fDiffThree);
	}

	resultBessel += tmpSum;

	return resultBessel;
}

// Сеттер порядка N интерполирующей функции Бесселя
void Interpolation::setN(int N)
{
	this->N = (N > 0) ? (N) : (-N);
}

// Сеттер начало отрезка
void Interpolation::setBeginSegment(double beginSegment)
{
	this->beginSegment = beginSegment;
}

// Сеттер конца отрезка
void Interpolation::setEndSegment(double endSegment)
{
	this->endSegment = endSegment;
}

// Геттер аргументов функции (X)
std::vector<double> Interpolation::getArgument() const
{
	return argument;
}

// Геттер результатов функции (Y)
std::vector<double> Interpolation::getResultOurFunction() const
{
	return resultOurFunction;
}

// Обновление объекта и выполнение необходимых вычислений
void Interpolation::update()
{
	// Сначало делаем очистку
	clear();

	// Теперь вычисляем шаг
	findValueStep();

	// Вычисляем все аргументы
	createdArgument();

	// Вычисляем значения функции
	createdResultOurFunction();

	// Вычисляем конечные разности
	createdFiniteDifference();
}

// Очистка векторов и результирующих величин
void Interpolation::clear()
{
	// Очистка вектора аргументов функции
	argument.clear();

	// Очистка вектора результатов функции
	resultOurFunction.clear();

	// Очищаем и освобождаем память вектора конечных разностей
	if (!vectorFiniteDifference.empty())
		for (int i = 0; i < vectorFiniteDifference.size(); i++)
			delete vectorFiniteDifference[i];
	vectorFiniteDifference.clear();
}

// Функция факториала
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

// Метод по созданию аргументов для функции (X)
void Interpolation::createdArgument()
{
	for (int i = 0; i < findCountNodesIntegration(); i++)
		argument.push_back(beginSegment + i * valueStep);
}

// Метод по созданию результатов для функции (Y)
void Interpolation::createdResultOurFunction()
{
	for (int i(0); i < argument.size(); i++)
		resultOurFunction.push_back(ourFunction(argument[i]));
}

// Метод по созданию конечных разностей
void Interpolation::createdFiniteDifference()
{
	// Определним максимальный порядок разностей
	int maxIndexOrder = findCountNodesIntegration() - 1;

	// Создадим вектора для всех конечных разностей
	for (int i = 0; i < maxIndexOrder; i++)
		vectorFiniteDifference.push_back(new std::vector<double>);

	// Посчитаем нулевую конечную разность первого порядка
	for (int i = 0; i < (resultOurFunction.size() - 1); i++)
		vectorFiniteDifference[0]->push_back(resultOurFunction[i+1]
											 - resultOurFunction[i]);

	// Посчитаем остальные конечные разности
	for (int i = 1; i < vectorFiniteDifference.size(); i++)
	{
		for (int j = 0; j < (vectorFiniteDifference[i - 1]->size() - 1); j++)
			vectorFiniteDifference[i]->push_back((*vectorFiniteDifference[i - 1])[j + 1] - (*vectorFiniteDifference[i - 1])[j]);
	}
}

// Метод по вычислению величины Q
void Interpolation::findQ(double X, double xZero)
{
	double resultFindQ(0);

	resultFindQ = (X - xZero) / valueStep;

	Q = resultFindQ;
}

// Определение количества узлов интегрирования
int Interpolation::findCountNodesIntegration() const
{
	// N * 2 - количество узлов интегрирования
	return (N * 2) + 3;
}

// Определение шага разбиения (h)
void Interpolation::findValueStep()
{
	valueStep = (endSegment - beginSegment)
		/ findCountNodesIntegration();
}

// Метод поиска нужного разбиения
/*
	order - порядок конечной разности
	number - номер конечной разности
*/
double Interpolation::getFiniteDifference(int order, int number) const
{
	double tmpResult(0);

	// Определим реальный индекс элемента
	/*int realNumber = N + number;*/
	int realNumber = number + static_cast<int>(findCountNodesIntegration() / 2.);

	// Ищем нужную разность
	tmpResult = (*vectorFiniteDifference[order - 1])[realNumber];

	return tmpResult;
}

// Метод расчёта полинома
long double Interpolation::polynom(double Q, int K)
{
	long double resultPolynom(1);

	// Считаем полином
	for (int i = 0; i <= K; i++)
		resultPolynom *= ((Q - i) * (Q + i - 1));

	return resultPolynom;
}