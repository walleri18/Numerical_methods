#pragma once

#include <vector>

// Указатель на функцию двух пременных
typedef double (*Function)(double, double);

// Указатель на функцию проверки вхождения точки в область D
typedef bool (*Comporator)(double, double);

/*
	Класс реализующий метод 
	Монте-Карло для вычисления
	объёма цилиндроида
*/
class MonteCarloMethod
{
// Данные
private:

	// Наша функция поверхности F(x, y)
	Function FourFunction;

	// Вектор функций проверок на вхождение точки в область D
	std::vector<Comporator> vectorComporator;

	/*
		Данные об поверхности D
	*/
	// Минимальный X. (Задаётся пользователем)
	double minX;

	// Максимальный X. (Задаётся пользователем)
	double maxX;

	// Минимальный Y. (Задаётся пользователем)
	double minY;

	// Максимальный Y. (Задаётся пользователем)
	double maxY;

	// Площадь основания цилиндроида
	double baseAreaCylindroid;

	/*
		Данные для вычисления
		объёма цилиндроида
	*/
	// Средняя высота цилиндроида
	double mediumHeight;

	// Вектор случайных точек X_i
	std::vector<double> vectorX_i;

	// Вектор случайных точек Y_i
	std::vector<double> vectorY_i;

	// Количество точек попавших на поверхность D
	int n;

	// Вектор X_i попавших точек в область D
	std::vector<double> vectorInDX_i;

	// Вектор Y_i попавших точек в область D
	std::vector<double> vectorInDY_i;

	// Количество точек сгенерированно. (Задаётся пользователем)
	int N;

	/*
		Результат работы программы
	*/
	// Объём цилиндроида
	double volumeCylindroid;

// Функционал
public:

	// Конструктор
	MonteCarloMethod(Function FourFunction, double minX, 
					 double maxX, double minY, double maxY, int N,
					 std::vector<Comporator> vectorComporator);

	// Сеттер нашей функции
	void setFourFunction(Function FourFunction);

	// Сеттер компараторов
	void setComparator(std::vector<Comporator> vectorComporator);

	// Сеттер минимума X
	void setMinX(double minX);

	// Геттер минимума X
	double getMinX() const;

	// Сеттер максимума X
	void setMaxX(double maxX);

	// Геттер максимума X
	double getMaxX() const;

	// Сеттер минимума Y
	void setMinY(double minY);

	// Геттер минимума Y
	double getMinY() const;

	// Сеттер максимума Y
	void setMaxY(double maxY);

	// Геттер максимума Y
	double getMaxY() const;

	// Вывод результата
	void showResultVolumeCylindroid();

private:

	// Обновление данных объекта
	void update();

	// Очистка
	void clear();

	// Генерация точек
	void generationVectorPoints();

	// Выясняем какое количество и какие точки попало в область D
	void findValueLittleN();

	// Считаем среднюю высоту
	void calculateMediumHeight();

	// Считаем объём цилиндроида
	void calculateVolume();
};