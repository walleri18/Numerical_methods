#pragma once

#include <vector>

// Тип функций
typedef double(*Function)(double);


/*
	Класс реализует все необходимые метода для предоставления интерполирующей функции Бесселя
*/
class Interpolation
{
// Данные
private:

	/*
		Всё необходимые данные для метода Бесселя
	*/
	// Указатель на нашу функцию
	Function ourFunction;

	// Начало интервала интерполяции
	double beginSegment;

	// Конец интервала интерполяции
	double endSegment;

	// Величина N - порядок интерполяционной формулы Бесселя
	int N;

	// Шаг (h)
	double valueStep;

	// Величина Q - сокращение формулы ((x - x0) / h, где h - шаг, x0 - нулевой узел интерполяции, x - текущий аргумент функции)
	double Q;

	// Вектор аргументов нашей функции (X)
	std::vector<double> argument;

	// Вектор результатов узлов интегрирования функции (Y)
	std::vector<double> resultOurFunction;

	// Вектор конечных разностей
	std::vector<std::vector<double>*> vectorFiniteDifference;

// Функционал
public:
	
	// Заполняем объект
	Interpolation(Function ourFunction, double beginSegment, double endSegment, int N);

	// Освобождаем занятую нами память вручную
	~Interpolation();

	// Интерполирующая функция Бесселя
	double interpolantBesselFunction(double X);

	/*
		Интерфейс управления объектом
	*/
	// Сеттер порядка N интерполирующей функции Бесселя
	void setN(int N);

	// Сеттер начало отрезка
	void setBeginSegment(double beginSegment);

	// Сеттер конца отрезка
	void setEndSegment(double endSegment);

	// Геттер аргументов функции (X)
	std::vector<double> getArgument() const;

	// Геттер результатов функции (Y)
	std::vector<double> getResultOurFunction() const;

	// Обновление объекта и выполнение необходимых вычислений
	void update();

private:

	/*
		Общий функционал
	*/
	// Метод очистки всех векторов и результатов
	void clear();

	// Функция факториала
	long long Factorial(long long n);

	/*
		Необходимый функционал для функции интегрирования Бесселя
	*/
	// Метод по созданию аргументов для функции (X)
	void createdArgument();

	// Метод по созданию результатов для функции (Y)
	void createdResultOurFunction();

	// Метод по созданию конечных разностей
	void createdFiniteDifference();

	// Расчёт величины Q
	void findQ(double X, double xZero);

	// Определение количества узлов интегрирования
	int findCountNodesIntegration() const;

	// Определение шага разбиения (h)
	void findValueStep();

	// Метод поиска нужного разбиения
	/*
		order - порядок конечной разности
		number - номер конечной разности
	*/
	double getFiniteDifference(int order, int number) const;

	// Метод расчёта полинома
	long double polynom(double Q, int K);

};