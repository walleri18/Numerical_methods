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

	/*
		����������� ���� ��� ������ ������� ��������
	*/
	// �������� Q
	double QSimpleIterationMethod;

	// �������� ���������� �� ������: �������� �� �������� Q �� �������
	bool isQ;

	/*
		�������������� ���������
	*/
	// ���������� ������ ����� ����� ��� ����������� � ������
	int coutNumber;

// ����������������
public:

	// �������� ����������� ������
	SolutionEquation(double beginSegment, double endSegment,
					 double precision, int coutNumber);

	// ������������ ��������
	~SolutionEquation();

	// ���������� ������ �������
	void NewtonMethod(Function ourFunction, Function firstDerivativeOurFunction, Function secondDerivativeOurFunction);

	// ���������� ������ ������� ��������
	void SimpleIterationMethod(Function newOurFunction, Function firstDerivativeNewOurFunction, double argument);

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
	// ����� ���������� ���������� �� ������ �� ������ ������� ��� ������ �������
	bool isRootNewtonMethod(Function ourFunction);

	// ����� ��������� �����
	double findStartingPointNewtonMethod(Function ourFunction, Function secondDerivativeOurFunction);

	/*
		����������� ���������� ��� ������ ������� ��������
	*/
	// ����� ���������� ���������� �� ������ �� ������ ������� ��� ������ ������� ��������
	bool isJobSimpleIterationMethod(Function firstDerivativeNewOurFunction);

	// ����� ������ Q
	void findQSimpleIterationMethod(Function firstDerivativeNewOurFunction);

};