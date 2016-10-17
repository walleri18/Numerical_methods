#include "aboutqcustomplots.h"
#include "ui_aboutqcustomplots.h"

AboutQCustomPlots::AboutQCustomPlots(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutQCustomPlots)
{
    ui->setupUi(this);
}

AboutQCustomPlots::~AboutQCustomPlots()
{
    delete ui;
}
