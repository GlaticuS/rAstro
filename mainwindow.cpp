#include "mainwindow.h"
#include "drawingarea.h"
#include "ui_mainwindow.h"
#include "ui_dialognew.h"
#include "dialognew.h"
#include <QtWidgets>
#include <QDialog>
#include <QColorDialog>
#include <QFileDialog>
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
    ui->widget->clearImage();
}

void MainWindow::on_actionSet_Color_triggered()
{
    QColor color;
    color = QColorDialog::getColor(Qt::white, this);
    ui->widget->setPenColor(color);
}

void MainWindow::on_spinBoxLineWidth_valueChanged(int arg1)
{
    ui->widget->setPenWidth(arg1);
}

void MainWindow::on_buttonPencil_clicked(bool checked)
{

}

void MainWindow::on_buttonPaintBucket_clicked(bool checked)
{
    if(checked)
    {
        ui->widget->fillImage();
    }
}

void MainWindow::on_actionOpen_triggered()
{
    QFileDialog::getOpenFileName(this);
}

void MainWindow::on_actionSave_triggered()
{
    QFileDialog::getSaveFileName(this);
}

void MainWindow::on_buttonEraser_clicked(bool checked)
{
    QColor color;
    if(checked)
    {

        color = Qt::white;
        ui->widget->setPenColor(color);
    }
    else
    {
        color = Qt::black;
        ui->widget->setPenColor(color);
    }
}

void MainWindow::on_actionNew_triggered()
{
    DialogNew *wnd = new DialogNew(this);
    wnd->show();

    connect(wnd, SIGNAL(NewSize(QSize)), this, SLOT(NewImageSize(QSize)));
}

void MainWindow::NewImageSize(const QSize &size)
{
    ui->widget->setSize(size);
    ui->widget->setFixedSize(size);
}
