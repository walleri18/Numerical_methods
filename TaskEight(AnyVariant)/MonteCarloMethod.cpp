#include "MonteCarloMethod.h"
#include <time.h>
#include <iostream>

// Конструктор
MonteCarloMethod::MonteCarloMethod(Function FourFunction, double minX,
								   double maxX, double minY, double maxY, int N) :
	FourFunction(FourFunction), minX(minX), maxX(maxX), minY(minY), maxY(maxY), N(N),
	n(0), mediumHeight(0), volumeCylindroid(0)
{}

// Сеттер нашей функции
void MonteCarloMethod::setFourFunction(Function FourFunction)
{
	this->FourFunction = FourFunction;
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

// Вывод результата
void MonteCarloMethod::showResultVolumeCylindroid()
{
	// Обновление и вычисления
	update();

	// Вывод результата
	std::cout << std::endl << std::endl << "Количество сгенерированных точек: " << N
		<< std::endl << "Количество точек попавших в область D: " << n << std::endl
		<< "Выроятность попадания в область D: " << (n / static_cast<double>(N)) * 100 
		<< "%" << std::endl
		<< "Объём цилиндроида в данный момент: " << volumeCylindroid << std::endl;
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
	n = 0;
	mediumHeight = 0;
	volumeCylindroid = 0;
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
		// Если точка попадает в область
		if (vectorX_i[i] > minX && vectorX_i[i] < maxX
			&& vectorY_i[i] > minY && vectorY_i[i] < maxY)
		{
			// Количество попавших точек возрастает
			n++;

			// Заносим точку попадающюю в область
			vectorInDX_i.push_back(vectorX_i[i]);
			vectorInDY_i.push_back(vectorY_i[i]);
		}
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

	// Вычисляем объём цилиндра
	volumeCylindroid = S * mediumHeight;
}
