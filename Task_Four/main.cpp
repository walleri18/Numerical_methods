/*
	Работу выполнил:
	студент 2 курса по направлению Информационные системы и технологии
	Туров Виталий Александрович

	Задание №4. Вариант №16.
	Суть работы заключается в том, чтобы с помощью метода Бесселя получить интерполяционную формулу.
	И построить таблицы и графики исходной нашей функции и интерполирующей функции.

	Всё математическое ядро будет написано и протестированно в VS, а реализацию GUI будем делать в Qt.

*/
#include <iostream>
#include <cmath>

using namespace std;

/*
	Прототипы
*/
// Наша исходная функция
double ourFunction(double);

int main(void)
{
	// Установка кодировки 1251
	setlocale(LC_ALL, ".1251");

	

	return 0;
}

// Наша исходная функция
double ourFunction(double argument)
{
	double resultOurFunction(0);

	if (argument != 0)
		resultOurFunction = exp(argument) / argument;

	return resultOurFunction;
}