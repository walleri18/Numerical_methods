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

	matrix.update();

	// ������� ������� �������
	matrix.showSourseMatrix();

	// ������� ������� �������� �������
	matrix.showInverseMatrix();

	// ������� ������� ��������� ������� (B)
	matrix.showEMatrix();

	// ������� ������� ����������� �������� �������
	matrix.showDeterminantSourseMatrix();

	// ������� ������� ����������� �������� �������
	matrix.showDeterminantInverseMatrix();

	// ������� ������� ����� ���������������
	matrix.showConditionNumber();

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

	result = static_cast<typeElementMatrix>(1) / static_cast<typeElementMatrix>(cos(static_cast<typeElementMatrix>(i) - j) * cos(static_cast<typeElementMatrix>(i) - j));

	return result;
}