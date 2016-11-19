/*
	Работу выполнил:
		студент 2 курса по направлению Информационные системы и технологии
		Туров Виталий Александрович

	Задание №3. Вариант №23.
	Суть работы заключается в том, чтобы с помощью численных методов вычислить опрделённый интеграл.

	Я написал более или менее универсальный класс, который можно будет использовать для любых подынтегральных функций.
	Нужно только каждый раз переписывать реализацию ourFunction и подобных привидённых в main.cpp

	P.S: Реализацию класса менят не надо. 
*/
#include "SolutionIntegrals.h"
#include <iostream>
#include <cmath>
#include <iomanip>
#include <vector>

using namespace std;

const double MINIMUM = -1;
const double MAXIMUM = 2;

/*
	Прототипы
*/
// Наша исходная функция
double ourFunction(double);

// Функция поиска "бесконечности" с заданной точностью
double findInfinityNegativ(double, double, Function);
//double findInfinity(double, double, Function);

int main(void)
{
	// Установка кодировки 1251
	setlocale(LC_ALL, ".1251");
	
	cout << "Наша подынтегральная функция: exp(t)/t" << endl << endl;

	/*
		Хранители наших результатов
	*/
	// Результаты метода Симпсона
	vector<double>  resultsSimpson;

	// Результаты метода Гаусса
	vector<double>  resultsGauss;

	// Результаты ExpIntegralEi
	vector<double>  resultsExpIntegrateEi;

	///*
	//	Проба таблицы
	//*/
	//resultsSimpson.push_back(1.81);
	//resultsGauss.push_back(1.81);
	//resultsExpIntegrateEi.push_back(1.81);

	//resultsSimpson.push_back(2.81);
	//resultsGauss.push_back(2.81);
	//resultsExpIntegrateEi.push_back(2.81);

	//resultsSimpson.push_back(3.81);
	//resultsGauss.push_back(3.81);
	//resultsExpIntegrateEi.push_back(3.81);

	//resultsSimpson.push_back(4.81);
	//resultsGauss.push_back(4.81);
	//resultsExpIntegrateEi.push_back(4.81);

	//resultsSimpson.push_back(5.81);
	//resultsGauss.push_back(5.81);
	//resultsExpIntegrateEi.push_back(5.81);

	//resultsSimpson.push_back(6.81);
	//resultsGauss.push_back(6.81);
	//resultsExpIntegrateEi.push_back(6.81);

	//resultsSimpson.push_back(7.81);
	//resultsGauss.push_back(7.81);
	//resultsExpIntegrateEi.push_back(7.81);

	//resultsSimpson.push_back(8.81);
	//resultsGauss.push_back(8.81);
	//resultsExpIntegrateEi.push_back(8.81);

	//resultsSimpson.push_back(9.81);
	//resultsGauss.push_back(9.81);
	//resultsExpIntegrateEi.push_back(9.81);

	//resultsSimpson.push_back(10.81);
	//resultsGauss.push_back(10.81);
	//resultsExpIntegrateEi.push_back(10.81);

	SolutionIntegrals sol(findInfinityNegativ(MINIMUM, 1.E-4, ourFunction), MAXIMUM, 1.E-4, 4);

	cout << endl << endl << "Выполнение необходимых расчётов..." << endl << endl;

	// Получение всех результатов
	for (int X = 1; X <= 10; X++)
	{
		// Установление X
		sol.setEndSegment(X);

		// Подсчёт метода Симпсона
		sol.SimpsonMethod(ourFunction);

		// Получение результата метода Симпсона
		resultsSimpson.push_back(sol.getResultSolutionIntegral());

		// Подсчёт метода Гаусса
		sol.GaussMethod(ourFunction);

		// Получение результата метода Гаусса
		resultsGauss.push_back(sol.getResultSolutionIntegral());

		// Подсчёт ExpIntegralEi и получение результата
		resultsExpIntegrateEi.push_back(sol.ExpIntegrateEi(X));
	}

	/*
		Финальный вывод таблицы
	*/
	cout << endl
		<< "******************************************************************" << endl
		<< "|" << setw(5) << right << "X |" << setw(20) << right << "Симпсон |" << setw(20) << right << "Гаусс |" << setw(20) << right << "ExpIntegralEi |" << endl;

	for (int i = 0; i < 10; i++)
	{
		cout << "|" << setw(4) << right << (i + 1) << "|" << setw(19) << setprecision(10) << right << resultsSimpson[i] << "|" << setw(19) << setprecision(10) << right << resultsGauss[i] << "|" << setw(19) << setprecision(10) << right << resultsExpIntegrateEi[i] << "|" << endl;
	}

	cout << endl << endl;

	return 0;
}

// Наша исходная функция
double ourFunction(double argument)
{
	double resultOurFunction(0);

	if (argument != 0)
		resultOurFunction = exp(argument) / argument;

	return resultOurFunction;
}

//double findInfinity(double xZero, double precision, Function ourFunction)
//{
//	// Искомый результат
//	double resultFindInfinity(xZero);
//
//	// Значение функции
//	double resultFunction(0);
//
//	// Первый подсчёт
//	resultFunction = fabs(ourFunction(resultFindInfinity));
//
//	while (resultFunction > precision)
//	{
//		resultFindInfinity += 0.1;
//		resultFunction = fabs(ourFunction(resultFindInfinity));
//	}
//
//	return resultFindInfinity;
//}

double findInfinityNegativ(double xZero, double precision, Function ourFunction)
{
	// Искомый результат
	double resultFindInfinityNegativ(xZero);

	// Значение функции
	double resultFunction(0);

	// Первый подсчёт
	resultFunction = fabs(ourFunction(resultFindInfinityNegativ));

	while (resultFunction > precision)
	{
		resultFindInfinityNegativ -= 0.1;
		resultFunction = fabs(ourFunction(resultFindInfinityNegativ));
	}

	return resultFindInfinityNegativ;
}
