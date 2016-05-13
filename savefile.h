#ifndef SAVEFILE_H
#define SAVEFILE_H

#include <QDialog>
#include <QString>

namespace Ui {
class SaveFile;
}

class SaveFile : public QDialog
{
    Q_OBJECT

public:
    explicit SaveFile(QWidget *parent = 0);
    ~SaveFile();

private:
    Ui::SaveFile *ui;
signals:
    void FilePath(const QString &str);
private slots:
    void OkClicked();

};

#endif // SAVEFILE_H
