#include "mainwindow.h"
#include "drawingarea.h"
#include "ui_mainwindow.h"
#include <QColorDialog>
#include <QPainter>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionExit_triggered()
{
    exit(0);
}

void MainWindow::on_actionClear_triggered()
{
    DrawingArea area;
    area.clearImage();
}
