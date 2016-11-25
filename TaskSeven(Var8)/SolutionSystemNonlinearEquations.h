#pragma once
#include <array>
#include <vector>

// �������� ��������� �� �������
typedef double (*Function)(double, double);

/*
	����� �������������� ������ ������� ������� ���������� ���������. (���)
*/
class SolutionSystemNonlinearEquations
{
// ������
private:

	/*
		�������� �������
	*/
	// ������� F(x, y)
	Function FourFunction;

	// ������� G(x, y)
	Function GourFunction;

	/*
		������� ������� ����������� ����� ������� ��� ������� �����
	*/
	// ������� ����������� dF/dx
	Function dFdxOurFunction;

	// ������� ����������� dF/dy
	Function dFdyOurFunction;

	// ������� ����������� dG/dx
	Function dGdxOurFunction;

	// ������� ����������� dG/dy
	Function dGdyOurFunction;

	/*
		������ ������
	*/
	// �������� ��������
	double precision;
	
	// ������������ ���������� �����������
	const int maxCountApproximations = 1000;

	// ������� ����������� Xk
	double currentX;

	// ���������� ����������� Xk
	double previousX;

	// ������� ����������� Yk
	double currentY;

	// ���������� ����������� Yk
	double previousY;

	// �����������
	std::vector<double> approximationsX;
	std::vector<double> approximationsY;

	// ����������� ������� ��������
	double determinantJacobian;

	// ������� �������
	std::array<std::array<double, 2>, 2> jacobian;

	// �������� ������� ��������
	std::array<std::array<double, 2>, 2> inverseJacobian;

// ����������
public:

	// �����������
	SolutionSystemNonlinearEquations(Function FourFunction, Function GourFunction, Function dFdxOurFunction, Function dFdyOurFunction, Function dGdxOurFunction, Function dGdyOurFunction, double xZero, double yZero, double precision);

	// ������ ������� F(x, y)
	void setFourFunction(Function FourFunction);

	// ������ ������� G(x, y)
	void setGourFunction(Function GourFunction);

	// ������ ������� ����������� dF/dx
	void setdFdxOurFunction(Function dFdxOurFunction);

	// ������ ������� ����������� dF/dy
	void setdFdyOurFunction(Function dFdyOurFunction);

	// ������ ������� ����������� dG/dx
	void setdGdxOurFunction(Function dGdxOurFunction);

	// ������ ������� ����������� dG/dy
	void setdGdyOurFunction(Function dGdyOurFunction);

	// ������ ��������
	void setPrecision(double precision);

	// ������ ��������
	double getPrecision() const;

	// ������ ���������� �����������
	void setZeroApproximations(double xZero, double yZero);

	// ������ ���������� ����������� X
	void setZeroX(double xZero);

	// ������ ���������� ����������� Y
	void setZeroY(double yZero);

	// ��������������� ����� ���������� � �����������
	void showResult();

private:
	
	// ���������� �������� �����
	void createdJacobian();

	// ��������� ����������� ������� �����
	void calculateDeterminantJacobian();

	// ���������� �������� �������� ������� �����
	void createdInverseJacobian();

	// ���������� �����������
	void calculateApproximations();

};