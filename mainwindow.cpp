#include "mainwindow.h"
#include "drawingarea.h"
#include "ui_mainwindow.h"
#include "ui_dialognew.h"
#include "dialognew.h"
#include "savefile.h"
#include "dialogopen.h"
#include <QtWidgets>
#include <QDialog>
#include <QColorDialog>
#include <QFileDialog>
#include <QPainter>
#include <QFile>
#include <QImageWriter>
#include <QScrollArea>

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
    if(checked)
        ui->widget->setTool(1);
    else
        ui->widget->setTool(0);
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
    DialogOpen *wnd = new DialogOpen(this);
    wnd->show();

    connect(wnd, SIGNAL(FilePath(QString)), this, SLOT(OpenMyFile(QString)));
}

void MainWindow::OpenMyFile(const QString &str)
{
    QFile mFile(str);

    if(!mFile.open(QFile::ReadWrite))
    {
        QMessageBox::information(this, "Error", "File not exist");
        ui->statusBar->showMessage("Error");
        return ;
    }

    QImage image;
    image.load(str, "jpg");

    NewImageSize(image.size());

    ui->widget->setImage(image);

}

void MainWindow::on_actionSave_triggered()
{
    SaveFile *wnd = new SaveFile(this);
    wnd->show();

    connect(wnd, SIGNAL(FilePath(QString)), this, SLOT(SaveMyFile(QString)));
}

void MainWindow::SaveMyFile(const QString &str)
{
    QFile mFile(str);

    if(!mFile.open(QFile::WriteOnly))
    {
        QMessageBox::information(this, "Error", "Path not correct");
        ui->statusBar->showMessage("Error");
        return ;
    }

    QImage image = ui->widget->myImage();
    QImageWriter writer(str);
    writer.setFormat("jpg");
    writer.setQuality(100);
    writer.write(image);
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

void MainWindow::on_buttonRectangle_clicked(bool checked)
{
    if(checked)
        ui->widget->setTool(2);
    else
        ui->widget->setTool(0);
}

void MainWindow::on_buttonEllipse_clicked(bool checked)
{
    if(checked)
        ui->widget->setTool(3);
    else
        ui->widget->setTool(0);
}
