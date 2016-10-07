#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qcustomplot.h"

/*
    Прототипы необходиые для сборки
*/
// Прототип интерполяции
class Interpolation;

typedef double(*Function)(double);


namespace Ui {
class MainWindow;
}

// Класс главного окна
class MainWindow : public QMainWindow
{
    Q_OBJECT

// Функционал
public:
    explicit MainWindow(Function ourFunction, QWidget *parent = 0);
    ~MainWindow();

private:

    // Очистка от старых данных и генерирование новых данных
    void clearData();

    // Генерирование данных для построения графика
    void createDataPlots();

    // Генерирование данных для занесения в таблицу
    void createDateTable();

    // Настройка и занесение данных на графики
    void settingAndPushDateGraf();

private slots:

    // Слот для обновления величины "n" - количество узлов интерполирования
    void updateValueN(int N);

    // Слот для обновления начала отрезка
    void updateValueBeginSegment(double beginSegment);

    // Слот для обновления конца отрезка
    void updateValueEndSegment(double endSegment);

    // Слот для обновления графика
    void updateInterpolation();

    // Вызов окна справки об Qt
    void on_action_Qt_triggered();

    // Вызов окна справки об авторе
    void on_action_aboutMe_triggered();

    // Вызов окна справки об библиотеке построения
    void on_action_QCustomPlot_triggered();

// Данные
private:

    // Графический интерфейс
    Ui::MainWindow *ui;

    // Указатель на нашу функцию
    Function ourFunction;

    // Указатель на объект интерполяции
    Interpolation *solutionInterpol;

    // Вектор для отображения в таблице результатов x_j
    QVector<double> vectorArgumentTable;
    QVector<double> vectorResultInterpolTable;

    // Вектор аргументов функции (для отображения узлов интерполирования)
    QVector<double> vectorArgumentGrafic;

    // Вектор значений интерполяций (для отображения узлов интерполирования)
    QVector<double> vectorResultInterpolGrafic;

    // Вектор для отображения графика функций
    QVector<double> vectorArgumentOurFunctionGrafic;

    // Вектор значений функции (для отображения графика нашей функции)
    QVector<double> vectorResultOurFunctionGrafic;

    // Вектор значений полинома Бесселя (для отображения графика полинома Бесселя)
    QVector<double> vectorResultBesselFunctionGrafic;

};

#endif // MAINWINDOW_H
