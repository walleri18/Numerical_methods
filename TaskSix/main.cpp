/*
	������� �6. ������� �16.
	�����: ����� ������� �������������
	������: 05154
	���� �������:
	1) ��������� ������� �� ����������� �������
	2) ��������� � �����������
	3) ����� �������� �������
	4) ��������� ������������ ���������� � ������� ��������� �������� ������� �� ��������
	5) ����� ����� ���������������
*/

#include "Matrix.h"
#include <iostream>

using namespace std;

/*
	���������
*/
// ���� �������
typeElementMatrix ourFunction(int i, int j);

int main(void)
{
	setlocale(LC_ALL, ".1251");

	cout << "������ �6. ������� �16." << endl << endl;

	// ������������ ������ ������
	Matrix matrix(ourFunction, 2);

	try
	{
		matrix.update();
	}
	catch (...)
	{
		cout << endl << endl << "���������� ����� �������� �������" << endl << endl;

		// ������� ������� �������� �������
		matrix.showSourseMatrix();

		return 1;
	}

	// ������� ������� �������� �������
	matrix.showSourseMatrix();

	// ������� ������� �������� �������
	matrix.showInverseMatrix();

	// ������� ������� ��������� ������� (B)
	matrix.showEMatrix();

	try
	{
		// ������� ������� ����������� �������� �������
		matrix.showDeterminantSourseMatrix();
	}
	catch (...)
	{
		cout << endl << endl << "���������� ��������� ����������� �������� �������" << endl << endl;

		return 1;
	}

	try
	{
		// ������� ������� ����������� �������� �������
		matrix.showDeterminantInverseMatrix();
	}
	catch (...)
	{
		cout << endl << endl << "���������� ��������� ����������� �������� �������" << endl << endl;

		return 1;
	}

	// ������� ������� ����� ���������������
	matrix.showConditionNumber();

	// ����� � �����
	matrix.saveFileSourseMatrix();
	matrix.saveFileInverseMatrix();
	matrix.saveFileEMatrix();

	cout << endl;

	return 0;
}
/*
	����������
*/
// ���� �������
typeElementMatrix ourFunction(int i, int j)
{
	typeElementMatrix result(0);

	result = 1 / (cos(i - j) * cos(i - j));

	//result = 1 / sin(i + j);

	return result;
}