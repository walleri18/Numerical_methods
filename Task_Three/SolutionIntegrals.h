#pragma once
#define RELEASE
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
	unsigned int numberSplits;

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

	// ��������� ������
	const double C = 0.577215665;

	// ���������� ���������
	std::vector<int> *countSplit;

	// ��������� ��� ����� ���������
	std::vector<double> *resultSplit;

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

	// ��������� ����������
	double getResultSolutionIntegral() const;

	// ��������� ���������
	std::vector<int>* getCountSplit() const;

	// ��������� ����������� ������ ���������
	std::vector<double>* getResultSplit() const;

	// ������ ����� �������
	void setEndSegment(double newEndSegment);

private:

	/*
		����� ����������
	*/
	// ����� ����������
	void show();

	// ������� �������������� ����������
	void clear();

	/*
		��� ������ ��������
	*/
	// ������� �������� ��� ���������� ��������� � ����������� ����������.
	double SimpsonFormula(Function ourFunction, unsigned int N);

	/*
		��� ������ ������
	*/
	// ������� ������
	double GaussFormula(Function ourFunction, unsigned int N);

	/*
		��� ������ ��������
	*/
	public: double ExpIntegrateEi(double X);
};