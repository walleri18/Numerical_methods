#include "SolutionSystemNonlinearEquations.h"
#include <iostream>
#include <iomanip>

// �����������
SolutionSystemNonlinearEquations::SolutionSystemNonlinearEquations(Function FourFunction, Function GourFunction, Function dFdxOurFunction, Function dFdyOurFunction, Function dGdxOurFunction, Function dGdyOurFunction, double xZero, double yZero, double precision)
	: FourFunction(FourFunction), GourFunction(GourFunction), dFdxOurFunction(dFdxOurFunction), dFdyOurFunction(dFdyOurFunction), dGdxOurFunction(dGdxOurFunction), dGdyOurFunction(dGdyOurFunction), precision(precision)
{
	this->xZero = xZero;
	this->yZero = yZero;

	currentX = xZero;
	currentY = yZero;
}

// ������ ������� F(x, y)
void SolutionSystemNonlinearEquations::setFourFunction(Function FourFunction)
{
	this->FourFunction = FourFunction;
}

// ������ ������� G(x, y)
void SolutionSystemNonlinearEquations::setGourFunction(Function GourFunction)
{
	this->GourFunction = GourFunction;
}

// ������ ������� ����������� dF/dx
void SolutionSystemNonlinearEquations::setdFdxOurFunction(Function dFdxOurFunction)
{
	this->dFdxOurFunction = dFdxOurFunction;
}

// ������ ������� ����������� dF/dy
void SolutionSystemNonlinearEquations::setdFdyOurFunction(Function dFdyOurFunction)
{
	this->dFdyOurFunction = dFdyOurFunction;
}

// ������ ������� ����������� dG/dx
void SolutionSystemNonlinearEquations::setdGdxOurFunction(Function dGdxOurFunction)
{
	this->dGdxOurFunction = dGdxOurFunction;
}

// ������ ������� ����������� dG/dy
void SolutionSystemNonlinearEquations::setdGdyOurFunction(Function dGdyOurFunction)
{
	this->dGdyOurFunction = dGdyOurFunction;
}

// ������ ��������
void SolutionSystemNonlinearEquations::setPrecision(double precision)
{
	this->precision = precision;
}

// ������ ��������
double SolutionSystemNonlinearEquations::getPrecision() const
{
	return this->precision;
}

// ������ ���������� �����������
void SolutionSystemNonlinearEquations::setZeroApproximations(double xZero, double yZero)
{
	currentX = xZero;
	currentY = yZero;

	this->xZero = xZero;
	this->yZero = yZero;
}

// ������ ���������� ����������� X
void SolutionSystemNonlinearEquations::setZeroX(double xZero)
{
	this->currentX = xZero;
	this->xZero = xZero;
}

// ������ ���������� ����������� X
double SolutionSystemNonlinearEquations::getXZero() const
{
	return this->xZero;
}

// ������ ���������� ����������� Y
void SolutionSystemNonlinearEquations::setZeroY(double yZero)
{
	this->currentY = yZero;
	this->yZero = yZero;
}

// ������ ���������� ����������� Y
double SolutionSystemNonlinearEquations::getYZero() const
{
	return this->yZero;
}

// ��������������� ����� ���������� � �����������
void SolutionSystemNonlinearEquations::showResult()
{
	// ���������� �����������
	calculateApproximations();

	// ����� ������
	std::cout << std::endl << std::endl << "���������� ��������: " << approximationsX.size() << std::endl << std::endl;
	for (int i = 0; i < approximationsX.size(); i++)
	{
		std::cout << "�������� � " << i  << ":" << std::endl
			<< "X = " << std::setprecision(6) << approximationsX[i] << std::endl
			<< "Y = " << std::setprecision(6) << approximationsY[i] << std::endl << std::endl;
	}
	std::cout << "���������: X = " << approximationsX[approximationsX.size() - 1] << "; Y = " << approximationsY[approximationsY.size() - 1] << std::endl << std::endl;
}

// ���������� �������� �����
void SolutionSystemNonlinearEquations::createdJacobian()
{
	jacobian[0][0] = dFdxOurFunction(currentX, currentY);
	jacobian[0][1] = dFdyOurFunction(currentX, currentY);
	jacobian[1][0] = dGdxOurFunction(currentX, currentY);
	jacobian[1][1] = dGdyOurFunction(currentX, currentY);
}

// ��������� ����������� ������� �����
void SolutionSystemNonlinearEquations::calculateDeterminantJacobian()
{
	determinantJacobian = (jacobian[0][0] * jacobian[1][1]) - (jacobian[0][1] * jacobian[1][0]);
}

// ���������� �������� �������� ������� �����
void SolutionSystemNonlinearEquations::createdInverseJacobian()
{
	if (determinantJacobian == 0)
		throw new std::string("���������� ��������� �������� ������� ����� => ����������� ������� ����� ����� ����!!!");

	inverseJacobian[0][0] = jacobian[1][1] / determinantJacobian;
	inverseJacobian[0][1] = -jacobian[0][1] / determinantJacobian;
	inverseJacobian[1][0] = -jacobian[1][0] / determinantJacobian;
	inverseJacobian[1][1] = jacobian[0][0] / determinantJacobian;
}

// ���������� �����������
void SolutionSystemNonlinearEquations::calculateApproximations()
{
	// ������� ��������
	approximationsX.clear();
	approximationsY.clear();

	// ���������� �������� �����������
	approximationsX.push_back(currentX);
	approximationsY.push_back(currentY);

	// ���������� �����������
	previousX = currentX;
	previousY = currentY;
	
	// ������� ���������
	std::array<double, 2> multiResult;

	do
	{
		// ������ ������� �����
		createdJacobian();

		// ��������� ����������� ������� �����
		calculateDeterminantJacobian();

		// ��������� �������� ������� �����
		createdInverseJacobian();

		// ��������� �������� ������� ����� �� �������� �������� ��������
		multiResult[0] = (inverseJacobian[0][0] * FourFunction(currentX, currentY) + inverseJacobian[0][1] * GourFunction(currentX, currentY));

		multiResult[1] = (inverseJacobian[1][0] * FourFunction(currentX, currentY) + inverseJacobian[1][1] * GourFunction(currentX, currentY));

		// ���������� ��������� ����� ��������� ��������
		previousX = currentX;
		previousY = currentY;

		// ������������� ���������� ������ �������� �����������
		currentX = previousX - multiResult[0];
		currentY = previousY - multiResult[1];

		// ��������� ����� ����������� � ������
		approximationsX.push_back(currentX);
		approximationsY.push_back(currentY);

		if (approximationsX.size() > maxCountApproximations)
			throw new std::string("��������� ������ ����������� ��������: " + maxCountApproximations);

	} while ((std::fabs(currentX - previousX) > precision)
		&& (std::fabs(currentY - previousY) > precision));
}