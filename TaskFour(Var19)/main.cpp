#include <iostream>
#include "Interpol.h"

using namespace std;

double ourFunction(double);

int main(void)
{
	Interpol sol(ourFunction, 0.1, 1.1, 3);

	sol.update();

	vector<double> X_i = sol.getX_i();

	vector<double> Y_i;

	for (size_t i = 0, maxI(X_i.size()); i < maxI; ++i)
	{
		Y_i.push_back(sol.Lagrange(X_i[i]));
	}

	return 0;
}

double ourFunction(double X)
{
	return (1 / X);
}