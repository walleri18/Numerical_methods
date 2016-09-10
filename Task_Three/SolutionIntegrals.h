#pragma once
#include <vector>

/*
	����� ��� - ��� ��������� �� �������
*/
typedef double(*Function)(double);

/*
	���� ����� ������������ ������ ������
	������� ���������� � ������� ��������� �������.

	� ������ ������ ������������ ��� ���� ��������� ������:
	1) ����� ��������;
	2) ����� ������.

	��������� ������ ��������������� ���� ������� ��������
	������� ���������� ���������� ���������
	� ������� ������ �� ��������� �������.

	����� ��� �������� ����� �������, ����� ��� �� ����� ���� ������������.
	��� ����� ���� �������������� ��������� �� �������, ������� ����� ����� ���������� � main.

	��������� ������������� ����� ������ =)
*/
class SolutionIntegrals
{
// ������
private:

	/*
		������� ������� �� ������� �������� ����������� ��������
	*/
	// ������ �������
	double beginSegment;

	// ����� �������
	double endSegment;

	/*
		�������� ����������
	*/
	double precision;

	/*
		��������� ���������� (I)
	*/
	double resultSolutionIntegral;

	/*
		����������� ��������� ��� ������ ��������
	*/
	// ���������� ����� (h)
	double countSteps;

	// ����� ��������� (n)
	int numberSplits;

	/*
		����������� ��������� ��� ������ ������
	*/
	// ������������ ������������ �������
	std::vector<double> A;

	// ���� �������� ��������
	std::vector<double> t;

	/*
		�������������� ���������
	*/
	// ���������� ������ ����� ����� ��� �����������
	int coutNumber;

// ����������������
public:

	// �������� ����������� ������
	SolutionIntegrals(double beginSegment, double endSegment,
					  double precision,
					  int coutNumber);

	// ������������ ��������
	~SolutionIntegrals();

	// ����� ��������
	void SimpsonMethod(Function ourFunction);

	// ����� ������
	void GaussMethod(Function ourFunction);

private:

	/*
		����� ����������
	*/
	// ����� ����������
	void show();

	// ��������� ������
	double getResultSolutionIntegral() const;

	/*
		��� ������ ��������
	*/
	// ������� �������� ��� ���������� ��������� � ����������� ����������.
	double SimpsonFormula(Function ourFunction, int N);
};