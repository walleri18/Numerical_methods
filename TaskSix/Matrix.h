#pragma once
#include <vector>

// ��� ��������� �������
typedef long double typeElementMatrix;

// ��� �������
typedef std::vector< std::vector<typeElementMatrix>* > typeMatrix;

// ��� ����������� ������� � ������� ������� �� ����� ��������� �������
typedef typeElementMatrix(*Function)(int, int);

/*
	����� Matrix
	��������� �����������:
	1) ���������� ������� �� ����������� �������;
	2) ���������� ������������ ���� ������� (�� ������ ������)
	3) ���������� �������� ������� (�� ������ ������)
	4) ���������� ��������� ������� (������� ���������)(� ������� ������������ �������� ������� �� ��������)
	5) ����� ����� ���������������
*/
class Matrix
{
// ������
private:

	// ������� ��� ������� ��������� �������
	Function ourFunction;

	// ������� ������� (n)
	int n;

	// ������� �������� (A)
	typeMatrix sourseMatrix;

	// ������� �������� (A^(-1))
	typeMatrix inverseMatrix;

	// ��������� ������� (B)
	typeMatrix EMatrix;

// ����������������
public:

	// �����������
	Matrix(Function ourFunction, int n);

	// ������ �������� �������
	typeMatrix getSourseMatrix() const;

	// ������ �������� �������
	typeMatrix getInverseMatrix() const;

	// ������ ��������� �������
	typeMatrix getEMatrix() const;

	// ����� �������� �������
	void showSourseMatrix();

	// ����� �������� �������
	void showInverseMatrix();

	// ����� ��������� �������
	void showEMatrix();

	// ����� ������������ �������� �������
	void showDeterminantSourseMatrix();

	// ����� ������������ �������� �������
	void showDeterminantInverseMatrix();

	// ����� ����� ���������������
	void showConditionNumber();

	// ���������� ������� � ����������� ��� ��
	void update();

private:

	// ������� ������� ������
	void clear();

	// ������� ������ �������
	void showMatrix(typeMatrix matrix);

	// ������� ���������� ������������
	typeElementMatrix determinantMatrix(typeMatrix matrix);

	// ����� ����� ���������������
	typeElementMatrix findConditionNumber();

	// �������� �������� ������� (A)
	void createdSourseMatrix();

	// ���������� �������� ������� (A^(-1))
	void createdInverseMatrix();

	// ���������� ��������� �������. (B)
	void createdEMatrix();

};