#include "dialogopen.h"
#include "ui_dialogopen.h"
#include <QPushButton>

DialogOpen::DialogOpen(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogOpen)
{
    ui->setupUi(this);

    connect(ui->buttonBox->button(QDialogButtonBox::Ok), SIGNAL(clicked(bool)), this, SLOT(OkClicked()));
}

DialogOpen::~DialogOpen()
{
    delete ui;
}

void DialogOpen::OkClicked()
{
    emit FilePath(ui->lineEdit->text());
    close();
}
