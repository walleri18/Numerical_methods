#pragma once
#include <vector>

// New type point Function
typedef double(*Function)(double);

/*
	Interpolation for Lagrange
*/
class Interpol
{
// Data
private:

	// Point ourFunction
	Function ourFunction;

	// Count segment interpolation (n)
	size_t n;

	// Begin segment (a)
	double a;

	// End segment (b)
	double b;

	// Vector X_i
	std::vector<double> X_i;

	// Vector Y_i
	std::vector<double> Y_i;

// Interface (API)
public:

	// Constryktor
	Interpol(Function ourFunction, double a, double b, size_t n);

	// Setter value (n)
	void setValueN(size_t n);

	// Setter begin segment (a)
	void setValueA(double a);

	// Setter end segment (b)
	void setValueB(double b);

	// Getter vector X_i
	std::vector<double> getX_i() const;

	// Getter vector Y_i
	std::vector<double> getY_i() const;

	// Update interpolation formyla and data
	void update();

	// Interpol function Lagrange
	double Lagrange(double X);

// Functional
private:

	// Clear vectors data
	void clear();

	// Root Chebichev
	double rootChebichev(size_t i);

	// Created X_i
	void createdVectorX_i();

	// Created Y_i
	void createdVectorY_i();

};

