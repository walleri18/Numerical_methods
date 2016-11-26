#include "MonteCarloMethod.h"
#include <time.h>
#include <iostream>

// �����������
MonteCarloMethod::MonteCarloMethod(Function FourFunction, double minX,
								   double maxX, double minY, double maxY, int N) :
	FourFunction(FourFunction), minX(minX), maxX(maxX), minY(minY), maxY(maxY), N(N),
	n(0), mediumHeight(0), volumeCylindroid(0)
{}

// ������ ����� �������
void MonteCarloMethod::setFourFunction(Function FourFunction)
{
	this->FourFunction = FourFunction;
}

// ������ �������� X
void MonteCarloMethod::setMinX(double minX)
{
	this->minX = minX;
}

// ������ �������� X
double MonteCarloMethod::getMinX() const
{
	return this->minX;
}

// ������ ��������� X
void MonteCarloMethod::setMaxX(double maxX)
{
	this->maxX = maxX;
}

// ������ ��������� X
double MonteCarloMethod::getMaxX() const
{
	return this->maxX;
}

// ������ �������� Y
void MonteCarloMethod::setMinY(double minY)
{
	this->minY = minY;
}

// ������ �������� Y
double MonteCarloMethod::getMinY() const
{
	return this->minY;
}

// ������ ��������� Y
void MonteCarloMethod::setMaxY(double maxY)
{
	this->maxY = maxY;
}

// ������ ��������� Y
double MonteCarloMethod::getMaxY() const
{
	return this->maxY;
}

// ����� ����������
void MonteCarloMethod::showResultVolumeCylindroid()
{
	// ���������� � ����������
	update();

	// ����� ����������
	std::cout << std::endl << std::endl << "���������� ��������������� �����: " << N
		<< std::endl << "���������� ����� �������� � ������� D: " << n << std::endl
		<< "����������� ��������� � ������� D: " << (n / static_cast<double>(N)) * 100 
		<< "%" << std::endl
		<< "����� ����������� � ������ ������: " << volumeCylindroid << std::endl;
}

// ���������� ������ �������
void MonteCarloMethod::update()
{
	// �������
	clear();

	// ��������� �����
	generationVectorPoints();

	// �������� ����� ���������� � ����� ����� ������ � ������� D
	findValueLittleN();

	// ������ ������� ������
	calculateMediumHeight();

	// ������� ����� �����������
	calculateVolume();
}

// �������
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

// ��������� �����
void MonteCarloMethod::generationVectorPoints()
{
	// ����� ����� �������
	srand(time(NULL));

	// ��������� ������� X_i � Y_i
	for (int i = 0; i < N; ++i)
	{
		// ��������� ����� r � ��������� [0; 1]
		double r = rand() / static_cast<double>(RAND_MAX);

		// ��������� ������ X_i
		vectorX_i.push_back(minX + r * (maxX - minX));

		// ������ ���������� ����� r
		r = rand() / static_cast<double>(RAND_MAX);

		// ��������� ������ Y_i
		vectorY_i.push_back(minY + r * (maxY - minY));
	}
}

// �������� ����� ���������� � ����� ����� ������ � ������� D
void MonteCarloMethod::findValueLittleN()
{
	// �������� ����� ���������� ����� 
	// ������������� �������� ��������� � ������� D
	for (int i = 0; i < N; ++i)
	{
		// ���� ����� �������� � �������
		if (vectorX_i[i] > minX && vectorX_i[i] < maxX
			&& vectorY_i[i] > minY && vectorY_i[i] < maxY)
		{
			// ���������� �������� ����� ����������
			n++;

			// ������� ����� ���������� � �������
			vectorInDX_i.push_back(vectorX_i[i]);
			vectorInDY_i.push_back(vectorY_i[i]);
		}
	}
}

// ������� ������� ������
void MonteCarloMethod::calculateMediumHeight()
{
	// ��������� ������� ������
	for (int i = 0; i < n; ++i)
		mediumHeight += (FourFunction(vectorInDX_i[i], vectorInDY_i[i]));

	mediumHeight /= n;
}

// ������� ����� �����������
void MonteCarloMethod::calculateVolume()
{
	// ��������� ������� ��������� �������. ������� D.
	double S = (maxX - minX) * (maxY - minY) * (n / static_cast<double>(N));

	// ��������� ����� ��������
	volumeCylindroid = S * mediumHeight;
}
