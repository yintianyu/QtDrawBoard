/*****************************************
 * Copyright: Fudan University
 * Author: Yin Tianyu
 * StudentID: 18212020046
 * Date: 2018-09-18
 * Description: Implement File of the main class Drawboard
 *****************************************/
#include "drawboard.h"
#include "mainwindow.h"

/*
 * Summary: Constructor of DrawBoard
 * Parameters:
 *      parent:
 * Return: Void
 */
DrawBoard::DrawBoard(QWidget *parent) : QWidget(parent)
{
    shapes.clear();
    beginDraw = false;
    colorType = 0;
    isModified = false;
    fileName = tr("");
    mousePosLabel = new QLabel;
    mousePosLabel->setText("");
    mousePosLabel->setFixedWidth(150);
    MainWindow *p = (MainWindow*)parent;
    p->statusBar()->addPermanentWidget(mousePosLabel);
    setMinimumSize(500, 400);
    setMouseTracking(true);
}

/*
 * Summary: The event of paint
 * Parameters:
 *      *event: the event pointer of paint
 * Return: Void
 */
void DrawBoard::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    QColor c;
    for(auto shape:shapes)
    {
        switch(colorType)
        {
        case 0:
            shape->setColor(Qt::black);
            c = Qt::black;
            break;
        case 1:
            shape->setColor(Qt::green);
            c = Qt::green;
            break;
        case 2:
            shape->setColor(Qt::red);
            c = Qt::red;
            break;
        }
        shape->draw(&p);
    }

    Shape *temp = nullptr;
    switch(drawType)
    {
    case 0:
        temp = new Line(p1, p2, c);
        break;
    case 1:
        temp = new Ellipse(p1, p2, c);
        break;
    case 2:
        temp = new Rectangle(p1, p2, c);
        break;
    }
    temp->draw(&p);
    delete temp;
}

void DrawBoard::setDrawType(int type)
{
    drawType = type;
}

void DrawBoard::setcolorType(int color)
{
    colorType = color;
}

void DrawBoard::mousePressEvent(QMouseEvent *event)
{
    p1 = event->pos();
    p2 = p1;
    beginDraw = true;
}

void DrawBoard::mouseReleaseEvent(QMouseEvent *event)
{
    p2 = event->pos();
    beginDraw = false;
    if(p1 == p2)
        return;
    Shape *shape = nullptr;
    switch(drawType)
    {
    case 0:
        shape = new Line(p1, p2);
        break;
    case 1:
        shape = new Ellipse(p1, p2);
        break;
    case 2:
        shape = new Rectangle(p1, p2);
        break;
    }
    shapes.append(shape);
    isModified = true;
    update();
}

void DrawBoard::mouseMoveEvent(QMouseEvent *event)
{
    mousePosLabel->setText("X:" + QString::number(event->x()) + QString::number(event->y()));
    if(false == beginDraw)
        return;
    p2 = event->pos();
    update();
}

bool DrawBoard::getModifiedFlag()
{
    return isModified;
}

/*
 * Summary: make a new draw
 * Parameters:
 *      void
 * Return: void
 */
void DrawBoard::newDrawing()
{
    for(auto shape:shapes)
    {
        printf("%d\n", shape->type);
        delete shape;
    }
    shapes.clear();
    beginDraw = false;
    isModified = false;
    fileName = tr("");
    parentWidget()->setWindowTitle(tr("Draw Board Untitled"));
    update();
}

/*
 * Summary: open a draw
 * Parameters:
 *      void
 * Return: void
 */
void DrawBoard::openDrawing()
{
    fileName = QFileDialog::getOpenFileName(this, tr("Open File Dialog"), QDir::currentPath(),\
                                            "Draw File(*.draw);;Images(*.png *.xpm *.jpg)");
    if(fileName == tr(""))
        return;

    for(auto shape:shapes)
        delete shape;
    shapes.clear();
    beginDraw = false;
    isModified = false;
    openFile(fileName);
    parentWidget()->setWindowTitle(tr("Draw Board ") + fileName);
    update();
}

/*
 * Summary: save a draw
 * Parameters:
 *      void
 * Return: void
 */
void DrawBoard::saveDrawing()
{
    if(fileName == tr(""))
    {
        fileName = QFileDialog::getSaveFileName(this, tr("Save File Dialog"), QDir::currentPath(),\
                                                "Draw File(*.draw);;Images(*.png *.xpm *.jpg)");
        if(fileName == tr(""))
            return;
    }
    saveFile(fileName);
    parentWidget()->setWindowTitle(tr("Draw Board ") + fileName);
    isModified = false;
}

void DrawBoard::saveFile(QString fileName)
{
    QFile file(fileName);
    if(file.open(QFile::WriteOnly | QFile::Truncate))
    {
        QTextStream out(&file);
        out << shapes.length()<<endl;
        for(auto shape:shapes)
            shape->save(out);
        file.close();
    }
}

void DrawBoard::openFile(QString fileName)
{
    QFile file(fileName);
    if(file.open(QFile::ReadOnly))
    {
        QTextStream in(&file);
        int nums;
        in >> nums;
        int type;
        Shape *currentShape;
        for(int i = 0;i < nums;i++)
        {
            in >> type;
            switch(type)
            {
            case 0:
                currentShape = Line::read(in);
                break;
            case 1:
                currentShape = Ellipse::read(in);
                break;
            case 2:
                currentShape = Rectangle::read(in);
            }
            shapes.append(currentShape);
        }
        file.close();
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
    for(auto shape:shapes)
        delete shape;
}












