#pragma once

#include <vector>

// ��� �������
typedef double(*Function)(double);


/*
	����� ��������� ��� ����������� ������ ��� �������������� ��������������� ������� �������
*/
class Interpolation
{
// ������
private:

	/*
		�� ����������� ������ ��� ������ �������
	*/
	// ��������� �� ���� �������
	Function ourFunction;

	// ������ ��������� ������������
	double beginSegment;

	// ����� ��������� ������������
	double endSegment;

	// �������� N - ������� ���������������� ������� �������
	int N;

	// ��� (h)
	double valueStep;

	// �������� Q - ���������� ������� ((x - x0) / h, ��� h - ���, x0 - ������� ���� ������������, x - ������� �������� �������)
	double Q;

	// ������ ���������� ����� ������� (X)
	std::vector<double> argument;

	// ������ ����������� ����� �������������� ������� (Y)
	std::vector<double> resultOurFunction;

	// ������ �������� ���������
	std::vector<std::vector<double>*> vectorFiniteDifference;

// ����������
public:
	
	// ��������� ������
	Interpolation(Function ourFunction, double beginSegment, double endSegment, int N);

	// ����������� ������� ���� ������ �������
	~Interpolation();

	// ��������������� ������� �������
	double interpolantBesselFunction(double X);

	/*
		��������� ���������� ��������
	*/
	// ������ ������� N ��������������� ������� �������
	void setN(int N);

	// ������ ������ �������
	void setBeginSegment(double beginSegment);

	// ������ ����� �������
	void setEndSegment(double endSegment);

	// ������ ���������� ������� (X)
	std::vector<double> getArgument() const;

	// ������ ����������� ������� (Y)
	std::vector<double> getResultOurFunction() const;

	// ���������� ������� � ���������� ����������� ����������
	void update();

private:

	/*
		����� ����������
	*/
	// ����� ������� ���� �������� � �����������
	void clear();

	// ������� ����������
	long long Factorial(long long n);

	/*
		����������� ���������� ��� ������� �������������� �������
	*/
	// ����� �� �������� ���������� ��� ������� (X)
	void createdArgument();

	// ����� �� �������� ����������� ��� ������� (Y)
	void createdResultOurFunction();

	// ����� �� �������� �������� ���������
	void createdFiniteDifference();

	// ������ �������� Q
	void findQ(double X, double xZero);

	// ����������� ���������� ����� ��������������
	int findCountNodesIntegration() const;

	// ����������� ���� ��������� (h)
	void findValueStep();

	// ����� ������ ������� ���������
	/*
		order - ������� �������� ��������
		number - ����� �������� ��������
	*/
	double getFiniteDifference(int order, int number) const;

	// ����� ������� ��������
	long double polynom(double Q, int K);

};