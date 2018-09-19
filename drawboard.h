#ifndef DRAWBOARD_H
#define DRAWBOARD_H

#include <QWidget>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QPainter>
#include <QString>

class DrawBoard : public QWidget
{
    Q_OBJECT
public:
    explicit DrawBoard(QWidget *parent = 0);
    void setBackgroundPath(QString path);
    ~DrawBoard();

protected:
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);
    void resizeEvent(QResizeEvent *);
    void mouseReleaseEvent(QMouseEvent *);

private:
    QPen pen;
    enum {DRAW_START=0, DRAW_ING=1, DRAW_END=2};
    struct DrawLinePath{
        int startX;
        int startY;
        int endX;
        int endY;
    };
    int DRAW_STATUS = DRAW_END;
    QList<QPainterPath> paintPathList;
    QList<DrawLinePath> drawLinePathList;
    int startX, startY, endX, endY;
    QString backgroundPath;
    QColor color;
    QImage *image;
};

#endif // DRAWBOARD_H
