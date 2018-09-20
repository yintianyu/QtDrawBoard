#ifndef DRAWBOARD_H
#define DRAWBOARD_H

#include <QWidget>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QPainter>
#include <QString>
#include <QFileDialog>
#include <QLabel>
#include <QStatusBar>
#include "shape.h"
#include "line.h"
#include "ellipse.h"
#include "rectangle.h"

class DrawBoard : public QWidget
{
    Q_OBJECT
public:
    explicit DrawBoard(QWidget *parent = 0);
    ~DrawBoard();
    void paintEvent(QPaintEvent *);
    void setDrawType(int type);
    void setcolorType(int color);
    void newDrawing();
    void openDrawing();
    void saveDrawing();
    bool getModifiedFlag();

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);


private:
    QList<Shape*> shapes;
    QPoint p1, p2;
    int drawType;    // Current draw type, 0-line, 1-ellipse, 2-rectangle
    int colorType;
    bool beginDraw;
    QLabel *mousePosLabel;
    bool isModified;
    QString fileName;
//    void drawLine(QColor c, QPen &p, QPoint p1, QPoint p2);
    void saveFile(QString fileName);
    void openFile(QString fileName);
};

#endif // DRAWBOARD_H
