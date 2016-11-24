#include "SolutionSystemNonlinearEquations.h"
#include <iostream>
#include <iomanip>

// Конструктор
SolutionSystemNonlinearEquations::SolutionSystemNonlinearEquations(Function FourFunction, Function GourFunction, Function dFdxOurFunction, Function dFdyOurFunction, Function dGdxOurFunction, Function dGdyOurFunction, double xZero, double yZero, double precision)
	: FourFunction(FourFunction), GourFunction(GourFunction), dFdxOurFunction(dFdxOurFunction), dFdyOurFunction(dFdyOurFunction), dGdxOurFunction(dGdxOurFunction), dGdyOurFunction(dGdyOurFunction), precision(precision)
{
	currentX = xZero;
	currentY = yZero;
}

// Сеттер функции F(x, y)
void SolutionSystemNonlinearEquations::setFourFunction(Function FourFunction)
{
	this->FourFunction = FourFunction;
}

// Сеттер функции G(x, y)
void SolutionSystemNonlinearEquations::setGourFunction(Function GourFunction)
{
	this->GourFunction = GourFunction;
}

// Сеттер частной производной dF/dx
void SolutionSystemNonlinearEquations::setdFdxOurFunction(Function dFdxOurFunction)
{
	this->dFdxOurFunction = dFdxOurFunction;
}

// Сеттер частной производной dF/dy
void SolutionSystemNonlinearEquations::setdFdyOurFunction(Function dFdyOurFunction)
{
	this->dFdyOurFunction = dFdyOurFunction;
}

// Сеттер частной производной dG/dx
void SolutionSystemNonlinearEquations::setdGdxOurFunction(Function dGdxOurFunction)
{
	this->dGdxOurFunction = dGdxOurFunction;
}

// Сеттер частной производной dG/dy
void SolutionSystemNonlinearEquations::setdGdyOurFunction(Function dGdyOurFunction)
{
	this->dGdyOurFunction = dGdyOurFunction;
}

// Сеттер точности
void SolutionSystemNonlinearEquations::setPrecision(double precision)
{
	this->precision = precision;
}

// Сеттер начального приближения
void SolutionSystemNonlinearEquations::setZeroApproximations(double xZero, double yZero)
{
	currentX = xZero;
	currentY = yZero;
}

// Форматированный вывод результата и приближений
void SolutionSystemNonlinearEquations::showResult()
{
	// Вычисление приближений
	calculateApproximations();

	// Вывод данных
	std::cout << std::endl << std::endl << "Количество итераций: " << approximationsX.size() << std::endl << std::endl;
	for (int i = 0; i < approximationsX.size(); i++)
	{
		std::cout << "Итерация № " << i  << ":" << std::endl
			<< "X = " << std::setprecision(6) << approximationsX[i] << std::endl
			<< "Y = " << std::setprecision(6) << approximationsY[i] << std::endl << std::endl;
	}
	std::cout << "Результат: X = " << approximationsX[approximationsX.size() - 1] << "; Y = " << approximationsY[approximationsY.size() - 1] << std::endl << std::endl;
}

// Генерируем значение Якоби
void SolutionSystemNonlinearEquations::createdJacobian()
{
	jacobian[0][0] = dFdxOurFunction(currentX, currentY);
	jacobian[0][1] = dFdyOurFunction(currentX, currentY);
	jacobian[1][0] = dGdxOurFunction(currentX, currentY);
	jacobian[1][1] = dGdyOurFunction(currentX, currentY);
}

// Вычисляем детерминант матрицы Якоби
void SolutionSystemNonlinearEquations::calculateDeterminantJacobian()
{
	determinantJacobian = (jacobian[0][0] * jacobian[1][1]) - (jacobian[0][1] * jacobian[1][0]);
}

// Генерируем значения обратной матрицы Якоби
void SolutionSystemNonlinearEquations::createdInverseJacobian()
{
	inverseJacobian[0][0] = jacobian[1][1] / determinantJacobian;
	inverseJacobian[0][1] = -jacobian[0][1] / determinantJacobian;
	inverseJacobian[1][0] = -jacobian[1][0] / determinantJacobian;
	inverseJacobian[1][1] = jacobian[0][0] / determinantJacobian;
}

// Вычисления приближений
void SolutionSystemNonlinearEquations::calculateApproximations()
{
	// Очистка векторов
	approximationsX.clear();
	approximationsY.clear();

	// Сохранение нулевого приближения
	approximationsX.push_back(currentX);
	approximationsY.push_back(currentY);

	// Предыдущее преближение
	previousX = currentX;
	previousY = currentY;
	
	// Матрица умножения
	std::array<double, 2> multiResult;

	do
	{
		// Создаём матрицу Якоби
		createdJacobian();

		// Вычисляем детерминант матрицы Якоби
		calculateDeterminantJacobian();

		// Вычисляем обратную матрицу Якоби
		createdInverseJacobian();

		// Умножение обратной матрицы Якоби на значения исходных значений
		multiResult[0] = (inverseJacobian[0][0] * FourFunction(currentX, currentY) + inverseJacobian[0][1] * GourFunction(currentX, currentY));

		multiResult[1] = (inverseJacobian[1][0] * FourFunction(currentX, currentY) + inverseJacobian[1][1] * GourFunction(currentX, currentY));

		// Предыдущий результат равен нынешнему текущему
		previousX = currentX;
		previousY = currentY;

		// Окончательное вычисление нового текущего приближения
		currentX = previousX - multiResult[0];
		currentY = previousY - multiResult[1];

		// Сохраняем новое приближение в вектор
		approximationsX.push_back(currentX);
		approximationsY.push_back(currentY);

	} while ((std::fabs(currentX - previousX) > precision)
		&& (std::fabs(currentY - previousY) > precision) && (approximationsX.size() < maxCountApproximations));
}