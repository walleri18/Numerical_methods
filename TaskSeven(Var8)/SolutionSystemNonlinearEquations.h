#pragma once
#include <array>
#include <vector>

// Прототип указателя на функцию
typedef double (*Function)(double, double);

/*
	Класс обеспечивающий работу решений системы нелинейных уравнений. (СНУ)
*/
class SolutionSystemNonlinearEquations
{
// Данные
private:

	/*
		Исходные функции
	*/
	// Функция F(x, y)
	Function FourFunction;

	// Функция G(x, y)
	Function GourFunction;

	/*
		Функции частных производных наших функций для матрицы Якоби
	*/
	// Частная производная dF/dx
	Function dFdxOurFunction;

	// Частная производная dF/dy
	Function dFdyOurFunction;

	// Частная производная dG/dx
	Function dGdxOurFunction;

	// Частная производная dG/dy
	Function dGdyOurFunction;

	/*
		Прочие данные
	*/
	// Заданная точность
	double precision;
	
	// Максимальное количество приближений
	const int maxCountApproximations = 1000;

	// Нулевое приближение X
	double xZero;

	// Нулевое приближение Y
	double yZero;

	// Текущее приближение Xk
	double currentX;

	// Предыдущее приближение Xk
	double previousX;

	// Текущее приближение Yk
	double currentY;

	// Предыдущее приближение Yk
	double previousY;

	// Приближения
	std::vector<double> approximationsX;
	std::vector<double> approximationsY;

	// Детерминант матрицы Якобиана
	double determinantJacobian;

	// Матрица Якобиан
	std::array<std::array<double, 2>, 2> jacobian;

	// Обратная матрица Якобиана
	std::array<std::array<double, 2>, 2> inverseJacobian;

// Функционал
public:

	// Конструктор
	SolutionSystemNonlinearEquations(Function FourFunction, Function GourFunction, Function dFdxOurFunction, Function dFdyOurFunction, Function dGdxOurFunction, Function dGdyOurFunction, double xZero, double yZero, double precision);

	// Сеттер функции F(x, y)
	void setFourFunction(Function FourFunction);

	// Сеттер функции G(x, y)
	void setGourFunction(Function GourFunction);

	// Сеттер частной производной dF/dx
	void setdFdxOurFunction(Function dFdxOurFunction);

	// Сеттер частной производной dF/dy
	void setdFdyOurFunction(Function dFdyOurFunction);

	// Сеттер частной производной dG/dx
	void setdGdxOurFunction(Function dGdxOurFunction);

	// Сеттер частной производной dG/dy
	void setdGdyOurFunction(Function dGdyOurFunction);

	// Сеттер точности
	void setPrecision(double precision);

	// Геттер точности
	double getPrecision() const;

	// Сеттер начального приближения
	void setZeroApproximations(double xZero, double yZero);

	// Сеттер начального приближения X
	void setZeroX(double xZero);

	// Геттер начального приближения X
	double getXZero() const;

	// Сеттер начального приближения Y
	void setZeroY(double yZero);

	// Геттер начального приближения Y
	double getYZero() const;

	// Форматированный вывод результата и приближений
	void showResult();

private:
	
	// Генерируем значение Якоби
	void createdJacobian();

	// Вычисляем детерминант матрицы Якоби
	void calculateDeterminantJacobian();

	// Генерируем значения обратной матрицы Якоби
	void createdInverseJacobian();

	// Вычисления приближений
	void calculateApproximations();

};