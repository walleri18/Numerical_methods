#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Interpolation.h"
#include "aboutme.h"
#include "aboutqcustomplots.h"

MainWindow::MainWindow(Function ourFunction, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow), ourFunction(ourFunction)
{
    ui->setupUi(this);

    // Создание объекта интерполяции
    solutionInterpol = new Interpolation(ourFunction,
                                         ui->doubleSpinBoxBeginSegment->value(),
                                         ui->doubleSpinBoxEndSegment->value(),
                                         ui->spinBoxValueN->value());
    // Первоначальное построение
    updateInterpolation();

    // Задаём название столбцов таблицы
    ui->tableWidget->setHorizontalHeaderLabels(QStringList()
                                               << tr("Аргумент (x_j)")
                                               << tr("Результат нашей функции (f(x_j))")
                                               << tr("Результат интерполяции (F(x_j))")
                                               << tr("Дельта (f(x_j) - F(x_j))"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

// Очистка от старых данных и генерирование новых данных
void MainWindow::clearData()
{
    // Обновление функции интерполяции
    solutionInterpol->update();

    // Очистка данных
    vectorArgumentTable.clear();
    vectorResultInterpolTable.clear();
    vectorArgumentGrafic.clear();
    vectorResultInterpolGrafic.clear();
    vectorArgumentOurFunctionGrafic.clear();
    vectorResultOurFunctionGrafic.clear();
    vectorResultBesselFunctionGrafic.clear();

    ui->tableWidget->clearContents();
}

// Генерирование данных для построения графика
void MainWindow::createDataPlots()
{
    /*
        Будем строить график в интервале от -1 до 1
    */
    double beginSegment = ui->doubleSpinBoxBeginPlotsX->value();
    double endSegment = ui->doubleSpinBoxEndPlotsX->value();

    // Получаем узлы интерполяции
    vectorArgumentGrafic = QVector<double>::fromStdVector(solutionInterpol->getArgument());

    vectorResultInterpolGrafic = QVector<double>::fromStdVector(solutionInterpol->getResultOurFunction());

    // Количество разбиений
    int countSplit = (std::fabs(beginSegment) + std::fabs(endSegment)) * 100;

    // Шаг построения
    double valueStep = (endSegment - beginSegment) / countSplit;

    // Текущий аргумент функции
    double tmpArgumentPlots(beginSegment);
    vectorArgumentOurFunctionGrafic.push_back(tmpArgumentPlots);
    vectorResultOurFunctionGrafic.push_back(ourFunction(tmpArgumentPlots));
    vectorResultBesselFunctionGrafic.push_back(solutionInterpol->interpolantBesselFunction(tmpArgumentPlots));

    // Заполняем данные для построения
    while (tmpArgumentPlots <= endSegment)
    {
        // Делаем шаг
        tmpArgumentPlots += valueStep;

        // Запоминаем X
        vectorArgumentOurFunctionGrafic.push_back(tmpArgumentPlots);

        // Запоминаем Y (для нашей функции)
        vectorResultOurFunctionGrafic.push_back(ourFunction(tmpArgumentPlots));

        // Запоминаем Y (для полинома Бесселя)
        vectorResultBesselFunctionGrafic.push_back(solutionInterpol->interpolantBesselFunction(tmpArgumentPlots));
    }
}

// Генерирование данных для занесения в таблицу и занесение в таблицу
void MainWindow::createDateTable()
{
    /*
        Генерирование данных для занесения в таблицу
    */
    // Начало и конец отрезка
    const double begin = 0.1;
    const double end = 1.2;

    // Временная переменная аргумента
    double X(begin);

    // Шаг разбиения
    double countStep = 0.05;

    // Для первого стобца (x_j)
    while (X <= (end + countStep))
    {
        vectorArgumentTable.push_back(X);

        X += countStep;
    }

    // Выделение определённого количества строк
    ui->tableWidget->setRowCount(vectorArgumentTable.size());

    // Для третьего столбца (F(x_j))
    for (int i = 0, n(vectorArgumentTable.size()); i < n; ++i)
    {
        vectorResultInterpolTable.push_back(solutionInterpol->interpolantBesselFunction(vectorArgumentTable[i]));
    }

    /*
        Заполнение таблицы
    */
    // Первый столбец (x_j)
    for (int i = 0, n(vectorArgumentTable.size()); i < n; i++)
    {
        QTableWidgetItem *item = new QTableWidgetItem(tr("%1").arg(vectorArgumentTable[i]));

        ui->tableWidget->setItem(i, 0, item);
    }

    // Второй столбец
    for (int i = 0, n(vectorArgumentTable.size()); i < n; i++)
    {
        QTableWidgetItem *item = new QTableWidgetItem(tr("%1").arg(this->ourFunction(vectorArgumentTable[i])));

        ui->tableWidget->setItem(i, 1, item);
    }

    // Третий столбец (F(x_j))
    for (int i = 0, n(vectorResultInterpolTable.size()); i < n; i++)
    {
        QTableWidgetItem *item = new QTableWidgetItem(tr("%1").arg(vectorResultInterpolTable[i]));

        ui->tableWidget->setItem(i, 2, item);
    }

    // Четвёртый столбец (f(x_j)-F(x_j))
    for (int i = 0, n(vectorArgumentTable.size()); i < n; i++)
    {
        QTableWidgetItem *item = new QTableWidgetItem(tr("%1").arg(this->ourFunction(vectorArgumentTable[i]) - vectorResultInterpolTable[i]));

        ui->tableWidget->setItem(i, 3, item);
    }
}

// Настройка и занесение данных на графики
void MainWindow::settingAndPushDateGraf()
{
    // Текст на графике
    QCPItemText *textLabel = new QCPItemText(ui->customPlot);
    ui->customPlot->addItem(textLabel);
    textLabel->setPositionAlignment(Qt::AlignTop|Qt::AlignHCenter);
    textLabel->position->setType(QCPItemPosition::ptAxisRectRatio);
    textLabel->position->setCoords(0.5, 0);
    textLabel->setText(tr("Задание №4. Интерполяция по формуле Бесселя"));
    textLabel->setFont(QFont(font().family(), 10));
    textLabel->setPen(QPen(Qt::black));

    /*
        Предоставляем данные библиотеке
    */
    // Предворительная очистка виджета от предыдущих графиков
    ui->customPlot->clearGraphs();

    // Создаём графики
    ui->customPlot->addGraph();
    ui->customPlot->addGraph();
    ui->customPlot->addGraph();

    // Передаём данные в графопостроитель
    ui->customPlot->graph(0)->setData(vectorArgumentOurFunctionGrafic, vectorResultOurFunctionGrafic);
    ui->customPlot->graph(1)->setData(vectorArgumentOurFunctionGrafic, vectorResultBesselFunctionGrafic);
    ui->customPlot->graph(2)->setData(vectorArgumentGrafic, vectorResultInterpolGrafic);

    // Задаём названия графикам
    ui->customPlot->graph(0)->setName(tr("1 / x^2"));
    ui->customPlot->graph(1)->setName(tr("Интерполирующая функция Бесселя"));
    ui->customPlot->graph(2)->setName(tr("Узлы интерполирования"));

    // Стили графиков
    QPen *penOne = new QPen();
    QPen *penTwo = new QPen();

    // Цвет
    penOne->setColor(Qt::red);
    penTwo->setColor(Qt::blue);

    // Стиль линии
    penOne->setStyle(Qt::SolidLine);
    penTwo->setStyle(Qt::DashLine);

    ui->customPlot->graph(0)->setPen(*penOne);
    ui->customPlot->graph(1)->setPen(*penTwo);
    ui->customPlot->graph(2)->setLineStyle(QCPGraph::lsNone);
    ui->customPlot->graph(2)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 10));

    // Границы отрисовки графика
    ui->customPlot->xAxis->setRange(ui->doubleSpinBoxBeginPlotsX->value(), ui->doubleSpinBoxEndPlotsX->value());
    ui->customPlot->yAxis->setRange(ui->doubleSpinBoxBeginPlotsY->value(), ui->doubleSpinBoxEndPlotsY->value());

    // Название осей
    ui->customPlot->xAxis->setLabel("X - абсцисса");
    ui->customPlot->yAxis->setLabel("Y - ордината");

    // Отображать "легенду"
    ui->customPlot->legend->setVisible(true);

    // Настройка зума и перемещения осей
    ui->customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);

    // Перерисовка
    ui->customPlot->repaint();
}

// Слот для обновления количества узлов интерполирования
void MainWindow::updateValueN(int N)
{
    solutionInterpol->setN(N);

    ui->statusBar->showMessage(tr("Значение величины N обновлено: %1").arg(N), 2000);

    updateInterpolation();
}

// Слот для обновления начала отрезка
void MainWindow::updateValueBeginSegment(double beginSegment)
{
    solutionInterpol->setBeginSegment(beginSegment);

    ui->statusBar->showMessage(tr("Значение начало отрезка обновлено: %1").arg(beginSegment), 2000);

    updateInterpolation();
}

// Слот для обновления конца отрезка
void MainWindow::updateValueEndSegment(double endSegment)
{
    solutionInterpol->setEndSegment(endSegment);

    ui->statusBar->showMessage(tr("Значение конца отрезка обновлено: %1").arg(endSegment), 2000);

    updateInterpolation();
}

// Слот для обновления графика
void MainWindow::updateInterpolation()
{
    // Очистка и расчёт новых данных
    this->clearData();

    // Генерирование данных для графиков
    createDataPlots();

    // Генерирование и вставка данных для таблицы
    createDateTable();

    // Настройка и построение графиков
    settingAndPushDateGraf();

    // Изменение информационного табло
    ui->labelInfo->setText(tr("Функция 1 / x^2; "
                              " Отрезок интерполирования: [%1, %2]; "
                              "Количество узлов интерполирования: %3")
                           .arg(ui->doubleSpinBoxBeginSegment->value())
                           .arg(ui->doubleSpinBoxEndSegment->value())
                           .arg(ui->spinBoxValueN->value()));
}

void MainWindow::on_action_Qt_triggered()
{
    qApp->aboutQt();
}

void MainWindow::on_action_aboutMe_triggered()
{
    AboutMe *aboutme = new AboutMe(this);

    aboutme->exec();

    delete aboutme;
}

void MainWindow::on_action_QCustomPlot_triggered()
{
    AboutQCustomPlots *aboutqcustomplots = new AboutQCustomPlots(this);

    aboutqcustomplots->exec();

    delete aboutqcustomplots;
}
