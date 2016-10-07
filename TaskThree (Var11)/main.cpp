/*
	Работу выполнила Маевская Алёна.
	Группа 05154.
	Задание №3. Вариант №11.
	Суть задания:
	с помощью численных методов вычислить определённый интеграл.
*/
#include <iostream>
#include <map>

using namespace std;

/*
	Прототипы наших функций
*/
// Наша подынтегральная функция
double ourFunction(double, map<double, double>&);

// Формула Симпсона
double SimpsonFormyla(double, double, int, int&, map<double, double>&);

// Формула Трапеций
double TrapetionFormyla(double, double, int, int&, map<double, double>&);

// Метод Симпсона
double SimpsonMethod(double, double, double, int&, int&, map<double, double>&);

// Метод Трапеций
double TrapetionMethod(double, double, double, int&, int&, map<double, double>&);

// Вход в программу
int main()
{
	// Кодировка
	setlocale(LC_ALL, ".1251");

	// Словарь результатов и аргументов. (ключ - это аргумент, значение - это результат функции)
	// Он нужен чтобы уменьшить количество обращений в подынтегральную функцию
	map<double, double> mapResultOurFunction;

	// Концы отрезка интегрирования
	double begin(-2), end(-1);

	// Точность
	double e(1.E-7);

	// Количество итераций в методе Трапеций
	int countIterationTrapetion(0);

	// Количество итераци в методе Симпсона
	int countIterationSimpson(0);

	// Количество вызовов функций в методе Трапеций
	int countCallFunctionTrapetion(0);

	// Количество вызово функций в методе Симпсона
	int countCallFunctionSimpson(0);

	// Результата численного интегрирования методом Трапеций
	double resultTrapetion = TrapetionMethod(begin, end, e, countIterationTrapetion, countCallFunctionTrapetion, mapResultOurFunction);

	// Результат численного интегрирования методом Симпсона
	double resultSimpson = SimpsonMethod(begin, end, e, countIterationSimpson, countCallFunctionSimpson, mapResultOurFunction);

	// Настройка точности вывода
	cout.precision(7);

	// Вывод результата
	cout << "Работу выполнила Маевская Алёна. Группа 05154." << endl
		<< "Задание №3. Вариант №11." << endl
		<< "Подынтегральная функций: (2^x) / (1-4^x)" << endl
		<< "Интервал интегрирования [" << begin << "; " << end << "]" << endl << endl
		<< "Метод Трапеций:" << endl
		<< "Результат численного интегрирования: " << resultTrapetion << endl
		<< "Количество итераций: " << countIterationTrapetion << endl
		<< "Количество вызовов подынтегральной функции: " << countCallFunctionTrapetion << endl << endl << endl
		<< "Метод Симпсона:" << endl
		<< "Результат численного интегрирования: " << resultSimpson << endl
		<< "Количество итераций: " << countIterationSimpson << endl
		<< "Количество вызовов подынтегральной функции: " << countCallFunctionSimpson << endl;

	return 0;
}

/*
	Реализации наших функций
*/
// Наша подынтегральная функция
double ourFunction(double x, map<double, double> &mapResultOurFunction)
{
	double result(0);

	// Вычисляем функцию
	result = (pow(2, x)) / (1 - pow(4, x));

	// Сохраняем значение
	mapResultOurFunction[x] = result;

	return result;
}

// Формула Симпсона
double SimpsonFormyla(double begin, double end, int N, int &countCallFunction, map<double, double> &mapResultOurFunction)
{
	double result(0);

	// Переменная счётчик обсчитывающий количество вызовов подынтегральной функции
	//countCallFunction;

	// Шаг h
	double h = (end - begin) / N;

	// Временная сумма для квадратной скобки
	double tmpSum(0);

	/*
		Вычисления значений на концах отрезка интегрирования
	*/

	// Считаем значения функции на концах отрезка интегрирования
	// Сначало проверяем есть ли у нас это значение в словаре
	if (mapResultOurFunction.find(begin) == mapResultOurFunction.end())
	{
		// Считаем новое значение
		tmpSum += ourFunction(begin, mapResultOurFunction);

		// Увеличиваем счётчик свидетельствующий об вызове подынтегральной функции
		countCallFunction++;
	}

	// В случае, если у нас это значение уже есть в словаре
	else
		tmpSum += mapResultOurFunction[begin];

	// Аналогично
	if (mapResultOurFunction.find(end) == mapResultOurFunction.end())
	{
		tmpSum += ourFunction(end, mapResultOurFunction);

		countCallFunction++;
	}

	else
		tmpSum += mapResultOurFunction[end];

	/*
		Вычисление первой суммы
	*/

	// Временная сумма для первой суммы
	double tmpSumFirst(0);

	// Начнём подсчёт
	for (int k = 1; k <= (N / 2); k++)
	{
		double argument = begin + h * (2 * k - 1);

		// Проверка на существование результат
		if (mapResultOurFunction.find(argument) == mapResultOurFunction.end())
		{
			tmpSumFirst += ourFunction(argument, mapResultOurFunction);

			countCallFunction++;
		}

		else
			tmpSumFirst += mapResultOurFunction[argument];
	}

	tmpSumFirst *= 4;

	/*
		Вычисление второй суммы
	*/

	// Временная сумма для второй суммы
	double tmpSumSecond(0);

	// Начнём подсчёт
	for (int k = 2; k <= (N / 2); k++)
	{
		double argument = begin + h * (2 * k - 2);

		// Проверка на существование результат
		if (mapResultOurFunction.find(argument) == mapResultOurFunction.end())
		{
			tmpSumSecond += ourFunction(argument, mapResultOurFunction);

			countCallFunction++;
		}

		else
			tmpSumSecond += mapResultOurFunction[argument];
	}

	tmpSumSecond *= 2;

	// Складывание всех сумм
	tmpSum += tmpSumFirst;
	tmpSum += tmpSumSecond;

	// Выполнение последнего действия в формуле: умножение на h/3
	tmpSum *= (h / 3);

	// Передача окончательного результата в переменную для выкидывания из функции
	result = tmpSum;

	return result;
}

// Формула Трапеций
double TrapetionFormyla(double begin, double end, int N, int &countCallFunction, map<double, double> &mapResultOurFunction)
{
	double result(0);

	// Переменная счётчик обсчитывающий количество вызовов подынтегральной функции
	//countCallFunction;

	// Шаг h
	double h = (end - begin) / N;

	// Временная сумма для квадратной скобки
	double tmpSum(0);

	/*
		Вычисления значений на концах отрезка интегрирования
	*/

	// Считаем значения функции на концах отрезка интегрирования
	// Сначало проверяем есть ли у нас это значение в словаре
	if (mapResultOurFunction.find(begin) == mapResultOurFunction.end())
	{
		// Считаем новое значение
		tmpSum += (ourFunction(begin, mapResultOurFunction) / 2.);

		// Увеличиваем счётчик свидетельствующий об вызове подынтегральной функции
		countCallFunction++;
	}

	// В случае, если у нас это значение уже есть в словаре
	else
		tmpSum += (mapResultOurFunction[begin] / 2.);

	// Аналогично
	if (mapResultOurFunction.find(end) == mapResultOurFunction.end())
	{
		tmpSum += (ourFunction(end, mapResultOurFunction) / 2.);

		countCallFunction++;
	}

	else
		tmpSum += (mapResultOurFunction[end] / 2.);

	/*
		Вычисление первой суммы
	*/

	// Временная сумма для первой суммы
	double tmpSumFirst(0);

	// начнём подсчёт
	for (int k = 1; k <= (N - 1); k++)
	{
		double argument = begin + h * k;

		// Проверка на существование результат
		if (mapResultOurFunction.find(argument) == mapResultOurFunction.end())
		{
			tmpSumFirst += ourFunction(argument, mapResultOurFunction);

			countCallFunction++;
		}

		else
			tmpSumFirst += mapResultOurFunction[argument];
	}

	// Складывание всех сумм
	tmpSum += tmpSumFirst;

	// Выполнение последнего действия в формуле: умножение на h
	tmpSum *= h;

	// Передача окончательного результата в переменную для выкидывания из функции
	result = tmpSum;

	return result;
}

// Метод Симпсона
double SimpsonMethod(double begin, double end, double e, int &countIteration, int &countCallFunction, map<double, double> &mapResultOurFunction)
{
	double result(0);

	// countIteration - количество итераций
	// countCallFunction - количество вызово функций

	// Обнуление счётчиков итераций и вызова функций
	countIteration = 0, countCallFunction = 0;

	// Начальное разбиение
	int N = 2;

	/*
		Переменные для результатов разных разбиений
	*/
	// Результат численного интегрирования при N
	double In(0);

	// Результата численного интегрирования при 2N
	double I2n(0);

	// Первая итерация
	In = SimpsonFormyla(begin, end, N, countCallFunction, mapResultOurFunction);
	I2n = SimpsonFormyla(begin, end, 2 * N, countCallFunction, mapResultOurFunction);

	// Увеличиваем количество итераций
	countIteration++;

	// Начнём считать
	while ((fabs(I2n - In) / 15) > e)
	{
		// Удвоение узлов
		N *= 2;

		// Новая итерация
		In = I2n;
		I2n = SimpsonFormyla(begin, end, 2 * N, countCallFunction, mapResultOurFunction);

		// Увеличение количества итераций
		countIteration++;
	}

	// Присвоение результата
	result = I2n;

	return result;
}

// Метод Трапеций
double TrapetionMethod(double begin, double end, double e, int &countIteration, int &countCallFunction, map<double, double> &mapResultOurFunction)
{
	double result(0);

	// countIteration - количество итераций
	// countCallFunction - количество вызово функций

	// Обнуление счётчиков итераций и вызова функций
	countIteration = 0, countCallFunction = 0;

	// Начальное разбиение
	int N = 2;

	/*
	Переменные для результатов разных разбиений
	*/
	// Результат численного интегрирования при N
	double In(0);

	// Результата численного интегрирования при 2N
	double I2n(0);

	// Первая итерация
	In = TrapetionFormyla(begin, end, N, countCallFunction, mapResultOurFunction);
	I2n = TrapetionFormyla(begin, end, 2 * N, countCallFunction, mapResultOurFunction);

	// Увеличиваем количество итераций
	countIteration++;

	// Начнём считать
	while ((fabs(I2n - In) / 3) > e)
	{
		// Удвоение узлов
		N *= 2;

		// Новая итерация
		In = I2n;
		I2n = TrapetionFormyla(begin, end, 2 * N, countCallFunction, mapResultOurFunction);

		// Увеличение количества итераций
		countIteration++;
	}

	// Присвоение результата
	result = I2n;

	return result;
}