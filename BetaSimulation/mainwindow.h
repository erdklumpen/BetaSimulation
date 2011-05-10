#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "eca50.h"
#include "onedimensionstate.h"
#include <QDebug>

#include <QGraphicsGridLayout>
#include <QGraphicsWidget>
#include <QGraphicsScene>
#include <QPen>
#include <QBrush>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

private slots:
    void on_actionECA50_triggered();
};

#endif // MAINWINDOW_H
