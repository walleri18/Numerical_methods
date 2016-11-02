#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Spline.h"

MainWindow::MainWindow(Function ourFunction, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow), ourFunction(ourFunction)
{
    ui->setupUi(this);

    // Заполнение объекта сплайна
    spline = new Spline(ourFunction, -3, 3, ui->spinBoxValueN->value());

    // Первое построение
    on_spinBoxValueN_editingFinished();

    // Именование столбцов таблицы
    ui->tableWidget->setHorizontalHeaderLabels(QStringList() << tr("x_j") << tr("f(x_j)") << tr("F(x_j)") << tr("f(x_j) - F(x_j)"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

// Построение графика, таблицы
void MainWindow::on_spinBoxValueN_editingFinished()
{
    spline->setValueN(ui->spinBoxValueN->value());

    // Обновление интерполяции
    spline->update();

    // График
    ui->qcustomplot->clearGraphs();

    ui->qcustomplot->addGraph();// Исходная функция
    ui->qcustomplot->addGraph();// Интерполирующий полином
    ui->qcustomplot->addGraph();// Узлы интерполяции
    ui->qcustomplot->addGraph();// Надпись в легенде число узлов

    // Узлы
    QVector<double> x_i = QVector<double>::fromStdVector(spline->getX_i());
    QVector<double> y_i = QVector<double>::fromStdVector(spline->getY_i());

    ui->qcustomplot->graph(2)->setData(x_i, y_i);

    // Исходная функция
    QVector<double> X;
    QVector<double> Y;

    // Шаг построения
    double h = (3. - (-3.)) / 10000;

    for (int i = 0, maxI(10000 + 1); i < maxI; i++)
    {
        X.push_back(-3 + h * i);
        Y.push_back(ourFunction(X[i]));
    }

    ui->qcustomplot->graph(0)->setData(X, Y);

    // Задаём названия графикам
    ui->qcustomplot->graph(0)->setName(tr("Исходная функция"));
    ui->qcustomplot->graph(1)->setName(tr("Сплайн"));
    ui->qcustomplot->graph(2)->setName(tr("Узлы интерполирования"));
    ui->qcustomplot->graph(3)->setName(tr("Число узлов: %1").arg(ui->spinBoxValueN->value() + 1));

    // Стили графиков
    QPen *penOne = new QPen();
    QPen *penTwo = new QPen();

    // Цвет
    penOne->setColor(Qt::red);
    penTwo->setColor(Qt::blue);

    // Стиль линии
    penOne->setStyle(Qt::SolidLine);
    penTwo->setStyle(Qt::DashLine);

    ui->qcustomplot->graph(0)->setPen(*penOne);
    ui->qcustomplot->graph(1)->setPen(*penTwo);
    ui->qcustomplot->graph(2)->setLineStyle(QCPGraph::lsNone);
    ui->qcustomplot->graph(2)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 8));
    ui->qcustomplot->graph(3)->setLineStyle(QCPGraph::lsNone);

    ui->qcustomplot->legend->setVisible(true);

    // Интерполирующая функция
    QVector<double> YInterpol;

    for (int i = 0, maxI(10000 + 1); i < maxI; i++)
    {
        YInterpol.push_back(spline->Interpol(X[i]));
    }

    ui->qcustomplot->graph(1)->setData(X, YInterpol);

    ui->qcustomplot->xAxis->setRange(-3 - 0.2, 3 + 0.2);
    ui->qcustomplot->yAxis->setRange(-0.2, 1.05);

    ui->qcustomplot->replot();

    // Таблица
    ui->tableWidget->clearContents();

    QVector<double> x_j = QVector<double>::fromStdVector(spline->getX_j());
    QVector<double> y_jSourse = QVector<double>::fromStdVector(spline->getY_jSourse());
    QVector<double> y_jInterpol = QVector<double>::fromStdVector(spline->getY_jInterpol());

    for (int i = 0; i < 13; i++)
    {
        QTableWidgetItem *itemX_j = new QTableWidgetItem(tr("%1").arg(x_j[i]));
        QTableWidgetItem *itemY_jSourse = new QTableWidgetItem(tr("%1").arg(y_jSourse[i]));
        QTableWidgetItem *itemY_jInterpol = new QTableWidgetItem(tr("%1").arg(y_jInterpol[i]));
        QTableWidgetItem *itemDelta = new QTableWidgetItem(tr("%1").arg(y_jSourse[i] - y_jInterpol[i]));

        ui->tableWidget->setItem(i, 0, itemX_j);
        ui->tableWidget->setItem(i, 1, itemY_jSourse);
        ui->tableWidget->setItem(i, 2, itemY_jInterpol);
        ui->tableWidget->setItem(i, 3, itemDelta);
    }
}
