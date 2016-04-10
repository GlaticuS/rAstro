#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
class DrawingArea;

namespace Ui {
class MainWindow;
class DrawingArea;
}


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionExit_triggered();



    void on_actionClear_triggered();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
