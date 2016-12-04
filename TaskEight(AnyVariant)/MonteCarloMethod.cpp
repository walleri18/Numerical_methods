#include "MonteCarloMethod.h"
#include <time.h>
#include <iostream>

// Конструктор
MonteCarloMethod::MonteCarloMethod(Function FourFunction, double minX,
								   double maxX, double minY, double maxY, int N,
								   std::vector<Comporator> vectorComporator) :
	FourFunction(FourFunction), minX(minX), maxX(maxX), minY(minY), maxY(maxY), N(N),
	n(0), mediumHeight(0), volumeCylindroid(0), vectorComporator(vectorComporator)
{}

// Сеттер нашей функции
void MonteCarloMethod::setFourFunction(Function FourFunction)
{
	this->FourFunction = FourFunction;
}

// Сеттер компараторов
void MonteCarloMethod::setComparator(std::vector<Comporator> vectorComporator)
{
	this->vectorComporator = vectorComporator;
}

// Сеттер минимума X
void MonteCarloMethod::setMinX(double minX)
{
	this->minX = minX;
}

// Геттер минимума X
double MonteCarloMethod::getMinX() const
{
	return this->minX;
}

// Сеттер максимума X
void MonteCarloMethod::setMaxX(double maxX)
{
	this->maxX = maxX;
}

// Геттер максимума X
double MonteCarloMethod::getMaxX() const
{
	return this->maxX;
}

// Сеттер минимума Y
void MonteCarloMethod::setMinY(double minY)
{
	this->minY = minY;
}

// Геттер минимума Y
double MonteCarloMethod::getMinY() const
{
	return this->minY;
}

// Сеттер максимума Y
void MonteCarloMethod::setMaxY(double maxY)
{
	this->maxY = maxY;
}

// Геттер максимума Y
double MonteCarloMethod::getMaxY() const
{
	return this->maxY;
}

// Сеттер количества точек необходимых пользователю. (N)
void MonteCarloMethod::setN(int N)
{
	this->N = N;
}

// Геттер площади поверхности D
double MonteCarloMethod::getS() const
{
	return this->S;
}

// Вывод результата
void MonteCarloMethod::showResultVolumeCylindroid()
{
	// Обновление и вычисления
	update();

	// вывод результата
	std::cout << std::endl << std::endl << "Количество сгенерированных точек: " << N
		<< std::endl << "Количество точек попавших в область d: " << n << std::endl
		<< "Вероятность попадания в область d: " << (n / static_cast<double>(N)) * 100 
		<< "%" << std::endl
		<< "Объём цилиндроида в данный момент: " << this->volumeCylindroid << std::endl;
}

// Обновление данных объекта
void MonteCarloMethod::update()
{
	// Очистка
	clear();

	// Генерация точек
	generationVectorPoints();

	// Выясняем какое количество и какие точки попало в область D
	findValueLittleN();

	// Считаём среднюю высоту
	calculateMediumHeight();

	// Считаем объём цилиндроида
	calculateVolume();
}

// Очистка
void MonteCarloMethod::clear()
{
	this->vectorX_i.clear();
	this->vectorY_i.clear();
	this->vectorInDX_i.clear();
	this->vectorInDY_i.clear();
	this->n = 0;
	this->mediumHeight = 0;
	this->S = 0;
	this->volumeCylindroid = 0;
}

// Генерация точек
void MonteCarloMethod::generationVectorPoints()
{
	// Задаём зерно рандома
	srand(time(NULL));

	// Заполняем вектора X_i и Y_i
	for (int i = 0; i < N; ++i)
	{
		// Случайное число r в диапозоне [0; 1]
		double r = rand() / static_cast<double>(RAND_MAX);

		// Заполняем вектор X_i
		vectorX_i.push_back(minX + r * (maxX - minX));

		// Заново генерируем число r
		r = rand() / static_cast<double>(RAND_MAX);

		// Заполняем вектор Y_i
		vectorY_i.push_back(minY + r * (maxY - minY));
	}
}

// Выясняем какое количество и какие точки попало в область D
void MonteCarloMethod::findValueLittleN()
{
	// Выясняем какое количество точек 
	// удовлетворяет условиям попадания в область D
	for (int i = 0; i < N; ++i)
	{
		// Флаг сигнализирующий о следующей точке
		static bool flag = false;

		// Если точка попадает в область
		for (int j = 0; j < vectorComporator.size(); ++j)
			if (!vectorComporator[j](vectorX_i[i], vectorY_i[i]))
				flag = true;
			else
				flag = false;

		// Если точка не входит в область D
		if (flag)
			continue;

		// Количество попавших точек возрастает
		n++;

		// Заносим точку попадающюю в область
		vectorInDX_i.push_back(vectorX_i[i]);
		vectorInDY_i.push_back(vectorY_i[i]);
		
	}
}

// Считаем среднюю высоту
void MonteCarloMethod::calculateMediumHeight()
{
	// Вычисляем среднюю высоту
	for (int i = 0; i < n; ++i)
		mediumHeight += (FourFunction(vectorInDX_i[i], vectorInDY_i[i]));

	mediumHeight /= n;
}

// Считаем объём цилиндроида
void MonteCarloMethod::calculateVolume()
{
	// Вычисляем площадь основания цилинда. Площадь D.
	double S = (maxX - minX) * (maxY - minY) * (n / static_cast<double>(N));

	// Передаём посчитанное значение площади D в нашу "глобальную переменную" S
	this->S = S;

	// Вычисляем объём цилиндра
	volumeCylindroid = S * mediumHeight;
}
