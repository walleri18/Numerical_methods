#include <iostream>
#include <iomanip>
#include "MonteCarloMethod.h"

/*
	Прототипы
*/
// Наша функция F(x, y)
double FourFunction(double x, double y);

/*
	Компораторы
*/
bool ComOne(double x, double y);
bool ComTwo(double x, double y);

using namespace std;

int main(void)
{
	setlocale(LC_ALL, ".1251");

	// Векторов компараторов
	vector<Comporator> vectorComporator;

	vectorComporator.push_back(ComOne);
	vectorComporator.push_back(ComTwo);

	// Объект для расчёта объёма цилиндроида
	MonteCarloMethod solve(FourFunction, -1, 1, -1, 1, 1000, vectorComporator);

	// Результаты числа при разных количествах разбиениях
	vector<double> vectorPI;

	// Вычисление числа PI при разном количестве точек и вывод
	for (int i = 0, N = 100; i < 5; i++)
	{
		// Устанавливаем величину N
		solve.setN(N *= 10);

		// Обновляем данные объекта и считаем
		solve.showResultVolumeCylindroid();

		// Вычисляем число PI
		vectorPI.push_back(solve.getS());

		// Выводим число PI
		cout << endl << endl << "При количестве сгенерированных точек: " << N << endl
			<< "Число PI: " << setprecision(16) << vectorPI[i];
	}

	cout << endl;

	return 0;
}
/*
	Реализации
*/
// Наша функция F(x, y)
double FourFunction(double x, double y)
{
	return sqrt(1 - x * x - y * y);
}

/*
	Компораторы
*/
bool ComOne(double x, double y)
{
	return (x > -1 && x < 1);
}

bool ComTwo(double x, double y)
{
	return (y > (-sqrt(1 - x * x)) && y < sqrt(1 - x * x));
}
