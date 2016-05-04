#include "dialognew.h"
#include "ui_dialognew.h"
#include <QPushButton>
#include <QSize>
#include <QPainter>
#include "drawingarea.h"
#include <QtWidgets>

DialogNew::DialogNew(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogNew)
{
    ui->setupUi(this);
    connect(ui->buttonBox->button(QDialogButtonBox::Ok), SIGNAL(clicked(bool)), this, SLOT(OkClicked()));

}

DialogNew::~DialogNew()
{
    delete ui;
}

void DialogNew::OkClicked()
{
    const QSize size(ui->spinBox->value(), ui->spinBox_2->value());


    DrawingArea area;
    area.setSize(size);

    close();
}

