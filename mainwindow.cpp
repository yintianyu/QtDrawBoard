#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :QMainWindow(parent)
{
    setWindowTitle(tr("Draw Boatd "));
    pstDrawBoardObject = new DrawBoard(this);
    setCentralWidget(pstDrawBoardObject);

    fileMenu = menuBar()->addMenu(tr("File"));
    newAction=new QAction(/*QIcon("new.gif"),*/tr("New"),this);
    newAction->setShortcut(tr("Ctrl+N"));
    newAction->setStatusTip(tr("New Draw File"));
    openAction=new QAction(/*QIcon("open.gif"),*/tr("Open"),this);
    openAction->setShortcut(tr("Ctrl+O"));
    openAction->setStatusTip(tr("Open Draw File"));
    saveAction=new QAction(/*QIcon("save.gif"),*/tr("Save"),this);
    saveAction->setShortcut(tr("Ctrl+S"));
    saveAction->setStatusTip(tr("Save Current Draw"));
    exitAction=new QAction(tr("Exit"),this);
    exitAction->setShortcut(tr("Ctrl+X"));
    exitAction->setStatusTip(tr("Exit Draw Board"));
    fileMenu->addAction(newAction);
    fileMenu->addAction(openAction);
    fileMenu->addAction(saveAction);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);

    lineAction=new QAction(/*QIcon("line.gif"),*/tr("Line"),this);
    lineAction->setShortcut(tr("Ctrl+L"));
    lineAction->setStatusTip(tr("Draw Line"));
    ellipseAction=new QAction(/*QIcon("ellipse.gif"),*/tr("Ellipse"),this);
    ellipseAction->setShortcut(tr("Ctrl+E"));
    ellipseAction->setStatusTip(tr("Draw Ellipse"));
    rectangleAction=new QAction(/*QIcon("rectangle.gif"),*/tr("Rectangle"),this);
    rectangleAction->setShortcut(tr("Ctrl+R"));
    rectangleAction->setStatusTip(tr("Draw Rectangle"));
    drawMenu= menuBar()->addMenu(tr("Draw"));
    lineAction->setCheckable(true);
    ellipseAction->setCheckable(true);
    rectangleAction->setCheckable(true);

    blackAction=new QAction(tr("black"),this);
    blackAction->setStatusTip("balck");
    greenAction=new QAction(tr("green"),this);
    greenAction->setStatusTip("green");
    yellowAction=new QAction(tr("yellow"),this);
    yellowAction->setStatusTip("yello");
    colorMenu=this->menuBar()->addMenu(tr("color"));
    colorMenu->addAction(blackAction);
    colorMenu->addAction(greenAction);
    colorMenu->addAction(yellowAction);

    QActionGroup *group=new QActionGroup(this);
    group->addAction(lineAction);
    group->addAction(ellipseAction);
    group->addAction(rectangleAction);
    group->setExclusive (true);
    lineAction->setChecked(true);
    drawMenu->addAction(lineAction);
    drawMenu->addAction(ellipseAction);
    drawMenu->addAction(rectangleAction);

    drawToolBar=addToolBar(tr("Draw"));
    drawToolBar->addAction(newAction);
    drawToolBar->addAction(openAction);
    drawToolBar->addAction(saveAction);
    drawToolBar->addSeparator();
    drawToolBar->addAction(lineAction);
    drawToolBar->addAction(ellipseAction);
    drawToolBar->addAction(rectangleAction);

    statusBar()->show();

    connect(exitAction,SIGNAL(triggered()),this,SLOT(close()));
    connect(lineAction,SIGNAL(triggered()),this,SLOT(line()));
    connect(ellipseAction,SIGNAL(triggered()),this,SLOT(ellipse()));
    connect(rectangleAction,SIGNAL(triggered()),this,SLOT(rectangle()));
    connect(newAction,SIGNAL(triggered()),this,SLOT(newDrawing()));
    connect(openAction,SIGNAL(triggered()),this,SLOT(openDrawing()));
    connect(saveAction,SIGNAL(triggered()),this,SLOT(saveDrawing()));
    connect(blackAction,SIGNAL(triggered()),this,SLOT(black()));
    connect(greenAction,SIGNAL(triggered()),this,SLOT(green()));
    connect(yellowAction,SIGNAL(triggered()),this,SLOT(yellow()));
}

MainWindow::~MainWindow()
{
    delete pstDrawBoardObject;
}


void MainWindow::line(){
    pstDrawBoardObject->setDrawType(0);
}
void MainWindow::ellipse(){
    pstDrawBoardObject->setDrawType(1);
}
void MainWindow::rectangle(){
    pstDrawBoardObject->setDrawType(2);
}
void MainWindow::newDrawing()
{
    if(pstDrawBoardObject->getModifiedFlag()==true)
    { //File Modified
        switch(QMessageBox::question(this,tr("Save Tips"),
               tr("File modified, save?"),
               QMessageBox::Ok|
               QMessageBox::Cancel|
               QMessageBox::No,
               QMessageBox::Ok))
        {
        case QMessageBox::Ok: pstDrawBoardObject->saveDrawing(); break;
        case QMessageBox::Cancel: return;
        case QMessageBox::No: break;
        default: break;
        }
    }
        pstDrawBoardObject->newDrawing();
}
void MainWindow::openDrawing(){
    if(pstDrawBoardObject->getModifiedFlag()==true){ //File Modified
        switch(QMessageBox::question(this,tr("Save Tips"),
                                     tr("File modified, save?"),
                                     QMessageBox::Ok|QMessageBox::Cancel |
                                     QMessageBox::No, QMessageBox::Ok)){
        case QMessageBox::Ok: pstDrawBoardObject->saveDrawing(); break;
        case QMessageBox::Cancel: return;
        case QMessageBox::No: break;
        default: break;
        }
    }
    pstDrawBoardObject->openDrawing();
}
void MainWindow::saveDrawing(){
    pstDrawBoardObject->saveDrawing();
}
void MainWindow::closeEvent(QCloseEvent *event){
    if(pstDrawBoardObject->getModifiedFlag()==true){ //File Modified
        switch(QMessageBox::question(this,tr("Save Tips"),
                                     tr("File modified, save?"),
                                     QMessageBox::Ok|
                                     QMessageBox::Cancel |
                                     QMessageBox::No, QMessageBox::Ok)){
        case QMessageBox::Ok: pstDrawBoardObject->saveDrawing(); event->accept(); break;
        case QMessageBox::Cancel: event->ignore(); break;
        case QMessageBox::No: event->accept(); break;
        default: event->accept(); break;
        }
    }
}
void MainWindow::black(){
    pstDrawBoardObject->setcolorType(0);
    pstDrawBoardObject->update();
}
void MainWindow::green(){
    pstDrawBoardObject->setcolorType(1);
    pstDrawBoardObject->update();
}
void MainWindow::yellow(){
    pstDrawBoardObject->setcolorType(2);
    pstDrawBoardObject->update();
}
