#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_densityData = new QVector<int>();
    m_activityData = new QVector<int>();

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
    int size = QInputDialog::getInt(this, "Automatengröße", "Bitte gewünschte Größe des Automaten eingeben", 1, 1, 1000);

    m_activityData->clear();
    m_densityData->clear();

    ECA eca(m_alpha, m_beta, size, ecaNumber);
    QGraphicsScene *scene = new QGraphicsScene;
    ui->graphicsView->setScene(scene);

    OneDimensionState *state = eca.state();

    drawOneDimensionState(state, 0, scene);

    for(int j = 0; j < 50; ++j)
    {
        eca.run(1);
        state = eca.state();

        drawOneDimensionState(state, j, scene);
        saveDensity(eca.density());
        saveActivity(eca.activity());
    }
}

void MainWindow::drawOneDimensionState(OneDimensionState *state, int line, QGraphicsScene *scene)
{
    for(int i = 0; i < state->size(); ++i)
    {
        QPen pen(Qt::black);
        QBrush brush;

        if(state->atEigen(i))
            brush = QBrush(Qt::black);
        else
            brush = QBrush(Qt::white);

        scene->addRect(0 + 10*i, 10 + line*10, 10, 10, pen, brush);
    }
}

void MainWindow::plotDensity()
{
    QwtPlotCurve *curve = new QwtPlotCurve();
    QwtArrayData *data = new QwtArrayData(m_densityData);

    curve->setData(data);

    QwtPlot *plot = newPlot();
}

void MainWindow::plotActivity()
{

}

QwtPlot* MainWindow::newPlot()
{
    QwtPlot *plot = new QwtPlot();

    QDockWidget *dock =  new QDockWidget();
    dock->setWidget(plot);
    this->addDockWidget(Qt::RightDockWidgetArea, dock);

    return plot;
}

void MainWindow::on_action1_Dichte_triggered()
{
    plotDensity();
}
