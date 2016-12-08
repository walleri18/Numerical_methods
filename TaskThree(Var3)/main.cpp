#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>

/*
	������� �3. ������� �3;
	������ 05154;
	���� ������� ��������� �������� ������� ��������;
	�����: ������������ ������;
*/

using namespace std;

/*
	���������
*/
// ��������������� �������
double ourFunction(double x);

// ������� ��������
double formulaTrapezoid(double a, double b, int n, int &countCallFunction);

// ������� ��������
double formulaSimpson(double a, double b, int n, int &countCallFunction);

int main(void)
{
	setlocale(LC_ALL, ".1251");

	// ��������� �������� ������ ����� � 15 ������ ����� �������
	cout.precision(15);

	// ������� ��������������
	double a(0), b(M_PI / 2);

	// ���������� ������� �������
	int countItTrap(0), countItSimpson(0);

	// ��������� �������� ��������� ������� ��������
	double resultTrap(0);

	// ��������� �������� ��������� ������� ��������
	double resultSimpson(0);


	// ���������� � �����
	for (int N = 4; N <= 50; N += 2)
	{
		/*
			���������� ����������� ����������
		*/

		// ���������� �������� ���������� ������� �������� � ������� ����������
		resultTrap = formulaTrapezoid(a, b, N, countItTrap);

		// ���������� �������� ���������� ������� �������� � ������� ����������
		resultSimpson = formulaSimpson(a, b, N, countItSimpson);

		/*
			���������� ����������� �����
		*/
		cout << "��� N = " << N << endl << "�. ��������: Result = " << resultTrap << " CountCallOurFunction = " << countItTrap << endl
			<< "�. ��������: Result = " << resultSimpson << " CountCallOurFunction = " << countItSimpson << endl << endl;
	}

	return 0;
}

/*
	����������
*/
// ��������������� �������
double ourFunction(double x)
{
	return (sin(1 + x * x));
}

// ������� ��������
double formulaTrapezoid(double a, double b, int n, int &countCallFunction)
{
	/*
		a - ������ ��������������
		b - ����� ��������������
		n - ���������� �������� ���������
		countCallFunction - ������� ���������� ������� �������� �������
		& - ����������� �������� �� ������
	*/

	// ��������� ��������
	countCallFunction = 0;

	// ��� h
	double h = (b - a) / n;

	// ���������� ���������
	double result(0);

	// ���������� ������� ���������� - ����� �� k = 1 �� (n - 1) ������������
	for (int k = 1; k <= (n - 1); k++)
	{
		// ��������� �������� � ����� ��������������� ������� � ��������� � ���������
		result += ourFunction(a + h * k);

		// ������� �� ������������� �������
		countCallFunction++;
	}

	// ����� ������������� �� h, ��� � �������
	result *= h;
	
	// ������ ���������
	result += (h * (ourFunction(a) / 2.));

	// ������� �� ������������� �������
	countCallFunction++;

	// ������ ���������
	result += (h * (ourFunction(b) / 2.));

	// ������� �� ������������� �������
	countCallFunction++;

	// ���������� ��������� ���������
	return result;
}

// ������� ��������
double formulaSimpson(double a, double b, int n, int &countCallFunction)
{
	/*
		a - ������ ��������������
		b - ����� ��������������
		n - ���������� �������� ���������
		countCallFunction - ������� ���������� ������� �������� �������
		& - ����������� �������� �� ������
	*/

	// ��������� ��������
	countCallFunction = 0;

	// ��� h
	double h = (b - a) / n;

	// ���������� ��� ��������� ����
	double tmpSum(0);

	// ���������� ���������
	double result(0);

	// ������ � �������� ���������
	result += ((h / 3) * (ourFunction(a) + ourFunction(b)));

	// ������� �� ������������� �������
	countCallFunction += 2;

	// ������ ���������
	tmpSum = 0;

	for (int k = 1; k <= (n / 2); k++)
	{
		// ��������� �������� � ����� ��������������� ������� � ��������� � ���������
		tmpSum += ourFunction(a + h * (2 * k - 1));

		// ������� �� ������������� �������
		countCallFunction++;
	}

	tmpSum *= 4;

	result += ((h / 3) * tmpSum);

	// ������ ���������
	tmpSum = 0;

	for (int k = 2; k <= (n / 2); k++)
	{
		// ��������� �������� � ����� ��������������� ������� � ��������� � ���������
		tmpSum += ourFunction(a + h * (2 * k - 2));

		// ������� �� ������������� �������
		countCallFunction++;
	}

	tmpSum *= 2;

	result += ((h / 3) * tmpSum);

	// ���������� ��������� ���������
	return result;
}