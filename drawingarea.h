#ifndef DRAWINGAREA_H
#define DRAWINGAREA_H

#include <QWidget>
#include <QColor>
#include <QImage>
#include <QPoint>
#include <QSize>
#include <QRect>

class DrawingArea : public QWidget
{
    Q_OBJECT

public:
    DrawingArea(QWidget *parent = 0);

    void setPenColor(const QColor &newColor);
    void setPenWidth(int newWidth);
    void setSize(const QSize &size);
    void setTool(int tool);
    void setImage(const QImage myImage);


    bool isModified() const { return modified; }
    QColor penColor() const { return myPenColor; }
    int penWidth() const { return myPenWidth; }
    QSize imageSize() const{ return myImageSize; }
    QImage myImage() const{ return image; }

public slots:
    void clearImage();
    void fillImage();

protected:
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
   // void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;

private:
    void drawLineTo(const QPoint &endPoint);
    void drawFigure(QPoint topLeft, QPoint bottomRight);
    void resizeImage(QImage *image);

    bool modified;
    bool scribbling;
    int myTool;
    int myPenWidth;
    QPoint topLeft;
    QPoint bottomRight;
    QColor myPenColor;
    QImage image;
    QPoint lastPoint;
    QSize myImageSize;

};

#endif // DRAWINGAREA_H
