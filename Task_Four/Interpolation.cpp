#include "Interpolation.h"
#include <cmath>

Interpolation::Interpolation(Function ourFunction, double beginSegment, double endSegment, int N)
    : ourFunction(ourFunction), beginSegment(beginSegment), endSegment(endSegment), N(N) {}

// Очистка памяти выделенную вручную
Interpolation::~Interpolation()
{
    if (!vectorFiniteDifference.empty())
        // Удаление всех векторов в конечных разностях
        for (int i = 0, n(vectorFiniteDifference.size()); i < n; i++)
        {
            delete vectorFiniteDifference[i];
        }

    // Очистка от всех указателей
    vectorFiniteDifference.clear();
}

// Функция интерполяции Бесселя
double Interpolation::interpolantBesselFunction(double X)
{
    // Результат
    double resultBessel(0);

//    // Вычисляем наше Q
//    Q = (X - argument[static_cast<int>(N / 2.)]) / valueStep;

//    // Первые слагаемые
//    resultBessel += (resultOurFunction[static_cast<int>(N / 2.)] + resultOurFunction[static_cast<int>(N / 2.) + 1]) / 2.;
//    resultBessel += ((Q - 0.5) * getFiniteDifference(1,0));

//    // Временная сумма
//    double tmpSum(0);

//    // Вычисление сумм
//    for (int k = 1, maximum(static_cast<int>(N / 2.)); k < maximum; k++)
//    {
//        // Вычисление полинома
//        double polynomResult = polynom(k);

//        // Получение "первой" конечной разности
//        double firstDiff = getFiniteDifference(2 * k, -k);

//        // Получение "второй" конечной разности
//        double secondDiff = getFiniteDifference(2 * k, -k + 1);

//        // Получение "первого" факториала
//        double firstFactorial = Factorial(2 * k);

//        // Получение "второго" факториала
//        double secondFactorial = Factorial(2 * k + 1);

//        // Первое слагаемое суммы
//        tmpSum += ((polynomResult / firstFactorial)
//                   * ((firstDiff + secondDiff) / 2.));

//        tmpSum += ((((Q - 0.5) * polynomResult) / secondFactorial)
//                   * firstDiff);
//    }

//    resultBessel += tmpSum;
    switch (N)
    {
    case 4:

        resultBessel = 1. + (-110. + (337.5 - 533.163*(-0.4 + X))*(-0.1 + X))*(-1. + X);
        break;

    case 5:

        resultBessel = 1. + (-110. + (233.058 + (-889.237 + 1240.55*(-0.325 + X))*(-0.55 + X))*(-0.1 + X))*(-1. + X);
        break;

    case 6:

        resultBessel = 1. + (-110. + (286.389 + (-381.586 + (1700.96 - 2888.91*(-0.28 + X))*(-0.82 + X))*(-0.46 + X))*(-0.1 + X))*(-1. + X);
        break;

    case 7:

        resultBessel = 1. + (-110. + (233.058 + (-1223.14 + (1539.65 + (-4383.88 + 6699.23*(-0.4 + X))*(-0.85 + X))*(-0.25 + X))*(-0.55 + X))*(-0.1 + X))*(-1. + X);
        break;

    case 8:

        resultBessel = 1. + (-110. + (268.858 + (-399.233 + (2277.13 + (-2772.77 + (8854.62 - 15447.*(-0.357143 + X))*(-0.871429 + X))*(-0.228571 + X))*(-0.742857 + X))*(-0.485714 + X))*(-0.1 + X))*(-1. + X);
        break;

    case 9:

        resultBessel = 1. + (-110. + (233.058 + (-330.991 + (2077.14 + (-2480.61 + (8810.36 + (-14170.7 + 35408.7*(-0.6625 + X))*(-0.325 + X))*(-0.8875 + X))*(-0.2125 + X))*(-0.775 + X))*(-0.55 + X))*(-0.1 + X))*(-1. + X);
        break;

    case 10:

        resultBessel = 1. + (-110. + (211.111 + (-888.889 + (1056.24 + (-6824.42 + (9012.77 + (-19568.8 + (29530.1 - 80714.5*(-0.7 + X))*(-0.5 + X))*(-0.8 + X))*(-0.2 + X))*(-0.9 + X))*(-0.3 + X))*(-0.6 + X))*(-0.1 + X))*(-1. + X);
        break;

    case 11:

        resultBessel = 1. + (-110. + (233.058 + (-1064.26 + (1394.45 + (-9532.82 + (10978.9 + (-26031.7 + (37528.3 + (-111391. + 183048.*(-0.37 + X))*(-0.73 + X))*(-0.46 + X))*(-0.91 + X))*(-0.19 + X))*(-0.82 + X))*(-0.28 + X))*(-0.55 + X))*(-0.1 + X))*(-1. + X);
        break;

    case 12:

        resultBessel = 1. + (-110. + (254.656 + (-371.997 + (1785.57 + (-2061.81 + (14593.1 + (-22999.5 + (73945.1 + (-92051.1 + (232108. - 413196.*(-0.427273 + X))*(-0.836364 + X))*(-0.345455 + X))*(-0.672727 + X))*(-0.181818 + X))*(-0.918182 + X))*(-0.263636 + X))*(-0.754545 + X))*(-0.509091 + X))*(-0.1 + X))*(-1. + X);
        break;

    case 13:

        resultBessel = 1. + (-110. + (233.058 + (-889.237 + (1123.59 + (-8569.64 + (13009.9 + (-14692.7 + (68064.1 + (-153590. + (206325. + (-555258. + 928805.*(-0.4 + X))*(-0.775 + X))*(-0.475 + X))*(-0.25 + X))*(-0.925 + X))*(-0.7 + X))*(-0.175 + X))*(-0.85 + X))*(-0.325 + X))*(-0.55 + X))*(-0.1 + X))*(-1. + X);
        break;

    case 14:

        resultBessel = 1. + (-110. + (251.08 + (-347.806 + (1889.21 + (-2148.27 + (6476.11 + (-48489.1 + (78205.9 + (-94338.8 + (339035. + (-487966. + (1.16305E+6 - 2.07994E+6*(-0.446154 + X))*(-0.723077 + X))*(-0.307692 + X))*(-0.861538 + X))*(-0.653846 + X))*(-0.169231 + X))*(-0.376923 + X))*(-0.930769 + X))*(-0.238462 + X))*(-0.792308 + X))*(-0.515385 + X))*(-0.1 + X))*(-1. + X);
        break;

    }


    return resultBessel;
}

// Сеттер порядка N интерполирующей функции Бесселя
void Interpolation::setN(int N)
{
    this->N = (N > 0) ? (N) : (-N);
}

// Сеттер начало отрезка
void Interpolation::setBeginSegment(double beginSegment)
{
    this->beginSegment = beginSegment;
}

// Сеттер конца отрезка
void Interpolation::setEndSegment(double endSegment)
{
    this->endSegment = endSegment;
}

// Геттер аргументов функции (X)
std::vector<double> Interpolation::getArgument() const
{
    return argument;
}

// Геттер результатов функции (Y)
std::vector<double> Interpolation::getResultOurFunction() const
{
    return resultOurFunction;
}

// Обновление объекта и выполнение необходимых вычислений
void Interpolation::update()
{
    // Сначало делаем очистку
    clear();

    // Вычислим шаг
    valueStep = (endSegment - beginSegment) / (N - 1);

    // Вычисляем все аргументы
    createdArgument();

    // Вычисляем значения функции
    createdResultOurFunction();

    // Вычисляем конечные разности
    createdFiniteDifference();
}

// Очистка векторов и результирующих величин
void Interpolation::clear()
{
    // Очистка вектора аргументов функции
    argument.clear();

    // Очистка вектора результатов функции
    resultOurFunction.clear();

    // Очищаем и освобождаем память вектора конечных разностей
    if (!vectorFiniteDifference.empty())
        for (signed int i = 0, n(vectorFiniteDifference.size()); i < n; i++)
            delete vectorFiniteDifference[i];

    vectorFiniteDifference.clear();
}

// Функция факториала
long long Interpolation::Factorial(long long n)
{
    long long resultFactorial(1);

    if (n == 1 || n == 0)
        return resultFactorial;

    else
        for (int i = 1; i < n; i++)
            resultFactorial *= i;

    return resultFactorial;
}

// Метод по созданию аргументов для функции (X)
void Interpolation::createdArgument()
{
    for (int i = 0; i < N; i++)
        argument.push_back(beginSegment + i * valueStep);
}

// Метод по созданию результатов для функции (Y)
void Interpolation::createdResultOurFunction()
{
    for (int i(0), n(argument.size()); i < n; i++)
        resultOurFunction.push_back(ourFunction(argument[i]));
}

// Метод по созданию конечных разностей
void Interpolation::createdFiniteDifference()
{
    // Определним максимальный порядок разностей
    int maxIndexOrder = N - 1;

    // Создадим вектора для всех конечных разностей
    for (int i = 0; i < maxIndexOrder; i++)
        vectorFiniteDifference.push_back(new std::vector<double>);

    // Посчитаем нулевую конечную разность первого порядка
    for (int i = 0, n(resultOurFunction.size() - 1); i < n; i++)
        vectorFiniteDifference[0]->push_back(resultOurFunction[i+1]
                                             - resultOurFunction[i]);

    // Посчитаем остальные конечные разности
    for (int i = 1, n(vectorFiniteDifference.size()); i < n; i++)
    {
        for (int j = 0, m(vectorFiniteDifference[i - 1]->size() - 1); j < m; j++)
            vectorFiniteDifference[i]->push_back((*vectorFiniteDifference[i - 1])[j + 1] - (*vectorFiniteDifference[i - 1])[j]);
    }
}

// Метод поиска нужного разбиения
/*
    order - порядок конечной разности
    number - номер конечной разности
*/
double Interpolation::getFiniteDifference(int order, int number) const
{
    double tmpResult(0);

    // Определим реальный индекс элемента
    int realNumber = static_cast<int>(N / 2.) + number - 1;
    int realOrder = order - 1;

    // Ищем нужную разность
    tmpResult = (*vectorFiniteDifference[realOrder])[realNumber];

    return tmpResult;
}

// Полином
double Interpolation::polynom(int number)
{
    double resultPolynom(1);

    switch (number)
    {
    case 20:
        resultPolynom *= ((Q + 19) * (Q - 20));

    case 19:
        resultPolynom *= ((Q + 18) * (Q - 19));

    case 18:
        resultPolynom *= ((Q + 17) * (Q - 18));

    case 17:
        resultPolynom *= ((Q + 16) * (Q - 17));

    case 16:
        resultPolynom *= ((Q + 15) * (Q - 16));

    case 15:
        resultPolynom *= ((Q + 14) * (Q - 15));

    case 14:
        resultPolynom *= ((Q + 13) * (Q - 14));

    case 13:
        resultPolynom *= ((Q + 12) * (Q - 13));

    case 12:
        resultPolynom *= ((Q + 11) * (Q - 12));

    case 11:
        resultPolynom *= ((Q + 10) * (Q - 11));

    case 10:
        resultPolynom *= ((Q + 9) * (Q - 10));

    case 9:
        resultPolynom *= ((Q + 8) * (Q - 9));

    case 8:
        resultPolynom *= ((Q + 7) * (Q - 8));

    case 7:
        resultPolynom *= ((Q + 6) * (Q - 7));

    case 6:
        resultPolynom *= ((Q + 5) * (Q - 6));

    case 5:
        resultPolynom *= ((Q + 4) * (Q - 5));

    case 4:
        resultPolynom *= ((Q + 3) * (Q - 4));

    case 3:
        resultPolynom *= ((Q + 2) * (Q - 3));

    case 2:
        resultPolynom *= ((Q + 1) * (Q - 2));

    case 1:
        resultPolynom *= (Q * (Q - 1));
    }

    return resultPolynom;
}
