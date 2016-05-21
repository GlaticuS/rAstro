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

void DrawingArea::setPenColor(const QColor &newColor)
{
    myPenColor = newColor;
}

void DrawingArea::setPenWidth(int newWidth)
{
    myPenWidth = newWidth;
}

void DrawingArea::setTool(int tool)
{
    myTool = tool;
}

void DrawingArea::setImage(const QImage myImage)
{
    image = myImage;
}

void DrawingArea::mousePressEvent(QMouseEvent *event)
{
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
}

void DrawingArea::mouseMoveEvent(QMouseEvent *event)
{
    if((event->buttons() & Qt::LeftButton) && scribbling && (myTool == 1))
        drawLineTo(event->pos());
}

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

/*void DrawingArea::drawRectangle()
{
    QPainter painter(&image);
    painter.setPen(QPen(myPenColor, myPenWidth, Qt::SolidLine, Qt::RoundCap,
                        Qt::RoundJoin));

    painter.drawRect();
}*/
