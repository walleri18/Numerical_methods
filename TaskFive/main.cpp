/*
	������ ��������:
	����� ������� �������������
	������: 05154
	������� �5. ������� �16.
*/
#include <iostream>
#include "SolutionApproximation.h"

using namespace std;

/*
	���������
*/
// ���� �������
double ourFunction(double);

int main(void)
{
	setlocale(LC_ALL, ".1251");
	
	return 0;
}
/*
	����������
*/
// ���� �������
double ourFunction(double argument)
{
	double resultOurFunction(0);

	resultOurFunction = exp(-argument) * cos(argument);

	return resultOurFunction;
}