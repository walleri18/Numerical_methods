#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "SolutionApproximation.h"

MainWindow::MainWindow(Function ourFunction, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow), ourFunction(ourFunction)
{
    ui->setupUi(this);

    // Создание объекта интерполяции
    solutionApproximation = new SolutionApproximation(ourFunction,
                                         ui->doubleSpinBoxBeginSegment->value(),
                                         ui->doubleSpinBoxEndSegment->value(),
                                         ui->spinBoxValueN->value(),
                                         ui->spinBoxValueM->value(),
                                         ui->spinBoxValueC->value());
    // Первоначальное построение
    updateApproximat();

    // Задаём название столбцов таблицы с коэффициентами и невязками
    ui->tableWidget->setHorizontalHeaderLabels(QStringList() << tr("Коэффициенты полинома: %1").arg(QChar(945))
                                               << tr("Невязки: %1").arg(QChar(949)) << tr("S"));

    // Добавление пункта в контексное меню
    ui->customPlot->addAction(ui->actionGenerationNewPoints);
    ui->customPlot->addAction(ui->actionReset);
    ui->customPlot->addAction(ui->action_N_increment);
    ui->customPlot->addAction(ui->action_N_decrement);
    ui->customPlot->addAction(ui->action_M_increment);
    ui->customPlot->addAction(ui->action_M_decrement);
    ui->customPlot->addAction(ui->action_C_increment);
    ui->customPlot->addAction(ui->action_C_decrement);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// Очистка от старых данных и генерирование новых данных
void MainWindow::clearData()
{
    // Обновление функции аппроксимации
    solutionApproximation->update();

    // Очистка данных
    vectorArgumentGrafic.clear();
    vectorResultApproxinGrafic.clear();
    vectorArgumentOurFunctionGrafic.clear();
    vectorResultOurFunctionGrafic.clear();
    vectorResultApproxinFunctionGrafic.clear();

    ui->tableWidget->clearContents();
}

// Генерирование данных для построения графика
void MainWindow::createDataPlots()
{
    /*
        Будем строить график в интервале от beginSegmentPlots до endSegmentPlot
    */
    double beginSegment = ui->doubleSpinBoxBeginPlotsX->value();
    double endSegment = ui->doubleSpinBoxEndPlotsX->value();

    // Получаем узлы аппроксимации
    vectorArgumentGrafic = QVector<double>::fromStdVector(solutionApproximation->getVectorX_i());

    vectorResultApproxinGrafic = QVector<double>::fromStdVector(solutionApproximation->getVectorF_i());

    // Количество разбиений
    int countSplit = (std::fabs(beginSegment) + std::fabs(endSegment)) * 100;

    // Шаг построения
    double valueStep = (endSegment - beginSegment) / countSplit;

    // Текущий аргумент функции
    double tmpArgumentPlots(beginSegment);
    vectorArgumentOurFunctionGrafic.push_back(tmpArgumentPlots);
    vectorResultOurFunctionGrafic.push_back(ourFunction(tmpArgumentPlots));
    vectorResultApproxinFunctionGrafic.push_back(solutionApproximation->ApproximationPolynom(tmpArgumentPlots));

    // Заполняем данные для построения
    while (tmpArgumentPlots <= endSegment)
    {
        // Делаем шаг
        tmpArgumentPlots += valueStep;

        // Запоминаем X
        vectorArgumentOurFunctionGrafic.push_back(tmpArgumentPlots);

        // Запоминаем Y (для нашей функции)
        vectorResultOurFunctionGrafic.push_back(ourFunction(tmpArgumentPlots));

        // Запоминаем Y (для полинома аппроксимации)
        vectorResultApproxinFunctionGrafic.push_back(solutionApproximation->ApproximationPolynom(tmpArgumentPlots));
    }
}

// Генерирование данных для занесения в таблицу и занесение в таблицу
void MainWindow::createDateTable()
{
    /*
        Генерирование данных для занесения в таблицу
    */
    // Вектор коэффициентов аппроксимирующего полинома
    QVector<double> kPolynom = QVector<double>::fromStdVector(solutionApproximation->getPolynomialCoefficients());

    // Запишем формулу аппроксимирующего полинома
    QString formylaApproximate(tr("<span style=' color:#ff0000;'>Аппроксимирующий полином: </span><span style=' color:#00c100;'>"));

    for (int i = kPolynom.size() - 1; i >= 0; --i)
    {
        if (i > 1)

            if (kPolynom[i] < 0)
                formylaApproximate.push_back(tr("%1 * %2^%3 ").arg(kPolynom[i]).arg("x").arg(i));

            else if (kPolynom[i] == 0)
                continue;

            else
            {
                if (i == (kPolynom.size() - 1))
                    formylaApproximate.push_back(tr("%1 * %2^%3 ").arg(tr("%1").arg(kPolynom[i])).arg("x").arg(i));

                formylaApproximate.push_back(tr("%1 * %2^%3 ").arg(tr("%1%2").arg('+').arg(kPolynom[i])).arg("x").arg(i));
            }

        else if (i == 1)

            if (kPolynom[i] < 0)
                formylaApproximate.push_back(tr("%1 * %2 ").arg(kPolynom[i]).arg("x"));

            else if (kPolynom[i] == 0)
                continue;

            else
                formylaApproximate.push_back(tr("%1 * %2 ").arg(tr("%1%2").arg('+').arg(kPolynom[i])).arg("x"));

        else

            if (kPolynom[i] < 0)
                formylaApproximate.push_back(tr("%1").arg(kPolynom[i]));

            else if (kPolynom[i] == 0)
                continue;

            else
                formylaApproximate.push_back(tr("%1").arg(tr("%1%2").arg('+').arg(kPolynom[i])));
    }

    formylaApproximate.push_back(tr("</span>"));

    ui->labelApproximant->setText(formylaApproximate);

    // Вектор невязок
    QVector<double> residuals = QVector<double>::fromStdVector(solutionApproximation->getResiduals());

    // Устанавливаем количество строк в таблице
    ui->tableWidget->setRowCount(residuals.size());

    // Посчитаем величину (S)
    double S(0);

    for (int i = 1, m(ui->spinBoxValueM->value()); i < m; ++i)
    {
        double tmpOne = solutionApproximation->ApproximationPolynom(vectorArgumentGrafic[i]);
        double tmpTwo = vectorResultApproxinGrafic[i];

        S += ((tmpOne - tmpTwo) * (tmpOne - tmpTwo));
    }

    this->S = S;

    /*
        Заполнение таблицы
    */
    // Первый столбец
    for (int i = 0, n(kPolynom.size()); i < n; ++i)
    {
        QTableWidgetItem *item = new QTableWidgetItem(tr("%1[%2] = %3").arg(QChar(945)).arg(i).arg(kPolynom[i]));

        ui->tableWidget->setItem(i, 0, item);
    }

    // Второй столбец (невязки)
    for (int i = 0, n(residuals.size()); i < n; ++i)
    {
        QTableWidgetItem *item = new QTableWidgetItem(tr("%1[%2] = %3").arg(QChar(949)).arg(i).arg(residuals[i]));

        ui->tableWidget->setItem(i, 1, item);
    }

    // Третий столбец (S)
    QTableWidgetItem *item = new QTableWidgetItem(tr("S = %1").arg(S));

    ui->tableWidget->setItem(0, 2, item);
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
    textLabel->setText(tr("Задание №5. Аппроксимация алгебраическими полиномами. Вариант №16."));
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
    ui->customPlot->addGraph();

    // Передаём данные в графопостроитель
    ui->customPlot->graph(0)->setData(vectorArgumentOurFunctionGrafic, vectorResultOurFunctionGrafic);
    ui->customPlot->graph(1)->setData(vectorArgumentOurFunctionGrafic, vectorResultApproxinFunctionGrafic);
    ui->customPlot->graph(2)->setData(vectorArgumentGrafic, vectorResultApproxinGrafic);

    // Задаём названия графикам
    ui->customPlot->graph(0)->setName(tr("exp(-x) * cos(x)"));
    ui->customPlot->graph(1)->setName(tr("Аппроксимирующий полином"));
    ui->customPlot->graph(2)->setName(tr("Узлы аппроксимирования"));
    ui->customPlot->graph(3)->setName(tr("S = %1").arg(this->S));

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
    ui->customPlot->graph(2)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 6));
    ui->customPlot->graph(3)->setLineStyle(QCPGraph::lsNone);

    // Границы отрисовки графика
    ui->customPlot->xAxis->setRange(ui->doubleSpinBoxBeginPlotsX->value(), ui->doubleSpinBoxEndPlotsX->value());
    ui->customPlot->yAxis->setRange(ui->doubleSpinBoxBeginPlotsY->value(), ui->doubleSpinBoxEndPlotsY->value());

    // Название осей
    ui->customPlot->xAxis->setLabel("X - абсцисса");
    ui->customPlot->yAxis->setLabel("Y - ордината");

    // Шаг пометки на осях
    ui->customPlot->xAxis->setAutoTickStep(false);
    ui->customPlot->xAxis->setTickStep(0.2);
    ui->customPlot->yAxis->setAutoTickStep(false);
    ui->customPlot->yAxis->setTickStep(0.2);

    // Отображать "легенду"
    ui->customPlot->legend->setVisible(true);

    // Настройка зума и перемещения осей
    ui->customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);

    // Перерисовка
    ui->customPlot->repaint();
}

// Слот для обновления графика
void MainWindow::updateApproximat()
{
    // Обновление аппроксиманта
    solutionApproximation->setBeginSegment(ui->doubleSpinBoxBeginSegment->value());
    solutionApproximation->setEndSegment(ui->doubleSpinBoxEndSegment->value());
    solutionApproximation->setValueC(ui->spinBoxValueC->value());
    solutionApproximation->setValueM(ui->spinBoxValueM->value());
    solutionApproximation->setValueN(ui->spinBoxValueN->value());

    ui->spinBoxCurrentMaxN->setRange(1, ui->spinBoxValueM->value());
    ui->spinBoxCurrentMaxN->setValue(ui->spinBoxValueM->value());
    ui->spinBoxCurrentMaxM->setRange(1, ui->spinBoxValueM->value());
    ui->spinBoxCurrentMaxM->setValue(ui->spinBoxValueM->value());

    // Очистка и расчёт новых данных
    clearData();

    // Генерирование данных для графиков
    createDataPlots();

    // Генерирование и вставка данных для таблицы
    createDateTable();

    // Настройка и построение графиков
    settingAndPushDateGraf();

    // Изменение информационного табло
    ui->labelInfo->setText(tr("Функция exp(-x) * cos(x);"
                              "\nОтрезок аппроксимирования: [%1, %2];"
                              "\nКоличество узлов аппроксимации: %3;"
                              "\nПорядок аппроксимирующего полинома: %4;"
                              "\nЗначение величины C: %5")
                           .arg(ui->doubleSpinBoxBeginSegment->value())
                           .arg(ui->doubleSpinBoxEndSegment->value())
                           .arg(ui->spinBoxValueM->value() + 1)
                           .arg(ui->spinBoxValueN->value())
                           .arg(ui->spinBoxValueC->value()));

    // Исследование зависимости величины S(n)
    studyDependence();
}

// Слот исследования зависимости S(n)
void MainWindow::studyDependence()
{
    /*
        Генерация данных для исследования
    */
    // Установление нужной величины (m) для ислледования зависимости
    solutionApproximation->setValueM(ui->spinBoxCurrentMaxM->value());

    // Вектор величины (x_i)
    QVector<double> x_i = QVector<double>::fromStdVector(solutionApproximation->getVectorX_i());

    // Вектор величины (F_i)
    QVector<double> f_i = QVector<double>::fromStdVector(solutionApproximation->getVectorF_i());

    // Вектор величин (S)
    QVector<double> vectorS(ui->spinBoxCurrentMaxN->value());

    // Вектор величины (n)
    QVector<double> vectorN(vectorS.size());

    // Вектор векоров невязок
    QVector< QVector<double> > reduse;

    for (size_t i = 1, maxI(vectorS.size() + 1); i < maxI; ++i)
    {
        // Передача нужного (n) в класса по расчёту Аппроксимического полинома
        solutionApproximation->setValueN(i);

        // Обновление аппроксимического полинома
        solutionApproximation->update(false);

        // Получение векторов невязок
        reduse.push_back(QVector<double>::fromStdVector(solutionApproximation->getResiduals()));

        // Зануление (на всякий случай =) )
        vectorS[i - 1] = 0;

        // Заполнение вектора величины (n)
        vectorN[i - 1] = static_cast<double>(i);

        // Расчет текущей величины S
        for (size_t j = 0, maxJ(x_i.size()); j < maxJ; ++j)
        {
            double tmp = (solutionApproximation->ApproximationPolynom(x_i[j]) - f_i[j]);

            vectorS[i - 1] += (tmp * tmp);
        }
    }

    /*
        Подготовка данных к выводу и сам вывод
    */
    // Максимальные и минимальные значения S
    double minS(vectorS[0]);
    double maxS(vectorS[0]);

    for (size_t i = 1, maxI(vectorS.size()); i < maxI; ++i)
    {
        if (vectorS[i] < minS)
            minS = vectorS[i];

        else if (vectorS[i] > maxS)
            maxS = vectorS[i];
    }

    // Настройка и заполнение таблицы
    ui->tableWidgetS_n->clearContents();

    ui->tableWidgetS_n->setRowCount(reduse[reduse.size() - 1].size());
    ui->tableWidgetS_n->setColumnCount(vectorN.size() + 3);

    QStringList listHeaderLabels;
    listHeaderLabels << "n:" << "s:" << "Max & min:";

    // Заполнение заголовков невязок какого порядка
    for (int i = 0, maxI(reduse.size()); i < maxI; ++i)
    {
        listHeaderLabels.push_back(tr("%1(n = %2):").arg(QChar(949)).arg(i + 1));
    }

    ui->tableWidgetS_n->setHorizontalHeaderLabels(listHeaderLabels);

    QTableWidgetItem *itemSMin = new QTableWidgetItem(tr("%1").arg("<-min S"));
    QTableWidgetItem *itemSMax = new QTableWidgetItem(tr("%1").arg("<-max S"));

    itemSMin->setTextColor(Qt::red);
    itemSMax->setTextColor(Qt::red);

    // Заполнение таблицы значениями
    for (size_t i = 0, maxI(vectorN.size()); i < maxI; ++i)
    {
        QTableWidgetItem *itemN = new QTableWidgetItem(tr("%1").arg(vectorN[i]));

        ui->tableWidgetS_n->setItem(i, 0, itemN);

        QTableWidgetItem *itemS = new QTableWidgetItem(tr("%1").arg(vectorS[i]));

        ui->tableWidgetS_n->setItem(i, 1, itemS);

        if (i % 2 == 0)
        {
            itemN->setBackgroundColor(Qt::magenta);
            itemS->setBackgroundColor(Qt::cyan);

            itemN->setTextColor(Qt::black);
            itemS->setTextColor(Qt::black);
        }

        else
        {
            itemN->setBackgroundColor(Qt::darkMagenta);
            itemS->setBackgroundColor(Qt::darkCyan);

            itemN->setTextColor(Qt::white);
            itemS->setTextColor(Qt::white);
        }

        if (vectorS[i] == minS)
            ui->tableWidgetS_n->setItem(i, 2, itemSMin);

        else if (vectorS[i] == maxS)
            ui->tableWidgetS_n->setItem(i, 2, itemSMax);
    }

    for (size_t i = 0, maxI(reduse.size()); i < maxI; ++i)
    {
        for (size_t j = 0, maxJ(reduse[i].size()); j < maxJ; ++j)
        {
            QTableWidgetItem *itemReduse = new QTableWidgetItem(tr("%1").arg(reduse[i][j]));

            ui->tableWidgetS_n->setItem(j, i + 3, itemReduse);
        }
    }
}

// Вызов окна справки об Qt
void MainWindow::on_action_Qt_triggered()
{
    qApp->aboutQt();
}

// Сброс значений настроек
void MainWindow::on_actionReset_triggered()
{
    ui->doubleSpinBoxBeginSegment->setValue(0.);
    ui->doubleSpinBoxEndSegment->setValue(2.);

    ui->doubleSpinBoxBeginPlotsX->setValue(-0.4);
    ui->doubleSpinBoxEndPlotsX->setValue(2.);
    ui->doubleSpinBoxBeginPlotsY->setValue(-0.4);
    ui->doubleSpinBoxEndPlotsY->setValue(1.6);

    ui->spinBoxValueN->setValue(1);
    ui->spinBoxValueM->setValue(10);
    ui->spinBoxValueC->setValue(2);

    updateApproximat();
}

void MainWindow::on_actionGenerationNewPoints_triggered()
{
    updateApproximat();

    this->repaint();
}

void MainWindow::on_action_N_increment_triggered()
{
    ui->spinBoxValueN->setValue(ui->spinBoxValueN->value() + 1);
    updateApproximat();
}

void MainWindow::on_action_N_decrement_triggered()
{
    if (ui->spinBoxValueN->value() > 1)
    {
        ui->spinBoxValueN->setValue(ui->spinBoxValueN->value() - 1);
        updateApproximat();
    }
}

void MainWindow::on_action_M_increment_triggered()
{
    ui->spinBoxValueM->setValue(ui->spinBoxValueM->value() + 1);
    updateApproximat();
}

void MainWindow::on_action_M_decrement_triggered()
{
    if (ui->spinBoxValueM->value() > 2)
    {
        ui->spinBoxValueM->setValue(ui->spinBoxValueM->value() - 1);
        updateApproximat();
    }
}

void MainWindow::on_action_C_increment_triggered()
{
    ui->spinBoxValueC->setValue(ui->spinBoxValueC->value() + 1);
    updateApproximat();
}

void MainWindow::on_action_C_decrement_triggered()
{
    ui->spinBoxValueC->setValue(ui->spinBoxValueC->value() - 1);
    updateApproximat();
}
