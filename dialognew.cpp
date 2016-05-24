#include "dialognew.h"
#include "ui_dialognew.h"
#include <QPushButton>
#include <QSize>
#include <QPainter>
#include "drawingarea.h"
#include <QtWidgets>
#include "ui_mainwindow.h"

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

/*!
 * \brief DialogNew::OkClicked Действие при нажатии на клавишу Ok.
 * Запоминает размеры, установленные в полях Width и Height и отправляет на дальнейшую обработку с помощью NewSize.
 */
void DialogNew::OkClicked()
{
    const QSize size(ui->spinBox->value(), ui->spinBox_2->value());
    emit NewSize(size);

    close();
}

