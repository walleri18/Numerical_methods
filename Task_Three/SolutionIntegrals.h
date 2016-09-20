#pragma once
#define RELIESE
#include <vector>

/*
	Новый тип - тип указателя на функцию
*/
typedef double(*Function)(double);

/*
	Этот класс обеспечивает логику работы
	решений интегралов с помощью численных методов.

	В данном классе реализованно два типа численных метода:
	1) Метод Симпсона;
	2) Метод Гаусса.

	Публичные методы предоставляемые этим классом являются
	вызовом выполнения вычисления интеграла
	с помощью одного из численных методов.

	Класс был построен таким образом, чтобы его не нужно было переписывать.
	Для этого были использзованны указатели на функции, которые нужно будет передавать в main.

	Приятного использования моего класса =)
*/
class SolutionIntegrals
{
	/*
		Структура отрезков
	*/
	struct Segment
	{
	public:
		// Начало отрезка
		double beginSegment;

		// Конец отрезка
		double endSegment;

		// Конструктор
		Segment(double beginSegment, double endSegment) : beginSegment(beginSegment), endSegment(endSegment) {}
	};
// Данные
private:

	/*
		Границы отрезка на котором численно вычисляется интеграл
	*/
	// Начало отрезка
	double beginSegment;

	// Конец отрезка
	double endSegment;

	// Отрезки рабиения на несколько интегралов
	std::vector<Segment> vectorSegment;

	/*
		Точность вычислений
	*/
	double precision;

	/*
		Результат вычислений (I)
	*/
	double resultSolutionIntegral;

	/*
		Необходимые параметры для метода Симпсона
	*/
	// Количество шагов (h)
	double countSteps;

	// Число разбиений (n)
	unsigned int numberSplits;

	/*
		Необходимые параметры для метода Гаусса
	*/
	// Коэффициенты квадратурной формулы
	std::vector<double> A;

	// Нули полинома Лежандра
	std::vector<double> t;

	/*
		Дополнительные параметры
	*/
	// Количество знаков после точки для приближений
	int coutNumber;

	// Константа Эйлера
	const double C = 0.577215665;

	// Количество разбиений
	std::vector<int> *countSplit;

	// Результат для этого разбиения
	std::vector<double> *resultSplit;

// Функциональность
public:

	// Загрузка необходимых данных
	SolutionIntegrals(double beginSegment, double endSegment,
					  double precision,
					  int coutNumber);

	// Освобождение ресурсов
	~SolutionIntegrals();

	// Метод Симпсона
	void SimpsonMethod(Function ourFunction);

	// Метод Гаусса
	void GaussMethod(Function ourFunction);

	// Получение результата
	double getResultSolutionIntegral() const;

	// Получение разбиений
	std::vector<int>* getCountSplit() const;

	// Получение результатов данных разбиений
	std::vector<double>* getResultSplit() const;

	// Сеттер конца отрезка
	void setEndSegment(double newEndSegment);

private:

	/*
		Общий функционал
	*/
	// Вывод результата
	void show();

	// Очистка дополнительных параметрах
	void clear();

	/*
		Для метода Симпсона
	*/
	// Формула Симпсона для вычисления интеграла с определённым разбиением.
	double SimpsonFormula(Function ourFunction, unsigned int N, double beginSegment, double endSegment);

	/*
		Для метода Гаусса
	*/
	// Формула Гаусса
	double GaussFormula(Function ourFunction, unsigned int N, double beginSegment, double endSegment);

	/*
		Для точной проверки
	*/
	public: double ExpIntegrateEi(double X);
};