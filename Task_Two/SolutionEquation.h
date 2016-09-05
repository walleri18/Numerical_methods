#pragma once
#include <vector>

/*
	Новый тип - тип указателя на функцию
*/
typedef double(*Function)(double);

/*
	Этот класс обеспечивает логику работы
	решений уравнений с помощью численных методов.

	В данном классе реализованно четыре типа численных метода:
	1) Метод Ньютона или метод касательных;
	2) Метод Простых итераций;
	3) Метод Половинного деления;
	4) Метод Хорд.

	Публичные методы предоставляемые этим классом являются
	вызовом выполнения нахождения корня конкретного уравнения
	с помощью одного из численных методов.

	Класс был построен таким образом, чтобы его не нужно было переписывать.
	Для этого были использзованны указатели на функции, которые нужно будет передавать в main.

	Приятного использования моего класса =)
*/
class SolutionEquation
{
// Данные
private:

	/*
		Границы отрезка на котором ищется корень уравнения
	*/
	// Начало отрезка
	double beginSegment;

	// Конец отрезка
	double endSegment;

	/*
			   Необходимая точность, до которой будут вестись
			   расчёты по поиску корня уравнения на данном
			   отрезке
	*/
	double precision;

	/*
		Вычисляемые приближения для корня
	*/
	// Следующее приближение
	double xNext;

	// Предыдущее приближение
	double xPrev;

	/*
		Количество итераций за которое был найден корень
	*/
	int iteration;

	/*
		Все совершённые итерации
	*/
	std::vector<double> *iterationVector;

	/*
		Необходимое полу для метода Простых итераций
	*/
	// Величина Q
	double QSimpleIterationMethod;

	// Величина отвечающее на вопрос: найденна ли величина Q на отрезке
	bool isQ;

	/*
		Дополнительные параметры
	*/
	// Количество знаков после точки для приближений и корней
	int coutNumber;

// Функциональность
public:

	// Загрузка необходимых данных
	SolutionEquation(double beginSegment, double endSegment,
					 double precision, int coutNumber);

	// Освобождение ресурсов
	~SolutionEquation();

	// Выполнение метода Ньютона
	void NewtonMethod(Function ourFunction, Function firstDerivativeOurFunction, Function secondDerivativeOurFunction);

	// Выполнение метода Простых итераций
	void SimpleIterationMethod(Function newOurFunction, Function firstDerivativeNewOurFunction, double argument);

	// Выполнение метода Половинного деления
	void HalfDivisionMethod(Function ourFunction);

	// Выполнение метода хорд
	void DichotomyMethod(Function ourFunction);

private:

	/*
		Общий функционал
	*/
	// Очистка количества итераций
	void clearIteration();

	// Предоставление данных об итерациях
	std::vector<double>* getData() const;

	// Вывод результата
	void show();

	/*
		Необходимый функционал для метода Ньютона
	*/
	// Метод проверящий существует ли корень на данном отрезке для метода Ньютона
	bool isRootNewtonMethod(Function ourFunction);

	// Поиск начальной точки
	double findStartingPointNewtonMethod(Function ourFunction, Function secondDerivativeOurFunction);

	/*
		Необходимый функционал для метода Простых итераций
	*/
	// Метод проверящий существует ли корень на данном отрезке для метода Простых итераций
	bool isJobSimpleIterationMethod(Function firstDerivativeNewOurFunction);

	// Метод поиска Q
	void findQSimpleIterationMethod(Function firstDerivativeNewOurFunction);

};