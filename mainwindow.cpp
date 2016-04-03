#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QColorDialog>

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

void MainWindow::on_actionSet_Color_triggered()
{
    QColor color;
    color = QColorDialog::getColor(Qt::white, this);
    ui->graphicsView->setPalette(color);
}
