#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class Spline;
typedef double (*Function)(double);

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(Function ourFunction, QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_spinBoxValueN_editingFinished();

private:
    Ui::MainWindow *ui;

    // Указатель на логику сплайна
    Spline *spline;

    // Указатель на исходную функцию
    Function ourFunction;
};

#endif // MAINWINDOW_H
