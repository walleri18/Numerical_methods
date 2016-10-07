#include "mainwindow.h"
#include <QApplication>
#include <cmath>
#include <iostream>

// Прототип нашей функции
double ourFunction(double argument);

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w(ourFunction);
    w.show();

    return a.exec();
}

// Реализация нашей функции
double ourFunction(double argument)
{
    double result(0);

    result = 1 / (argument * argument);

    return result;
}
