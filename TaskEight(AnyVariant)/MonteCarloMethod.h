#pragma once

#include <vector>

// ��������� �� ������� ���� ���������
typedef double (*Function)(double, double);

// ��������� �� ������� �������� ��������� ����� � ������� D
typedef bool (*Comporator)(double, double);

/*
	����� ����������� ����� 
	�����-����� ��� ����������
	������ �����������
*/
class MonteCarloMethod
{
// ������
private:

	// ���� ������� ����������� F(x, y)
	Function FourFunction;

	// ������ ������� �������� �� ��������� ����� � ������� D
	std::vector<Comporator> vectorComporator;

	/*
		������ �� ����������� D
	*/
	// ����������� X. (������� �������������)
	double minX;

	// ������������ X. (������� �������������)
	double maxX;

	// ����������� Y. (������� �������������)
	double minY;

	// ������������ Y. (������� �������������)
	double maxY;

	// ������� ��������� �����������
	double baseAreaCylindroid;

	/*
		������ ��� ����������
		������ �����������
	*/
	// ������� ������ �����������
	double mediumHeight;

	// ������ ��������� ����� X_i
	std::vector<double> vectorX_i;

	// ������ ��������� ����� Y_i
	std::vector<double> vectorY_i;

	// ���������� ����� �������� �� ����������� D
	int n;

	// ������ X_i �������� ����� � ������� D
	std::vector<double> vectorInDX_i;

	// ������ Y_i �������� ����� � ������� D
	std::vector<double> vectorInDY_i;

	// ���������� ����� ��������������. (������� �������������)
	int N;

	/*
		��������� ������ ���������
	*/
	// ����� �����������
	double volumeCylindroid;

// ����������
public:

	// �����������
	MonteCarloMethod(Function FourFunction, double minX, 
					 double maxX, double minY, double maxY, int N,
					 std::vector<Comporator> vectorComporator);

	// ������ ����� �������
	void setFourFunction(Function FourFunction);

	// ������ ������������
	void setComparator(std::vector<Comporator> vectorComporator);

	// ������ �������� X
	void setMinX(double minX);

	// ������ �������� X
	double getMinX() const;

	// ������ ��������� X
	void setMaxX(double maxX);

	// ������ ��������� X
	double getMaxX() const;

	// ������ �������� Y
	void setMinY(double minY);

	// ������ �������� Y
	double getMinY() const;

	// ������ ��������� Y
	void setMaxY(double maxY);

	// ������ ��������� Y
	double getMaxY() const;

	// ����� ����������
	void showResultVolumeCylindroid();

private:

	// ���������� ������ �������
	void update();

	// �������
	void clear();

	// ��������� �����
	void generationVectorPoints();

	// �������� ����� ���������� � ����� ����� ������ � ������� D
	void findValueLittleN();

	// ������� ������� ������
	void calculateMediumHeight();

	// ������� ����� �����������
	void calculateVolume();
};