/*****************************************
 * Copyright: Fudan University
 * Author: Yin Tianyu
 * StudentID: 18212020046
 * Date: 2018-09-18
 * Description: Implement File of the main class Drawboard
 *****************************************/
#include "drawboard.h"

/*
 * Summary: Constructor of DrawBoard
 * Parameters:
 *      parent:
 * Return: Void
 */
DrawBoard::DrawBoard(QWidget *parent) : QWidget(parent)
{
    backgroundPath = "-1";
    setAttribute(Qt::WA_StaticContents); // Automatically Resize
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);
    image = new QImage(this->width(), this->height(), QImage::Format_Indexed8);
    image->fill(qRgba(0, 0, 0, 0));
    color = Qt::black;
    pen.setWidth(10);
    pen.setCapStyle(Qt::RoundCap);
    pen.setJoinStyle(Qt::RoundJoin);
    pen.setStyle(Qt::SolidLine);
}

/*
 * Summary: The event of mouse's release event
 * Parameters:
 *      *event: the pointer of release event
 * Return: Void
 */
void DrawBoard::mouseReleaseEvent(QMouseEvent *event)
{
    repaint();
    DRAW_STATUS = DRAW_END;
    update();
}

/*
 * Summary: The event of resize the window
 * Parameters:
 *      *event: the pointer of release event
 * Return: Void
 */
void DrawBoard::resizeEvent(QResizeEvent *event)
{
    update();
}

/*
 * Summary: set Background's path
 * Parameters:
 *      path: QString, path of the background
 * Return: Void
 */
void DrawBoard::setBackgroundPath(QString path)
{
    this->backgroundPath = path;
    image->load(path);
    update();
}

/*
 * Summary: The event of paint
 * Parameters:
 *      *event: the pointer of paint event
 * Return: Void
 */
void DrawBoard::paintEvent(QPaintEvent *event)
{
    QPainter painter(this); // generate an object of painter
    painter.setPen(pen);
    painter.drawImage(rect(), *image);
    switch(DRAW_STATUS)
    {
    case DRAW_START:
        break;
    case DRAW_ING:
    case DRAW_END:
        for(int i = 0;i < drawLinePathList.size(); i++)
        {
            DrawLinePath drawlinePath = drawLinePathList.at(i);
            painter.drawLine(drawlinePath.startX, drawlinePath.startY, drawlinePath.endX, drawlinePath.endY);
        }
        break;
    }
}

/*
 * Summary: The event of mouse move
 * Parameters:
 *      *event: the pointer of mouse move event
 * Return: Void
 */
void DrawBoard::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons() & Qt::LeftButton)
    {
        endX = event->x();
        endY = event->y();
        DRAW_STATUS = DRAW_ING;
        DrawLinePath drawlinePath{startX, startY, endX, endY};
        drawLinePathList.push_back(drawlinePath);

        if(((endX - startX) > 1) || ((endY - startY) > 1))
        {
            repaint();
        }
        else
        {
            update();
        }
        startX = endX;
        startY = endY;
    }
    else if(event->buttons() & Qt::RightButton)
    {

    }
}




/*
 * Summary: The event of mouse press
 * Parameters:
 *      *event: the pointer of mouse press event
 * Return: Void
 */
void DrawBoard::mousePressEvent(QMouseEvent *event)
{
    DRAW_STATUS = DRAW_START;
    if(event->button() == Qt::LeftButton)
    {
        startX = event->x();
        startY = event->y();
    }
}

/*
 * Summary: Destructor of drawboard
 * Parameters:
 *      void
 * Return: None
 */
DrawBoard::~DrawBoard()
{

}












