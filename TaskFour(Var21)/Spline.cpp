#include "Spline.h"

// Конструктор
Spline::Spline(Function ourFunction, double beginSegment, double endSegment, int N) : ourFunction(ourFunction), beginSegment(beginSegment), endSegment(endSegment), N(N)
{
}

// Функция интерполирования
double Spline::Interpol(double X)
{
	double result(0);

	// Определение i
	int i = findIndex(X);

	// Считаем шаг
	double h = (endSegment - beginSegment) / N;

	// Первое слагаемое
	result = ((((x_i[i + 1] - X) * (x_i[i + 1] - X) * (h + 2 * (X - x_i[i])))/(h * h * h)) * y_i[i]);

	// Второе слагаемое
	result += ((((X - x_i[i]) * (X - x_i[i]) * (h + 2 * (x_i[i + 1] - X))) / (h * h * h)) * y_i[i + 1]);

	// Третье слагаемое
	result += ((((x_i[i + 1] - X) * (x_i[i + 1] - X) * (X - x_i[i])) /(h * h)) * m_i[i]);

	// Четвёртое слагаемое
	result += ((((X - x_i[i]) * (X - x_i[i]) * (X - x_i[i + 1])) / (h * h)) * m_i[i + 1]);

	return result;
}

// Сеттер величины N
void Spline::setValueN(int N)
{
	this->N = N;
}

// Сеттер величины начала отрезка
void Spline::setBeginSegment(double beginSegment)
{
	this->beginSegment = beginSegment;
}

// Сеттер величины конца отрезка
void Spline::setEndSegment(double endSegment)
{
	this->endSegment = endSegment;
}

// Геттер x_i
std::vector<double> Spline::getX_i() const
{
	return this->x_i;
}

// Геттер y_i
std::vector<double> Spline::getY_i() const
{
    return this->y_i;
}

// Геттер x_j
std::vector<double> Spline::getX_j() const
{
    return this->x_j;
}

// Геттер y_jSourse
std::vector<double> Spline::getY_jSourse() const
{
    return this->y_jSourse;
}

// Геттер y_jInterpol
std::vector<double> Spline::getY_jInterpol() const
{
    return this->y_jInterpol;
}

// Обновление интерполяции
void Spline::update()
{
	// Очистка
	clear();

	// Генерирование x_i
	createdX_i();

	// Генерирование y_i
	createdY_i();

	// Генерирование m_i
	createdM_i();

	// Генерирование x_j
	createdX_j();

	// Генерирование y_jSourse
	createdY_jSourse();

	// Генерирование y_jInterpol
	createdY_jInterpol();

}

// Очистка векторов
void Spline::clear()
{
	this->x_i.clear();

	this->y_i.clear();

	this->m_i.clear();

	this->x_j.clear();

	this->y_jSourse.clear();

	this->y_jInterpol.clear();
}

// Генерирование x_i
void Spline::createdX_i()
{
	// Шаг
	double h = (endSegment - beginSegment) / N;

	for (int i = 0; i <= N; i++)
	{
		x_i.push_back(beginSegment + i * h);
	}
}

// Генерирование y_i
void Spline::createdY_i()
{
	for (int i = 0, maxI(x_i.size()); i < maxI; i++)
	{
		y_i.push_back(ourFunction(x_i[i]));
	}
}

// Генерирование m_i
void Spline::createdM_i()
{
	// Шаг
	double h = (endSegment - beginSegment) / N;

	// Выделеяем определённое количество элементов и зануляем
	m_i.assign(N + 1, 0);

	// Нулевой элемент рассчитываем
	m_i[0] = ((4 * y_i[1] - y_i[2] - 3 * y_i[0]) / (2 * h));

	// i-ые элементы
	for (int i = 1; i < (N - 1); i++)
	{
		m_i[i] = ((y_i[i + 1] - y_i[i - 1]) / (2 * h));
	}

	// n-ый элемент
	m_i[N] = ((3 * y_i[N] + y_i[N - 2] - 4 * y_i[N - 1]) / (2 * h));
}

// Генерирование x_j
void Spline::createdX_j()
{
	// Шаг
	double h = 0.5;

	for (int i = 0; i < 13; i++)
	{
		x_j.push_back(-3 + h * i);
	}
}

// Генерирование y_jSourse
void Spline::createdY_jSourse()
{
	for (int i = 0, maxI(x_j.size()); i < maxI; i++)
	{
		y_jSourse.push_back(ourFunction(x_j[i]));
	}
}

// Генерирование y_jInterpol
void Spline::createdY_jInterpol()
{
	for (int i = 0, maxI(x_j.size()); i < maxI; i++)
	{
		y_jInterpol.push_back(Interpol(x_j[i]));
	}
}

// Поиск индекса начального узла между которыми расположен X
int Spline::findIndex(double X)
{
	int result(-1);

	for (int i = 0; i < N; i++)
	{
		if ((X < x_i[i + 1]) && (X >= x_i[i]))
			result = i;
	}

	if (result == -1)
	{
		if (X > x_i[N])
			result = N - 1;

		else if (X < x_i[0])
			result = 0;
	}

	return result;
}
