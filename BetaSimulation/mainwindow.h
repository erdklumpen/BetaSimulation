#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "eca.h"
#include "onedimensionstate.h"
#include "automatasettings.h"
#include <QDebug>

#include <QGraphicsGridLayout>
#include <QGraphicsWidget>
#include <QGraphicsScene>
#include <QPen>
#include <QBrush>
#include <QInputDialog>

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

    double m_alpha;
    double m_beta;

private slots:
    void on_actionECA_triggered();
    void on_actionEinstellungen_triggered();
    void on_actionECA50_triggered();
};

#endif // MAINWINDOW_H
