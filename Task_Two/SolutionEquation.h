#pragma once
#include <vector>

/*
	����� ��� - ��� ��������� �� �������
*/
typedef double(*Function)(double);

/*
	���� ����� ������������ ������ ������
	������� ��������� � ������� ��������� �������.

	� ������ ������ ������������ ������ ���� ��������� ������:
	1) ����� ������� ��� ����� �����������;
	2) ����� ������� ��������;
	3) ����� ����������� �������;
	4) ����� ����.

	��������� ������ ��������������� ���� ������� ��������
	������� ���������� ���������� ����� ����������� ���������
	� ������� ������ �� ��������� �������.

	����� ��� �������� ����� �������, ����� ��� �� ����� ���� ������������.
	��� ����� ���� �������������� ��������� �� �������, ������� ����� ����� ���������� � main.

	��������� ������������� ����� ������ =)
*/
class SolutionEquation
{
// ������
private:

	/*
		������� ������� �� ������� ������ ������ ���������
	*/
	// ������ �������
	double beginSegment;

	// ����� �������
	double endSegment;

	/*
			   ����������� ��������, �� ������� ����� �������
			   ������� �� ������ ����� ��������� �� ������
			   �������
	*/
	double precision;

	/*
		����������� ����������� ��� �����
	*/
	// ��������� �����������
	double xNext;

	// ���������� �����������
	double xPrev;

	/*
		���������� �������� �� ������� ��� ������ ������
	*/
	int iteration;

	/*
		��� ����������� ��������
	*/
	std::vector<double> *iterationVector;

// ����������������
public:

	// �������� ����������� ������
	SolutionEquation(double beginSegment, double endSegment,
					 double precision);

	// ������������ ��������
	~SolutionEquation();

	// ���������� ������ �������
	void NewtonMethod(Function ourFunction, Function firstDerivativeOurFunction, Function secondDerivativeOurFunction);

	// ���������� ������ ������� ��������
	void SimpleIterationMethod(Function newOurFunction, double argument);

	// ���������� ������ ����������� �������
	void HalfDivisionMethod(Function ourFunction);

	// ���������� ������ ����
	void DichotomyMethod(Function ourFunction);

private:

	/*
		����� ����������
	*/
	// ������� ���������� ��������
	void clearIteration();

	// �������������� ������ �� ���������
	std::vector<double>* getData() const;

	// ����� ����������
	void show();

	/*
		����������� ���������� ��� ������ �������
	*/
	// ����� ���������� ���������� �� ������ �� ������ �������
	bool isRoot(Function ourFunction);

	// ����� ��������� �����
	double findStartingPoint(Function ourFunction, Function secondDerivativeOurFunction);

};