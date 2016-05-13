#include "savefile.h"
#include "ui_savefile.h"
#include <QPushButton>

SaveFile::SaveFile(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SaveFile)
{
    ui->setupUi(this);

    connect(ui->buttonBox->button(QDialogButtonBox::Ok), SIGNAL(clicked(bool)), this, SLOT(OkClicked()));
}

SaveFile::~SaveFile()
{
    delete ui;
}

void SaveFile::OkClicked()
{
    emit FilePath(ui->lineEdit->text());
    close();
}
