#include "SolutionEquation.h"

int main(void)
{
	SolutionEquation sol(-1.8, 0, 1.E-9);

	sol.NewtonMethod();

	return 0;
}