#include "mainwindow.h"
#include <QApplication>
#include <cmath>
#include <QDebug>

using namespace std;

// Прототип нашей функции
double ourFunction(double argument);

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    a.setStyle(QStyleFactory::create("Fusion"));

    MainWindow w(ourFunction);
    w.show();

    return a.exec();
}

// Реализация нашей функции
double ourFunction(double argument)
{
    double result(0);

    result = exp(-argument) * cos(argument);
//    result = pow(argument, 5) - pow(argument, 4) - argument * argument + argument - 1;

    return result;
}
