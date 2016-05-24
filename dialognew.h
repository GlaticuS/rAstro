#ifndef DIALOGNEW_H
#define DIALOGNEW_H

#include <QDialog>
#include <QImage>
#include <QSize>

namespace Ui {
class DialogNew;
}

/*!
 * \brief The DialogNew class Реализует диалоговое окно создания нового файла.
 */
class DialogNew : public QDialog
{
    Q_OBJECT

public:
    explicit DialogNew(QWidget *parent = 0);

    void setAreaWidth(int width);
    void setAreaHeight(int height);
    ~DialogNew();

private:
    Ui::DialogNew *ui;
signals:
    void NewSize(const QSize &size);

private slots:
    void OkClicked();

};

#endif // DIALOGNEW_H
