#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSize>
#include <QString>
class DrawingArea;

namespace Ui {
class MainWindow;
class DrawingArea;
}


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionExit_triggered();

    void on_actionClear_triggered();

    void on_actionSet_Color_triggered();

    void on_spinBoxLineWidth_valueChanged(int arg1);

    void on_buttonPencil_clicked(bool checked);

    void on_buttonPaintBucket_clicked(bool checked);

    void on_actionOpen_triggered();

    void on_actionSave_triggered();

    void on_buttonEraser_clicked(bool checked);

    void on_actionNew_triggered();

    void NewImageSize(const QSize &size);
    void SaveMyFile(const QString &str);
    void OpenMyFile(const QString &str);

    void on_buttonRectangle_clicked(bool checked);

    void on_buttonEllipse_clicked(bool checked);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
