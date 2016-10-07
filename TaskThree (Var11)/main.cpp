/*
	������ ��������� �������� ����.
	������ 05154.
	������� �3. ������� �11.
	���� �������:
	� ������� ��������� ������� ��������� ����������� ��������.
*/
#include <iostream>
#include <map>

using namespace std;

/*
	��������� ����� �������
*/
// ���� ��������������� �������
double ourFunction(double, map<double, double>&);

// ������� ��������
double SimpsonFormyla(double, double, int, int&, map<double, double>&);

// ������� ��������
double TrapetionFormyla(double, double, int, int&, map<double, double>&);

// ����� ��������
double SimpsonMethod(double, double, double, int&, int&, map<double, double>&);

// ����� ��������
double TrapetionMethod(double, double, double, int&, int&, map<double, double>&);

// ���� � ���������
int main()
{
	// ���������
	setlocale(LC_ALL, ".1251");

	// ������� ����������� � ����������. (���� - ��� ��������, �������� - ��� ��������� �������)
	// �� ����� ����� ��������� ���������� ��������� � ��������������� �������
	map<double, double> mapResultOurFunction;

	// ����� ������� ��������������
	double begin(-2), end(-1);

	// ��������
	double e(1.E-7);

	// ���������� �������� � ������ ��������
	int countIterationTrapetion(0);

	// ���������� ������� � ������ ��������
	int countIterationSimpson(0);

	// ���������� ������� ������� � ������ ��������
	int countCallFunctionTrapetion(0);

	// ���������� ������ ������� � ������ ��������
	int countCallFunctionSimpson(0);

	// ���������� ���������� �������������� ������� ��������
	double resultTrapetion = TrapetionMethod(begin, end, e, countIterationTrapetion, countCallFunctionTrapetion, mapResultOurFunction);

	// ��������� ���������� �������������� ������� ��������
	double resultSimpson = SimpsonMethod(begin, end, e, countIterationSimpson, countCallFunctionSimpson, mapResultOurFunction);

	// ��������� �������� ������
	cout.precision(7);

	// ����� ����������
	cout << "������ ��������� �������� ����. ������ 05154." << endl
		<< "������� �3. ������� �11." << endl
		<< "��������������� �������: (2^x) / (1-4^x)" << endl
		<< "�������� �������������� [" << begin << "; " << end << "]" << endl << endl
		<< "����� ��������:" << endl
		<< "��������� ���������� ��������������: " << resultTrapetion << endl
		<< "���������� ��������: " << countIterationTrapetion << endl
		<< "���������� ������� ��������������� �������: " << countCallFunctionTrapetion << endl << endl << endl
		<< "����� ��������:" << endl
		<< "��������� ���������� ��������������: " << resultSimpson << endl
		<< "���������� ��������: " << countIterationSimpson << endl
		<< "���������� ������� ��������������� �������: " << countCallFunctionSimpson << endl;

	return 0;
}

/*
	���������� ����� �������
*/
// ���� ��������������� �������
double ourFunction(double x, map<double, double> &mapResultOurFunction)
{
	double result(0);

	// ��������� �������
	result = (pow(2, x)) / (1 - pow(4, x));

	// ��������� ��������
	mapResultOurFunction[x] = result;

	return result;
}

// ������� ��������
double SimpsonFormyla(double begin, double end, int N, int &countCallFunction, map<double, double> &mapResultOurFunction)
{
	double result(0);

	// ���������� ������� ������������� ���������� ������� ��������������� �������
	//countCallFunction;

	// ��� h
	double h = (end - begin) / N;

	// ��������� ����� ��� ���������� ������
	double tmpSum(0);

	/*
		���������� �������� �� ������ ������� ��������������
	*/

	// ������� �������� ������� �� ������ ������� ��������������
	// ������� ��������� ���� �� � ��� ��� �������� � �������
	if (mapResultOurFunction.find(begin) == mapResultOurFunction.end())
	{
		// ������� ����� ��������
		tmpSum += ourFunction(begin, mapResultOurFunction);

		// ����������� ������� ����������������� �� ������ ��������������� �������
		countCallFunction++;
	}

	// � ������, ���� � ��� ��� �������� ��� ���� � �������
	else
		tmpSum += mapResultOurFunction[begin];

	// ����������
	if (mapResultOurFunction.find(end) == mapResultOurFunction.end())
	{
		tmpSum += ourFunction(end, mapResultOurFunction);

		countCallFunction++;
	}

	else
		tmpSum += mapResultOurFunction[end];

	/*
		���������� ������ �����
	*/

	// ��������� ����� ��� ������ �����
	double tmpSumFirst(0);

	// ����� �������
	for (int k = 1; k <= (N / 2); k++)
	{
		double argument = begin + h * (2 * k - 1);

		// �������� �� ������������� ���������
		if (mapResultOurFunction.find(argument) == mapResultOurFunction.end())
		{
			tmpSumFirst += ourFunction(argument, mapResultOurFunction);

			countCallFunction++;
		}

		else
			tmpSumFirst += mapResultOurFunction[argument];
	}

	tmpSumFirst *= 4;

	/*
		���������� ������ �����
	*/

	// ��������� ����� ��� ������ �����
	double tmpSumSecond(0);

	// ����� �������
	for (int k = 2; k <= (N / 2); k++)
	{
		double argument = begin + h * (2 * k - 2);

		// �������� �� ������������� ���������
		if (mapResultOurFunction.find(argument) == mapResultOurFunction.end())
		{
			tmpSumSecond += ourFunction(argument, mapResultOurFunction);

			countCallFunction++;
		}

		else
			tmpSumSecond += mapResultOurFunction[argument];
	}

	tmpSumSecond *= 2;

	// ����������� ���� ����
	tmpSum += tmpSumFirst;
	tmpSum += tmpSumSecond;

	// ���������� ���������� �������� � �������: ��������� �� h/3
	tmpSum *= (h / 3);

	// �������� �������������� ���������� � ���������� ��� ����������� �� �������
	result = tmpSum;

	return result;
}

// ������� ��������
double TrapetionFormyla(double begin, double end, int N, int &countCallFunction, map<double, double> &mapResultOurFunction)
{
	double result(0);

	// ���������� ������� ������������� ���������� ������� ��������������� �������
	//countCallFunction;

	// ��� h
	double h = (end - begin) / N;

	// ��������� ����� ��� ���������� ������
	double tmpSum(0);

	/*
		���������� �������� �� ������ ������� ��������������
	*/

	// ������� �������� ������� �� ������ ������� ��������������
	// ������� ��������� ���� �� � ��� ��� �������� � �������
	if (mapResultOurFunction.find(begin) == mapResultOurFunction.end())
	{
		// ������� ����� ��������
		tmpSum += (ourFunction(begin, mapResultOurFunction) / 2.);

		// ����������� ������� ����������������� �� ������ ��������������� �������
		countCallFunction++;
	}

	// � ������, ���� � ��� ��� �������� ��� ���� � �������
	else
		tmpSum += (mapResultOurFunction[begin] / 2.);

	// ����������
	if (mapResultOurFunction.find(end) == mapResultOurFunction.end())
	{
		tmpSum += (ourFunction(end, mapResultOurFunction) / 2.);

		countCallFunction++;
	}

	else
		tmpSum += (mapResultOurFunction[end] / 2.);

	/*
		���������� ������ �����
	*/

	// ��������� ����� ��� ������ �����
	double tmpSumFirst(0);

	// ����� �������
	for (int k = 1; k <= (N - 1); k++)
	{
		double argument = begin + h * k;

		// �������� �� ������������� ���������
		if (mapResultOurFunction.find(argument) == mapResultOurFunction.end())
		{
			tmpSumFirst += ourFunction(argument, mapResultOurFunction);

			countCallFunction++;
		}

		else
			tmpSumFirst += mapResultOurFunction[argument];
	}

	// ����������� ���� ����
	tmpSum += tmpSumFirst;

	// ���������� ���������� �������� � �������: ��������� �� h
	tmpSum *= h;

	// �������� �������������� ���������� � ���������� ��� ����������� �� �������
	result = tmpSum;

	return result;
}

// ����� ��������
double SimpsonMethod(double begin, double end, double e, int &countIteration, int &countCallFunction, map<double, double> &mapResultOurFunction)
{
	double result(0);

	// countIteration - ���������� ��������
	// countCallFunction - ���������� ������ �������

	// ��������� ��������� �������� � ������ �������
	countIteration = 0, countCallFunction = 0;

	// ��������� ���������
	int N = 2;

	/*
		���������� ��� ����������� ������ ���������
	*/
	// ��������� ���������� �������������� ��� N
	double In(0);

	// ���������� ���������� �������������� ��� 2N
	double I2n(0);

	// ������ ��������
	In = SimpsonFormyla(begin, end, N, countCallFunction, mapResultOurFunction);
	I2n = SimpsonFormyla(begin, end, 2 * N, countCallFunction, mapResultOurFunction);

	// ����������� ���������� ��������
	countIteration++;

	// ����� �������
	while ((fabs(I2n - In) / 15) > e)
	{
		// �������� �����
		N *= 2;

		// ����� ��������
		In = I2n;
		I2n = SimpsonFormyla(begin, end, 2 * N, countCallFunction, mapResultOurFunction);

		// ���������� ���������� ��������
		countIteration++;
	}

	// ���������� ����������
	result = I2n;

	return result;
}

// ����� ��������
double TrapetionMethod(double begin, double end, double e, int &countIteration, int &countCallFunction, map<double, double> &mapResultOurFunction)
{
	double result(0);

	// countIteration - ���������� ��������
	// countCallFunction - ���������� ������ �������

	// ��������� ��������� �������� � ������ �������
	countIteration = 0, countCallFunction = 0;

	// ��������� ���������
	int N = 2;

	/*
	���������� ��� ����������� ������ ���������
	*/
	// ��������� ���������� �������������� ��� N
	double In(0);

	// ���������� ���������� �������������� ��� 2N
	double I2n(0);

	// ������ ��������
	In = TrapetionFormyla(begin, end, N, countCallFunction, mapResultOurFunction);
	I2n = TrapetionFormyla(begin, end, 2 * N, countCallFunction, mapResultOurFunction);

	// ����������� ���������� ��������
	countIteration++;

	// ����� �������
	while ((fabs(I2n - In) / 3) > e)
	{
		// �������� �����
		N *= 2;

		// ����� ��������
		In = I2n;
		I2n = TrapetionFormyla(begin, end, 2 * N, countCallFunction, mapResultOurFunction);

		// ���������� ���������� ��������
		countIteration++;
	}

	// ���������� ����������
	result = I2n;

	return result;
}