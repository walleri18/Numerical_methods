#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qcustomplot.h"

/*
    Прототипы необходиые для сборки
*/
// Прототип интерполяции
class SolutionApproximation;

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

    // Слот для обновления графика
    void updateApproximat();

    // Слот исследования зависимости S(n)
    void studyDependence();

    // Вызов окна справки об Qt
    void on_action_Qt_triggered();

    // Сброс значений настроек
    void on_actionReset_triggered();

    // Генерирование новых точек
    void on_actionGenerationNewPoints_triggered();

// Данные
    void on_action_N_increment_triggered();

    void on_action_N_decrement_triggered();

    void on_action_M_increment_triggered();

    void on_action_M_decrement_triggered();

    void on_action_C_increment_triggered();

    void on_action_C_decrement_triggered();

private:

    // Графический интерфейс
    Ui::MainWindow *ui;

    // Указатель на нашу функцию
    Function ourFunction;

    // Указатель на объект интерполяции
    SolutionApproximation *solutionApproximation;

    // Вектор аргументов функции (для отображения узлов аппроксимирования)
    QVector<double> vectorArgumentGrafic;

    // Вектор значений аппроксимаций (для отображения узлов аппроксимации)
    QVector<double> vectorResultApproxinGrafic;

    // Вектор для отображения графика функций
    QVector<double> vectorArgumentOurFunctionGrafic;

    // Вектор значений функции (для отображения графика нашей функции)
    QVector<double> vectorResultOurFunctionGrafic;

    // Вектор значений полинома аппроксиманта (для отображения графика полинома аппроксиманта)
    QVector<double> vectorResultApproxinFunctionGrafic;

    // Величина S
    double S;

};

#endif // MAINWINDOW_H
