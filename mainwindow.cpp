#include "mainwindow.h"
#include "drawingarea.h"
#include "ui_mainwindow.h"
#include "ui_dialognew.h"
#include "dialognew.h"
#include "savefile.h"
#include "dialogopen.h"
#include "2dgraph.cpp"
#include <QtWidgets>
#include <QDialog>
#include <QColorDialog>
#include <QFileDialog>
#include <QPainter>
#include <QFile>
#include <QImageWriter>
#include <QScrollArea>
#include <QByteArray>

/*!
 * \brief MainWindow::MainWindow класс основного диалогового окна
 * \param parent
 */
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

QString openedFile;

/*!
 * \brief MainWindow::on_actionExit_triggered Действие при нажатии на Exit
 *
 * При нажатии на Exit выходим из программы.
 */
void MainWindow::on_actionExit_triggered()
{
    exit(0);
}

/*!
 * \brief MainWindow::on_actionClear_triggered Очистка полотна.
 *
 * При нажатии на Clear очищаем полотно.
 */
void MainWindow::on_actionClear_triggered()
{
    ui->widget->clearImage();
}

/*!
 * \brief MainWindow::on_actionSet_Color_triggered Выбрать цвет ручки.
 *
 * При нажатии открывается меню для выбора цвета ручки.
 */
void MainWindow::on_actionSet_Color_triggered()
{
    QColor color;
    color = QColorDialog::getColor(Qt::white, this);
    ui->widget->setPenColor(color);
}

/*!
 * \brief MainWindow::on_spinBoxLineWidth_valueChanged Изменение размера ручки.
 * \param arg1 Размер ручки.
 */
void MainWindow::on_spinBoxLineWidth_valueChanged(int arg1)
{
    ui->widget->setPenWidth(arg1);
}

/*!
 * \brief MainWindow::on_buttonPencil_clicked Клавиша для инструмента "Карандаш".
 * \param checked Нажатие клавиши.
 *
 * Если клавиша нажата, то назначаем номер инструмента 1.
 */
void MainWindow::on_buttonPencil_clicked(bool checked)
{
    if(checked)
        ui->widget->setTool(1);
    else
        ui->widget->setTool(0);
}

/*!
 * \brief MainWindow::on_buttonPaintBucket_clicked Клавиша для инструмента "Заливка".
 * \param checked Нажатие.
 *
 * Если клавиша нажата, то назначаем номер инструмента 4.
 */
void MainWindow::on_buttonPaintBucket_clicked(bool checked)
{
    if(checked)
        ui->widget->setTool(4);
    else
        ui->widget->setTool(0);
}

/*!
 * \brief MainWindow::on_actionOpen_triggered Открыть существующий файл.
 *
 * Вызывает диалоговое окно, куда нужно ввести абсолютный путь до файла. Файл может быть в
 * любом формате растровых изображений.
 */
void MainWindow::on_actionOpen_triggered()
{
    DialogOpen *wnd = new DialogOpen(this);
    wnd->show();

    connect(wnd, SIGNAL(FilePath(QString)), this, SLOT(OpenMyFile(QString)));
}

/*!
 * \brief MainWindow::OpenMyFile Загрузить изображение на полотно.
 * \param str Абсолютный путь к файлу.
 *
 * Загружает изображение на полотно для дальнейшего его редактирования.
 */
void MainWindow::OpenMyFile(const QString &str)
{
    QImage image;

    if(!image.load(str))
    {
        QMessageBox::information(this, "Error", "File not exist");
        ui->statusBar->showMessage("Error");
        return ;
    }

    NewImageSize(image.size());

    ui->widget->setImage(image);
    openedFile = str;

}

/*!
 * \brief MainWindow::on_actionSave_triggered Сохранить изображение.
 *
 * При нажатии на Save вызывает диалоговое окно, куда нужно ввести абсолютный путь к сохраняемому изображению
 * в любом формате растровых изображений.
 */
void MainWindow::on_actionSave_triggered()
{
    SaveFile *wnd = new SaveFile(this);
    wnd->show();

    connect(wnd, SIGNAL(FilePath(QString)), this, SLOT(SaveMyFile(QString)));
}

/*!
 * \brief MainWindow::SaveMyFile Сохранить изображение с полотна.
 * \param str Абсолютный путь к файлу.
 *
 * Сохраняет изображение в формате BMP.
 */
void MainWindow::SaveMyFile(const QString &str)
{
    QFile mFile(str);

    if(!mFile.open(QFile::WriteOnly))
    {
        QMessageBox::information(this, "Error", "Path not correct");
        ui->statusBar->showMessage("Error");
        return ;
    }
    openedFile = str;
    QImage image = ui->widget->myImage();
    QImageWriter writer(str);
    writer.setFormat("bmp");
    writer.setQuality(100);
    writer.write(image);
}

/*!
 * \brief MainWindow::on_buttonEraser_clicked Действие при нажатии на Ластик.
 * \param checked Нажатие.
 *
 * Если кнопка нажата, то задействован инструмент Ластик - Карандаш белого(стандартного) цвета.
 */
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

/*!
 * \brief MainWindow::on_actionNew_triggered Действие при нажатии на New
 *
 * Открывает диалоговое окно для создания нового полотна.
 */
void MainWindow::on_actionNew_triggered()
{
    DialogNew *wnd = new DialogNew(this);
    wnd->show();

    connect(wnd, SIGNAL(NewSize(QSize)), this, SLOT(NewImageSize(QSize)));
}

/*!
 * \brief MainWindow::NewImageSize Задать новый размер полотна.
 * \param size Новый размер.
 *
 * Подстраивает размер виджета под новый размер полотна.
 */
void MainWindow::NewImageSize(const QSize &size)
{
    ui->widget->setSize(size);
    ui->widget->setFixedSize(size);
}

/*!
 * \brief MainWindow::on_buttonRectangle_clicked Действие при нажатии на кнопку Прямоугольник.
 * \param checked Нажатие.
 *
 * Если клавиша нажата, то назначаем номер инструмента 2.
 */
void MainWindow::on_buttonRectangle_clicked(bool checked)
{
    if(checked)
        ui->widget->setTool(2);
    else
        ui->widget->setTool(0);
}

/*!
 * \brief MainWindow::on_buttonEllipse_clicked Действие при нажатии на кнопку Эллипс.
 * \param checked Нажатие.
 *
 * Если клавиша нажата, то назначаем номер инструмента 3.
 */
void MainWindow::on_buttonEllipse_clicked(bool checked)
{
    if(checked)
        ui->widget->setTool(3);
    else
        ui->widget->setTool(0);
}

/*!
 * \brief MainWindow::on_actionFlip_Horizontal_triggered Действие при нажатии на Flip Horizontal.
 *
 * При нажатии изображение отражается относительно горизонтальной оси.
 * (Функции предоставлены библиотекой 2D графики от Евтеевой А.)
 */
void MainWindow::on_actionFlip_Horizontal_triggered()
{
    QByteArray file;
    file = openedFile.toLatin1();
    myFlipHorizontal(file.data());

    QImage image;
    image.load(openedFile);

    NewImageSize(image.size());

    ui->widget->setImage(image);
    ui->widget->update();
}

/*!
 * \brief MainWindow::on_actionRotate_2_triggered Действие при нажатии на Rotate.
 *
 * При нажатии изображение поворачивается на 90 градусов против часовой стрелки.
 * (Функции предоставлены библиотекой 2D графики от Евтеевой А.)
 */
void MainWindow::on_actionRotate_2_triggered()
{
    QByteArray file;
    file = openedFile.toLatin1();
    myRotate(file.data());

    QImage image;
    image.load(openedFile);

    NewImageSize(image.size());

    ui->widget->setImage(image);
    ui->widget->update();
}

/*!
 * \brief MainWindow::on_actionFlip_Vertical_triggered Действие при нажатии на Flip Vertical.
 *
 * При нажатии изображение отражается относительно вертикальной оси.
 * (Функции предоставлены библиотекой 2D графики от Евтеевой А.)
 */
void MainWindow::on_actionFlip_Vertical_triggered()
{
    QByteArray file;
    file = openedFile.toLatin1();
    myFlipVertical(file.data());

    QImage image;
    image.load(openedFile);

    NewImageSize(image.size());

    ui->widget->setImage(image);
    ui->widget->update();
}

/*!
 * \brief MainWindow::on_actionFlip_Both_triggered Действие при нажатии Flip Both.
 *
 * При нажатии изображение отражается относительно обеих осей - вертикальной и горизонтальной.
 * (Функции предоставлены библиотекой 2D графики от Евтеевой А.)
 */
void MainWindow::on_actionFlip_Both_triggered()
{
    QByteArray file;
    file = openedFile.toLatin1();
    myFlipBoth(file.data());

    QImage image;
    image.load(openedFile);

    NewImageSize(image.size());

    ui->widget->setImage(image);
    ui->widget->update();
}

/*!
 * \brief MainWindow::on_actionBlur_triggered Действие при нажатии на Blur
 *
 * При нажатии изображение слегка размывается.
 * (Функции предоставлены библиотекой 2D графики от Евтеевой А.)
 */
void MainWindow::on_actionBlur_triggered()
{
    QByteArray file;
    file = openedFile.toLatin1();
    myBlurFilter(file.data());

    QImage image;
    image.load(openedFile);

    NewImageSize(image.size());

    ui->widget->setImage(image);
    ui->widget->update();
}

/*!
 * \brief MainWindow::on_actionSharpness_triggered Действие при нажатии Sharpness.
 *
 * При нажатии изображение делается более чётким.
 * (Функции предоставлены библиотекой 2D графики от Евтеевой А.)
 */
void MainWindow::on_actionSharpness_triggered()
{
    QByteArray file;
    file = openedFile.toLatin1();
    mySharpnessFilter(file.data());

    QImage image;
    image.load(openedFile);

    NewImageSize(image.size());

    ui->widget->setImage(image);
    ui->widget->update();
}

/*!
 * \brief MainWindow::on_actionBrightness_triggered Действие при нажатии на Brightness.
 *
 * При нажатии увеличивается яркость изображения.
 * (Функции предоставлены библиотекой 2D графики от Евтеевой А.)
 */
void MainWindow::on_actionBrightness_triggered()
{
    QByteArray file;
    file = openedFile.toLatin1();
    myBrightFilter(file.data());

    QImage image;
    image.load(openedFile);

    NewImageSize(image.size());

    ui->widget->setImage(image);
    ui->widget->update();
}

/*!
 * \brief MainWindow::on_actionDarkness_triggered Действие при нажатии на Darkness.
 *
 * При нажатии изображение становится темнее, уменьшается яркость.
 * (Функции предоставлены библиотекой 2D графики от Евтеевой А.)
 */
void MainWindow::on_actionDarkness_triggered()
{
    QByteArray file;
    file = openedFile.toLatin1();
    myDarkFilter(file.data());

    QImage image;
    image.load(openedFile);

    NewImageSize(image.size());

    ui->widget->setImage(image);
    ui->widget->update();
}

/*!
 * \brief MainWindow::on_doubleSpinBox_valueChanged Действие при изменении счётчика Zoom'а.
 * \param arg1 Увеличение в arg1 раз.
 *
 * Посредством счётчика можно увеличивать/уменьшать изображение.
 * (Функции предоставлены библиотекой 2D графики от Евтеевой А.)
 */
void MainWindow::on_doubleSpinBox_valueChanged(double arg1)
{
    QByteArray file;
    file = openedFile.toLatin1();
    myZoom(file.data(), arg1);

    QImage image;
    image.load(openedFile);

    NewImageSize(image.size());

    ui->widget->setImage(image);
    ui->widget->update();
}
