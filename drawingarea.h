#ifndef DRAWINGAREA_H
#define DRAWINGAREA_H

#include <QWidget>
#include <QColor>
#include <QImage>
#include <QPoint>
#include <QSize>


/*Объявить переменные цвета и размера пера;
 * объявить функции, позволяющие рисовать на области;
 * объявить события при нажатии на кнопку мыши
 */
class DrawingArea : public QWidget
{
    Q_OBJECT

public:
    DrawingArea(QWidget *parent = 0);

    void setPenColor(const QColor &newColor);
    void setPenWidth(int newWidth);
    void setSize(const QSize &size);

    bool isModified() const { return modified; }
    QColor penColor() const { return myPenColor; }
    int penWidth() const { return myPenWidth; }
    QSize imageSize() const{ return myImageSize; }

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
    void resizeImage(QImage *image);

    bool modified;
    bool scribbling;
    int myPenWidth;
    QColor myPenColor;
    QImage image;
    QPoint lastPoint;
    QSize myImageSize;

};

#endif // DRAWINGAREA_H
