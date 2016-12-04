#include <iostream>
#include "SolutionSystemNonlinearEquations.h"

/*
	Прототипы
*/
// Функция F(x, y)
double FourFunction(double, double);

// Функция G(x, y)
double GourFunction(double, double);

// Частная производная dF/dx
double dFdxOurFunction(double ,double);

// Частная производная dF/dy
double dFdyOurFunction(double, double);

// Частная производная dG/dx
double dGdxOurFunction(double, double);

// Частная производная dG/dy
double dGdyOurFunction(double, double);

using namespace std;

int main(void)
{
	setlocale(LC_ALL, ".1251");

	// Класс по решению системы нелинейных уравнений
	SolutionSystemNonlinearEquations sol(FourFunction, GourFunction, dFdxOurFunction, dFdyOurFunction, dGdxOurFunction, dGdyOurFunction, 0.3, 3.7, 1.e-6);
	
	// Переменная выбора
	char select(' ');

	do
	{
		// Очистка окна от предыдущих выходных данных
		system("cls");

		// Вопрос об изменении точности вычислений
		cout << endl << endl << "Желаете изменить точность вычислений? (y/n or Y/N): ";
		cin >> select;

		// Изменяем точность на необходимую
		if (select == 'Y' || select == 'y')
		{
			double tmpPrecision(0);

			cout << endl << endl << "Текущая точность: " << sol.getPrecision() << endl << "Введите желаемую точность: ";
			cin >> tmpPrecision;

			sol.setPrecision(tmpPrecision);
		}

		// Вопрос об изменении начального приближения X
		cout << endl << endl << "Желаете изменить начальное приближение X? (y/n or Y/N): ";
		cin >> select;

		// Изменение начального приближения X
		if (select == 'y' || select == 'Y')
		{
			double tmpXZero(0);

			cout << endl << endl << "Текущее приближение X: " << sol.getXZero() << endl << "Введите желаемое начальное приближение X: ";
			cin >> tmpXZero;

			sol.setZeroX(tmpXZero);
		}

		// Вопрос об изменении начального приближения Y
		cout << endl << endl << "Желаете изменить начальное приближение Y?(y/n or Y/N): ";
		cin >> select;

		// Изменение начального приближения Y
		if (select == 'y' || select == 'Y')
		{
			double tmpYZero(0);

			cout << endl << endl << "Текущее приближение Y: " << sol.getYZero() << endl << "Введите желаемое начальное приближение Y: ";
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

		// Вопрос о выходе из программы
		cout << endl << endl << "Желаете выйти из программы? (y/n or Y/N): ";
		cin >> select;

		if (select == 'y' || select == 'Y')
			break;

	} while (true);

	return 0;
}
/*
	Реализация
*/
// Функция F(x, y)
double FourFunction(double x, double y)
{
	return (std::sin(y) - x + 1);
}

// Функция G(x, y)
double GourFunction(double x, double y)
{
	return (std::tan(x * y) - x - 0.5);
}

// Частная производная dF/dx
double dFdxOurFunction(double x, double y)
{
	return -1;
}

// Частная производная dF/dy
double dFdyOurFunction(double x, double y)
{
	return (std::cos(y));
}

// Частная производная dG/dx
double dGdxOurFunction(double x, double y)
{
	return (-1 + y * (1 / std::cos(x * y)) * (1 / std::cos(x * y)));
}

// Частная производная dG/dy
double dGdyOurFunction(double x, double y)
{
	return (x * (1 / std::cos(x * y)) * (1 / std::cos(x * y)));
}