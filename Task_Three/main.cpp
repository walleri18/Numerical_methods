/*
	������ ��������:
		������� 2 ����� �� ����������� �������������� ������� � ����������
		����� ������� �������������

	������� �3. ������� �23.
	���� ������ ����������� � ���, ����� � ������� ��������� ������� ��������� ���������� ��������.

	� ������� ����� ��� ����� ������������� �����, ������� ����� ����� ������������ ��� ����� ��������������� �������.
	����� ������ ������ ��� ������������ ���������� ourFunction � �������� ���������� � main.cpp

	P.S: ���������� ������ ����� �� ����. 
*/
#include "SolutionIntegrals.h"
#include <iostream>
#include <cmath>
#include <iomanip>
#include <vector>

using namespace std;

const double MINIMUM = -1;
const double MAXIMUM = 2;

/*
	���������
*/
// ���� �������� �������
double ourFunction(double);

// ������� ������ "�������������" � �������� ���������
double findInfinityNegativ(double, double, Function);
//double findInfinity(double, double, Function);

int main(void)
{
	// ��������� ��������� 1251
	setlocale(LC_ALL, ".1251");
	
	cout << "���� ��������������� �������: exp(t)/t" << endl << endl;

	/*
		��������� ����� �����������
	*/
	// ���������� ������ ��������
	vector<double>  resultsSimpson;

	// ���������� ������ ������
	vector<double>  resultsGauss;

	// ���������� ExpIntegralEi
	vector<double>  resultsExpIntegrateEi;

	///*
	//	����� �������
	//*/
	//resultsSimpson.push_back(1.81);
	//resultsGauss.push_back(1.81);
	//resultsExpIntegrateEi.push_back(1.81);

	//resultsSimpson.push_back(2.81);
	//resultsGauss.push_back(2.81);
	//resultsExpIntegrateEi.push_back(2.81);

	//resultsSimpson.push_back(3.81);
	//resultsGauss.push_back(3.81);
	//resultsExpIntegrateEi.push_back(3.81);

	//resultsSimpson.push_back(4.81);
	//resultsGauss.push_back(4.81);
	//resultsExpIntegrateEi.push_back(4.81);

	//resultsSimpson.push_back(5.81);
	//resultsGauss.push_back(5.81);
	//resultsExpIntegrateEi.push_back(5.81);

	//resultsSimpson.push_back(6.81);
	//resultsGauss.push_back(6.81);
	//resultsExpIntegrateEi.push_back(6.81);

	//resultsSimpson.push_back(7.81);
	//resultsGauss.push_back(7.81);
	//resultsExpIntegrateEi.push_back(7.81);

	//resultsSimpson.push_back(8.81);
	//resultsGauss.push_back(8.81);
	//resultsExpIntegrateEi.push_back(8.81);

	//resultsSimpson.push_back(9.81);
	//resultsGauss.push_back(9.81);
	//resultsExpIntegrateEi.push_back(9.81);

	//resultsSimpson.push_back(10.81);
	//resultsGauss.push_back(10.81);
	//resultsExpIntegrateEi.push_back(10.81);

	SolutionIntegrals sol(findInfinityNegativ(MINIMUM, 1.E-4, ourFunction), MAXIMUM, 1.E-4, 4);

	cout << endl << endl << "���������� ����������� ��������..." << endl << endl;

	// ��������� ���� �����������
	for (int X = 1; X <= 10; X++)
	{
		// ������������ X
		sol.setEndSegment(X);

		// ������� ������ ��������
		sol.SimpsonMethod(ourFunction);

		// ��������� ���������� ������ ��������
		resultsSimpson.push_back(sol.getResultSolutionIntegral());

		// ������� ������ ������
		sol.GaussMethod(ourFunction);

		// ��������� ���������� ������ ������
		resultsGauss.push_back(sol.getResultSolutionIntegral());

		// ������� ExpIntegralEi � ��������� ����������
		resultsExpIntegrateEi.push_back(sol.ExpIntegrateEi(X));
	}

	/*
		��������� ����� �������
	*/
	cout << endl
		<< "******************************************************************" << endl
		<< "|" << setw(5) << right << "X |" << setw(20) << right << "������� |" << setw(20) << right << "����� |" << setw(20) << right << "ExpIntegralEi |" << endl;

	for (int i = 0; i < 10; i++)
	{
		cout << "|" << setw(4) << right << (i + 1) << "|" << setw(19) << setprecision(10) << right << resultsSimpson[i] << "|" << setw(19) << setprecision(10) << right << resultsGauss[i] << "|" << setw(19) << setprecision(10) << right << resultsExpIntegrateEi[i] << "|" << endl;
	}

	cout << endl << endl;

	return 0;
}

// ���� �������� �������
double ourFunction(double argument)
{
	double resultOurFunction(0);

	if (argument != 0)
		resultOurFunction = exp(argument) / argument;

	return resultOurFunction;
}

//double findInfinity(double xZero, double precision, Function ourFunction)
//{
//	// ������� ���������
//	double resultFindInfinity(xZero);
//
//	// �������� �������
//	double resultFunction(0);
//
//	// ������ �������
//	resultFunction = fabs(ourFunction(resultFindInfinity));
//
//	while (resultFunction > precision)
//	{
//		resultFindInfinity += 0.1;
//		resultFunction = fabs(ourFunction(resultFindInfinity));
//	}
//
//	return resultFindInfinity;
//}

double findInfinityNegativ(double xZero, double precision, Function ourFunction)
{
	// ������� ���������
	double resultFindInfinityNegativ(xZero);

	// �������� �������
	double resultFunction(0);

	// ������ �������
	resultFunction = fabs(ourFunction(resultFindInfinityNegativ));

	while (resultFunction > precision)
	{
		resultFindInfinityNegativ -= 0.1;
		resultFunction = fabs(ourFunction(resultFindInfinityNegativ));
	}

	return resultFindInfinityNegativ;
}
