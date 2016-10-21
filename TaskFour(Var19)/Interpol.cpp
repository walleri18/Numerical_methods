#define _USE_MATH_DEFINES
#include "Interpol.h"
#include <cmath>

// Constryktor
Interpol::Interpol(Function ourFunction, double a, double b, size_t n)
	: ourFunction(ourFunction), a(a), b(b), n(n)
{}

// Setter value (n)
void Interpol::setValueN(size_t n)
{
	this->n = n;
}

// Setter begin segment (a)
void Interpol::setValueA(double a)
{
	this->a = a;
}

// Setter end segment (b)
void Interpol::setValueB(double b)
{
	this->b = b;
}

// Getter vector X_i
std::vector<double> Interpol::getX_i() const
{
	return this->X_i;
}

// Getter vector Y_i
std::vector<double> Interpol::getY_i() const
{
	return this->Y_i;
}

// Update interpolation formyla and data
void Interpol::update()
{
	clear();

	createdVectorX_i();

	createdVectorY_i();
}

// Interpol function Lagrange
double Interpol::Lagrange(double X)
{
	double Y_result(0);

	for (size_t i = 0; i <= n; ++i)
	{
		double tmp;

		tmp = Y_i[i];

		for (size_t j = 0; j <= n; ++j)
		{
			if (j != i)
				tmp *= ((X - X_i[j]) / (X_i[i] - X_i[j]));
		}

		Y_result += tmp;
	}

	return Y_result;
}

// Clear vectors data
void Interpol::clear()
{
	X_i.clear();

	Y_i.clear();
}

// Root Chebichev
double Interpol::rootChebichev(size_t i)
{
	double result;
	
	result = (-std::cos(((static_cast<double>(2 * i) + 1) / (static_cast<double>(2 * n) + 2)) * M_PI));

	return result;
}

// Created X_i
void Interpol::createdVectorX_i()
{
	//double h = (b - a) / n;

	for (size_t i = 0, maxI(n + 1); i < maxI; ++i)
	{
		double tmp = (b + a) / 2;
		tmp += ((b - a) / 2) * rootChebichev(i);

		//tmp = a + i * h;

		X_i.push_back(tmp);
	}
}

// Created Y_i
void Interpol::createdVectorY_i()
{
	for (size_t i = 0, maxI(X_i.size()); i < maxI; ++i)
	{
		Y_i.push_back(ourFunction(X_i[i]));
	}
}
