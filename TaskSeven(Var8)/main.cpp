#include <iostream>
#include "SolutionSystemNonlinearEquations.h"

/*
	���������
*/
// ������� F(x, y)
double FourFunction(double, double);

// ������� G(x, y)
double GourFunction(double, double);

// ������� ����������� dF/dx
double dFdxOurFunction(double ,double);

// ������� ����������� dF/dy
double dFdyOurFunction(double, double);

// ������� ����������� dG/dx
double dGdxOurFunction(double, double);

// ������� ����������� dG/dy
double dGdyOurFunction(double, double);

using namespace std;

int main(void)
{
	setlocale(LC_ALL, ".1251");

	// ����� �� ������� ������� ���������� ���������
	SolutionSystemNonlinearEquations sol(FourFunction, GourFunction, dFdxOurFunction, dFdyOurFunction, dGdxOurFunction, dGdyOurFunction, 0.3, 3.7, 1.e-6);
	
	// ���������� ������
	char select(' ');

	do
	{
		// ������� ���� �� ���������� �������� ������
		system("cls");

		// ������ �� ��������� �������� ����������
		cout << endl << endl << "������� �������� �������� ����������? (y/n or Y/N): ";
		cin >> select;

		// �������� �������� �� �����������
		if (select == 'Y' || select == 'y')
		{
			double tmpPrecision(0);

			cout << endl << endl << "������� ��������: " << sol.getPrecision() << endl << "������� �������� ��������: ";
			cin >> tmpPrecision;

			sol.setPrecision(tmpPrecision);
		}

		// ������ �� ��������� ���������� ����������� X
		cout << endl << endl << "������� �������� ��������� ����������� X? (y/n or Y/N): ";
		cin >> select;

		// ��������� ���������� ����������� X
		if (select == 'y' || select == 'Y')
		{
			double tmpXZero(0);

			cout << endl << endl << "������� ����������� X: " << sol.getXZero() << endl << "������� �������� ��������� ����������� X: ";
			cin >> tmpXZero;

			sol.setZeroX(tmpXZero);
		}

		// ������ �� ��������� ���������� ����������� Y
		cout << endl << endl << "������� �������� ��������� ����������� Y?(y/n or Y/N): ";
		cin >> select;

		// ��������� ���������� ����������� Y
		if (select == 'y' || select == 'Y')
		{
			double tmpYZero(0);

			cout << endl << endl << "������� ����������� Y: " << sol.getYZero() << endl << "������� �������� ��������� ����������� Y: ";
			cin >> tmpYZero;

			sol.setZeroY(tmpYZero);
		}

		try
		{
			sol.showResult();
		}
		catch (string *message)
		{
			cout << endl << endl << message->c_str() << endl << endl;
		}

		// ������ � ������ �� ���������
		cout << endl << endl << "������� ����� �� ���������? (y/n or Y/N): ";
		cin >> select;

		if (select == 'y' || select == 'Y')
			break;

	} while (true);

	return 0;
}
/*
	����������
*/
// ������� F(x, y)
double FourFunction(double x, double y)
{
	return (std::sin(y) - x + 1);
}

// ������� G(x, y)
double GourFunction(double x, double y)
{
	return (std::tan(x * y) - x - 0.5);
}

// ������� ����������� dF/dx
double dFdxOurFunction(double x, double y)
{
	return -1;
}

// ������� ����������� dF/dy
double dFdyOurFunction(double x, double y)
{
	return (std::cos(y));
}

// ������� ����������� dG/dx
double dGdxOurFunction(double x, double y)
{
	return (-1 + y * (1 / std::cos(x * y)) * (1 / std::cos(x * y)));
}

// ������� ����������� dG/dy
double dGdyOurFunction(double x, double y)
{
	return (x * (1 / std::cos(x * y)) * (1 / std::cos(x * y)));
}