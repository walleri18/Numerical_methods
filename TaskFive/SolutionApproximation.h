#pragma once
#include <vector>

// ��� ��������� �� �������� �������
typedef double(*Function)(double);

/*
	���� ����� ��������� ���������� ��� ������������� ������
*/
class SolutionApproximation
{
// ������
private:

	/*
		��������� �� �������� �������
	*/
	Function ourFunction;

	/*
		����� ������� �������������
	*/
	// ������ ������� (a)
	double beginSegment;

	// ����� ������� (b)
	double endSegment;

	/*
		������� ���������������� ������� (n)
	*/
	int n;

	/*
		���������� ����� ����������������� (m)
	*/
	int m;

	/*
		�������� (c) �������� ����������� � �������� [2 ; 20]
	*/
	int c;

	/*
		������ �������� X_i
	*/
	std::vector<double> vectorX_i;

	/*
		������ �������� F_i
	*/
	std::vector<double> vectorF_i;

	/*
		��� ������� ������� �������� ���������
	*/
	// ����������� �������
	std::vector< std::vector<double> > matrix;

	// ������ ������������� ���������������� ��������
	std::vector<double> polynomialCoefficients;

	// ������ �������
	std::vector<double> residuals;

// ����������
public:

	// �����������
	SolutionApproximation(Function ourFunction,
						  double beginSegment,
						  double endSegment,
						  int n, int m, int c);

	/*
		��������� ��� ������ � �������� �� ��� (API)
	*/
	// ������ ourFunction
	void setOurFunction(Function ourFunction);

	// ������ ourFunction
	Function getOurFunction() const;

	// ������ ������ ������� (a)
	void setBeginSegment(double beginSegment);

	// ������ ������ ������� (a)
	double getBeginSegment() const;

	// ������ ����� ������� (b)
	void setEndSegment(double endSegment);

	// ������ ����� ������� (b)
	double getEndSegment() const;

	// ������ �������� (n)
	void setValueN(int n);

	// ������ �������� (n)
	int getValueN() const;

	// ������ �������� (m)
	void setValueM(int m);

	// ������ �������� (m)
	int getValueM() const;

	// ������ �������� (c)
	void setValueC(int c);

	// ������ �������� (c)
	int getValueC() const;

	// ������ ������� �������� X_i
	std::vector<double> getVectorX_i() const;

	// ������ ������� �������� F_i
	std::vector<double> getVectorF_i() const;

	// ������ ������� �������
	std::vector<double> getResiduals() const;

	// ���������� ���������������� ������� � � ������
	void update();

	// ��������� ����������������� ��������
	double ApproximationPolynom(double X);

private:

	// ������� ���� �������� �� ������ ������
	void clear();

	// �������� ������� �������� X_i
	void createdVectorX_i();

	// �������� ������� �������� F_i
	void createdVectorF_i();

	// �������� ����������� �������
	void createdMatrix();

	// ������� ������������ ������� ������
	double GaussDeterminant();

	// ���������� ������������� (������� ������� �������� ��������� ������� �������)
	void KramerSolve();

	// ���������� �������
	void searchResiduals();
};