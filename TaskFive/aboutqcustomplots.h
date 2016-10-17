#ifndef ABOUTQCUSTOMPLOTS_H
#define ABOUTQCUSTOMPLOTS_H

#include <QDialog>

namespace Ui {
class AboutQCustomPlots;
}

class AboutQCustomPlots : public QDialog
{
    Q_OBJECT

public:
    explicit AboutQCustomPlots(QWidget *parent = 0);
    ~AboutQCustomPlots();

private:
    Ui::AboutQCustomPlots *ui;
};

#endif // ABOUTQCUSTOMPLOTS_H
