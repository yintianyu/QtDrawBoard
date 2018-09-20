#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include "drawboard.h"
//extern class DrawBoard;


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected slots:
    void line();
    void ellipse();
    void rectangle();
    void newDrawing();
    void openDrawing();
    void saveDrawing();
    void closeEvent(QCloseEvent *);
    void black();
    void yellow();
    void green();


private:
    DrawBoard *pstDrawBoardObject;
    QMenu *fileMenu;
    QMenu *drawMenu;
    QMenu *colorMenu;
    QAction *newAction;
    QAction *openAction;
    QAction *saveAction;
    QAction *exitAction;
    QAction *lineAction;
    QAction *ellipseAction;
    QAction *rectangleAction;
    QToolBar *drawToolBar;
    QAction *blackAction;
    QAction *greenAction;
    QAction *yellowAction;
};

#endif // MAINWINDOW_H
