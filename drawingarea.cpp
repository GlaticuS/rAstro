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
    pencilOn = false;
    myPenWidth = 1;
    myPenColor = Qt::black;
    myImageSize = QSize(100, 100);
}

void DrawingArea::setPenColor(const QColor &newColor)
{
    myPenColor = newColor;
}

void DrawingArea::setPenWidth(int newWidth)
{
    myPenWidth = newWidth;
}

void DrawingArea::setPencilling(bool pencilling)
{
    pencilOn = pencilling;
}

void DrawingArea::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton && pencilOn)
    {
        lastPoint = event->pos();
        scribbling = true;
    }
}

void DrawingArea::mouseMoveEvent(QMouseEvent *event)
{
    if((event->buttons() & Qt::LeftButton) && scribbling)
        drawLineTo(event->pos());
}

void DrawingArea::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && scribbling)
    {
        drawLineTo(event->pos());
        scribbling = false;
    }
}

void DrawingArea::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QRect dirtyRect = event->rect();
    painter.drawImage(dirtyRect, image, dirtyRect);
}


void DrawingArea::setSize(const QSize &size)
{
    myImageSize = size;
    resizeImage(&image);
}

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

void DrawingArea::clearImage()
{
    image.fill(qRgb(255, 255, 255));
    modified = true;
    update();
}

void DrawingArea::fillImage()
{
    image.fill(myPenColor);
    modified = true;
    update();
}
