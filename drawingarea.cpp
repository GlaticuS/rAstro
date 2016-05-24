#include <QtWidgets>
#ifndef QT_NO_PRINTER
#endif

#include "drawingarea.h"
#include <iostream>

DrawingArea::DrawingArea(QWidget *parent) :
    QWidget(parent)
{
    modified = false;
    scribbling = false;
    myTool = 0;
    myPenWidth = 1;
    myPenColor = Qt::black;
    myImageSize = QSize(100, 100);
}

/*!
 * \brief DrawingArea::setPenColor Установить цвет для рисования.
 * \param newColor Новый цвет, выбираемый в специальном диалоговом окне.
 */
void DrawingArea::setPenColor(const QColor &newColor)
{
    myPenColor = newColor;
}

/*!
 * \brief DrawingArea::setPenWidth Установить толщину линий.
 * \param newWidth Новая ширина, устанавливаемая с помощью счётчика.
 */
void DrawingArea::setPenWidth(int newWidth)
{
    myPenWidth = newWidth;
}

/*!
 * \brief DrawingArea::setTool Установить номер инструмента для рисования.
 * \param tool Номер инструмента для рисования.
 */
void DrawingArea::setTool(int tool)
{
    myTool = tool;
}

/*!
 * \brief DrawingArea::setImage Установить полотно.
 * \param myImage Полотно.
 */
void DrawingArea::setImage(const QImage myImage)
{
    image = myImage;
}

/*!
 * \brief DrawingArea::mousePressEvent Действие при нажатии левой кнопки мыши.
 * \param event Элемент действия.
 *
 * Проверяет переменную myTool и по её номеру подбирает действие, которое следует совершить с изображением.
 * Объявляет переменную scribbling ==  true и задаёт некоторые переменные, впоследствие использующиеся функциями
 * инструментов.
 */
void DrawingArea::mousePressEvent(QMouseEvent *event)
{
    printf("tool %d\n", myTool);
    if(event->button() == Qt::LeftButton && (myTool == 1))
    {
        lastPoint = event->pos();
        scribbling = true;
    }
    else if(event->button() == Qt::LeftButton && (myTool == 2 || 3))
    {
        topLeft = event->pos();
        scribbling = true;
    }
    if(event->button() == Qt::LeftButton && (myTool == 4))
    {
        printf("painting?\n");
        lastPoint = event->pos();
        /*QColor clr;
        clr.fromRgb(image.pixel(lastPoint));
        fillArea(lastPoint, clr);*/
        scribbling = true;
    }
}

/*!
 * \brief DrawingArea::mouseMoveEvent Действие при движении мышки
 * \param event Элемент действия.
 *
 * Движение мышки нам необходимо при рисовании карандашом.
 */
void DrawingArea::mouseMoveEvent(QMouseEvent *event)
{
    if((event->buttons() & Qt::LeftButton) && scribbling && (myTool == 1))
        drawLineTo(event->pos());
}

/*!
 * \brief DrawingArea::mouseReleaseEvent Действие при отпускании левой кнопки мышки.
 * \param event Элемент действия
 *
 * Проверяет переменную myTool и по её номеру подбирает действие, которое следует совершить с изображением.
 * Задаёт функцию для обработки действия и после её совершения объявляет переменную scribbling = false.
 *
 */
void DrawingArea::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && scribbling && (myTool == 1))
    {
        drawLineTo(event->pos());
        scribbling = false;
    }
    else if(event->button() == Qt::LeftButton && scribbling && (myTool == 2 || 3))
    {
        bottomRight = event->pos();
        drawFigure(topLeft, bottomRight);
        scribbling = false;
    }
    if(event->button() == Qt::LeftButton && scribbling && (myTool == 4))
    {
        //lastPoint = event->pos();
        printf("painting!!!1\n");
        QColor clr;
        clr.fromRgb(image.pixel(lastPoint));
        fillArea(lastPoint, clr);

        scribbling = false;
    }
}

/*!
 * \brief DrawingArea::paintEvent Действие рисования.
 * \param event Элемент действия.
 */
void DrawingArea::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QRect dirtyRect = event->rect();
    painter.drawImage(dirtyRect, image, dirtyRect);
}

/*!
 * \brief DrawingArea::setSize Назначить новый размер полотна.
 * \param size Размер
 *
 * Определяет переменную myImageSize как size и изменяет размер полотна посредством функции resizeImage.
 */
void DrawingArea::setSize(const QSize &size)
{
    myImageSize = size;
    resizeImage(&image);
}

/*!
 * \brief DrawingArea::drawLineTo Провести линию карандаша.
 * \param endPoint Конечная точка рисования.
 *
 * Рисует линию от начальной точки до конечной, используя цвет и ширину линий, заданные пользователем.
 * Рисует попиксельно.
 */
void DrawingArea::drawLineTo(const QPoint &endPoint)
{
    QPainter painter(&image);

    painter.setPen(QPen(myPenColor, myPenWidth, Qt::SolidLine, Qt::RoundCap,
                        Qt::RoundJoin));
    painter.drawLine(lastPoint, endPoint);
    modified = true;

    int rad = (myPenWidth / 2) + 2;
    update(QRect(lastPoint, endPoint).normalized()
                                     .adjusted(-rad, -rad, +rad, +rad));
    lastPoint = endPoint;
}

/*!
 * \brief DrawingArea::drawFigure Нарисовать фигуру.
 * \param topLeft Координата верхнего левого угла.
 * \param bottomRight Координата нижнего правого угла.
 *
 * Рисует одну из двух фигур на выбор - Прямоугольник или Эллипс. Выбор зависит от значения переменной myTool.
 * Координаты верхнего левого и нижнего правого угла задают размеры прямоугольника. Для эллипса задается размер
 * прямоугольника, внутрь которого будет вписан эллипс.
 */
void DrawingArea::drawFigure(QPoint topLeft, QPoint bottomRight)
{
    QPainter painter(&image);
    painter.setPen(QPen(myPenColor, myPenWidth, Qt::SolidLine, Qt::RoundCap,
                        Qt::RoundJoin));

    QRect myRect(topLeft, bottomRight);

    if(myTool == 2)
        painter.drawRect(myRect);
    if(myTool == 3)
        painter.drawEllipse(myRect);

    update();
}

/*!
 * \brief DrawingArea::resizeImage Изменить размер полотна.
 * \param image Полотно.
 *
 * Изменяет размер полотна на новый, заданный в myImageSize.
 */
void DrawingArea::resizeImage(QImage *image)
{
    if (image->size() == myImageSize)
        return;

    QImage newImage(myImageSize, QImage::Format_RGB32);
    newImage.fill(qRgb(255, 255, 255));
    QPainter painter(&newImage);
    painter.drawImage(QPoint(0, 0), *image);
    *image = newImage;
    update();
}

/*!
 * \brief DrawingArea::clearImage Очистить полотно.
 *
 * Заливает всё полотно белым цветом.
 */
void DrawingArea::clearImage()
{
    image.fill(qRgb(255, 255, 255));
    modified = true;
    update();
}

/*!
 * \brief DrawingArea::fillImage Залить полотно.
 *
 * Заливает всё полотно пользовательским цветом.
 */
void DrawingArea::fillImage()
{
    image.fill(myPenColor);
    modified = true;
    update();
}

/*!
 * \brief DrawingArea::fillArea - Залить область.
 * \param point Точка начала заливки.
 * \param act Цвет области, которую нужно залить.
 *
 * Заливает область пользовательским цветом, ограниченную линией другого цвета.
 * Для заливки используется floodFill алгоритм, использующий очередь из точек и
 * продвигающийся по четырем направлениям.
 */
void DrawingArea::fillArea(const QPoint &point, QColor act)
{
    QPainter painter(&image);
             printf("painтттting!!!1\n");
    QPen myPen(myPenColor);
    myPen.setWidth(1);
    painter.setPen(myPen);

    QQueue<QPoint> pixels;
    pixels.enqueue(point);
    while(pixels.isEmpty() == 0)
    {
        QPoint newPoint = pixels.dequeue();
        QColor actual;
        actual.fromRgb(image.pixel(newPoint));
            if(actual == act)
            {
               painter.drawPoint(newPoint);
               update();

               QPoint left((newPoint.x()-1), newPoint.y());
               if(left.x() >0 && left.x() < image.width() && image.pixel(left) == act.rgb())
               {
                   pixels.enqueue(left);
                   painter.drawPoint(left);
                   update();
               }

               QPoint right((newPoint.x()+1), newPoint.y());
               if(right.x() > 0 && right.x() < image.width() && image.pixel(right) == act.rgb())
               {
                   pixels.enqueue(right);
                   painter.drawPoint(right);
                   update();
               }

               QPoint up((newPoint.x()), (newPoint.y()-1));
               if(up.y() > 0 && up.y() < image.height() && image.pixel(up) == act.rgb())
               {
                   pixels.enqueue(up);
                   painter.drawPoint(up);
                   update();
               }

               QPoint down((newPoint.x()), (newPoint.y()+1));
               if(down.y() > 0 && down.y() < image.height() && image.pixel(down) == act.rgb())
               {
                   pixels.enqueue(down);
                   painter.drawPoint(down);
                   update();
               }
            }
      }
}
