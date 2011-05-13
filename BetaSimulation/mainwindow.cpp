#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_alpha = 1;
    m_beta = 1;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionECA50_triggered()
{
    ECA eca(m_alpha, m_beta, 50, 50);
    QGraphicsScene *scene = new QGraphicsScene;
    ui->graphicsView->setScene(scene);

    OneDimensionState *state = eca.state();

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
        eca.run(1);
        state = eca.state();

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

void MainWindow::on_actionEinstellungen_triggered()
{
    AutomataSettings* settings = new AutomataSettings(this, m_alpha, m_beta);
    settings->exec();
    m_alpha = settings->alpha();
    m_beta = settings->beta();
}

void MainWindow::on_actionECA_triggered()
{
    int ecaNumber = QInputDialog::getInt(this, "ECA Nummer", "Bitte Nummer des ECA eingeben", 0, 0, 255);

    ECA eca(m_alpha, m_beta, 50, ecaNumber);
    QGraphicsScene *scene = new QGraphicsScene;
    ui->graphicsView->setScene(scene);

    OneDimensionState *state = eca.state();

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
        eca.run(1);
        state = eca.state();

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
