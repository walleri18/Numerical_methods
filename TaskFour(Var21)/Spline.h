#pragma once
#include <vector>

// Тип указателя на функцию
typedef double (*Function)(double);

/*
	Класс интерполияции по сплайну
*/
class Spline
{
// Данные
private:

	// Вектор узлов интерполирования (x_i)
	std::vector<double> x_i;

	// Вектор узлов интерполирования (y_i)
	std::vector<double> y_i;

	// Вектор наклонов (m_i)
	std::vector<double> m_i;

	// Вектор x_j для таблицы
	std::vector<double> x_j;

	// Вектор y_jSourse для таблицы
	std::vector<double> y_jSourse;

	// Вектор y_jInterpol для таблицы
	std::vector<double> y_jInterpol;

	// Указатель на нашу функцию
	Function ourFunction;
	
	// Величина N - количество отрезков интерполирования
	// Минимальное число это два (2)!!!
	int N;

	// Начало отрезка интерполирования
	double beginSegment;

	// Конец отрезка интерполирования
	double endSegment;

// Функциональность
public:

	// Конструктор
	Spline(Function ourFunction, double beginSegment, double endSegment, int N);

	// Функция интерполирования
	double Interpol(double X);

	// Сеттер величины N
	void setValueN(int N);

	// Сеттер величины начала отрезка
	void setBeginSegment(double beginSegment);

	// Сеттер величины конца отрезка
	void setEndSegment(double endSegment);

	// Геттер x_i
	std::vector<double> getX_i() const;

	// Геттер y_i
	std::vector<double> getY_i() const;

    // Геттер x_j
    std::vector<double> getX_j() const;

    // Геттер y_jSourse
    std::vector<double> getY_jSourse() const;

    // Геттер y_jInterpol
    std::vector<double> getY_jInterpol() const;

	// Обновление интерполяции
	void update();

private:

	// Очистка векторов
	void clear();

	// Генерирование x_i
	void createdX_i();

	// Генерирование y_i
	void createdY_i();

	// Генерирование m_i
	void createdM_i();

	// Генерирование x_j
	void createdX_j();

	// Генерирование y_jSourse
	void createdY_jSourse();

	// Генерирование y_jInterpol
	void createdY_jInterpol();

	// Поиск индекса начального узла между которыми расположен X
	int findIndex(double X);

};
