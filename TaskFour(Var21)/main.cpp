#include "mainwindow.h"
#include <QApplication>
#include <cmath>

double ourFunction(double x)
{
    double result;

    result = std::exp(-(x * x));

    return result;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w(ourFunction);
    w.show();

    return a.exec();
}
