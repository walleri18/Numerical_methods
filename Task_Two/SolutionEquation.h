#pragma once
#include <vector>

/*
	���� ����� ������������ ������ ������
	������� ��������� � ������� ��������� �������.

	� ������ ������ ������������ ��� ���� ��������� ������:
	1) ����� ������� ��� ����� �����������;
	2) ����� ������� ��������.

	��������� ������ ��������������� ���� ������� ��������
	������� ���������� ���������� ����� ����������� ���������
	� ������� ������ �� ��������� �������.

	��������� �������� ������ ����� ������������, ��� ��� ���
	�������� �������� ��������� ���� ��� ������������.
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
	void NewtonMethod();

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
	// ���� ������� (������ � ����� ������������
	// ��� ����� ���������)
	double ourFunction(double argument);

	// ������ ����������� ����� ������� (���� ����� ������������)
	double firstDerivativeOurFunction(double argument);

	// ������ ����������� ����� ������� (���� ����� ������������)
	double secondDerivativeOurFunction(double argument);

	// ����� ���������� ���������� �� ������ �� ������ �������
	bool isRoot();

	// ����� ��������� �����
	double findStartingPoint();

	// ������� ��������� 

	/*
		����������� ���������� ��� ������ ������� ��������
	*/

};

