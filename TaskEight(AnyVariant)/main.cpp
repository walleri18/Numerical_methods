#include <iostream>
#include <iomanip>
#include "MonteCarloMethod.h"

/*
	���������
*/
// ���� ������� F(x, y)
double FourFunction(double x, double y);

/*
	�����������
*/
bool ComOne(double x, double y);
bool ComTwo(double x, double y);

using namespace std;

int main(void)
{
	setlocale(LC_ALL, ".1251");

	// �������� ������������
	vector<Comporator> vectorComporator;

	vectorComporator.push_back(ComOne);
	vectorComporator.push_back(ComTwo);

	// ������ ��� ������� ������ �����������
	MonteCarloMethod solve(FourFunction, -1, 1, -1, 1, 1000, vectorComporator);

	// ���������� ����� ��� ������ ����������� ����������
	vector<double> vectorPI;

	// ���������� ����� PI ��� ������ ���������� ����� � �����
	for (int i = 0, N = 100; i < 5; i++)
	{
		// ������������� �������� N
		solve.setN(N *= 10);

		// ��������� ������ ������� � �������
		solve.showResultVolumeCylindroid();

		// ��������� ����� PI
		vectorPI.push_back(solve.getS());

		// ������� ����� PI
		cout << endl << endl << "��� ���������� ��������������� �����: " << N << endl
			<< "����� PI: " << setprecision(16) << vectorPI[i];
	}

	cout << endl;

	return 0;
}
/*
	����������
*/
// ���� ������� F(x, y)
double FourFunction(double x, double y)
{
	return sqrt(1 - x * x - y * y);
}

/*
	�����������
*/
bool ComOne(double x, double y)
{
	return (x > -1 && x < 1);
}

bool ComTwo(double x, double y)
{
	return (y > (-sqrt(1 - x * x)) && y < sqrt(1 - x * x));
}
