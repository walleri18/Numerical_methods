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
	int orderApproximatFunction;

	/*
		�������� (m)
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
		������� ��� ������������� � ������� �������� ���������
	*/
	std::vector< std::vector<double> > matrix;

// ����������
public:

	// �����������
	SolutionApproximation(Function ourFunction,
						  double beginSegment,
						  double endSegment,
						  int orderApproximatFunction,
						  int m, int c);

	// ����������� �����������
	SolutionApproximation();

	/*
		�������� ��� ������ � �������� �� ��� (API)
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

	// ������ ������� ���������������� ������� (n)
	void setOrderApproximatFunction(int orderApproximatFunction);

	// ������ ������� ���������������� ������� (n)
	int getOrderApproximatFunction() const;

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

	// ������ �������
	void setMatrix(std::vector< std::vector<double> > matrix);

	// ������ �������
	std::vector< std::vector<double> > getMatrix() const;

	// ���������� ���������������� ������� � � ������
	void update();

private:

	// ������� ���� �������� �� ������ ������
	void clear();

	// �������� ������� �������� X_i
	void createdVectorX_i();

	// �������� ������� �������� F_i
	void createdVectorF_i();

	// ������� ������������ ������� ������
	double GaussDeterminant();

	//// ���������� ������������� (������� ������� �������� ��������� ������� ������)
	//std::vector<double> GaussSolve(std::vector< std::vector<double> > matrix);

	// ���������� ������������� (������� ������� �������� ��������� ������� �������)
	std::vector<double> KramerSolve();
};