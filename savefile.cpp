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

/*!
 * \brief SaveFile::OkClicked Действие при нажатии на кнопку Ok.
 *
 * Вызывает сигнал FilePath, куда записывает строку - путь сохранения, полученную из области ввода.
 */
void SaveFile::OkClicked()
{
    emit FilePath(ui->lineEdit->text());
    close();
}
