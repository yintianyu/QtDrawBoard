#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setCentralWidget(pstDrawBoardObject);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete pstDrawBoardObject;
}
