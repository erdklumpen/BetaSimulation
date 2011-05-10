#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionECA50_triggered()
{
    ECA50 eca50(1, 1, 50);
    QGraphicsScene *scene = new QGraphicsScene;
    ui->graphicsView->setScene(scene);

    OneDimensionState *state = eca50.state();

    for(int i = 0; i < state->size(); ++i)
    {
        QPen pen(Qt::black);
        QBrush brush;

        if(state->atEigen(i))
            brush = QBrush(Qt::black);
        else
            brush = QBrush(Qt::white);

        scene->addRect(0 + 10*i, 0, 10, 10, pen, brush);
    }

    for(int j = 0; j < 50; ++j)
    {
        eca50.run(1);
        state = eca50.state();

        for(int i = 0; i < state->size(); ++i)
        {
            QPen pen(Qt::black);
            QBrush brush;

            if(state->atEigen(i))
                brush = QBrush(Qt::black);
            else
                brush = QBrush(Qt::white);

            scene->addRect(0 + 10*i, 10 + j*10, 10, 10, pen, brush);
        }
    }
}
