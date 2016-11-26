#include <iostream>
#include "MonteCarloMethod.h"

/*
	���������
*/
// ���� ������� F(x, y)
double FourFunction(double x, double y);

using namespace std;

int main(void)
{
	setlocale(LC_ALL, ".1251");

	// ������ ��� ������� ������ �����������
	MonteCarloMethod solve(FourFunction, -1, 1, 0, 1, 1000000);

	// �����
	for (int i = 0; i < 15; i++)
		solve.showResultVolumeCylindroid();

	return 0;
}
/*
	����������
*/
// ���� ������� F(x, y)
double FourFunction(double x, double y)
{
	return (1 - x * x - y * y);
}