/*
	������ ��������:
	������� 2 ����� �� ����������� �������������� ������� � ����������
	����� ������� �������������

	������� �4. ������� �16.
	���� ������ ����������� � ���, ����� � ������� ������ ������� �������� ���������������� �������.
	� ��������� ������� � ������� �������� ����� ������� � ��������������� �������.

	�� �������������� ���� ����� �������� � ��������������� � VS, � ���������� GUI ����� ������ � Qt.

*/
#include <iostream>
#include <cmath>

using namespace std;

/*
	���������
*/
// ���� �������� �������
double ourFunction(double);

int main(void)
{
	// ��������� ��������� 1251
	setlocale(LC_ALL, ".1251");

	

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