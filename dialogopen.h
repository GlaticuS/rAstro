#ifndef DIALOGOPEN_H
#define DIALOGOPEN_H

#include <QDialog>

namespace Ui {
class DialogOpen;
}

/*!
 * \brief The DialogOpen class Реализует диалоговое окно открытия файла.
 */
class DialogOpen : public QDialog
{
    Q_OBJECT

public:
    explicit DialogOpen(QWidget *parent = 0);
    ~DialogOpen();

private:
    Ui::DialogOpen *ui;
signals:
    void FilePath(const QString &str);

private slots:
    void OkClicked();
};

#endif // DIALOGOPEN_H
