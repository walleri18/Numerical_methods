#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>

/*
	Задание №3. Вариант №3;
	Группа 05154;
	Суть задания посчитать интеграл нужными методами;
	Автор: Перевезенцев Никита;
*/

using namespace std;

/*
	Прототипы
*/
// Подынтегральная функция
double ourFunction(double x);

// Формула трапеции
double formulaTrapezoid(double a, double b, int n, int &countCallFunction);

// Формула Симпсона
double formulaSimpson(double a, double b, int n, int &countCallFunction);

int main(void)
{
	setlocale(LC_ALL, ".1251");

	// Установка точности вывода чисел в 15 знаков после запятой
	cout.precision(15);

	// Пределы интегрирования
	double a(0), b(M_PI / 2);

	// Количество вызовов функций
	int countItTrap(0), countItSimpson(0);

	// Результат подсчёта интеграла методом трапеций
	double resultTrap(0);

	// Результат подсчёта интеграла методом Симпсона
	double resultSimpson(0);


	// Вычисления и вывод
	for (int N = 4; N <= 50; N += 2)
	{
		/*
			Производим необходимые вычисления
		*/

		// Вычисление значение иинтеграла методом трапеций с текущим разбиением
		resultTrap = formulaTrapezoid(a, b, N, countItTrap);

		// Вычисление значение иинтеграла методом Симпсона с текущим разбиением
		resultSimpson = formulaSimpson(a, b, N, countItSimpson);

		/*
			Производим необходимый вывод
		*/
		cout << "При N = " << N << endl << "М. Трапеций: Result = " << resultTrap << " CountCallOurFunction = " << countItTrap << endl
			<< "М. Симпсона: Result = " << resultSimpson << " CountCallOurFunction = " << countItSimpson << endl << endl;
	}

	return 0;
}

/*
	Реализации
*/
// Подынтегральная функция
double ourFunction(double x)
{
	return (sin(1 + x * x));
}

// Формула трапеции
double formulaTrapezoid(double a, double b, int n, int &countCallFunction)
{
	/*
		a - начало интегрирования
		b - конец интегрирования
		n - количество отрезков разбиения
		countCallFunction - счётчик количества вызовов исходной функции
		& - обозначение передачи по ссылки
	*/

	// Обнуление счётчика
	countCallFunction = 0;

	// Шаг h
	double h = (b - a) / n;

	// Переменная результат
	double result(0);

	// Вычисление второго слагаемого - сумма от k = 1 до (n - 1) включительно
	for (int k = 1; k <= (n - 1); k++)
	{
		// Вычисляем значение в нашей подынтегральной функции и суммируем в результат
		result += ourFunction(a + h * k);

		// Говорим об использовании функции
		countCallFunction++;
	}

	// Сумма перемножается на h, как в формуле
	result *= h;
	
	// Первое слагаемое
	result += (h * (ourFunction(a) / 2.));

	// Говорим об использовании функции
	countCallFunction++;

	// Третье слагаемое
	result += (h * (ourFunction(b) / 2.));

	// Говорим об использовании функции
	countCallFunction++;

	// Возвращаем результат интеграла
	return result;
}

// Формула Симпсона
double formulaSimpson(double a, double b, int n, int &countCallFunction)
{
	/*
		a - начало интегрирования
		b - конец интегрирования
		n - количество отрезков разбиения
		countCallFunction - счётчик количества вызовов исходной функции
		& - обозначение передачи по ссылки
	*/

	// Обнуление счётчика
	countCallFunction = 0;

	// Шаг h
	double h = (b - a) / n;

	// Переменная для временных сумм
	double tmpSum(0);

	// Переменная результат
	double result(0);

	// Первое и четвёртое слагаемые
	result += ((h / 3) * (ourFunction(a) + ourFunction(b)));

	// Говорим об использовании функции
	countCallFunction += 2;

	// Второе слагаемое
	tmpSum = 0;

	for (int k = 1; k <= (n / 2); k++)
	{
		// Вычисляем значение в нашей подынтегральной функции и суммируем в результат
		tmpSum += ourFunction(a + h * (2 * k - 1));

		// Говорим об использовании функции
		countCallFunction++;
	}

	tmpSum *= 4;

	result += ((h / 3) * tmpSum);

	// Третье слагаемое
	tmpSum = 0;

	for (int k = 2; k <= (n / 2); k++)
	{
		// Вычисляем значение в нашей подынтегральной функции и суммируем в результат
		tmpSum += ourFunction(a + h * (2 * k - 2));

		// Говорим об использовании функции
		countCallFunction++;
	}

	tmpSum *= 2;

	result += ((h / 3) * tmpSum);

	// Возвращаем результат интеграла
	return result;
}